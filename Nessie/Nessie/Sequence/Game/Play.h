#ifndef INCLUDED_SEQUENCE_GAME_PLAY_H
#define INCLUDED_SEQUENCE_GAME_PLAY_H

#include "Sequence/Game/Child.h"
namespace Sequence{
namespace Game{
class Parent;
class Play : public Game::Child{
public:
	Play();
	~Play();
	void update( Game::Parent* );
private:
	bool mStarted;

};
}//namespace Game
}//namespace Sequence

#endif