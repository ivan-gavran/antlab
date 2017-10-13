#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <ltl_multi_planner/primitive.h>
#include <ltl_multi_planner/readinputs.h>


using namespace std;

/*
float extractTrajectoryCostInformation()
{
  ifstream ifp;
  int location;
  string line;
  string var;
  string value;
  string str;
  float val1, val2;
  float cost = 0.0;

  ifp.open("z3_output");
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      line = line.substr(2, strlen(line.c_str()) - 3);
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        if (var == "total_cost")
        {
          value = line.substr(location + 4);
          location = value.find(' ');
          str = value.substr(0, location - 1);
          val1 = atof(str.c_str());
          str = value.substr(location + 1);
          val2 = atof(str.c_str());
          cost = val1 / val2;
        }
      }
    }
  }
  ifp.close();
  return cost;
}
*/

float extractTrajectoryCostInformation(string output_filename)
{
  ifstream ifp;
  int location, location1;
  string line;
  string var;
  string value, value1;
  string str;
  float val1, val2;
  float cost = 0.0;

  //ifp.open("z3_output");
  ifp.open(output_filename.c_str());
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      line = line.substr(2, strlen(line.c_str()) - 3);
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        if (var == "total_cost")
        { 
          value1 = line.substr(location + 1);
          location1 = value1.find('(');
          if (location1 == -1)
          {
            cost = atof(value1.c_str());
            cout << "cost = " << cost << endl;
          }
          else
          {
            value = line.substr(location + 4);
            location = value.find(' ');
            str = value.substr(0, location - 1);
            val1 = atof(str.c_str());
            str = value.substr(location + 1);
            val2 = atof(str.c_str());
            cost = val1 / val2;
          }
        }
      }
    }
  }
  ifp.close();
  return cost;
}



void extractTrajectoryVelocityInformation(string filename, vector< vector<int> > & velocities)
{
  ifstream ifp;
  int location;
  string line;
  string var;
  string index;
  int value;
  int robot, time;

  cout << filename << endl;
  ifp.open(filename.c_str());
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        istringstream (line.substr(location + 1)) >> value;
        location = var.find("vel_i_");
        if (location != -1)
        {
          index = var.substr(location + 6);
          location = index.find('_');
          if (location != -1)
          {
            //cout << "line=" << line << "--" << endl; 
            //cout << "var=" << var << "--" << endl; 
            //cout << "value=" << value << endl;
            //cout << "index=" << index << "--" << endl;
            istringstream (index.substr(0, location)) >> robot;
            istringstream (index.substr(location + 1)) >> time;
            //cout << "robot=" << robot << endl;
            //cout << "time=" << time << endl;
            if (robot > velocities.size())
            {
              velocities.resize(robot);
            }
            velocities[robot - 1].push_back(value);
          }
          else
          {
            cout << "parsing error 3.." << endl;
            exit(0);
          }
        }
      }
      else
      {
        cout << "parsing error 1.." << endl;
        exit(0);
      }
    }
  }
  ifp.close();
}



void extractTrajectoryInformation(int index, vector<int> & x_arr, vector<int> & y_arr , vector<int> & prim_arr, string output_filename)
{
  ifstream ifp;
  string line;
  int location;
  string str;
  char strindex[10];
  string var;
  int valindex;
  int value;

  ifp.open(output_filename.c_str());
  getline(ifp, line);
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      line = line.substr(2, strlen(line.c_str()) - 4);
      location = line.find(' ');
      if (location != -1)
      {
        istringstream (line.substr(location + 1)) >> value;
        str = line.substr(0, location);
        sprintf(strindex, "_%d_", index);
        location = str.find(strindex);
        //location = str.find("_1_");
        var = str.substr(0, location);
        istringstream (str.substr(location + 3, strlen(str.c_str()) - strlen(var.c_str()) - 3)) >> valindex;
        if (var == "x")
        {
          x_arr.insert(x_arr.begin() + valindex - 1, value);
        }
        if (var == "y")
        {
          y_arr.insert(y_arr.begin() + valindex - 1, value);
        }
        if (var == "prim")
        {
          prim_arr.insert(prim_arr.begin() + valindex - 1, value);
        }
      }
    }
  }
  ifp.close();
}

map<int, vector<position> > extractAssignments(string assignmentFilename){
	ifstream ifp;
	ifp.open(assignmentFilename.c_str());
	cout<<"in extract assignment"<<endl;
	cout<<"reading: "<<assignmentFilename<<endl;
	int a, b, c;
	map<int, vector<position> > assignments;
	while (ifp>>a>>b>>c)
	{
		cout<<"reading "<<a<<" "<<b<<" "<<c<<endl;
		position p;
		p.x = b;
		p.y = c;
		assignments[a].push_back(p);

	}
	return assignments;
}

