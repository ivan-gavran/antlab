
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
#include <math.h>
#include "primitive.h"
#include "readinputs.h"
#include "definepropositions.h"
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
	  ofp<<"(declare-const total_cost_"<<count1+1<<" Real)"<<endl;
  }

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
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(declare-const cost_" << count1 + 1 << "_" << count2 + 1 << " Real)" << endl;
    }
  }
  ofp << endl;
}


void declareVariablesYices(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1, count2;

  ofp << "(define obstacle::(-> int int bool))" << endl;
  ofp << endl;

  ofp << "(define total_cost::real)" << endl;
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(define prim_" << count1 + 1 << "_" << count2 + 1 << "::int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(define x_" << count1 + 1 << "_" << count2 + 1 << "::int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(define y_" << count1 + 1 << "_" << count2 + 1 << "::int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(define vel_i_" << count1 + 1 << "_" << count2 + 1 << "::int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(define vel_f_" << count1 + 1 << "_" << count2 + 1 << "::int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(define x_f_" << count1 + 1 << "_" << count2 + 1 << "::int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(define y_f_" << count1 + 1 << "_" << count2 + 1 << "::int)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(define cost_" << count1 + 1 << "_" << count2 + 1 << "::real)" << endl;
    }
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
  unsigned int count1;

  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
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
  }
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
      /*if (workspace_obstacles[count1][count2] == 0)
        ofp << "(assert (= (obstacle " << count1 << " " << count2 << ") " << "false" << "))" << endl;
        //ofp << "(assert (! (= (obstacle " << count1 << " " << count2 << ") " << "false" << ") :named obs_" << count1 << "_" << count2 << "))" << endl;
      else
        ofp << "(assert (= (obstacle " << count1 << " " << count2 << ") " << "true" << "))" << endl;
        //ofp << "(assert (! (= (obstacle " << count1 << " " << count2 << ") " << "true" << ") :named obs_" << count1 << "_" << count2 << "))" << endl;
      */
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

  /*bool workspace_obstacles[workspace.length_x + 1][workspace.length_y + 1];

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
  }*/

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

  /*for (count1 = 0; count1 <= workspace.length_x; count1++)
  {
    for (count2 = 0; count2 <= workspace.length_y; count2++)
    {
      if (workspace_obstacles[count1][count2] == 0)
        ofp << "(assert (= (obstacle " << count1 << " " << count2 << ") " << "false" << "))" << endl;
        //ofp << "(assert (! (= (obstacle " << count1 << " " << count2 << ") " << "false" << ") :named obs_" << count1 << "_" << count2 << "))" << endl;
      else
        //ofp << "(assert (= (obstacle " << count1 << " " << count2 << ") " << "true" << "))" << endl;
        ofp << "(assert (! (= (obstacle " << count1 << " " << count2 << ") " << "true" << ") :named obs_" << count1 << "_" << count2 << "))" << endl;
    }
  }
  ofp << endl;*/

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
        //ofp << "     (= cost_" << count1 + 1 << "_" << count2 + 1 << " " << floatToReal(cost) << ")" << endl;
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

void writeLoopDependentCostConstraint(ofstream &ofp, prim_vec_t primitives, pos_vec_t obstacles, workspace_t workspace)
{
	state q_i, q_f;
	position pos_f;
	pos_vec_t swath, swath1, swath2;
	string cost;
	int max_loop_cost = 1000;
	unsigned int count, count1, count2;
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
        ofp << "(assert (or (not (and (not loopexists) (= prim_" << count1 + 1 << "_" << count2 + 1 << " " << count + 1 << ")))" << endl;
        //ofp << "(assert (! (or (not (= prim_" << count1 + 1 << "_" << count2 + 1 << " " << count + 1 << "))" << endl;
        ofp << "     (= cost_" << count1 + 1 << "_" << count2 + 1 << " " << floatToReal(cost) << ")" << endl;

        ofp << "))" << endl;


        ofp << "(assert (or (not (and loopexists ";
		ofp<<"(and true ";
		for (int count3 = 0; count3 <= count2; count3++){

			ofp<<"(not l_"<<count3<<") "<<endl;
		}
		ofp<<") ";
		ofp<<"(= prim_" << count1 + 1 << "_" << count2 + 1 << " " << count + 1 << ")))" << endl;
		//ofp << "(assert (! (or (not (= prim_" << count1 + 1 << "_" << count2 + 1 << " " << count + 1 << "))" << endl;
		ofp << "     (= cost_" << count1 + 1 << "_" << count2 + 1 << " " << floatToReal(cost) << ")" << endl;

		ofp << "))" << endl;

		ofp << "(assert (or (not (and loopexists ";
		ofp<<"(or false ";
		for (int count3 = 0; count3 <= count2; count3++){

			ofp<<" l_"<<count3<<" "<<endl;
		}
		ofp<<") ";
		ofp<<"(= prim_" << count1 + 1 << "_" << count2 + 1 << " " << count + 1 << ")))" << endl;
		//ofp << "(assert (! (or (not (= prim_" << count1 + 1 << "_" << count2 + 1 << " " << count + 1 << "))" << endl;
		ofp << "     (= cost_" << count1 + 1 << "_" << count2 + 1 << " " <<  max_loop_cost << ")" << endl;

		ofp << "))" << endl;


        //ofp << ")) :named tran_" << count1 + 1 << "_" << count2 + 1 << "_" << count + 1 << "))" << endl;
        ofp << endl;
      }
    }
  }

}

void writeCostConstraint(ofstream &ofp, workspace_t workspace, prim_cost_t prim_cost)
{
  unsigned int count1, count2;
  float max_total_cost, min_total_cost;
  
  ofp << "(assert (= total_cost (+";
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << " cost_" << count1 + 1 << "_" << count2 + 1;
    }
  }
  ofp << ")))" << endl;
  
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
	  ofp << "(assert (= total_cost_"<<count1+1<<" (+";
	  for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
	      {
	        ofp << " cost_" << count1 + 1 << "_" << count2 + 1;
	      }
	  ofp<<")))"<<endl;
  }

  max_total_cost = workspace.number_of_points * workspace.number_of_robots * prim_cost.max_cost;
  min_total_cost = workspace.number_of_points * workspace.number_of_robots * prim_cost.min_cost;
  cout << "max_total_cost in write cost constraint = " << workspace.total_cost << endl;

  
