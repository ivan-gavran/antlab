#include <ltl_multi_planner/primitive.h>
#include <ltl_multi_planner/readinputs.h>
float extractTrajectoryCostInformation(string output_filename);
void extractTrajectoryVelocityInformation(string , vector< vector<int> > & );
void extractTrajectoryInformation(int , vector<int> & , vector<int> & , vector<int> &, string output_filename );
map<int, vector<position> > extractAssignments(string assignmentFilename);
