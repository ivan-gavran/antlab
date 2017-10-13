#ifndef TFD_PLANNER__READINPUTS_H_
#define TFD_PLANNER__READINPUTS_H_

struct w
{
  unsigned int length_x;
  unsigned int length_y;
  unsigned int number_of_robots;
  pos_vec_t pos_start;
  pos_vec_t pos_end;
  unsigned int number_of_points;
  string total_cost;
};

typedef struct w workspace_t;


struct d
{  
  unsigned int length_x;
  unsigned int length_y;
};

typedef struct d dimension_t;


struct c
{
  float max_cost;
  float min_cost;
  float min2_cost;
  float min_cost_diff;
  float min2_min_cost_diff;
};

typedef struct c prim_cost_t;

 
typedef std::vector<Primitive> prim_vec_t;

typedef std::vector<int> position_with_cost;

void readPrimitives(prim_vec_t &, string filename );
void writePrimitives(prim_vec_t );
void readPositions(pos_vec_t & , string filename);
void readPositionsWithCost(std::vector<position_with_cost> &, string filename);
void writePositions(pos_vec_t );
void writeWorkspace(workspace_t);
void readDimension(dimension_t &, string filename);
void writeDimension(dimension_t);

#endif
