

#include <metricff_planner/primitive.h>
bool operator<(const position a, const position b){

		if (a.x < b.x)
			return true;
		else if (a.x > b.x)
			return false;
		else
			return a.y < b.y;

}
Primitive::Primitive(state q_i, state q_f, position pos_f, string cost, pos_vec_t swath, position pos_min, position pos_max)
{
  this->q_i = q_i;
  this->q_f = q_f;
  this->pos_f = pos_f;
  this->cost = cost;
  this->swath = swath;
  this->pos_min = pos_min;
  this->pos_max = pos_max;
}

state Primitive::get_q_i()
{
  return q_i;
}

state Primitive::get_q_f()
{
  return q_f;
}

position Primitive::get_pos_f()
{
  return pos_f;
}

string Primitive::get_cost()
{
  return cost;
}

pos_vec_t Primitive::get_swath()
{
  return swath;
}

position Primitive::get_pos_min()
{
  return pos_min;
}

position Primitive::get_pos_max()
{
  return pos_max;
}

Primitive::~Primitive()
{
}
