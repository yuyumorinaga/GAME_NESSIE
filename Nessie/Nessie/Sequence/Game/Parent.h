#ifndef INCLUDED_SEQUENCE_GAME_PARENT_H
#define INCLUDED_SEQUENCE_GAME_PARENT_H

#include "Sequence/Child.h"

class State;
namespace Sequence{
namespace Game{
class Child;
class Parent : public Sequence::Child{
public:
	enum NextSequence{
		NEXT_PLAY,
		NEXT_CLEAR,
		NEXT_FAILURE,
		NEXT_TITLE,
		NEXT_ENDING,
		NEXT_GAMEOVER,
		

		NEXT_NONE
	};
	Parent();
	~Parent();
	void update( Sequence::Parent* );
	State* state();
	void drawState() const;
	void startLoading();
	void moveTo( NextSequence );
private:
	Game::Child* mChild;
	State* mState;
	NextSequence mNextSequence;
};
}//namespace Game
}//namespace Sequence

#endif