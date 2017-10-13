#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "../utils/primitive.h"
#include "../utils/readinputs.h"
//#include "../utils/writeconstraints.h"
//#include "../utils/extractoutput.h"
#include "../utils/generatetrajectory.h"
//#include "../ltlparser/generateloopconstraints.h"
//#include "definepropositions.h"

using namespace std;

//const unsigned int max_traj_length = 30;

/*
void printTimeDifference(double wcts, double wcte) 
{
  double duration;
  int hr, min;
  double sec;

  duration = wcte - wcts;
  hr = duration / 3600;
  min = (duration / 60) - (hr * 60) ;
  sec = duration - hr * 3600 - min * 60;
  cout << endl << duration << "s" << endl;
  cout << endl << hr << "h " << min << "m " << (((sec - int(sec)) > 0.5) ? (int(sec) + 1) : int(sec)) << "s" << endl << endl;

  ofstream ofp;
  ofp.open("result", fstream::app); 
  ofp << hr << "h " << min << "m " << (((sec - int(sec)) > 0.5) ? (int(sec) + 1) : int(sec)) << "s" << endl << endl;
  ofp.close();
}
*/

/*
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
    }
  }
  ofp << endl;
}
*/

/*
void generateZ3File(prim_vec_t primitives, prim_cost_t prim_cost, pos_vec_t obstacles, workspace_t workspace, prop_vec_t propositions, vector <vector<string> > related_propositions)
{
  ofstream ofp;
  ifstream ofpr;
  char command[100];
  string line;

  sprintf(command, "time ./constraints_generator output %d", workspace.number_of_points - 1);
  system(command);

  ofp.open("constraints.smt2");

  /* Declare the variables */
  declareVariables(ofp, workspace);
  ofp << endl << endl;

  //declareLastVariables(ofp, workspace);
  //ofp << endl << endl;

  ofpr.open("ltlvariables.txt");
  if (ofpr.is_open())
  {
    while(std::getline(ofpr, line))
    {
      std::istringstream iss(line);
      ofp << line << endl;
    }
  }
  ofpr.close();
  ofp << endl << endl;

  declareLoopVariables(ofp, workspace.number_of_points);
  
  declarePropositions(ofp, workspace, propositions);
  
  
  /* Write the General Constraints */
  writeInitialLocationConstraints(ofp, workspace);
  ofp << endl;

  writeObstacleConstraints(ofp, obstacles, workspace);
  ofp << endl;

  writeTransitionConstraints(ofp, primitives, obstacles, workspace);
  ofp << endl;

  //writeCollisionAvoidanceConstraints2(ofp, primitives, workspace);
  //ofp << endl;

  //writeDistanceConstraints(ofp, workspace);
  //ofp << endl;

  writeCostConstraint(ofp, workspace, prim_cost);
  ofp << endl;


  /* Write the specification constraints */
  definePropositions(ofp, workspace, propositions, related_propositions);
  ofp << endl << endl;
  
  ofpr.open("ltlconstraints.txt");
  if (ofpr.is_open())
  {
    while(std::getline(ofpr, line))
    {
      std::istringstream iss(line);
      ofp << line << endl;
    }
  }
  ofpr.close();
  ofp << endl << endl;

  writeLoopConstraints(ofp, workspace.number_of_points);
  writeStateLoopConstraints(ofp, workspace);

  ofp << "(check-sat)" << endl;
  //ofp << "(get-model)" << endl;
  writeOutputConstraints(ofp, workspace);
  writePropositionsOutputConstraints(ofp, workspace, propositions);
  writeLoopOutputConstraints(ofp, workspace);

  ofp.close();
}
*/


int main ()
{
  prim_vec_t primitives;
  pos_vec_t obstacles;
  workspace_t workspace;
  prim_cost_t prim_cost;
  prop_vec_t propositions;
  vector < vector<string> > related_propositions;
  char command[100];
  int trajectory_length;

  readPrimitives(primitives);
  //writePrimitives(primitives);

  getPrimitiveCost(primitives, prim_cost);
  //writePrimitiveCost(prim_cost);

  readObstacles(obstacles);
  //writeObstacles(obstacles);

  readWorkspace(workspace);
  //writeWorkspace(workspace);

  readPropositions(propositions);
  writePropositions(propositions);

  readRelatedPropositions(related_propositions);
  writeRelatedPropositions(related_propositions);

  sprintf(command, "time ./formula_simplifier input");
  system(command);

  struct timeval tm;
  double wcts, wcte;
  ofstream ofp;


  gettimeofday( &tm, NULL );
  wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  trajectory_length = generateTrajectory(primitives, prim_cost, obstacles, workspace, propositions, related_propositions);
  gettimeofday( &tm, NULL );
  wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  ofp.open("result", fstream::app);
  ofp << "Total Time Before Optimization = ";
  ofp.close();
  printTimeDifference(wcts, wcte);

  /*
  gettimeofday( &tm, NULL );
  wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  optimizeTrajectory(primitives, prim_cost, obstacles, workspace, propositions, related_propositions, trajectory_length);
  gettimeofday( &tm, NULL );
  wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  ofp.open("result", fstream::app);
  ofp << "Total Time For Optimization = ";
  ofp.close();
  printTimeDifference(wcts, wcte); 
  */
}
