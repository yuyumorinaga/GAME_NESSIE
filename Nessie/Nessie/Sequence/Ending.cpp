#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
using namespace GameLib;

#include "Sequence/Ending.h"
#include "Sequence/Parent.h"
#include "Image.h"
#include "StringRenderer.h"
namespace Sequence{

Ending::Ending() : 
mImage( 0 ),
mCount( 0 ),
mSrcY( 0 ),
mY( 0 ),
mSecond( 60 ){
	mImage = new Image( "data/image/black.dds" );
}

Ending::~Ending(){
	SAFE_DELETE( mImage );
}

namespace {

static const int SPEED = 500;

int convertInnerToPixel( int y ){
	return  ( y + 500 ) / 1000;
}

} //namespace{}

void Ending::update( Parent* parent ){
	

	

	if ( mCount == mSecond * 8 ){
		SAFE_DELETE( mImage );
		mImage = new Image( "data/image/endingNessie1.dds" );
	}
	if ( mCount >= mSecond * 8 ){
		mImage->draw( 0, 0, 0, mSrcY, 340, 240);
	}

	if ( mCount >= mSecond * 10 && mCount <= mSecond * 21 ){
		mY += SPEED;
	    int mSrcY = convertInnerToPixel( mY );
		if ( mSrcY > 240 ){
			mSrcY = 240;
		}
		mImage->draw( 0, 0, 0, mSrcY, 340, 240);
	}
	if ( mCount == mSecond * 21 ){
		mSrcY = 0;
	    SAFE_DELETE( mImage );
		mImage = new Image( "data/image/endingNessie2.dds" );
	}
	if ( mCount == mSecond * 24 ){
	    SAFE_DELETE( mImage );
		mImage = new Image( "data/image/endingNessie3.dds" );
	}
	if ( mCount == mSecond * 27 ){
		SAFE_DELETE( mImage );
		mImage = new Image( "data/image/endingNessie4.dds" );
	}
	if ( mCount == mSecond * 30 ){
		SAFE_DELETE( mImage );
		mImage = new Image( "data/image/endingNessie5.dds" );
	}
	if ( mCount == mSecond * 33 ){
		SAFE_DELETE( mImage );
		mImage = new Image( "data/image/endingNessie6.dds" );
	}
	if ( mCount == mSecond * 36 ){
		SAFE_DELETE( mImage );
		mImage = new Image( "data/image/endingNessie7.dds" );
	}
	if ( mCount == mSecond * 39 ){
		SAFE_DELETE( mImage );
		mImage = new Image( "data/image/endingNessie8.dds" );
	}
	if ( mCount == mSecond * 43 ){
		SAFE_DELETE( mImage );
		mImage = new Image( "data/image/black.dds" );
	}
	if ( mCount >= mSecond * 21 ){
		mImage->draw( 0, 0, 0, mSrcY, 340, 240);
	}
	

	StringRenderer* f = StringRenderer::instance();

	if ( mCount >= mSecond * 3 && mCount <= mSecond * 6 ){
		f->draw( 14, 6, "AN HOUR AGO" );
	}
	if ( mCount >= mSecond * 34 && mCount <= mSecond * 35 ){
		f->draw( 13, 6, "\"Hey, you.\"" );
	}
	if ( mCount >= mSecond * 43 && mCount <= mSecond * 48 ){
	    f->draw( 5, 6, "\"This is something you forget.\"" );
	}
	if ( mCount >= mSecond * 51 && mCount <= mSecond * 55 ){
	    f->draw( 8, 6, "Thank you for playing!" );
	    f->draw( 25, 12, "Created by" );
		f->draw( 26, 13, "Yoshida Iori" );
	}
	if ( mCount == mSecond * 55 ){ 
		parent->moveTo( Parent::NEXT_TITLE );
	}
	

	++mCount;
}

} //namespace Sequence