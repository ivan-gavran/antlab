#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "primitive.h"
#include "readinputs.h"
#include "extractoutput.h"
#include "writetrajectoryconstraints.h"


#define MAX_LENGTH_TRAJ 30
#define MAX_LENGTH_PRIM 3
#define MAX_COST 1000.0


using namespace std;


bool findPosition (pos_vec_t posvec, position pos)
{
  unsigned int count;

  for (count = 0; count < posvec.size(); count++)
  {
    if (posvec[count].x == pos.x && posvec[count].y == pos.y)
      return true;
  }
  return false;
}


void createWorkspace(dimension_t dimension, position initposition, position finalposition, int iteration, float cost, workspace_t &workspace)
{
  workspace.length_x = dimension.length_x;
  workspace.length_y = dimension.length_y;
  workspace.number_of_robots = 1;
  workspace.pos_start.clear();
  workspace.pos_end.clear();
  workspace.pos_start.push_back(initposition);
  workspace.pos_end.push_back(finalposition);
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

  writeFinalDestinationConstraints(ofp, workspace);
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


void generateTrajectory(prim_vec_t primitives, dimension_t dimension, pos_vec_t obstacles, position initposition, position finalposition, int max_length, int & traj_length, float & traj_cost)
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
    createWorkspace(dimension, initposition, finalposition, count, max_length, workspace);
    //writeWorkspace(workspace);
    
    generateZ3File(primitives, obstacles, workspace);
    system("z3 constraints.smt2 > z3_output");

    ifp.open("z3_output");
    getline(ifp, line);
    ifp.close();
    cout << "$$$$$$$$ " << count << " " << line << endl;

    if (line == "unsat")
    {
      count = count + 1;
      continue;
    }
    else
    {
      max_total_cost = extractCostInformation();
      min_total_cost = 0;
      current_cost = (max_total_cost + min_total_cost) / 2;
      system("mv z3_output z3_output_sat");
      traj_length = count - 1;
      traj_cost = max_total_cost;
    }

    cout << endl;
    cout << "max_total_cost = " << max_total_cost << endl;
    cout << "min_total_cost = " << min_total_cost << endl;
    cout << "current_cost  = " << current_cost << endl;

    while (max_total_cost - min_total_cost > 1)
    {
      createWorkspace(dimension, initposition, finalposition, count, current_cost, workspace);
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
        max_total_cost = extractCostInformation();
        system("mv z3_output z3_output_sat");
        traj_cost = max_total_cost;
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
    system("mv z3_output_sat z3_output");
    break;
  }
}


void printTrajectory(position initposition, position finalposition)
{
  ofstream ofp;
  string filename;
  int count;
  vector<int> x_arr, y_arr, prim_arr;
  position last_pos;

  x_arr.clear();
  y_arr.clear();
  prim_arr.clear();
  extractTrajectoryInformation(1, x_arr, y_arr , prim_arr);
  ostringstream os1, os2, os3, os4;
  os1 << initposition.x;
  os2 << initposition.y;
  os3 << finalposition.x;
  os4 << finalposition.y;

  filename = os1.str() + "_" + os2.str() + "_" + os3.str() + "_" + os4.str() + ".traj";
  ofp.open(filename.c_str());

  for (count = 0; count < x_arr.size(); count++)
  {
    if (last_pos.x != x_arr[count] || last_pos.y != y_arr[count])
    {
      ofp << x_arr[count] << " " << y_arr[count] << endl;
      last_pos.x = x_arr[count];
      last_pos.y = y_arr[count];
    }
  }
  ofp.close();
}


