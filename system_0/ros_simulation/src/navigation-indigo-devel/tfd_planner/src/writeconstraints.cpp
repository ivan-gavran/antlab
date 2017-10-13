#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <tfd_planner/primitive.h>
#include <tfd_planner/readinputs.h>
#include <tfd_planner/writeconstraints.h>
#include <map>
#include <cmath>





void declareDomainFile(ofstream &ofp, workspace_t workspace)
{

	ofp<<"(define (domain antlabWarehouse)\n";
	ofp<<"(:requirements :adl :durative-actions)"<<endl;
	ofp<<"\t(:types robot location)\n";

	//predicates
	ofp<<"\t(:predicates\n\t\t (at ?r - robot ?l - location)\n\t\t(can-traverse ?l1 - location ?l2 - location)\n\t\t(visited ?l - location)\n\t)"<<endl;

	//functions
	ofp<<"\t(:functions\n\t\t(total-cost)\n\t\t(traversal-cost ?lStart - location ?lGoal - location)\n\t)"<<endl;

	//actions
	ofp<<"\t(:durative-action move"<<endl;
	ofp<<"\t\t:parameters  (?r - robot ?from - location ?to - location)"<<endl;
	ofp<<"\t\t:duration (= ?duration (traversal-cost ?from ?to))"<<endl;
	ofp<<"\t\t:condition (and"<<endl;
	ofp<<"\t\t\t(at start"<<endl;
	ofp<<"\t\t\t\t(and"<<endl;
	ofp<<"\t\t\t\t\t(can-traverse ?from ?to)"<<endl;
	ofp<<"\t\t\t\t\t(at ?r ?from)"<<endl;
	ofp<<"\t\t\t\t)"<<endl;
	ofp<<"\t\t\t)"<<endl;
	ofp<<"\t\t)"<<endl;
	ofp<<"\t\t:effect (and"<<endl;
	ofp<<"\t\t\t(at start"<<endl;
	ofp<<"\t\t\t\t(and"<<endl;
	ofp<<"\t\t\t\t\t(not (at ?r ?from))"<<endl;
	ofp<<"\t\t\t\t)"<<endl;
	ofp<<"\t\t\t)"<<endl;
	ofp<<"\t\t\t(at end"<<endl;
	ofp<<"\t\t\t\t(and"<<endl;
	ofp<<"\t\t\t\t\t(at ?r ?to)"<<endl;
	ofp<<"\t\t\t\t\t(visited ?to)"<<endl;
	ofp<<"\t\t\t\t\t(increase (total-cost)(traversal-cost ?from ?to))"<<endl;
	ofp<<"\t\t\t\t)"<<endl;
	ofp<<"\t\t\t)"<<endl;
	ofp<<"\t\t)"<<endl;
	ofp<<"\t)"<<endl;

	//closing the domain definition
	ofp<<")";

}

void writeRobots(ofstream &ofp, workspace_t workspace)
{
	for (int i = 0; i < workspace.number_of_robots; ++i)
		{
			ofp<<"\t\tr"<<i<<endl;
		}
		ofp<<"\t\t- robot"<<endl;
}
void writeInitialRobotLocations(ofstream &ofp, workspace_t workspace)
{
	for (int i = 0; i < workspace.number_of_robots; ++i)
	{

		ofp<<"\t\t(at r"<<i<<" location_"<<workspace.pos_start[i].x<<"_"<<workspace.pos_start[i].y<<")"<<endl;
		ofp<<"\t\t(visited location_"<<workspace.pos_start[i].x<<"_"<<workspace.pos_start[i].y<<")"<<endl;

	}

}

void writeLocations(ofstream &ofp, workspace_t workspace)
{
	//vector<string> locations;
	for (int i = 0; i < workspace.length_x; ++i)
	{
		for (int j = 0; j < workspace.length_y; ++j)
		{
			// 1-base counting to respect the existing conventions (from implan)
			string loc = "location_" + tostr(i+1)+"_"+tostr(j+1);
			ofp<<"\t\t"<<loc<<endl;
			//locations.append(loc);
		}
	}
	ofp<<"\t\t - location"<<endl;
}

void writeGoal(ofstream &ofp, workspace_t workspace)
{
	ofp<<"\t(:goal"<<endl;
	ofp<<"\t\t(and"<<endl;
	for(int i = 0; i < workspace.pos_end.size(); ++i)
	{
		position p = workspace.pos_end[i];

		string loc ="location_" + tostr(p.x)+"_"+tostr(p.y);
		ofp<<"\t\t\t(visited "<<loc<<")"<<endl;

	}
	ofp<<"\t\t)"<<endl;
	ofp<<"\t)"<<endl;
}

void writeOptimizationCriterion(ofstream &ofp, workspace_t workspace)
{
	ofp<<"\t(:metric\n\t\tminimize (total-cost)\n\t)"<<endl;
}

void writeTraversingConstraints(ofstream &ofp, workspace_t workspace, map<string, int> alwaysEventuallyTraversingCost, set<position> obstacles)
{
	int safetyBelt = 3;
	//bool interesting = false;
	for(int i = 0; i < workspace.length_x; ++i)
	{
		for (int j = 0; j < workspace.length_y; ++j)
		{

			position currentLocation;

			currentLocation.x = i+1;
			currentLocation.y = j+1;
			if (obstacles.count(currentLocation) != 0)
			{
				continue;
			}
			int traversal_cost;
			string loc = "location_" + tostr(i+1)+"_"+tostr(j+1);

			for (int k = -1; k <= 1; ++k)
			{
				for (int l = -1; l <= 1; ++l)
				{
					int closeToObstacleCost = 0;
					if (abs(k+l) != 1 )
						continue;
					if ( i+k+1 == 0 || j+l+1 == 0 || i+k+1 == workspace.length_x+1 || j+l+1 == workspace.length_y+1 )
						continue;
					string neighbouring_loc = "location_" + tostr(i+k+1)+"_"+tostr(j+l+1);
					position neighbouringPosition;
					neighbouringPosition.x = i+k+1;
					neighbouringPosition.y = j+l+1;
					//interesting = false;
//					if (neighbouringPosition.x == 63 && neighbouringPosition.y== 18){
//						interesting = true;
//						cout<<"current position "<<currentLocation.x<<" "<<currentLocation.y<<endl;
//					}
					if (obstacles.count(neighbouringPosition) != 0){
//						if (interesting)
//							cout<<"our position was in obstacles"<<endl;
						continue;
					}
					if (alwaysEventuallyTraversingCost.count(neighbouring_loc) > 0)
					{
						traversal_cost = alwaysEventuallyTraversingCost[neighbouring_loc];
					}
					else
					{
						traversal_cost = 1;
					}
					ofp<<"\t\t(can-traverse "<<loc<<" "<<neighbouring_loc<<")"<<endl;
					ofp<<"\t\t(= (traversal-cost "<<loc<<" "<<neighbouring_loc<<") "<<traversal_cost<<")"<<endl;
				}
			}



		}
	}
	ofp<<")"<<endl;
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
