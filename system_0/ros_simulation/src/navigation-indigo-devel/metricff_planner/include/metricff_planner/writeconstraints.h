#include<map>
#include<set>
void declareDomainFile(ofstream & , workspace_t );
void writeInitialRobotLocations(ofstream & , workspace_t );
void writeRobots(ofstream &ofp, workspace_t workspace);
void writeLocations(ofstream &, workspace_t);
void writeInitialLocationConstraints(ofstream & , workspace_t );
void writeOptimizationCriterion(ofstream & , workspace_t );
void writeObstacleConstraints(ofstream & , pos_vec_t , workspace_t );
void writeTraversingConstraints(ofstream &ofp, workspace_t workspace, map<string, int> alwaysEventuallyTraversingCost, set<position> obstacles);
void writeCostConstraint(ofstream & , workspace_t );
void writeGoal(ofstream & , workspace_t );
void writeAlwaysEventuallyConstraints(ofstream &ofp, vector<position_with_cost> alwaysEventuallyFreeConstraints );
string floatToReal(string );
template <typename T> string tostr(const T& );
