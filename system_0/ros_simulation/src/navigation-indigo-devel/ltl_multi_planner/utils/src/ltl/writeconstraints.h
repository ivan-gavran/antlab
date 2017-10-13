/* License */
/*
Copyright (c) <2014>, <Indranil Saha>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


void declareVariables(ofstream & , workspace_t );
void declareVariablesYices(ofstream & , workspace_t );
void writeInitialLocationConstraints(ofstream & , workspace_t );
void writeFinalDestinationConstraints(ofstream & , workspace_t );
void writeObstacleConstraints(ofstream & , pos_vec_t , workspace_t );
void writeTransitionConstraints(ofstream & , prim_vec_t , pos_vec_t , workspace_t );
void writeLoopDependentCostConstraint(ofstream &ofp, prim_vec_t primitives, pos_vec_t obstacles, workspace_t workspace);
void writeCostConstraint(ofstream & , workspace_t , prim_cost_t );
void writeCollisionAvoidanceConstraints1(ofstream & , prim_vec_t , workspace_t );
void writeCollisionAvoidanceConstraints2(ofstream & , prim_vec_t , workspace_t );
void writeDistanceConstraints(ofstream & , workspace_t );
void writeStateLoopConstraints(ofstream & , workspace_t );
void writePropositionsOutputConstraints(ofstream & , workspace_t , prop_vec_t );
void writeLoopOutputConstraints(ofstream & , workspace_t );
void writeOutputConstraints(ofstream & , workspace_t );
string floatToReal(string );
template <typename T> string tostr(const T& );
