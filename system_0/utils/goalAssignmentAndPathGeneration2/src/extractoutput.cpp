#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;


float extractCostInformation()
{
  ifstream ifp;
  int location, location1;
  string line;
  string var;
  string value, value1;
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


void extractTrajectoryInformation(int index, vector<int> & x_arr, vector<int> & y_arr , vector<int> & prim_arr)
{
  ifstream ifp;
  string line;
  int location;
  string str;
  char strindex[10];
  string var;
  int valindex;
  int value;

  ifp.open("z3_output");
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


void extractAssignmentInformation(vector< vector<int> > & assignment)
{
  ifstream ifp;
  string line;
  int location;
  string str;
  string var;
  int value;
  int index1, index2;

  ifp.open("z3_output");
  getline(ifp, line);
  //cout << line << endl;
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      line = line.substr(2, strlen(line.c_str()) - 4);
      //cout << line << endl;
      location = line.find(' ');
      if (location != -1)
      {
        istringstream (line.substr(location + 1)) >> value;
        //cout << "value = " << value << endl;
        var = line.substr(0,1);
        //cout << "var = " << var << endl;
        if (var == "n")
        {
          str = line.substr(2, location);
          //cout << "str = " << str << endl;
          location = str.find('_');
          istringstream(str.substr(0, location)) >> index1;
          istringstream(str.substr(location + 1)) >> index2;
          //cout << "index1 = " << index1 << "   index2 = " << index2 << endl;
          assignment[index1-1][index2-1] = value;
        }
      }
    }
  }
  ifp.close();
}