void generateAllTrajectories(prim_vec_t primitives, dimension_t dimension, pos_vec_t obstacles, pos_vec_t initpos, pos_vec_t finalpos, int max_length, 
                             vector< vector<int> > & start_goal_traj_length,
                             vector< vector<int> > & goal_goal_traj_length, 
                             vector< vector<float> > & start_goal_traj_cost,
                             vector< vector<float> > & goal_goal_traj_cost)
{
  unsigned int count1, count2;
  int traj_length;
  float traj_cost;
  vector<int> tmp_int_vec;
  vector<float> tmp_float_vec;

  start_goal_traj_length.clear();
  start_goal_traj_cost.clear();
  for (count1 = 0; count1 < initpos.size(); count1++)
  {
    tmp_int_vec.clear();
    tmp_float_vec.clear();
    for (count2 = 0; count2 < finalpos.size(); count2++)
    {
      tmp_int_vec.push_back(0);
      tmp_float_vec.push_back(0.0);
    }
    start_goal_traj_length.push_back(tmp_int_vec);
    start_goal_traj_cost.push_back(tmp_float_vec);
  }

  goal_goal_traj_length.clear();
  goal_goal_traj_cost.clear();
  for (count1 = 0; count1 < finalpos.size(); count1++)
  {
    tmp_int_vec.clear();
    tmp_float_vec.clear();
    for (count2 = 0; count2 < finalpos.size(); count2++)
    {
      tmp_int_vec.push_back(0);
      tmp_float_vec.push_back(0.0);
    }
    goal_goal_traj_length.push_back(tmp_int_vec);
    goal_goal_traj_cost.push_back(tmp_float_vec);
  }

  for (count1 = 0; count1 < initpos.size(); count1++)
  {
    for (count2 = 0; count2 < finalpos.size(); count2++)
    {
      cout << endl << endl;
      cout << "Initial Position: " << initpos[count1].x << " " << initpos[count1].y << endl;
      cout << "Final Position: " << finalpos[count2].x << " " << finalpos[count2].y << endl;
      cout << endl;
      generateTrajectory(primitives, dimension, obstacles, initpos[count1], finalpos[count2], max_length, traj_length, traj_cost);
      start_goal_traj_length[count1][count2] = traj_length;
      start_goal_traj_cost[count1][count2] = traj_cost;
      printTrajectory(initpos[count1], finalpos[count2]);
    }
  }
  
  for (count1 = 0; count1 < finalpos.size(); count1++)
  {
    for (count2 = 0; count2 < finalpos.size(); count2++)
    {
      if (count1 != count2)
      {
        cout << endl << endl;
        cout << "Final Position: " << finalpos[count1].x << " " << finalpos[count1].y << endl;
        cout << "Final Position: " << finalpos[count2].x << " " << finalpos[count2].y << endl;
        cout << endl;
        generateTrajectory(primitives, dimension, obstacles, finalpos[count1], finalpos[count2], max_length, traj_length, traj_cost);
        goal_goal_traj_length[count1][count2] = traj_length;
        goal_goal_traj_cost[count1][count2] = traj_cost;
        printTrajectory(finalpos[count1], finalpos[count2]);
      }
    }
  }
}


void printTrajectoryInformation(vector< vector<int> > start_goal_traj_length,
                             vector< vector<int> > goal_goal_traj_length,
                             vector< vector<float> > start_goal_traj_cost,
                             vector< vector<float> > goal_goal_traj_cost)
{
  unsigned int count1, count2;
  vector<int> tmp_int_vec;
  vector<float> tmp_float_vec;
  
  cout << endl << endl;
  cout << "Trajectory Information: " << endl << endl;
   
  cout << "Start to Goal Trajectory Length:" << endl;
  for (count1 = 0; count1 < start_goal_traj_length.size(); count1++)
  {
    tmp_int_vec = start_goal_traj_length[count1];  
    for (count2 = 0; count2 < tmp_int_vec.size(); count2++)
    {
      cout << tmp_int_vec[count2] << " ";
    }
    cout << endl;
  }
  cout << endl;

  cout << "Goal to Goal Trajectory Length:" << endl;
  for (count1 = 0; count1 < goal_goal_traj_length.size(); count1++)
  {              
    tmp_int_vec = goal_goal_traj_length[count1];
    for (count2 = 0; count2 < tmp_int_vec.size(); count2++)
    {
      cout << tmp_int_vec[count2] << " ";
    }
    cout << endl;
  }
  cout << endl;

  cout << "Start to Goal Trajectory Cost" << endl;
  for (count1 = 0; count1 < start_goal_traj_cost.size(); count1++)
  {              
    tmp_float_vec = start_goal_traj_cost[count1];
    for (count2 = 0; count2 < tmp_float_vec.size(); count2++)
    {
      cout << tmp_float_vec[count2] << " ";
    }
    cout << endl;
  }
  cout << endl;

  cout << "Goal to Goal Trajectory Cost" << endl;
  for (count1 = 0; count1 < goal_goal_traj_cost.size(); count1++)
  {              
    tmp_float_vec = goal_goal_traj_cost[count1];
    for (count2 = 0; count2 < tmp_float_vec.size(); count2++)
    {
      cout << tmp_float_vec[count2] << " ";
    }
    cout << endl;
  }
  cout << endl;
}
