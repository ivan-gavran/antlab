/* License */
/*
Copyright (c) <2014>, <Indranil Saha>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


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
