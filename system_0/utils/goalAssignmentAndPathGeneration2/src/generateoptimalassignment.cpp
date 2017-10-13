#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "primitive.h"
#include "writeassignmentconstraints.h"
#include "extractoutput.h"

using namespace std;


void generateZ3File(vector<vector <float> > start_goal_traj_cost, vector<vector <float> > goal_goal_traj_cost, string total_cost)
{
  ofstream ofp;
  ofp.open("constraints.smt2");
  
  declareVariables(ofp, start_goal_traj_cost, goal_goal_traj_cost);
  ofp << endl;

  writeConstraints(ofp, start_goal_traj_cost, goal_goal_traj_cost, total_cost);
  ofp << endl;

  ofp << "(check-sat)" << endl;
  //ofp << "(get-model)" << endl;
  ofp << endl;

  writeOutputConstraints(ofp, start_goal_traj_cost, goal_goal_traj_cost);
  ofp << endl;

  ofp.close();
}


void generateOptimalAssignment(vector<vector <float> > start_goal_traj_cost, vector<vector <float> > goal_goal_traj_cost)
{
  unsigned int count1, count2;
  float max_total_cost, min_total_cost, current_cost;
  float traj_cost;
 
  ostringstream ss;
  ifstream ifp;
  string line;
  string str;
  bool sat_flag;

  max_total_cost = 0;
  for (count1 = 0; count1 < start_goal_traj_cost.size(); count1++)
  {
    for (count2 = 0; count2 < goal_goal_traj_cost.size(); count2++)
    {
      max_total_cost = max_total_cost + start_goal_traj_cost[count1][count2];
    }
  }
  for (count1 = 0; count1 < goal_goal_traj_cost.size(); count1++)
  {
    for (count2 = 0; count2 < goal_goal_traj_cost.size(); count2++)
    {
      max_total_cost = max_total_cost + goal_goal_traj_cost[count1][count2];
    }
  }
  min_total_cost = 0;
  current_cost = (max_total_cost + min_total_cost) / 2;
  cout << endl;
  cout << "max_total_cost = " << max_total_cost << endl;
  cout << "min_total_cost = " << min_total_cost << endl;
  cout << "current_cost  = " << current_cost << endl;

  while (max_total_cost - min_total_cost > 1)
  { 
    ss.clear(); ss.str("");
    ss << current_cost;
    generateZ3File(start_goal_traj_cost, goal_goal_traj_cost, ss.str());
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
}


void printAssignment(pos_vec_t initpos, pos_vec_t finalpos, vector< vector <int> > & assignment)
{
  ofstream ofp1;
  string filename;
  int count1, count2;
  vector<int> tmp_int_vec;

  ofp1.open("assignment.txt");
  assignment.clear();
  for (count1 = 0; count1 < initpos.size(); count1++)
  {
    tmp_int_vec.clear();
    for (count2 = 0; count2 < finalpos.size(); count2++)
    {
      tmp_int_vec.push_back(0);
    }
    assignment.push_back(tmp_int_vec);
  }
  extractAssignmentInformation(assignment);

  for (count1 = 0; count1 < assignment.size(); count1++)
  {
    count2 = 1;
    while(count2 < assignment[count1].size())
    {
      if (assignment[count1][count2] == assignment[count1][count2-1])
      {
        assignment[count1].erase(assignment[count1].begin() + count2 - 1);
      }
      else
      {
        count2++;
      }
    }
  }

  cout << endl<< "Goal Locations:" << endl << endl;
  for (count1 = 0; count1 < assignment.size(); count1++)
  {
    cout << "Robot " << count1 + 1 << " : ";
    ofp1 << "Robot " << count1 + 1 << " : " << endl << endl;
    for (count2 = 0; count2 < assignment[count1].size(); count2++)
    {
      cout << assignment[count1][count2] << " ";
    }
    cout << endl;
    ofp1 << "Initial Location:" << endl;
    ofp1 << initpos[count1].x << " " << initpos[count1].y << endl << endl;
    ofp1 << "Goal Locations:" << endl;
    for (count2 = 0; count2 < assignment[count1].size(); count2++)
    {
      cout << finalpos[assignment[count1][count2]-1].x << " " << finalpos[assignment[count1][count2]-1].y << endl;
      ofp1 << finalpos[assignment[count1][count2]-1].x << " " << finalpos[assignment[count1][count2]-1].y << endl;
    }
    cout << endl;
    ofp1 << endl << endl;
  }
  cout << endl;
  ofp1.close();
}


void printFinalTrajectories(pos_vec_t initpos, pos_vec_t finalpos, vector< vector <int> > assignment)
{
  ofstream ofp1;
  ifstream ifp2;
  string filename1, filename2;
  int count1, count2;
  ostringstream os1, os2, os3, os4, os5, os6;
  string line;
 
  for (count1 = 0; count1 < assignment.size(); count1++)
  {
    os1.clear(); os1.str("");
    os2.clear(); os2.str("");
    os1 << initpos[count1].x;
    os2 << initpos[count1].y;
    filename1 = os1.str() + "_" + os2.str() + ".traj";
    ofp1.open(filename1.c_str());  
    for (count2 = 0; count2 < assignment[count1].size(); count2++)
    {
      os3.clear(); os3.str("");
      os4.clear(); os4.str("");
      if (count2 == 0)
      {
        os3 << initpos[count1].x;
        os4 << initpos[count1].y;
      }
      else
      {
        os3 << finalpos[assignment[count1][count2-1]-1].x;
        os4 << finalpos[assignment[count1][count2-1]-1].y;
      }
      os5.clear(); os5.str("");
      os6.clear(); os6.str("");
      os5 << finalpos[assignment[count1][count2]-1].x;
      os6 << finalpos[assignment[count1][count2]-1].y;
      filename2 = os3.str() + "_" + os4.str() + "_" + os5.str() + "_" + os6.str() + ".traj";
      ifp2.open(filename2.c_str());
      if (count2 > 0)
        getline(ifp2, line);
      while (getline(ifp2, line))
      {
        ofp1 << line << endl;
      }
      ifp2.close();
    }
    ofp1.close();
  }
}
