#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;



void extractAssignmentInformation(map<string, vector<position> > propositionMap, string output_filename, string input_filename)
{
	  string line;
	  int location, location2;
	ifstream ifp;
	ofstream ofp;
	string str;
	ifp.open(input_filename.c_str());
	getline(ifp, line);
	ofp.open(output_filename.c_str());
	if (ifp.is_open())
	{
		while(getline(ifp, line))
		{
			
			location = line.find("assigned_r");
			if (location != -1)
				
			{
				int locationOfTrue = line.find("true");
				if (locationOfTrue == -1)
						continue;
				
				
				str = line.substr(location);
				location2 = str.find("_");
				string robotId = str.substr(0, location2);
				cout<<"++++++++++++"<<robotId<<endl;
				int numericRobotId = atoi(robotId);
				numericRobotId -= 1;
				string newRobotId = itoa(numericRobotId);
				ofp<<newRobotId<<" ";
				str = str.substr(location2+1);
				int locationOfBlank = str.find(" ");
				string propName = str.substr(0, locationOfBlank);
				cout<<"prop name is "<<propName<<endl;
				ofp<<propositionMap[propName][0].x<<" "<<propositionMap[propName][0].y<<endl;
			}
		}
	}
	ifp.close();
	ofp.close();

}

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

