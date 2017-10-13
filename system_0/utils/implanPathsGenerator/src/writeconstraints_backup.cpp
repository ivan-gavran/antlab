#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "primitive.h"
#include "readinputs.h"
#include "writeconstraints.h"


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
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
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
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
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
      ofp << "(declare-const final_position_" << count1 + 1 << "_" << count2 + 1 << " Bool)" << endl;
    }
    ofp << "(declare-const final_position_" << count1 + 1 << "_0" << " Bool)" << endl;
  }
  ofp << endl;

  for (count2 = 0; count2 < (workspace.pos_end).size(); count2++)
  {
    ofp << "(declare-const final_position_" << count2 + 1 << " Bool)" << endl;
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


void writeFinalDestinationChoiceConstraints(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1, count2, count3;

  // Each robot either reaches a goal location or remains in its initial location
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    ofp << "(assert (or " << endl;
    for (count2 = 0; count2 < workspace.pos_end.size(); count2++)
    {
      ofp << "    (= final_position_" << count1 + 1 << "_" << count2 + 1 << " true)" << endl;
    }
    ofp << "    (= final_position_" << count1 + 1 << "_0" << " true)" << endl;
    ofp << "))" << endl << endl;
  }

  // A goal location is covered if at least one robot reaches the goal location
  for (count2 = 0; count2 < workspace.pos_end.size(); count2++)
  {
    ofp << "(assert (=> (= final_position_" << count2 + 1 << " true) (or " << endl;
    for (count1 = 0; count1 < workspace.number_of_robots; count1++)
    {
      ofp << "    (= final_position_" << count1 + 1 << "_" << count2 + 1 << " true)" << endl;
    }
    ofp << ")))" << endl << endl;
  }
  
  // At most one robot can occupy a goal location
  for (count1  = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.pos_end.size(); count2++)
    {
      ofp << "(assert (=> (= final_position_" << count1 + 1 << "_" << count2 + 1 << " true) (and " << endl;
      for (count3 = 0; count3 < workspace.number_of_robots; count3++)
      {
        if (count3 != count1)
        {
          ofp << "    (= final_position_" << count3 + 1 << "_" << count2 + 1 << " false)" << endl;
        }
      }
      ofp << ")))" << endl;
    }
  }

  // Cost of not covering a goal location
  for (count2 = 0; count2 < workspace.pos_end.size(); count2++)
  {
    ofp << "(assert (=> (= final_position_" << count2 + 1 << " true) (= cost_goal_" << count2 + 1 << " 0)))" << endl;
    ofp << "(assert (=> (= final_position_" << count2 + 1 << " false) (= cost_goal_" << count2 + 1 << " 1000)))" << endl;
  }
}


