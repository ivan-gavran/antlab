/* License */
/*
Copyright (c) <2014>, <Indranil Saha>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "primitive.h"

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
