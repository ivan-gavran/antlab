#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "primitive.h"
#include "readinputs.h"

//#include "writeconstraints.h"
//#include "extractoutput.h"
#include "generatetrajectory.h"
//#include "../ltlparser/generateloopconstraints.h"
//#include "definepropositions.h"

using namespace std;

string static_folder = "src/multiple_robots_stage/static_files_folder/";
template <typename T> string tostr(const T& t)
{
  ostringstream os;
  os << t;
  return os.str();
}

void extractAssignmentInformation(map<string, vector<position> > propositionMap, string output_filename, string input_filename)
{
	  string line;
	  int location, location2;
	ifstream ifp;
	ofstream ofp;
	string str;
	ifp.open(input_filename.c_str());
	getline(ifp, line);
	ofp.open(output_filename.c_str());
	if (ifp.is_open())
	{
		while(getline(ifp, line))
		{

			location = line.find("assigned_r");
			if (location != -1)

			{
				int locationOfTrue = line.find("true");
				if (locationOfTrue == -1)
						continue;


				str = line.substr(location+10);
				cout<<"str is currently "<<str<<endl;
				location2 = str.find("_");
				string robotId = str.substr(0, location2);
				cout<<"++++++++++++"<<robotId<<endl;
				int numericRobotId = atoi(robotId.c_str());
				numericRobotId -= 1;
				string newRobotId = tostr(numericRobotId);
				ofp<<newRobotId<<" ";
				str = str.substr(location2+1);
				int locationOfBlank = str.find(" ");
				string propName = str.substr(0, locationOfBlank);
				cout<<"prop name is "<<propName<<endl;
				ofp<<propositionMap[propName][0].x<<" "<<propositionMap[propName][0].y<<endl;
				cout<<propositionMap[propName][0].x<<" "<<propositionMap[propName][0].y<<endl;
			}
		}
	}
	ifp.close();
	ofp.close();
}

int main ()
{
  prim_vec_t primitives;
  pos_vec_t obstacles;
  workspace_t workspace;
  prim_cost_t prim_cost;
  prop_vec_t propositions;
  map<string, vector<position> > propositionMap;
  vector < vector<string> > related_propositions;
  char command[100];
  int trajectory_length;

  readPrimitives(primitives);
  writePrimitives(primitives);
  
  

  getPrimitiveCost(primitives, prim_cost);
  //writePrimitiveCost(prim_cost);

  readObstacles(obstacles);
  //writeObstacles(obstacles);

  readWorkspace(workspace);
  writeWorkspace(workspace);

  propositionMap = readPropositions(propositions);

  writePropositions(propositions);


  system("cp src/multiple_robots_stage/static_files_folder/ltl_input src/multiple_robots_stage/static_files_folder/saved_ltl_input");
  system("cp src/multiple_robots_stage/static_files_folder/ltl_workspace.txt src/multiple_robots_stage/static_files_folder/saved_ltl_workspace.txt");
  system("cp src/multiple_robots_stage/static_files_folder/propositions_ltl_planner src/multiple_robots_stage/static_files_folder/saved_propositions_ltl_planner");
  system("cp src/multiple_robots_stage/static_files_folder/related_propositions_ltl_planner src/multiple_robots_stage/static_files_folder/saved_related_propositions_ltl_planner");
  readRelatedPropositions(related_propositions);
  cout<<"size of related props: "<<related_propositions.size()<<endl;
  writeRelatedPropositions(related_propositions);
  string inputFile = static_folder+"ltl_input";
  string commandToRun = "time src/navigation-indigo-devel/ltl_multi_planner/utils/examples/formula_simplifier "+inputFile;
  //sprintf(command, "time src/navigation-indigo-devel/ltl_multi_planner/utils/examples/formula_simplifier input");
  system(commandToRun.c_str());

  struct timeval tm;
  double wcts, wcte;
  ofstream ofp;
  
  

  gettimeofday( &tm, NULL );
  wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  trajectory_length = generateTrajectory(primitives, prim_cost, obstacles, workspace, propositions, related_propositions, propositionMap);
  gettimeofday( &tm, NULL );
  wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  ofp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/result", fstream::app);
  ofp << "Total Time Before Optimization = ";
  ofp.close();
  printTimeDifference(wcts, wcte);
  ofp.open("../staticFilesTesting/ltlResults", fstream::app);
  ofp<<"\nTime before optimization\t"<<wcte-wcts<<"\t";
  ofp.close();
  string z3ResultFilename = "src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output";
  string assignmentOutputFilename = "src/multiple_robots_stage/static_files_folder/assignmentFile.txt";
  //ofp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/result");
  extractAssignmentInformation(propositionMap, assignmentOutputFilename, z3ResultFilename);
  //ofp.close();

  cout<<"we reached this place----"<<endl;
  
  gettimeofday( &tm, NULL );
  wcts = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  optimizeTrajectory(primitives, prim_cost, obstacles, workspace, propositions, related_propositions, trajectory_length, propositionMap);
  cout<<"optimization finished -------------------------"<<endl;
  gettimeofday( &tm, NULL );
  wcte = (double)tm.tv_sec + (double)tm.tv_usec * .000001;
  ofp.open("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/result", fstream::app);
  ofp << "Total Time For Optimization = ";
  ofp.close();

  printTimeDifference(wcts, wcte);
  ofp.open("../staticFilesTesting/ltlResults", fstream::app);
  ofp<<"Time for optimization\t"<<wcte-wcts;
  ofp.close();

}