void writeFinalDestinationConstraints(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1, count2;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.pos_end.size(); count2++)
    {
      ofp << "(assert (=> (= final_position_" << count1 + 1 << "_" << count2 + 1 << " true)" << endl;
      ofp << "(or (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x << ")" << endl;
      ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y << "))" << endl;
      if ((workspace.pos_end[count1].x >= 0) && (workspace.pos_end[count1].y - 1 >= 0) && (workspace.pos_end[count2].x <= (int) workspace.length_x))
      {
        ofp << "    (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x << ")" << endl;
        ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y - 1 << "))" << endl;
      }
      if ((workspace.pos_end[count2].x >= 0) && (workspace.pos_end[count2].y + 1 >= 0) && (workspace.pos_end[count2].x <= (int) workspace.length_x) && (workspace.pos_end[count2].y + 1 <= (int) workspace.length_y))
      {
        ofp << "    (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x << ")" << endl;
        ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y + 1<< "))" << endl;
      }
      if ((workspace.pos_end[count2].x - 1 >= 0) && (workspace.pos_end[count2].y >= 0) && (workspace.pos_end[count2].y <= (int) workspace.length_y))
      {
        ofp << "    (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x - 1 << ")" << endl;
        ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y << "))" << endl;
      }
      if ((workspace.pos_end[count2].x - 1 >= 0) && (workspace.pos_end[count2].y - 1 >= 0))
      {
        ofp << "    (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x - 1 << ")" << endl;
        ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y - 1 << "))" << endl;
      }
      if ((workspace.pos_end[count2].x - 1 >= 0) && (workspace.pos_end[count2].y + 1 >= 0) && (workspace.pos_end[count2].y + 1 <= (int) workspace.length_y))
      {
        ofp << "    (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x - 1 << ")" << endl;
        ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y + 1 << "))" << endl;
      }
      if ((workspace.pos_end[count2].x + 1 >= 0) && (workspace.pos_end[count2].y >= 0) && (workspace.pos_end[count2].x + 1 <= (int) workspace.length_x) && (workspace.pos_end[count2].y <= (int) workspace.length_y))
      {
        ofp << "    (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x + 1 << ")" << endl;
        ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y << "))" << endl;
      }
      if ((workspace.pos_end[count2].x + 1 >= 0) && (workspace.pos_end[count2].y - 1 >= 0) && (workspace.pos_end[count2].x + 1 <= (int) workspace.length_x))
      {
        ofp << "    (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x + 1 << ")" << endl;
        ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y - 1 << "))" << endl;
      }
      if ((workspace.pos_end[count2].x + 1 >= 0) && (workspace.pos_end[count2].y + 1 >= 0) && (workspace.pos_end[count2].x + 1 <= (int) workspace.length_x) && (workspace.pos_end[count2].y + 1 <= (int) workspace.length_y))
      {
        ofp << "    (and (= x_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].x + 1 << ")" << endl;
        ofp << "         (= y_" << count1 + 1 << "_" << workspace.number_of_points << " " << workspace.pos_end[count2].y + 1<< "))" << endl;
      }
      ofp << ")))" << endl;
    }
    ofp << endl;
  }
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
        //ofp << "(assert (! (or (not (= prim_" << count1 + 1 << "_" << count2 + 1 << " " << count + 1 << "))" << endl;
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
        //ofp << ")) :named tran_" << count1 + 1 << "_" << count2 + 1 << "_" << count + 1 << "))" << endl;
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
      //ofp << "(assert (! (= x_" << count1 + 1 << "_" << count2 + 1 << " (+ x_" << count1 + 1 << "_" << count2 << " x_f_" << count1 + 1 << "_" << count2 << ")) :named xmatch_" << count1 << "_" << count2 << "))" << endl;
      ofp << "(assert (= y_" << count1 + 1 << "_" << count2 + 1 << " (+ y_" << count1 + 1 << "_" << count2 << " y_f_" << count1 + 1 << "_" << count2 << ")))" << endl;
      //ofp << "(assert (! (= y_" << count1 + 1 << "_" << count2 + 1 << " (+ y_" << count1 + 1 << "_" << count2 << " y_f_" << count1 + 1 << "_" << count2 << ")) :named ymatch_" << count1 << "_" << count2 << "))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 1; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(assert (= vel_i_" << count1 + 1 << "_" << count2 + 1 << " vel_f_" << count1 + 1 << "_" << count2 << "))" << endl;
      //ofp << "(assert (! (= vel_i_" << count1 + 1 << "_" << count2 + 1 << " vel_f_" << count1 + 1 << "_" << count2 << ") :named velmatch_" << count1 << "_" << count2 << "))" << endl;
    }
  }
  ofp << endl;
}


void writeCostConstraint(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1, count2, count3;

  ofp << "(assert (= total_cost (+";
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << " cost_" << count1 + 1 << "_" << count2 + 1;
    }
  }
  for (count3 = 0; count3 < (workspace.pos_end).size(); count3++)
  {
    ofp << " cost_goal_" << count3 + 1;
  }
  ofp << ")))" << endl;
  ofp << "(assert (< total_cost " << floatToReal(workspace.total_cost) << "))" << endl;
  ofp << endl;
}


void writeDistanceConstraints(ofstream &ofp, workspace_t workspace)
{
  unsigned int count, count1, count2;
  for (count = 1; count <= workspace.number_of_points; count++)
  {
    for (count1 = 1; count1 <= workspace.number_of_robots; count1++)
    {
      for (count2 = 1; count2 <= workspace.number_of_robots; count2++)
      {
        if (count1 != count2)
        {
          ofp << "(assert (or (> (- x_" << count1 << "_" << count << " x_" << count2 << "_" << count << ") 1)" << endl;
          ofp << "            (> (- x_" << count2 << "_" << count << " x_" << count1 << "_" << count << ") 1)" << endl;
          ofp << "            (> (- y_" << count1 << "_" << count << " y_" << count2 << "_" << count << ") 1)" << endl;
          ofp << "            (> (- y_" << count2 << "_" << count << " y_" << count1 << "_" << count << ") 1)))" << endl;
        }
      }
    }
  }
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


string floatToReal(string fls)
{
  float flf;
  string str1, str2;
  long int num, den;
  int length;
  int pos;
 
  istringstream (fls) >> flf;
  pos = fls.find('.');
  if (pos == -1)
  {
    return fls;
  }
  else
  {
    length = fls.length();
    den = pow(10, (length - pos));
    num = flf * den;
    str1 = tostr(num);
    str2 = tostr(den);
    return ("(/ " + str1 + " " + str2 + ")");
  }
}


template <typename T> string tostr(const T& t) 
{ 
  ostringstream os; 
  os << t; 
  return os.str(); 
} 
