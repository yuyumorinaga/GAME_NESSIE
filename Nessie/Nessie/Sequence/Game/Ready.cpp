#include "Sequence/Game/Ready.h"
#include "Image.h"
#include "GameLib/Framework.h"
using namespace GameLib;
#include "Sequence/Game/Parent.h"
#include "SoundManager.h"
#include "StringRenderer.h"

namespace Sequence{
namespace Game{

Ready::Ready() :
mImage( 0 ),
mCount( 0 ),
mStarted( false ){
	mImage = new Image( "data/image/playerDash.dds" );
}

Ready::~Ready(){
	SAFE_DELETE( mImage );
}

void Ready::update( Game::Parent* parent ){
	if ( !mStarted ){
		parent->startLoading();
		mStarted = true;
		SoundManager::instance()->playSe( SoundManager::SE_READY );
	}
	StringRenderer* f = StringRenderer::instance();
	
	if ( mCount <= 240 ){
	    mImage->draw();
	    f->draw( 25, 13, "Now Loading..." );
	}else if ( mCount >= 240 && mCount <= 360 ){
		parent->drawState();
		f->draw( 8, 4, "LEFT");
		f->draw( 4, 3, "[A]", 2 );
	    f->draw( 28, 4, "RIGHT");
		f->draw( 14, 3, "[S]", 2 );
	}else if ( mCount >= 360 && mCount <= 390 ){
		parent->drawState();
		f->draw( 3, 1, "3", 7 );
	}else if ( mCount >= 390 && mCount <= 420 ){
		parent->drawState();
		f->draw( 3, 1, "2", 7 );
	}else if ( mCount >= 420 && mCount <= 450 ){
		parent->drawState();
		f->draw( 3, 1, "1", 7 );
	}else if ( mCount >= 450 && mCount <= 480 ){
		parent->drawState();
		f->draw( 2, 1, "GO", 8 );
	}else if ( mCount >= 480 ){ 
		parent->moveTo( Parent::NEXT_PLAY );
	}
	++mCount;
}

}// namespace Game
}// namespace Sequence