#ifndef INCLUDED_SEQUENCE_ENDING_H
#define INCLUDED_SEQUENCE_ENDING_H

#include "Sequence/Child.h"

class Image;

namespace Sequence{
class Parent;

class Ending : public Child{
public:
	Ending();
	~Ending();
	void update( Parent* );
private:
	Image* mImage;
	int mCount;
	int mSrcY;
	double mY;
	int mSecond;
};

} //namespace Sequence

#endif
