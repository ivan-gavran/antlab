#include <iostream>
#include <fstream>
#include "primitive.h"
#include "readinputs.h"
#include "definepropositions.h"



void declarePropositions(ofstream &ofp, workspace_t workspace, prop_vec_t propositions)
{
  unsigned int count1, count2, count3;

  cout << endl;
  for (count1 = 0; count1 < propositions.size(); count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(declare-const " << propositions[count1].name << "_" << count2 + 1 << " Bool)" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < propositions.size(); count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_robots; count2++)
    {
      ofp << "(declare-const r" << count2 + 1 << propositions[count1].name << " Bool)" << endl;
    }
  }
  ofp << endl;    
  

  for (count1 = 0; count1 < propositions.size(); count1++)
  {
    for (count2 = 0; count2 < workspace.number_of_robots; count2++)
    {
      for (count3 = 0; count3 < workspace.number_of_points; count3++)
      {
        ofp << "(declare-const r" << count2 + 1 << propositions[count1].name << "_" << count3 + 1 << " Bool)" << endl;
      }
    }
  }
  ofp << endl;
}


void definePropositions(ofstream &ofp, workspace_t workspace, prop_vec_t propositions, vector< vector<string> > related_propositions)
{
  unsigned int count1, count2, count3, count4;
  prop_t prop;
  vector<string> rel_props;

  for (count1 = 0; count1 < propositions.size(); count1++)    
  {  
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      ofp << "(assert (=> " << propositions[count1].name << "_" << count2 + 1 << " (or";
      for (count3 = 0; count3 < workspace.number_of_robots; count3++)
      { 
        ofp << " r" << count3 + 1 << propositions[count1].name << "_" << count2 + 1;
      }
      ofp << ")))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < propositions.size(); count1++)
  {
    prop = propositions[count1];
    for (count2 = 0; count2 < workspace.number_of_points; count2++)
    {
      for (count3 = 0; count3 < workspace.number_of_robots; count3++)
      {
        ofp << "(assert (=> r" << count3 + 1 << prop.name << "_" << count2 + 1 << " (or";
        for (count4 = 0; count4 < prop.positions.size(); count4++)
        {
          ofp << " (and (= x_" << count3 + 1 << "_" << count2 + 1 << " " << prop.positions[count4].x << ")";
          ofp << " (= y_" << count3 + 1 << "_" << count2 + 1 << " " << prop.positions[count4].y << "))";
        }
        ofp << ")))" << endl;
      }
    }
  }
  ofp << endl; 

  for (count1 = 0; count1 < propositions.size(); count1++)
  {
    prop = propositions[count1];
    for (count2 = 0; count2 < workspace.number_of_robots; count2++)
    {
      ofp << "(assert (=> r" << count2 + 1 << prop.name << " (or";
      for (count3 = 0; count3 < workspace.number_of_points - 1; count3++)
      {
        ofp << " r" << count2 + 1 << prop.name << "_" << count3 + 1;
      }
      ofp << ")))" << endl;
    }
  }
  ofp << endl;

  for (count1 = 0; count1 < related_propositions.size(); count1++)
  {
    rel_props = related_propositions[count1];
    ofp << "(assert (or";
    for (count2 = 0; count2 < workspace.number_of_robots; count2++)
    {
      ofp << " (and";
      for (count3 = 0; count3 < rel_props.size(); count3++)
      {
        ofp << " r" << count2 + 1 << rel_props[count3];
      }
      ofp << ")";
    }
    ofp << "))" << endl;
  }
}

