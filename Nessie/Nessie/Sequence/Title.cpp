#include "Sequence/Title.h"
#include "Image.h"
#include "GameLib/Framework.h"
using namespace GameLib;
#include "Pad.h"
#include "Sequence/Parent.h"
#include "StringRenderer.h"

namespace Sequence{

Title::Title() :
mImage( 0 ){
	mImage = new Image( "data/image/nessieTitle.dds" );
}

Title::~Title(){
	SAFE_DELETE( mImage );
}

void Title::update( Parent* parent ){
	if ( Pad::isTriggered( Pad::A ) ){
		parent->moveTo( Parent::NEXT_PROLOGUE );
	}
	mImage->draw();
	StringRenderer* f = StringRenderer::instance();
	f->draw( 4, 12, "Please press [ D ] to start game." );
}

}//namespace Sequence