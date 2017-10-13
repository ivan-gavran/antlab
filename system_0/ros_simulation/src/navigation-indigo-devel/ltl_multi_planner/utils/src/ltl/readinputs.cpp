/* License */
/*
Copyright (c) <2014>, <Indranil Saha>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "primitive.h"
#include "readinputs.h"
using namespace std;

string static_files_folder = "src/multiple_robots_stage/static_files_folder/";

void readPrimitives(prim_vec_t &primitives)
{
  ifstream ifp;

  string line;
  string str;
  int location, location1, location2, location3;
  position pos_tmp;
  int xmin, ymin, xmax, ymax;
  
  state q_i, q_f;
  position pos_f;
  string cost;
  pos_vec_t swath;
  position pos_min;
  position pos_max;
  string fileToOpen = static_files_folder + "ltl_primitives";
  ifp.open(fileToOpen.c_str());

  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      //cout << line << endl;
      location = line.find(":");

      if (line.substr(0, location) == "q_i")
      {
        istringstream (line.substr(location+2, 1)) >> q_i.velocity;
      }

      if (line.substr(0, location) == "q_f")
      {
	istringstream (line.substr(location+2, 1)) >> q_f.velocity;
      }

      if (line.substr(0, location) == "pos_f")
      {
        location1 = line.find('[');
        location2 = line.find(',');
        location3 = line.find(']');
        istringstream (line.substr(location1 + 1, location2 - location1 - 1)) >> pos_f.x;
        istringstream (line.substr(location2 + 2, location3 - location2 - 2)) >> pos_f.y;
      }

      if (line.substr(0, location) == "cost")
      {
        cost = line.substr(location + 1);
        //cost.erase(cost.size() - 1);
      }

      if (line.substr(0, location) == "swath")
      {
        str = line.substr(location+1);
        xmin = 10000; ymin = 10000; xmax = -10000; ymax = -10000;
        location = str.find(';');
        while (location != -1)
        {
          location1 = str.find('[');
          location2 = str.find(',');
          location3 = str.find(']');
          istringstream (str.substr(location1 + 1, location2 - location1 - 1)) >> pos_tmp.x;
          istringstream (str.substr(location2 + 2, location3 - location2 - 2)) >> pos_tmp.y;
          swath.push_back(pos_tmp);
          if (pos_tmp.x < xmin) 
            xmin = pos_tmp.x;
          if (pos_tmp.y < ymin) 
            ymin = pos_tmp.y;
          if (pos_tmp.x > xmax) 
            xmax = pos_tmp.x;
          if (pos_tmp.y > ymax) 
            ymax = pos_tmp.y;
          str = str.substr(location+1);
          location = str.find(';');
          //cout << pos_tmp.x << "  ---  " << pos_tmp.y << endl;
        }
        location1 = str.find('[');
        location2 = str.find(',');
        location3 = str.find(']');
        istringstream (str.substr(location1 + 1, location2 - location1 - 1)) >> pos_tmp.x;
        istringstream (str.substr(location2 + 2, location3 - location2 - 2)) >> pos_tmp.y;
        //cout << pos_tmp.x << "  ---  " << pos_tmp.y << endl;
        swath.push_back(pos_tmp);
        if (pos_tmp.x < xmin) 
          xmin = pos_tmp.x;
        if (pos_tmp.y < ymin) 
          ymin = pos_tmp.y;
        if (pos_tmp.x > xmax) 
          xmax = pos_tmp.x;
        if (pos_tmp.y > ymax) 
          ymax = pos_tmp.y;
        pos_min.x = xmin;
        pos_min.y = ymin;
        pos_max.x = xmax;
        pos_max.y = ymax;        
        cout<<"primitives "<<cost<<endl;
        
        Primitive prim(q_i, q_f, pos_f, cost, swath, pos_min, pos_max);
        primitives.push_back(prim); 
        swath.erase (swath.begin(), swath.end());
      }
    }
    
    ifp.close();
  }
}


void writePrimitives(prim_vec_t primitives)
{
  unsigned int count1, count2;
  state q_i, q_f;
  position pos_f;
  string cost;
  pos_vec_t swath;
  position pos_min;
  position pos_max;

  cout << endl << "PRIMITIVES:" << endl << endl;
  cout<<primitives.size()<<endl;
  for(count1 = 0; count1 < primitives.size(); count1++)
  {
    cout << "Primitive " << count1 << endl;

    q_i = primitives[count1].get_q_i();
    cout << "q_i: " << q_i.velocity << endl;

    q_f = primitives[count1].get_q_f();
    cout << "q_f: " << q_f.velocity << endl;

    pos_f = primitives[count1].get_pos_f();
    cout << "pos_f: " << pos_f.x << " " << pos_f.y << endl;

    cost = primitives[count1].get_cost();
    cout << "cost: " << cost << endl;

    swath = primitives[count1].get_swath();
    cout << "swath: ";
    for(count2 = 0; count2 < swath.size(); count2++)
    {
      cout << swath[count2].x << " " << swath[count2].y << " | ";
    }
    cout << endl;
    
    pos_min = primitives[count1].get_pos_min();
    cout << "pos_min: " << pos_min.x << " " << pos_min.y << endl;

    pos_max = primitives[count1].get_pos_max();
    cout << "pos_max: " << pos_max.x << " " << pos_max.y << endl;

    cout << endl;
  }
}


void readObstacles(pos_vec_t &obstacles)
{
  ifstream ifp;
  string line;
  int location; 
  position pos_tmp;
  string obstacleFile = static_files_folder + "ltl_obstacle.txt";
  cout<<obstacleFile<<endl;
  ifp.open(obstacleFile.c_str());
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      location = line.find(' ');
      istringstream (line.substr(0, location)) >> pos_tmp.x;
      istringstream (line.substr(location + 1)) >> pos_tmp.y;
      obstacles.push_back(pos_tmp);
    }
  }
  ifp.close();
}


void writeObstacles (pos_vec_t obstacles)
{
  position pos_tmp;
  unsigned int count;
  cout << endl << "OBSTACLES:" << endl << endl;
  for(count = 0; count < obstacles.size(); count++)
  {
    pos_tmp = obstacles[count];
    cout << pos_tmp.x << " " << pos_tmp.y << endl;
  }
  cout << endl;
}


void writeObstaclesToFile (pos_vec_t obstacles)
{
  ofstream ofp;
  position pos_tmp;
  unsigned int count;
  
  ofp.open("obstacle.txt");  
  for(count = 0; count < obstacles.size(); count++)
  {
    pos_tmp = obstacles[count];
    ofp << pos_tmp.x << " " << pos_tmp.y << endl;
  }
  ofp.close();
}


void readWorkspace(workspace_t &workspace)
{
  ifstream ifp;
  string line;
  int location;
  position pos_tmp;
  unsigned int count;

  ifp.open("src/multiple_robots_stage/static_files_folder/ltl_workspace.txt");
 
  if (ifp.is_open())
  {
    getline(ifp, line);
    cout<<"reading workspae: "<<line<<endl;
    istringstream (line) >> workspace.length_x;

    getline(ifp, line);
    cout<<"reading workspae: "<<line<<endl;
    istringstream (line) >> workspace.length_y;

    getline(ifp, line);
    cout<<"reading workspae: "<<line<<endl;
    istringstream (line) >> workspace.number_of_robots;
 
    workspace.pos_start = new position[workspace.number_of_robots];
    for (count = 0; count < workspace.number_of_robots; count++)
    {
      getline(ifp, line);
      cout<<"reading workspae: "<<line<<endl;
      location = line.find(' ');
      istringstream (line.substr(0, location)) >> pos_tmp.x;
      istringstream (line.substr(location + 1)) >> pos_tmp.y;
      workspace.pos_start[count] = pos_tmp; 
    }

    workspace.pos_end = new position[workspace.number_of_robots];
    for (count = 0; count < workspace.number_of_robots; count++)
    {
      getline(ifp, line);
      cout<<"reading workspae: "<<line<<endl;
      location = line.find(' ');
      istringstream (line.substr(0, location)) >> pos_tmp.x;
      istringstream (line.substr(location + 1)) >> pos_tmp.y;
      workspace.pos_end[count] = pos_tmp;
    } 
 
    getline(ifp, line);
    cout<<"reading workspae: "<<line<<endl;
    istringstream (line) >> workspace.number_of_points;

    getline(ifp, line);
    cout<<"reading workspae: "<<line<<endl;
    workspace.total_cost = line;
  }
 
 
  ifp.close();
}


void writeWorkspace(workspace_t workspace)
{
  unsigned int count;

  cout << endl << "WORKSPACE:" << endl << endl;
  cout << workspace.length_x << endl;
  cout << workspace.length_y << endl;
  cout << workspace.number_of_robots << endl;  
  for (count = 0; count < workspace.number_of_robots; count++)
  {
    cout << workspace.pos_start[count].x << " " << workspace.pos_start[count].y << endl;
    cout << workspace.pos_end[count].x << " " << workspace.pos_end[count].y << endl;
  }
  cout << workspace.number_of_points << endl;
  cout << workspace.total_cost << endl;
  cout << endl;
}


void readDimension(dimension_t &dimension, string filename)
{
  cout<<"        ======= readDimension"<<endl;

  ifstream ifp;
  string line;

  ifp.open(filename.c_str());
  if (ifp.is_open())
  {
    getline(ifp, line);
    istringstream (line) >> dimension.length_x;

    getline(ifp, line);
    istringstream (line) >> dimension.length_y;


    ifp.close();
  }
  else
  {
    cout << filename<<" file cannot be opened.." << endl;
    exit(0);
  }
}
//
//
//void writeDimension(dimension_t dimension)
//{
//  cout << endl << "DIMENSION:" << endl << endl;
//  cout << dimension.length_x << endl;
//  cout << dimension.length_y << endl;
//  cout << dimension.number_of_robots << endl;
//  cout << dimension.perc_obs << endl;
//  cout << endl;
//}



std::map<std::string, std::vector<position> > readPropositions(prop_vec_t & propositions)
{
  std::map<std::string, std::vector<position> > propMap;
  ifstream ifp;
  string line;
  string prop;
  int location;
  position pos_tmp;
  prop_t proposition;
  string propositionsFile = static_files_folder + "propositions_ltl_planner";

  ifp.open(propositionsFile.c_str());
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      cout<<line<<endl;
      location = line.find(' ');
      proposition.name = line.substr(0, location);
      line = line.substr(location + 1);
      location = line.find(' ');
      proposition.positions.clear();
      while (location != -1)
      {
        istringstream (line.substr(0, location)) >> pos_tmp.x;
        line = line.substr(location + 1);
        location = line.find(' ');
        if (location != -1)
        {
          istringstream (line.substr(0, location)) >> pos_tmp.x;
          line = line.substr(location + 1);
        }
        else
          istringstream (line.substr(location + 1)) >> pos_tmp.y;

        (proposition.positions).push_back(pos_tmp);
        propMap[proposition.name].push_back(pos_tmp);
      }
      propositions.push_back(proposition);
    }
  }
  ifp.close();
  return propMap;

}


void writePropositions(prop_vec_t propositions)
{
  prop_t proposition;
  position pos_tmp;
  unsigned int count, count1;

  cout << endl << "PROPOSITIONS:" << endl << endl;
  for(count = 0; count < propositions.size(); count++)
  {
    proposition = propositions[count];
    cout << proposition.name << " ";
    for (count1 = 0; count1 < proposition.positions.size(); count1++)
    {
      pos_tmp = proposition.positions[count1];
      cout << pos_tmp.x << " " << pos_tmp.y << endl;
    }
  }
  cout << endl;
}


void readRelatedPropositions(vector< vector<string> > & related_props)
{
	cout<<"reading related propositions"<<endl;
  ifstream ifp;
  string line;
  int location;
  vector<string> propositions;
  string relatedPropositionsFile = static_files_folder + "related_propositions_ltl_planner";
  ifp.open(relatedPropositionsFile.c_str());
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
    	cout<<line<<endl;
      location = line.find(' ');
      propositions.push_back(line.substr(0, location));
      while (location != -1)
      {
        line = line.substr(location + 1);
        location = line.find(' ');
        if (location != -1)
        {
          propositions.push_back(line.substr(0, location));
          line = line.substr(location + 1);
          location = line.find(' ');
        }
        else
          propositions.push_back(line.substr(location + 1));
      }
      related_props.push_back(propositions);
      propositions.clear();
    }
  }
  ifp.close();
}


void writeRelatedPropositions(vector< vector<string> > related_props)
{
  vector<string> props;
  unsigned int count, count1;
  cout << endl << "RELATED PROPOSITIONS:" << endl << endl;
  for(count = 0; count < related_props.size(); count++)
  {
    props = related_props[count];
    for (count1 = 0; count1 < props.size(); count1++)
    {
      cout << props[count1] << " ";
    }
    cout << endl;
  }
  cout << endl;
}


//void writeDimensionToFile(dimension_t dimension)
//{
//  ofstream ofp;
//
//  ofp.open("dimension.txt");
//  ofp << dimension.length_x << endl;
//  ofp << dimension.length_y << endl;
//  ofp << dimension.number_of_robots << endl;
//  ofp << dimension.perc_obs << endl;
//  ofp.close();
//}


void getPrimitiveCost(prim_vec_t primitives, prim_cost_t & prim_cost)
{
  unsigned int count1, count2;
  string str1, str2;
 
  prim_cost.max_cost = 0;
  prim_cost.min_cost = 100000;
  prim_cost.min2_cost = 100000;
  prim_cost.min_cost_diff = 100000;

  for (count1 = 0; count1 < primitives.size(); count1++)
  {
    str1 = primitives[count1].get_cost();
    if ( atof(str1.c_str()) > prim_cost.max_cost)
      prim_cost.max_cost = atof(str1.c_str());
    if (atof(str1.c_str()) < prim_cost.min_cost)
      prim_cost.min_cost = atof(str1.c_str());
    if ((atof(str1.c_str()) < prim_cost.min2_cost) && (atof(str1.c_str()) > prim_cost.min_cost))
      prim_cost.min2_cost = atof(str1.c_str());

    for (count2 = count1 + 1; count2 < primitives.size(); count2++)
    {
      str2 = primitives[count2].get_cost();
      if (fabs(atof(str1.c_str()) - atof(str2.c_str())) > 0.0001 && fabs(atof(str1.c_str()) - atof(str2.c_str())) < prim_cost.min_cost_diff)
        prim_cost.min_cost_diff = fabs(atof(str1.c_str()) - atof(str2.c_str()));
    }
  }
  prim_cost.min2_min_cost_diff = prim_cost.min2_cost - prim_cost.min_cost;
}


void writePrimitiveCost(prim_cost_t & prim_cost)
{
  cout << endl << "PRIMITIVE COST INFORMATION:" << endl << endl;
  cout << "prim_max_cost = " << prim_cost.max_cost << endl;
  cout << "prim_min_cost = " << prim_cost.min_cost << endl;
  cout << "prim_min2_cost = " << prim_cost.min2_cost << endl;
  cout << "prim_min_cost_diff = " << prim_cost.min_cost_diff << endl;
  cout << "prim_min2_min_cost_diff = " << prim_cost.min2_min_cost_diff << endl;
}
