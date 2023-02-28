#include "Sequence/Parent.h"
#include "GameLib/GameLib.h"
#include "SoundManager.h"
#include "StringRenderer.h"
#include "Sequence/Title.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Prologue.h"
#include "Sequence/Ending.h"
#include "Sequence/GameOver.h"
namespace Sequence{

Parent* Parent::mInstance = 0;

Parent* Parent::instance(){
	return mInstance;
}

void Parent::create(){
	ASSERT( !mInstance );
	mInstance = new Parent();
}

void Parent::destroy(){
	ASSERT( mInstance );
	SAFE_DELETE( mInstance );
}

Parent::Parent():
mNextSequence( NEXT_NONE ),
mChild( 0 ){
	SoundManager::create();
	StringRenderer::create( "data/image/font12896.dds" );
	mChild = new Title();
}

Parent::~Parent(){
	SAFE_DELETE( mChild );
	SoundManager::destroy();
	StringRenderer::destroy();
}

void Parent::update(){
	mChild->update( this );
	switch ( mNextSequence ){
	    case NEXT_TITLE:
			SAFE_DELETE( mChild );
			mChild = new Title();
			break;
		case NEXT_PROLOGUE:
			SAFE_DELETE( mChild );
			mChild = new Prologue();
			break;
		case NEXT_GAME:
			SAFE_DELETE( mChild );
			mChild = new Game::Parent();
			break;
		case NEXT_GAMEOVER:
			SAFE_DELETE( mChild );
			mChild = new GameOver();
			break;
		case NEXT_ENDING:
			SAFE_DELETE( mChild );
			mChild = new Ending();
	}
	mNextSequence = NEXT_NONE;
}

void Parent::moveTo( NextSequence next ){
	ASSERT( mNextSequence == NEXT_NONE );
	mNextSequence = next;
}
}//namespace Sequnece