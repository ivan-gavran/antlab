#include <iostream>
#include "generateoptimaltrajectories.h"
#include "generateoptimalassignment.h"



int main ()
{
  prim_vec_t primitives;
  dimension_t dimension;
  pos_vec_t obstacles;
  pos_vec_t initpos, finalpos;
  int max_length;
  //clock_t start_time;
  vector< vector<int> > start_goal_traj_length;
  vector< vector<int> > goal_goal_traj_length;
  vector< vector<float> > start_goal_traj_cost;
  vector< vector<float> > goal_goal_traj_cost;
  vector< vector<int> > assignment;


  cout << endl << endl;
  cout << "*** Generate Trajectories ***" << endl << endl;

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

  //start_time = clock();
  generateAllTrajectories(primitives, dimension, obstacles, initpos, finalpos, max_length, start_goal_traj_length, goal_goal_traj_length, start_goal_traj_cost, goal_goal_traj_cost);
  //cout << double( clock() - start_time ) / (double)CLOCKS_PER_SEC << " seconds." << endl;

  printTrajectoryInformation(start_goal_traj_length, goal_goal_traj_length, start_goal_traj_cost, goal_goal_traj_cost);

  cout << endl << endl;
  cout << "*** Generate Assignments ***" << endl << endl;
  
  generateOptimalAssignment(start_goal_traj_cost, goal_goal_traj_cost);

  printAssignment(initpos, finalpos, assignment);
  
  printFinalTrajectories(initpos, finalpos, assignment);

  return 0;
}
