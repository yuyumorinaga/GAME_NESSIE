#include "Sequence/Game/Parent.h"
#include "GameLib/GameLib.h"
#include "Sequence/Parent.h"
#include "Sequence/Game/Ready.h"
#include "GameState/State.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Failure.h"

namespace Sequence{
namespace Game{
Parent::Parent() :
mChild( 0 ),
mState( 0 ){
	mChild = new Ready();
}
Parent::~Parent(){
	SAFE_DELETE( mChild );
}
void Parent::update( Sequence::Parent* parent ){
	mChild->update( this );
	switch ( mNextSequence ){
		case NEXT_PLAY:
			SAFE_DELETE( mChild );
			mChild = new Play();
			break;
		case NEXT_CLEAR:
			SAFE_DELETE( mChild );
			mChild = new Clear();
			break;
		case NEXT_FAILURE:
			SAFE_DELETE( mChild );
			mChild = new Failure();
			break;
		case NEXT_TITLE:
			SAFE_DELETE( mChild );
			parent->moveTo( Sequence::Parent::NEXT_TITLE );
			break;
		case NEXT_ENDING:
			SAFE_DELETE( mChild );
			parent->moveTo( Sequence::Parent::NEXT_ENDING );
			break;
		case NEXT_GAMEOVER:
			SAFE_DELETE( mChild );
			parent->moveTo( Sequence::Parent::NEXT_GAMEOVER );
			break;

	}
	mNextSequence = NEXT_NONE;
}

State* Parent::state(){
	return mState;
}

void Parent::startLoading(){
	SAFE_DELETE( mState );
	mState = new State();
}

void Parent::drawState() const {
	mState->draw();
}


void Parent::moveTo( NextSequence next ){
	ASSERT( mNextSequence == NEXT_NONE );
	mNextSequence = next;
}

}//namespace Game
}//namespace Sequence