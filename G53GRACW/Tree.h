#ifndef ___Tree__
#define ___Tree__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

class Tree : public DisplayableObject       // a Tree is a DisplayableObject
{
public:
	Tree();                                 // constructor
	~Tree() { };                            // destructor
	void display();                         // overloaded virtual display function
private:
	void trunk();                          // draw trunk function
	void leaves();

	float ranNum;
	int tier;
};
#endif
