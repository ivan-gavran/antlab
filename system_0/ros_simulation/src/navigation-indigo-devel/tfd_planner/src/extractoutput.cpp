#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>


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
  float f = -1.0;

  //ifp.open("z3_output");
  ifp.open(output_filename.c_str());
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      location = line.find("plan cost: ");
      if (location != -1)
      {
        str = line.substr( location + 11, -1);
        istringstream ss(str);

        if(!(ss >>f))
        {
        	cout<<"problem converting string to float"<<endl;
        }
        else
        {
        	cout<<"cost found: "<<f<<endl;
        }

      }
    }
  }
  ifp.close();
  cost = f;
  return cost;
}





template <typename T> string tostr(const T& t)
{
  ostringstream os;
  os << t;
  return os.str();
}


void extractTrajectoryInformation(int index, vector<int> & x_arr, vector<int> & y_arr , vector<int> & prim_arr, string output_filename)
{
  ifstream ifp;
  string line;
  int location, locationEnd, locationStart;
  int x, y;
  string str;
  char strindex[10];
  string var;
  int valindex;
  int value;
  ifp.open(output_filename.c_str());
  getline(ifp, line);
  bool foundSolutionStream = false;
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      location = line.find("move r"+tostr(index)+" location");
      //cout<<line<<endl;
      if (location == -1)
    	  continue;
      else
      {
    	  //to eliminate first location
    	  str = line.substr(location+16,-1);
    	  cout<<str<<endl;
    	  location = str.find("location_");
    	  str = str.substr(location+9, -1 );
    	  cout<<str<<endl;
    	  int endOfXCoord = str.find("_");
    	  string xCoord = str.substr(0,endOfXCoord);
    	  string yCoord = str.substr(endOfXCoord+1,-1);
    	  istringstream(xCoord) >> x;
    	  istringstream(yCoord) >> y;
    	  x_arr.push_back(x);
    	  y_arr.push_back(y);
    	  cout<<"locations found:"<<x<<" "<<y<<endl;

      }
//        istringstream (line.substr(location + 1)) >> value;
//        str = line.substr(0, location);
//        sprintf(strindex, "_%d_", index);
//        location = str.find(strindex);
//        //location = str.find("_1_");
//        var = str.substr(0, location);
//        istringstream (str.substr(location + 3, strlen(str.c_str()) - strlen(var.c_str()) - 3)) >> valindex;
//        if (var == "x")
//        {
//          x_arr.insert(x_arr.begin() + valindex - 1, value);
//        }
//        if (var == "y")
//        {
//          y_arr.insert(y_arr.begin() + valindex - 1, value);
//        }
//        if (var == "prim")
//        {
//          prim_arr.insert(prim_arr.begin() + valindex - 1, value);
//        }
      }
    }

  ifp.close();
}
