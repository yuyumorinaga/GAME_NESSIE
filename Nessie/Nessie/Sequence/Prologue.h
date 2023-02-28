#ifndef INCLUDED_SEQUENCE_PROLOGUE_H
#define INCLUDED_SEQUENCE_PROLOGUE_H
#include "Sequence/Child.h"

class Image;
namespace Sequence{
class Parent;
	
class Prologue : public Child{
public:
	Prologue();
	~Prologue();
	void update( Parent* );
private:
	
	Image* mImage;
	int mCount;
	int mSrcY;
	double mY;
	int mStart;
	int mSecond;
};
}//namespace Sequence

#endif