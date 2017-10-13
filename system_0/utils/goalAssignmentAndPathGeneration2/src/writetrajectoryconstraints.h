void declareVariables(ofstream & , workspace_t );
void writeInitialLocationConstraints(ofstream & , workspace_t );
void writeFinalDestinationConstraints(ofstream & , workspace_t );
void writeObstacleConstraints(ofstream & , pos_vec_t , workspace_t );
void writeTransitionConstraints(ofstream & , prim_vec_t , pos_vec_t , workspace_t );
void writeCostConstraint(ofstream & , workspace_t );
void writeOutputConstraints(ofstream & , workspace_t );
