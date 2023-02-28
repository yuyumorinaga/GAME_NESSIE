#include "Sequence/Game/Play.h"
#include "Sequence/Game/Parent.h"
#include "GameState/State.h"
#include "SoundManager.h"

namespace Sequence{
namespace Game{
Play::Play(){
	SoundManager::instance()->playBgm( SoundManager::BGM_GAME );
}

Play::~Play(){
	SoundManager::instance()->stopBgm();
}

void Play::update( Game::Parent* parent ){
	State* state = parent->state();
	bool cleared = state->hasCleared();
	bool die = !state->isAlive();
	if ( cleared && !die ){
		parent->moveTo( Parent::NEXT_CLEAR );
	}else if ( die ){
		parent->moveTo( Parent::NEXT_FAILURE );
	}
	state->update();
	state->draw();
}
}// namespace Game
}// namespace Sequence