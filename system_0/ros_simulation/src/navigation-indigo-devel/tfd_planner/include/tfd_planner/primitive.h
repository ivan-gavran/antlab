#ifndef TFD_PLANNER__PRIMITIVE_H_
#define TFD_PLANNER__PRIMITIVE_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct s1
{
  int velocity;
  //int configuration;
};

typedef struct s1 state;


struct s2
{
  int x;
  int y;


};

typedef struct s2 position;
bool operator<(const position  a, const position  b);

struct pos_2d
{
	float x;
	float y;
};

typedef std::vector<position> pos_vec_t;
struct s3
{
	position pos;
	string robot_name;
	};

typedef struct s3 robot_position;

typedef std::vector<position> pos_vec_t;
typedef std::vector<robot_position> robot_pos_vec_t;

class Primitive 
{
  private:
    state q_i;
    state q_f;
    position pos_f;
    string cost;
    pos_vec_t swath;    
    position pos_min;
    position pos_max;

  public:
    Primitive(state , state , position , string , pos_vec_t , position , position );
    state get_q_i();
    state get_q_f();
    position get_pos_f();
    string get_cost();
    pos_vec_t get_swath();
    position get_pos_min();
    position get_pos_max();
    ~Primitive();  
};

#endif
