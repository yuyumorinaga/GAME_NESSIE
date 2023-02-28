#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
using namespace GameLib;
#include "StringRenderer.h"
#include "Sequence/Game/Failure.h"
#include "Sequence/Game/Parent.h"
#include "Image.h"

namespace Sequence{
namespace Game{

Failure::Failure() : mImage( 0 ), mCount( 0 ){
	mImage = new Image( "data/image/nessieFailure.dds" );
}

Failure::~Failure(){
	SAFE_DELETE( mImage );
}

void Failure::update( Parent* parent ){
	if ( mCount == 60 ){ 
		parent->moveTo( Parent::NEXT_GAMEOVER ); 
	}
	parent->drawState();
	mImage->draw();
	

	++mCount;
}

} //namespace Game
} //namespace Sequence
