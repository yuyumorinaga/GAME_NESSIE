#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
using namespace GameLib;

#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Parent.h"
#include "Image.h"
#include "StringRenderer.h"
namespace Sequence{
namespace Game{

Clear::Clear() : mImage( 0 ), mCount( 0 ){
	mImage = new Image( "data/image/Alpha.dds" );
}

Clear::~Clear(){
	SAFE_DELETE( mImage );
}

void Clear::update( Parent* parent ){
	if ( mCount == 600 ){ 
		parent->moveTo( Parent::NEXT_ENDING );
	}
	if ( mCount <= 300 ){

	    parent->drawState();
	    mImage->draw();
	    StringRenderer::instance()->draw( 1, 1, "Clear!", 6 );
	}
	if ( mCount == 300 ){
		SAFE_DELETE( mImage );
		mImage = new Image( "data/image/nessieGoal.dds" );
	}
	if ( mCount >= 300 ){
		mImage->draw();
	}

	++mCount;
}

} //namespace Game
} //namespace Sequence
