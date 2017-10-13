#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "primitive.h"
#include "readinputs.h"
#include "extractoutput.h"
#include "writeconstraints.h"
#include <json/writer.h>



#define MAX_LENGTH_TRAJ 30
#define MAX_LENGTH_PRIM 3
#define MAX_COST 1000.0


using namespace std;


bool findPosition(pos_vec_t posvec, position pos)
{
  unsigned int count;

  for (count = 0; count < posvec.size(); count++)
  {
    if (posvec[count].x == pos.x && posvec[count].y == pos.y)
    {
      return true;
    }
  }
  return false;
}


void createWorkspace(dimension_t dimension, pos_vec_t initposition, pos_vec_t finalposition, int iteration, float cost, workspace_t &workspace)
{
  unsigned int count;

  workspace.length_x = dimension.length_x;
  workspace.length_y = dimension.length_y;
  workspace.number_of_robots = initposition.size();
  workspace.pos_start.clear();
  workspace.pos_end.clear();
  for (count = 0; count < workspace.number_of_robots; count++)
  {
    workspace.pos_start.push_back(initposition[count]);
  }
  for (count = 0; count < finalposition.size(); count++)
  {
    workspace.pos_end.push_back(finalposition[count]);
  }
  workspace.number_of_points = iteration;
  ostringstream ss;
  ss << cost;
  string str(ss.str());
  workspace.total_cost = str;
}


void generateZ3File(prim_vec_t primitives, pos_vec_t obstacles, workspace_t workspace)
{
  ofstream ofp;
  ofp.open("constraints.smt2");

  declareVariables(ofp, workspace);
  ofp << endl;

  writeInitialLocationConstraints(ofp, workspace);
  ofp << endl;

  writeFinalDestinationCoverageConstraints(ofp, workspace);
  ofp << endl;

  writeObstacleConstraints(ofp, obstacles, workspace);
  ofp << endl;

  writeTransitionConstraints(ofp, primitives, obstacles, workspace);
  ofp << endl;

  writeCostConstraint(ofp, workspace);
  ofp << endl;

  ofp << "(check-sat)" << endl;
  //ofp << "(get-model)" << endl;
  ofp << endl;

  writeOutputConstraints(ofp, workspace);
  ofp << endl;

  ofp.close();
}


void generateTrajectories(prim_vec_t primitives, dimension_t dimension, pos_vec_t obstacles, pos_vec_t initpos, pos_vec_t finalpos, int max_length)
{
  unsigned int count;
  workspace_t workspace;

  float max_total_cost, min_total_cost, current_cost;

  ifstream ifp;
  string line;
  bool sat_flag;

  count = 2;
  while (count <= max_length)
  {
    if (count == max_length)
      createWorkspace(dimension, initpos, finalpos, count, finalpos.size() * 1000, workspace);
    else
      createWorkspace(dimension, initpos, finalpos, count, 1000, workspace);
    //writeWorkspace(workspace);
    
    generateZ3File(primitives, obstacles, workspace);
    system("z3 constraints.smt2 > z3_output");

    ifp.open("z3_output");
    getline(ifp, line);
    ifp.close();
    cout << endl << "$$$$$$$$ " << count << " " << line << endl;

    if (line == "unsat")
    {
      count = count + 1;
      continue;
    }
    else
    {
      max_total_cost = extractTrajectoryCostInformation();
      min_total_cost = 0;
      current_cost = (max_total_cost + min_total_cost) / 2;
      system("mv z3_output z3_output_sat");
    }

    cout << endl;
    cout << "max_total_cost = " << max_total_cost << endl;
    cout << "min_total_cost = " << min_total_cost << endl;
    cout << "current_cost  = " << current_cost << endl;

    while (max_total_cost - min_total_cost > 1)
    {
      createWorkspace(dimension, initpos, finalpos, count, current_cost, workspace);
      //writeWorkspace(workspace);

      generateZ3File(primitives, obstacles, workspace);
      system("z3 constraints.smt2 > z3_output");
      ifp.open("z3_output");
      getline(ifp, line);
      ifp.close();
      //cout << "$$$$$$$$ " << count << " " << line << endl;
      cout << line << endl;

      if (line == "unsat")
      {
        min_total_cost = current_cost;
      }
      else if (line == "sat")
      {
        sat_flag = true;
        max_total_cost = extractTrajectoryCostInformation();
        cout<<"renaming z3 output"<<endl;
        system("mv z3_output z3_output_sat");
      }
      else
      {
        cout << "unknown output from z3.." << endl;
        min_total_cost = current_cost;
        if (sat_flag == true)
          break;
      }
      current_cost = (max_total_cost + min_total_cost) / 2;
      cout << "max_total_cost = " << max_total_cost << endl;
      cout << "min_total_cost = " << min_total_cost << endl;
      cout << "current_cost  = " << current_cost << endl;
    }
    count = count + 1;
    cout << "renaming z3 output back"<<endl;
    system("mv z3_output_sat z3_output");

    if (current_cost < 1000)
      break;
  }
}


