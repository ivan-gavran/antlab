#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <sys/time.h>
#include <exception>
#include "primitive.h"
#include "readinputs.h"
#include "definepropositions.h"
#include "writeconstraints.h"
#include "extractoutput.h"
#include "../ltlparser/generateloopconstraints.h"

const unsigned int max_traj_length = 25;

void generateZ3File(prim_vec_t , prim_cost_t, pos_vec_t , workspace_t , prop_vec_t, vector <vector<string> > );


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

  ofstream ofp, ofpOptimization;
  ofp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/result", fstream::app);
  ofp << hr << "h " << min << "m " << (((sec - int(sec)) > 0.5) ? (int(sec) + 1) : int(sec)) << "s" << endl << endl;
  ofp.close();
}



void generateZ3File(prim_vec_t primitives, prim_cost_t prim_cost, pos_vec_t obstacles, workspace_t workspace, prop_vec_t propositions, vector <vector<string> > related_propositions)
{
  ofstream ofp, ofpOptimization;
  ifstream ofpr;
  char command[1000];
  string line;
  cout<<"arg:::: "<<workspace.number_of_points-1<<endl;
  sprintf(command, "src/navigation-indigo-devel/ltl_multi_planner/utils/examples/constraints_generator src/navigation-indigo-devel/ltl_multi_planner/utils/examples/output %d", workspace.number_of_points - 1);
  try
  {
	  system(command);
  }
  catch(exception& e)
  {
	  cout<<"constraints generator problem"<<endl;
	  cout<<e.what()<<endl;
  }
  cout<<"generateZ3:  constraints_generator done!!!!!!!!!!!!!!!"<<endl;
  cout<<"still some writing"<<endl;
  
  
  
  ofp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/constraints.smt2");
  
  if(ofp.is_open())
	  cout<<"file is really open"<<endl;
  else
	  cout<<"file is not open"<<endl;
  cout<<"generateZ3:  constraints file opened"<<endl;
  /* Declare the variables */
  declareVariables(ofp, workspace);
  cout<<"variables declared"<<endl;
  //ofp << endl << endl;

  //declareLastVariables(ofp, workspace);
  //ofp << endl << endl;

  ofpr.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/ltlvariables.txt");
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
  cout<<"initial constraints written"<<endl;

  writeObstacleConstraints(ofp, obstacles, workspace);
  ofp << endl;
  cout<<"obstacle constraints written"<<endl;
  writeTransitionConstraints(ofp, primitives, obstacles, workspace);
  ofp << endl;
  cout<<"transition constraints written"<<endl;


  writeLoopDependentCostConstraint(ofp, primitives, obstacles, workspace);
  //writeCollisionAvoidanceConstraints2(ofp, primitives, workspace);
  //ofp << endl;

  //writeDistanceConstraints(ofp, workspace);
  //ofp << endl;

  writeCostConstraint(ofp, workspace, prim_cost);
  ofp << endl;

  cout<<"cost constraints written"<<endl;


  /* Write the specification constraints */
  definePropositions(ofp, workspace, propositions, related_propositions);
  ofp << endl << endl;
  cout<<"propositions defined"<<endl;
  ofpr.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/ltlconstraints.txt");
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



int generateTrajectory(prim_vec_t primitives, prim_cost_t prim_cost, pos_vec_t obstacles, workspace_t workspace, prop_vec_t propositions, vector < vector<string> > related_propositions, map<string, vector<position> > propositionMap)
{
	cout<<"in generate trajectory"<<endl;
	cout<<"propositions size"<<endl;
	cout<<propositions.size()<<endl;
	for(int i = 0; i < propositions.size(); ++i){
		cout<<"prop: "<<propositions[i].name<<endl;
		for (int j = 0; j < propositions[i].positions.size(); ++j)
		{
			cout<<propositions[i].positions[j].x<<" "<<propositions[i].positions[j].y<<endl;
		}
	}
  ifstream ifp;
  string line;
  unsigned int count;
  char buffer[100];
  float cost;
  float max_total_cost, min_total_cost;

  struct timeval tm;
  double wcts, wcte;

  ofstream ofp, ofpOptimization;

  count = 2;
  while (1)
  {
    gettimeofday( &tm, NULL );
    wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;

    workspace.number_of_points = count;
    cout<<"count = "<<count<<endl;
    cout<<"workspace.number_of_robots = "<<workspace.number_of_robots<<endl;
    cout<<"prim_cost.max_cost = "<<prim_cost.max_cost<<endl;
    cost = count * workspace.number_of_robots *  prim_cost.max_cost;
    cout<<"cost: "<<cost<<endl;
    sprintf(buffer, "%f", cost);
    cout << "Cost =" << cost << endl;
    workspace.total_cost = string(buffer);
    cout<<"what do I know about workspace"<<endl;
    cout<<workspace.number_of_points<<" "<<workspace.number_of_robots<<" "<<workspace.total_cost<<endl;
    generateZ3File(primitives, prim_cost, obstacles, workspace, propositions, related_propositions);
    
    //cout << endl << "Timeout is set at 3600s." << endl;
    //system("timeout 7200s z3 constraints.smt2 > z3_output");
    
    system("timeout 240 z3 src/navigation-indigo-devel/ltl_multi_planner/utils/examples/constraints.smt2 > src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output");
    string z3ResultFilename = "src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output";
    string assignmentOutputFilename = "src/multiple_robots_stage/static_files_folder/assignmentFile.txt";
      //ofp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/result");
    extractAssignmentInformation(propositionMap, assignmentOutputFilename, z3ResultFilename);
    ifp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output");
    if (ifp.is_open())
    {
      getline(ifp, line);
      ifp.close();
    }

    cout << "$$$$$$$$ " << count << " " << line << endl;
//    if (count == 15)
//    	throw;
    if (line == "unsat")
    {
      cout<<"unsat on count = "<<count<<endl;
      count = count + 1;
      if (count > max_traj_length)
      {
        cout << "Trajectory does not exist.." << endl;
        exit(0);
      }
    }
    else if (line == "sat")
    {
      system("cp  src/navigation-indigo-devel/ltl_multi_planner/utils/examples/constraints.smt2  src/navigation-indigo-devel/ltl_multi_planner/utils/examples/constraintsSaved.smt2");
      system("cp src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output_sat");
      gettimeofday( &tm, NULL );
      wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
      cout<<"in generate trajectory:::: reached"<<endl;
      ofp.open("result");
      ofp << "Trajectory Length = " << count << endl << endl;
      ofp.close();

      ofp.open("result", fstream::app);
      ofp << "Final Iteration Time = ";

      printTimeDifference(wcts, wcte);
      ofp.close();
//      ofpOptimization.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/optimizationResults", fstream::app);
//      ofpOptimization<<line<<"\t";
//      ofpOptimization.close();

      break;
    }
    else
    {
      cout << "unknown output from z3.." << endl;
      count = count + 1;
      if (count > max_traj_length)
      {
        exit(0);
      }
    }
    if (count > max_traj_length)
      break;
  }
  system("perl src/navigation-indigo-devel/ltl_multi_planner/utils/examples/processoutputfile.pl");
  system("mv src/navigation-indigo-devel/ltl_multi_planner/utils/examples/planner_output src/navigation-indigo-devel/ltl_multi_planner/utils/examples/plan_noopt");

//  max_total_cost = count * workspace.number_of_robots * prim_cost.max_cost;
//  min_total_cost = count * workspace.number_of_robots * prim_cost.min_cost;
//  cout << "max_total_cost = " << max_total_cost << endl;
//  cout << "min_total_cost = " << min_total_cost << endl;


  ofp.open("result", fstream::app);
//  ofp << "max_total_cost = " << max_total_cost << endl;
//  ofp << "min_total_cost = " << min_total_cost << endl;
  //ofp << "Cost Before Optimization = " << extractTrajectoryCostInformation() << endl << endl;
  ofp.close();
  
//  cout << "Cost  = " << extractTrajectoryCostInformation() << endl << endl;
  

  return count;
}


void optimizeTrajectory(prim_vec_t primitives, prim_cost_t prim_cost, pos_vec_t obstacles, workspace_t workspace, prop_vec_t propositions, vector < vector<string> > related_propositions, int trajectory_length, map<string, vector<position> > propositionMap)
{
  float max_total_cost, min_total_cost, current_cost;
  ifstream ifp;
  string line;
  char buffer[100];
  int allowedDifferenceFactor = 20;
  ofstream ofp, ofpOptimization;
  struct timeval tm;
  double wcts, wcte;


  workspace.number_of_points = trajectory_length;

  //max_total_cost = extractTrajectoryCostInformation("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output");
  system("python ../utils/measureCost.py");
   ifp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/costData");
   getline(ifp, line);
   cout<<"cost read: "<<line<<endl;
   max_total_cost = atof(line.c_str());
   ifp.close();
  cout<<"found max_total_cost to be "<<max_total_cost<<"**************"<<endl;
  ofpOptimization.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/optimizationResults", fstream::app);
  ofpOptimization<<"starting cost\t"<<max_total_cost<<endl;
  ofpOptimization.close();
  //max_total_cost = trajectory_length * workspace.number_of_robots * prim_cost.max_cost;
  min_total_cost = trajectory_length * workspace.number_of_robots * prim_cost.min_cost;
  current_cost = (max_total_cost + min_total_cost) / 2;

  cout << "min2_min_cost_diff = " << prim_cost.min2_min_cost_diff << endl << endl;

  cout << "max_total_cost new = " << max_total_cost << endl;
  cout << "min_total_cost = " << min_total_cost << endl;
  cout << "current_cost  = " << current_cost << endl;


  //system("mv z3_output z3_output_sat");
  system("mv src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output_sat");
  system("mv src/multiple_robots_stage/static_files_folder/assignmentFile.txt src/multiple_robots_stage/static_files_folder/assignmentFileSat.txt");

  while (max_total_cost - min_total_cost > allowedDifferenceFactor)
  {
	  cout <<"optimizing trajectory with diff factor "<<allowedDifferenceFactor<<endl;
    sprintf(buffer, "%f", current_cost);
    workspace.total_cost = string(buffer);ofpOptimization.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/optimizationResults", fstream::app);
          ofpOptimization<<current_cost<<"\t"<<max_total_cost<<endl;
          ofpOptimization.close();
    gettimeofday( &tm, NULL );
    wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;

    generateZ3File(primitives, prim_cost, obstacles, workspace, propositions, related_propositions);
    cout << endl << "optimization: Timeout is set at 7200s." << endl;
    system("timeout 240 z3 src/navigation-indigo-devel/ltl_multi_planner/utils/examples/constraints.smt2 > src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output");
    cout<<"z3 ran"<<endl;
    string z3ResultFilename = "src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output";
    string assignmentOutputFilename = "src/multiple_robots_stage/static_files_folder/assignmentFile.txt";
      //ofp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/result");
    extractAssignmentInformation(propositionMap, assignmentOutputFilename, z3ResultFilename);


//    system("time z3 constraints.smt2 > z3_output");
//
//    ifp.open("z3_output");
    ifp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output");
    getline(ifp, line);
    ifp.close();
    cout << "$$$$$$$$ " << trajectory_length << " " << line << endl;

    if (line == "unsat")
    {
      min_total_cost = current_cost;
//      ofpOptimization.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/optimizationResults", fstream::app);
//      ofpOptimization<<"remain\t";
//      ofpOptimization.close();
    }
    else if (line == "sat")
    {
      //max_total_cost = extractTrajectoryCostInformation("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output");
      //max_total_cost = current_cost;
    	system("python ../utils/measureCost.py");
    	 ifp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/costData");
    	  getline(ifp, line);
    	  cout<<"cost read: "<<line<<endl;
    	  max_total_cost = atof(line.c_str());
    	  ifp.close();
    	  ofpOptimization.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/optimizationResults", fstream::app);
    	  ofpOptimization<<"cost reached: "<<max_total_cost<<endl;
    	  ofpOptimization.close();


      //system("mv z3_output z3_output_sat");
      system("mv src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output_sat");
      system("mv src/multiple_robots_stage/static_files_folder/assignmentFile.txt src/multiple_robots_stage/static_files_folder/assignmentFileSat.txt");
    }
    else
    {
      cout << "unknown output from z3.." << endl;
      min_total_cost = current_cost;
    }
    gettimeofday( &tm, NULL );
    wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
    current_cost = (max_total_cost + min_total_cost) / 2;
    ofpOptimization.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/optimizationResults", fstream::app);
          ofpOptimization<<"time needed: "<<wcte-wcts<<endl;
          ofpOptimization.close();
    cout << "max_total_cost = " << max_total_cost << endl;
    cout << "min_total_cost = " << min_total_cost << endl;
    cout << "current_cost  = " << current_cost << endl;
  }
  
  ofpOptimization.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/optimizationResults", fstream::app);
  ofpOptimization<<"------"<<endl;
  ofpOptimization.close();


//  system("mv z3_output_sat z3_output");
//  system("perl processoutputfile.pl");
//  system("mv planner_output plan_opt");
  system("mv src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output_sat src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output");
  system("perl src/navigation-indigo-devel/ltl_multi_planner/utils/examples/processoutputfile.pl");
  system("mv src/navigation-indigo-devel/ltl_multi_planner/utils/examples/planner_output src/navigation-indigo-devel/ltl_multi_planner/utils/examples/plan_noopt");
  system("mv src/multiple_robots_stage/static_files_folder/assignmentFileSat.txt src/multiple_robots_stage/static_files_folder/assignmentFile.txt");

  /*ofp.open("result", fstream::app);
  ofp << "Cost After Optimization = " << extractTrajectoryCostInformation() << endl << endl;
  ofp.close();
  cout << "Cost  = " << extractTrajectoryCostInformation() << endl << endl;
  */
}