//  ofp << "(assert (>= total_cost " << min_total_cost << "))" << endl;
//  ofp << "(assert (<= total_cost " << max_total_cost << "))" << endl;

  //ofp << "(minimize total_cost)" << endl;
  ofp << "(assert (<= total_cost " << floatToReal(workspace.total_cost) << "))" << endl;
  ofp << endl;
}


/*
// Collision Avoidance without abstraction
void writeCollisionAvoidanceConstraints1(ofstream &ofp, prim_vec_t primitives, workspace_t workspace)
{
  unsigned int count, count1, count2, count3, count4, count5, count6;
  pos_vec_t swath1, swath2;

  for (count = 0; count < workspace.number_of_points - 1; count++)
  {
    for (count1 = 0; count1 < workspace.number_of_robots; count1++)
    {
      for (count2 = 0; count2 < workspace.number_of_robots; count2++)
      {
        if (count1 != count2)
        {
          for (count3 = 0; count3 < primitives.size(); count3++)
          {
            swath1 = primitives[count3].get_swath();
            for (count4 = 0; count4 < primitives.size(); count4++)
            {
              swath2 = primitives[count4].get_swath();
              ofp << "(assert (or (not (and (= prim_" << count1 + 1 << "_" << count + 1 << " " << count3 + 1 << ") (= prim_" << count2 + 1 << "_" << count + 1 << " " << count4 + 1 << ")))" << endl << "(and " << endl;
              for (count5 = 0; count5 < swath1.size(); count5++)
              {
                for (count6 = 0; count6 < swath2.size(); count6++)
                {
                   ofp << "    (or (not (= (+ x_" << count1 + 1 << "_" << count + 1 << " " << swath1[count5].x << ") (+ x_" << count2 + 1 << "_" << count + 1 << " " << swath2[count6].x << "))) (not (= (+ y_" << count1 + 1 << "_" << count + 1 << " " << swath1[count5].y << ") (+ y_" << count2 + 1 << "_" << count + 1 << " " << swath2[count6].y << "))))" << endl;
                }
              }
              ofp << ")))" << endl << endl;
            }
          }
        }
      }
    }
  }
}


// Collision Avoidance with abstraction
void writeCollisionAvoidanceConstraints2(ofstream &ofp, prim_vec_t primitives, workspace_t workspace)
{
  unsigned int count, count1, count2, count3, count4;
  position pos_min1, pos_max1, pos_min2, pos_max2;

  for (count = 0; count < workspace.number_of_points - 1; count++)
  {
    for (count1 = 0; count1 < workspace.number_of_robots; count1++)
    {
      for (count2 = 0; count2 < workspace.number_of_robots; count2++)
      {
        if (count1 != count2)
        {
          for (count3 = 0; count3 < primitives.size(); count3++)
          {
            pos_min1 = primitives[count3].get_pos_min();
            pos_max1 = primitives[count3].get_pos_max();
            for (count4 = 0; count4 < primitives.size(); count4++)
            {
              pos_min2 = primitives[count4].get_pos_min();
              pos_max2 = primitives[count4].get_pos_max();
              ofp << "(assert (or (not (and (= prim_" << count1 + 1 << "_" << count + 1 << " " << count3 + 1 << ") (= prim_" << count2 + 1 << "_" << count + 1 << " " << count4 + 1 << ")))" << endl;
              ofp << "  (or (> (+ x_" << count1 + 1 << "_" << count + 1 << " " << pos_min1.x - 1 << ") (+ x_" << count2 + 1 << "_" << count + 1 << " " << pos_max2.x << "))" << endl;
              ofp << "      (< (+ x_" << count1 + 1 << "_" << count + 1 << " " << pos_max1.x + 1 << ") (+ x_" << count2 + 1 << "_" << count + 1 << " " << pos_min2.x << "))" << endl;
              ofp << "      (> (+ y_" << count1 + 1 << "_" << count + 1 << " " << pos_min1.y - 1 << ") (+ y_" << count2 + 1 << "_" << count + 1 << " " << pos_max2.y << "))" << endl;
              ofp << "      (< (+ y_" << count1 + 1 << "_" << count + 1 << " " << pos_max1.y + 1 << ") (+ y_" << count2 + 1 << "_" << count + 1 << " " << pos_min2.y << "))" << endl;
              ofp << ")))" << endl << endl;
            }
          }
        }
      }
    }
  }
}
*/

