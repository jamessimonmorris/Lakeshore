#ifndef ___Animation__
#define ___Animation__

class Animation
{
public:
	virtual void update(float dT) = 0;                  // update function (MUST OVERLOAD)
};
#endif