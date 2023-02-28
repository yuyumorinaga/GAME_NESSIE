#include "Prologue.h"
#include "Image.h"
#include "GameLib/Framework.h"
using namespace GameLib;
#include "Sequence/Parent.h"
#include "Pad.h"
#include "StringRenderer.h"
#include "SoundManager.h"

namespace Sequence{

Prologue::Prologue() :
mImage( 0 ),
mSrcY( 240 ),
mY( 240000 ),
mStart( 120 ),
mSecond( 60 ),
mCount( 0 ){
	mImage = new Image( "data/image/prologueNessie.dds" );
}

Prologue::~Prologue(){
	SAFE_DELETE( mImage );
}

namespace {


static const int SPEED = 500;

int convertInnerToPixel( int y ){
	return  ( y + 500 ) / 1000;
}

} //namespace

void Prologue::update( Parent* parent ){
	if ( Pad::isTriggered( Pad::A ) ){
		parent->moveTo( Parent::NEXT_GAME );
		
	}

	StringRenderer* s = StringRenderer::instance();
	if ( mSrcY <= 0 ){
		mSrcY = 0;
	}
	if ( mCount >= mStart && mCount <= mSecond * 4  ){
	    mImage->draw( 0, 0, 0, mSrcY, 340, 240 );
	}
	if ( mCount == mSecond * 4 ){
		SoundManager::instance()->playSe( SoundManager::SE_PROLOGUE );
	}
	if ( mCount >= mSecond * 4 ){
		mY -= SPEED;
	    int mSrcY = convertInnerToPixel( mY );
		if ( mSrcY < 0 ){
			mSrcY = 0;
		}
		mImage->draw( 0, 0, 0, mSrcY, 340, 240 );

	    
	}
	if ( mCount >= mSecond * 15 && mCount <= mSecond * 19 ){
		s->draw( 3, 13, "You look up the sky, it is there." );
	}
	if ( mCount >= mSecond * 20  && mCount <= mSecond * 24 ){
		s->draw( 5, 13, "Your sense order to run away." );
	}
	if ( mCount >= mSecond * 25 && mCount <= mSecond * 29 ){
        s->draw( 3, 13, "The shadow coming soon behind you." );
	}
	if ( mCount >= mSecond * 30 ){
		s->draw( 14, 13, "Next : [ D ]" );
	}
	mCount++;
}

}//namespace Sequence