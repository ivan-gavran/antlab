#include <iostream>
#include <fstream>
#include "../ltl/primitive.h"
#include "../ltl/readinputs.h"
#include "generateloopconstraints.h"


void declareLoopVariables(ofstream & ofp, unsigned int length)
{
  unsigned int count;

  for (count = 0; count <= length; count++)
  {
    ofp << "(declare-const l_" << count << " Bool)" << endl;
  }
  for (count = 0; count <= length + 1; count++)
  {
    ofp << "(declare-const inloop_" << count << " Bool)" << endl;
  }
  ofp << "(declare-const loopexists Bool)" << endl;;
}


void writeLoopConstraints(ofstream & ofp, unsigned int length)
{
  unsigned int count;

  ofp << "(assert (= l_1 false))" << endl;
  ofp << "(assert (= inloop_1 false))" << endl;

  for (count = 2; count <= length - 1; count++)
  {
    ofp << "(assert (= inloop_" << count << " (or inloop_" << count - 1 << " l_" << count << ")))" << endl;
    ofp << "(assert (=> inloop_" << count - 1 << " (not l_" << count << ")))" << endl;
  }
  ofp << endl;
  ofp << "(assert (= loopexists inloop_" << length - 1 << "))" << endl;
  ofp << endl;
}

