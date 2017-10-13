#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "utils.h"


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