/*
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
*/


void writeStateLoopConstraints(ofstream &ofp, workspace_t workspace)
{
  unsigned int count1, count2;

  for (count1 = 2; count1 <= workspace.number_of_points - 1; count1++)
  {
    for (count2 = 1; count2 <= workspace.number_of_robots; count2++)
    {
      ofp << "(assert (=> l_" << count1 << " (= x_" << count2 << "_" << count1 << " x_" << count2 << "_" << workspace.number_of_points  << ")))" << endl;
      ofp << "(assert (=> l_" << count1 << " (= y_" << count2 << "_" << count1 << " y_" << count2 << "_" << workspace.number_of_points << ")))" << endl;
      ofp << "(assert (=> l_" << count1 << " (= vel_i_" << count2 << "_" << count1 << " vel_f_" << count2 << "_" << workspace.number_of_points - 1 << ")))" << endl;
    }
  }
  ofp << endl;
}


void writeLoopOutputConstraints(ofstream &ofp, workspace_t workspace)
{
  unsigned int count2;

  for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
  {
      ofp << "(get-value (l_" << count2 + 1 << "))" << endl;
  }
  ofp << endl;
}


void writePropositionsOutputConstraints(ofstream &ofp, workspace_t workspace, prop_vec_t propositions)
{
  unsigned int count1, count2, count3;

  for (count1 = 0; count1 < propositions.size(); count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_robots; count2++)
    {
      for (count3 = 0; count3 < workspace.number_of_points; count3++)
      {
        ofp << "(get-value (r" << count2 + 1 << propositions[count1].name << "_" << count3 + 1 << "))" << endl;
      }
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < propositions.size(); count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_robots; count2++)
    {
      ofp << "(get-value (r" << count2 + 1 << propositions[count1].name << "))" << endl;
      ofp << "(get-value (assigned_r" << count2 + 1 <<"_"<< propositions[count1].name << "))" << endl;
    }
  }
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
      ofp << "(get-value (y_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;

  /*for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(get-value (y_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;
  */
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
      ofp << "(get-value (y_f_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;

  /*for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(get-value (y_f_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;
  */
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points - 1; count2++)
    {
      ofp << "(get-value (cost_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << "(get-value (total_cost))" << endl;
  for (count1 = 0; count1 < workspace.number_of_robots; count1++)
  {
	  ofp<<"(get-value (total_cost_"<<count1+1<<"))"<<endl;
  }
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
