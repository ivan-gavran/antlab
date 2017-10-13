#include <fstream>
#include <vector>

using namespace std;

void declareVariables(ofstream & , vector<vector <float> > , vector<vector <float> > );
void writeConstraints(ofstream & , vector<vector <float> > , vector<vector <float> > , string );
void writeOutputConstraints(ofstream & , vector<vector <float> > , vector<vector <float> > );