void printTrajectories(int number_of_robots, pos_vec_t initpos, pos_vec_t finalpos)
{
  ofstream ofp1, ofp2, ofp3;
  string filename;
  int count, count1, count2;
  vector<int> x_arr, y_arr, prim_arr;
  position tmp_pos, last_pos;
  pos_vec_t tmp_pos_vec;

  ofp1.open("assignment.txt");
  ofp3.open("assignment.json");

  Json::Value event;
  Json::Value vec(Json::arrayValue);



  cout << endl<< "Goal Locations:" << endl << endl;
  cout << endl<< "Covered Goals:" << endl << endl;
  for (count = 1; count <= number_of_robots; count++)
  {
	Json::Value oneRobotItem;
    x_arr.clear();
    y_arr.clear();
    prim_arr.clear();
    oneRobotItem["name"] = "Robot "+std::to_string(count);
    cout << "Robot " << count << endl;
    ofp1 << "Robot " << count << endl << endl;
    ofp1 << "Initial Location:" << endl;
    ofp1 << initpos[count - 1].x << " " << initpos[count - 1].y << endl << endl;
    oneRobotItem["initial_location"]["x"] = initpos[count-1].x;
    oneRobotItem["initial_location"]["y"] = initpos[count-1].y;
    ofp1 << "Goal Locations:" << endl;
 
    extractTrajectoryInformation(count, x_arr, y_arr , prim_arr);
    ostringstream os1, os2;
    os1 << x_arr[0];
    os2 << y_arr[0];
    filename = os1.str() + "_" + os2.str() + ".traj";
    ofp2.open(filename.c_str());
    
    tmp_pos_vec.clear(); 

    Json::Value goalLocations(Json::arrayValue);

    for (count1 = 0; count1 < x_arr.size(); count1++)
    {
      tmp_pos.x = x_arr[count1];
      tmp_pos.y = y_arr[count1];
      if (last_pos.x != tmp_pos.x || last_pos.y != tmp_pos.y)
      {
        ofp2 << tmp_pos.x << " " << tmp_pos.y << endl;
        last_pos.x = tmp_pos.x;
        last_pos.y = tmp_pos.y;
      }
      for (count2 = 0; count2 < finalpos.size(); count2++)
      {
        if (finalpos[count2].x == tmp_pos.x && finalpos[count2].y == tmp_pos.y)
        {
          if (findPosition(tmp_pos_vec, tmp_pos) == false)
          {
            tmp_pos_vec.push_back(tmp_pos);
            cout << x_arr[count1] << " " << y_arr[count1] << endl;
            ofp1 << x_arr[count1] << " " << y_arr[count1] << endl;
            Json::Value goalLocation;
            goalLocation["x"] = x_arr[count1];
            goalLocation["y"] = y_arr[count1];
            goalLocations.append( goalLocation );
          }
        }
      }
    }
    cout << endl;
    oneRobotItem["goalLocations"] = goalLocations;
    ofp2.close();
    ofp1 << endl << endl;
    vec.append(oneRobotItem);
  }
  ofp3 << vec;
  ofp3.close();
  ofp1.close();
}


int main ()
{
  prim_vec_t primitives;
  dimension_t dimension;
  pos_vec_t obstacles;
  pos_vec_t initpos, finalpos;
  robot_pos_vec_t initposjson;
  int max_length;
  clock_t start_time;

  cout << endl << endl;
  cout << "*** Concurrent Assignment and Planning ***" << endl << endl;

  //cout << "Maximum Length of the Trajectory: ";
  //cin >> max_length;
  //cout << endl << endl;

  readPrimitives(primitives);
  //writePrimitives(primitives);

  readDimension(dimension);
  //writeDimension(dimension);

  readPositions(obstacles, "obstacle.txt");
  //cout << "Positions of the Obstacles:" << endl;
  //writePositions(obstacles);

  readPositions(initpos, "initpos.txt");
  cout << "Initial Positions of the Robots:" << endl;
  writePositions(initpos);

  readPositions(finalpos, "finalpos.txt");
  cout << "Positions of the Destinations:" << endl;
  writePositions(finalpos);



  max_length = dimension.length_x + dimension.length_y;
  cout << "Maximum Length = " << max_length << endl << endl;
  
  max_length = dimension.length_x + dimension.length_y;
  cout << "max_length = " << max_length << endl;
  start_time = clock();
  generateTrajectories(primitives, dimension, obstacles, initpos, finalpos, max_length);
  cout << double( clock() - start_time ) / (double)CLOCKS_PER_SEC << " seconds." << endl; 

  printTrajectories(initpos.size(), initpos, finalpos);
  
  return 0;
}
