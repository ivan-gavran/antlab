#include <iostream>
#include <fstream>
#include <sstream>
#include "utils.h"
#include "primitive.h"
#include "readinputs.h"
#include "writetrajectoryconstraints.h"


void declareVariables(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1, count2;

  ofp << "(declare-fun obstacle (Int Int) Bool)" << endl;
  ofp << endl;

  ofp << "(declare-const total_cost Real)" << endl;
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(declare-const prim_" << count1 + 1 << "_" << count2 + 1 << " Int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(declare-const x_" << count1 + 1 << "_" << count2 + 1 << " Int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(declare-const y_" << count1 + 1 << "_" << count2 + 1 << " Int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(declare-const vel_i_" << count1 + 1 << "_" << count2 + 1 << " Int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(declare-const vel_f_" << count1 + 1 << "_" << count2 + 1 << " Int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(declare-const x_f_" << count1 + 1 << "_" << count2 + 1 << " Int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(declare-const y_f_" << count1 + 1 << "_" << count2 + 1 << " Int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.pos_end.size(); count2++)
    {
      ofp << "(declare-const occupied_" << count1 + 1 << "_" << count2 + 1 << " Bool)" << endl;
    }
  }
  ofp << endl;

  for (count2 = 0; count2 < (workspace.pos_end).size(); count2++)
  {
    ofp << "(declare-const covered_" << count2 + 1 << " Bool)" << endl;
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(declare-const cost_" << count1 + 1 << "_" << count2 + 1 << " Real)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.pos_end.size(); count1++)
  {
    ofp << "(declare-const cost_goal_" << count1 + 1 << " Real)" << endl;
  }
  ofp << endl;
}


void writeInitialLocationConstraints(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    ofp << "(assert (= x_" << count1 + 1 << "_1 " << workspace.pos_start[count1].x << "))" << endl;
    ofp << "(assert (= y_" << count1 + 1 << "_1 " << workspace.pos_start[count1].y << "))" << endl;
  }
  ofp << endl;
}


void writeFinalDestinationConstraints(ofstream &ofp, workspace_t workspace)
{
  //unsigned int count1;

  ofp << "(assert (or (and (= x_1_" << workspace.number_of_points << " " << workspace.pos_end[0].x << ")";
  ofp << " (= y_1_" << workspace.number_of_points << " " << workspace.pos_end[0].y << "))))" << endl;

  /*
  for (count1 = 0; count1 < workspace.number_of_uavs; count1++)
  {
    ofp << "(assert (or (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x << ")" << endl;
    ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y << "))" << endl;
    if ((workspace.pos_end[count1].x >= 0) && (workspace.pos_end[count1].y - 1 >= 0) && (workspace.pos_end[count1].x <= (int) workspace.length_x))
    {
      ofp << "            (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x << ")" << endl;
      ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y - 1 << "))" << endl;
    }
    if ((workspace.pos_end[count1].x >= 0) && (workspace.pos_end[count1].y + 1 >= 0) && (workspace.pos_end[count1].x <= (int) workspace.length_x) && (workspace.pos_end[count1].y + 1 <= (int) workspace.length_y))
    {
      ofp << "            (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x << ")" << endl;
      ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y + 1<< "))" << endl;
    }
    if ((workspace.pos_end[count1].x - 1 >= 0) && (workspace.pos_end[count1].y >= 0) && (workspace.pos_end[count1].y <= (int) workspace.length_y))
    {
      ofp << "            (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x - 1 << ")" << endl;
      ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y << "))" << endl;
    }
    if ((workspace.pos_end[count1].x - 1 >= 0) && (workspace.pos_end[count1].y - 1 >= 0))
    {
      ofp << "            (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x - 1 << ")" << endl;
      ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y - 1 << "))" << endl;
    }
    if ((workspace.pos_end[count1].x - 1 >= 0) && (workspace.pos_end[count1].y + 1 >= 0) && (workspace.pos_end[count1].y + 1 <= (int) workspace.length_y))
    {
      ofp << "            (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x - 1 << ")" << endl;
      ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y + 1 << "))" << endl;
    }
    if ((workspace.pos_end[count1].x + 1 >= 0) && (workspace.pos_end[count1].y >= 0) && (workspace.pos_end[count1].x + 1 <= (int) workspace.length_x) && (workspace.pos_end[count1].y <= (int) workspace.length_y))
    {
      ofp << "            (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x + 1 << ")" << endl;
      ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y << "))" << endl;
    }
    if ((workspace.pos_end[count1].x + 1 >= 0) && (workspace.pos_end[count1].y - 1 >= 0) && (workspace.pos_end[count1].x + 1 <= (int) workspace.length_x))
    {
      ofp << "            (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x + 1 << ")" << endl;
      ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y - 1 << "))" << endl;
    }
    if ((workspace.pos_end[count1].x + 1 >= 0) && (workspace.pos_end[count1].y + 1 >= 0) && (workspace.pos_end[count1].x + 1 <= (int) workspace.length_x) && (workspace.pos_end[count1].y + 1 <= (int) workspace.length_y))
    {
      ofp << "            (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].x + 1 << ")" << endl;
      ofp << "                 (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count1].y + 1<< "))" << endl;
    }
    ofp << "))" << endl;
  }*/
  ofp << endl;
}


void writeObstacleConstraints(ofstream &ofp, pos_vec_t obstacles, workspace_t workspace)
{
  unsigned int count, count1, count2;

  bool workspace_obstacles[workspace.length_x + 1][workspace.length_y + 1];

  for (count1 = 0; count1 <= workspace.length_x; count1++)
  {
    for (count2 = 0; count2 <= workspace.length_y; count2++)
    {
      workspace_obstacles[count1][count2] = false;
    }
  }
  
  for (count = 0; count < obstacles.size(); count++)
  {
    workspace_obstacles[obstacles[count].x][obstacles[count].y] = true;
  }
  for (count1 = 0; count1 <= workspace.length_x; count1++)
  {
    for (count2 = 0; count2 <= workspace.length_y; count2++)
    {
      if (workspace_obstacles[count1][count2] == true)
        ofp << "(assert (= (obstacle " << count1 << " " << count2 << ") " << "true" << "))" << endl;
    }
  }
  ofp << endl;
}


void writeTransitionConstraints(ofstream &ofp, prim_vec_t primitives, pos_vec_t obstacles, workspace_t workspace)
{
  state q_i, q_f;
  position pos_f;
  pos_vec_t swath, swath1, swath2;
  string cost;
  unsigned int count, count1, count2, count3;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    ofp << "(assert (= vel_i_" << count1 + 1 << "_1 0))" << endl;
    ofp << "(assert (= vel_f_" << count1 + 1 << "_" << workspace.number_of_points - 1 << " 0))" << endl;
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(assert (and (>= prim_" << count1 + 1 << "_" << count2 + 1 << " 1) (<= prim_" << count1 + 1 << "_" << count2 + 1 << " " << primitives.size() << ")))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 1; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(assert (and (>= vel_i_" << count1 + 1 << "_" << count2 + 1 << " 0) (<= vel_i_" << count1 + 1 << "_" << count2 + 1 << " 8)))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 2; count2++)
    {
      ofp << "(assert (and (>= vel_f_" << count1 + 1 << "_" << count2 + 1 << " 0) (<= vel_f_" << count1 + 1 << "_" << count2 + 1 << " 8)))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(assert (and (>= x_" << count1 + 1 << "_" << count2 + 1 << " 0) (<= x_" << count1 + 1 << "_" << count2 + 1 << " " << workspace.length_x << ")))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(assert (and (>= y_" << count1 + 1 << "_" << count2 + 1 << " 0) (<= y_" << count1 + 1 << "_" << count2 + 1 << " " << workspace.length_y << ")))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      for (count = 0; count < primitives.size(); count++)
      {
        q_i = primitives[count].get_q_i();
        q_f = primitives[count].get_q_f();
        pos_f = primitives[count].get_pos_f();
        cost = primitives[count].get_cost();
        swath = primitives[count].get_swath();
        ofp << "(assert (or (not (= prim_" << count1 + 1 << "_" << count2 + 1 << " " << count + 1 << "))" << endl;
        ofp << "(and (= vel_i_" << count1 + 1 << "_" << count2 + 1 << " " << q_i.velocity << ")" << endl;
        ofp << "     (= vel_f_" << count1 + 1 << "_" << count2 + 1 << " " << q_f.velocity << ")" << endl;
        ofp << "     (= x_f_" << count1 + 1 << "_" << count2 + 1 << " " << pos_f.x << ")" << endl;
        ofp << "     (= y_f_" << count1 + 1 << "_" << count2 + 1 << " " << pos_f.y << ")" << endl;
        ofp << "     (= cost_" << count1 + 1 << "_" << count2 + 1 << " " << floatToReal(cost) << ")" << endl;
        for (count3 = 0; count3 < swath.size(); count3++)
        {
          ofp << "     (= (obstacle (+ x_" << count1 + 1 << "_" << count2 + 1 << " " << swath[count3].x << ") (+ y_" << count1 + 1 << "_" << count2 + 1 << " " << swath[count3].y << ")) false)" << endl;
        }
        ofp << ")))" << endl;
        ofp << endl;
      }
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 1; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(assert (= x_" << count1 + 1 << "_" << count2 + 1 << " (+ x_" << count1 + 1 << "_" << count2 << " x_f_" << count1 + 1 << "_" << count2 << ")))" << endl;
      ofp << "(assert (= y_" << count1 + 1 << "_" << count2 + 1 << " (+ y_" << count1 + 1 << "_" << count2 << " y_f_" << count1 + 1 << "_" << count2 << ")))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 1; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(assert (= vel_i_" << count1 + 1 << "_" << count2 + 1 << " vel_f_" << count1 + 1 << "_" << count2 << "))" << endl;
    }
  }
  ofp << endl;
}


void writeCostConstraint(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1, count2;

  ofp << "(assert (= total_cost (+";
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << " cost_" << count1 + 1 << "_" << count2 + 1;
    }
  }
  ofp << ")))" << endl;
  ofp << "(assert (< total_cost " << floatToReal(workspace.total_cost) << "))" << endl;
  ofp << endl;
}


void writeOutputConstraints(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1, count2;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(get-value (prim_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
    ofp << "(get-value (x_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(get-value (y_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;
  
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
    ofp << "(get-value (vel_i_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;
   
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(get-value (vel_f_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(get-value (x_f_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(get-value (y_f_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;
  
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(get-value (cost_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << "(get-value (total_cost))" << endl;
  ofp << endl;
}
