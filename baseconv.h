#ifndef BASECONV
#define BASECONV
#include <iostream>
#include <string>
#include <QString>
#include <sstream>
#include <cmath>
using namespace std;

const char reflect[]={'0','1','2','3','4','5','6','7','8','9',
                      'A','B','C','D','E','F','G','H','I','J',
                      'K','L','M','N','O','P','Q','R','S','T',
                      'U','V','W','X','Y','Z'};
bool judgeifnum(char t);
string convertwhole(string t,int base);
string convertto10(string t,int base);
string tobs(int,int);


#endif // BASECONV

