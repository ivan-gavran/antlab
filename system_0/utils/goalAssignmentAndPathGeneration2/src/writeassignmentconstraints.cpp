#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"

using namespace std;


void declareVariables(ofstream &ofp, vector<vector <float> > start_goal_traj_cost, vector<vector <float> > goal_goal_traj_cost)
{
  unsigned int count1, count2;

  for (count1 = 1; count1 <= start_goal_traj_cost.size(); count1++)
  {
    for (count2 = 0; count2 <= goal_goal_traj_cost.size(); count2++)
    {
      ofp << "(declare-const n_" << count1 << "_" << count2 << " Int)" << endl;
    }
  }
  ofp << endl;
  
  for (count1 = 1; count1 <= start_goal_traj_cost.size(); count1++)
  {
    for (count2 = 1; count2 <= goal_goal_traj_cost.size(); count2++)
    {
      ofp << "(declare-const cost_" << count1  << "_" << count2  << " Real)" << endl;
    }
  }
  ofp << endl;
  
  ofp << "(declare-const total_cost Real)" << endl;
  ofp << endl;

}


void writeConstraints(ofstream &ofp, vector<vector <float> > start_goal_traj_cost, vector<vector <float> > goal_goal_traj_cost, string total_cost)
{
  unsigned int count1, count2, count3, count4;

  for (count1 = 1; count1 <= start_goal_traj_cost.size(); count1++)
  {
    ofp << "(assert (= n_" << count1 << "_" << 0 << " 0))" << endl;
  }
  ofp << endl;

  for (count1 = 1; count1 <= start_goal_traj_cost.size(); count1++)
  {
    for (count2 = 1; count2 <= goal_goal_traj_cost.size(); count2++)
    {
      ofp << "(assert (and (>= n_" << count1 << "_" << count2 << " 1) (<= n_" << count1 << "_" << count2 << " " << goal_goal_traj_cost.size() << ")))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 1; count1 <= start_goal_traj_cost.size(); count1++)
  {
    for (count2 = 0; count2 <= goal_goal_traj_cost.size() - 1; count2++)
    {
      ofp << "(assert (=> (= n_" << count1  << "_" << count2 << " n_" << count1 << "_" << count2 + 1 << ") (= cost_" << count1 << "_" << count2 + 1 << " 0)))" << endl;
      
      ofp << "(assert (=> (and (not (= n_" << count1 << "_" << count2 << " n_" << count1 << "_" << count2 + 1 << ")) (= n_" << count1 << "_" << count2 << " 0)) (and " << endl;
      for (count3 = 1; count3 <= goal_goal_traj_cost.size(); count3++)
      {
        ofp << "(=> (= n_" << count1 << "_" << count2 + 1 << " " << count3 << ") (= cost_" << count1 << "_" << count2 + 1 << " " << start_goal_traj_cost[count1-1][count3-1] << "))" << endl;
      }
      ofp << ")))" << endl;

      ofp << "(assert (=> (and (not (= n_" << count1 << "_" << count2 << " n_" << count1 << "_" << count2 + 1 << ")) (not (= n_" << count1 << "_" << count2 << " 0))) (and " << endl; 
      for (count3 = 1; count3 <= goal_goal_traj_cost.size(); count3++)
      {
        for (count4 = 1; count4 <= goal_goal_traj_cost.size(); count4++)
        {
          ofp << "(=> (and (= n_" << count1 << "_" << count2 << " " << count3 << ") (= n_" << count1 << "_" << count2 + 1 << " " << count4 << ")) (= cost_" << count1 << "_" << count2 + 1 << " " << goal_goal_traj_cost[count3-1][count4-1] << "))" << endl;
        }
      }
      ofp << ")))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 1; count1 <= goal_goal_traj_cost.size(); count1++)
  {
    ofp << "(assert (or";
    for (count2 = 1; count2 <= start_goal_traj_cost.size(); count2++)
    {
      for (count3 = 1; count3 <= goal_goal_traj_cost.size(); count3++)
      {
        ofp << " (= n_" << count2 << "_" << count3 << " " << count1 << ")"; 
      }
    }
    ofp << "))" << endl;
  }
  ofp << endl;

  ofp << "(assert (= total_cost (+";
  for (count1 = 1; count1 <= start_goal_traj_cost.size(); count1++)
  {
    for (count2 = 1; count2 <= goal_goal_traj_cost.size(); count2++)
    {
      ofp << " cost_" << count1 << "_" << count2;
    }
  }
  ofp << ")))" << endl;
  ofp << "(assert (< total_cost " << floatToReal(total_cost) << "))" << endl;
  ofp << endl;
}


void writeOutputConstraints(ofstream &ofp, vector<vector <float> > start_goal_traj_cost, vector<vector <float> > goal_goal_traj_cost)
{
  unsigned int count1, count2;

  for (count1 = 0; count1 < start_goal_traj_cost.size(); count1++)
  {
    for (count2 = 0; count2 < goal_goal_traj_cost.size(); count2++)
    {
      ofp << "(get-value (n_" << count1 + 1 << "_" << count2 + 1 << "))" << endl;
    }
  }
  ofp << endl;

  ofp << "(get-value (total_cost))" << endl;
}
