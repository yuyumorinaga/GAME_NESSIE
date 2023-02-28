#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
using namespace GameLib;

#include "Sequence/GameOver.h"
#include "Sequence/Parent.h"
#include "Image.h"
#include "StringRenderer.h"
#include "Pad.h"
namespace Sequence{

GameOver::GameOver() : mImage( 0 ), mCursorPosition( 4 ){
	mImage = new Image( "data/image/black.dds" );
}

GameOver::~GameOver(){
	SAFE_DELETE( mImage );
}

void GameOver::update( Parent* parent ){
	if ( Pad::isTriggered( Pad::U ) ){
		--mCursorPosition;
		if ( mCursorPosition < 4 ){ 
 			mCursorPosition = 5;
		}
		
	}else if ( Pad::isTriggered( Pad::D ) ){
		++mCursorPosition;
		if ( mCursorPosition > 5 ){ 
			mCursorPosition = 4;
		}
		
	}else if ( Pad::isTriggered( Pad::A ) ){
		
		if ( mCursorPosition == 4 ){
			parent->moveTo( Parent::NEXT_GAME ); 
		}else if ( mCursorPosition == 5 ){
			parent->moveTo( Parent::NEXT_TITLE );
		}else{
			HALT( "arienai" );
		}
	}
	//描画
	mImage->draw();
	//字を出す
	StringRenderer* s = StringRenderer::instance();
	s->draw( 14, 6, "CONTINUE" );
	s->draw( 14, 7, "BACK TO TITLE" );
	s->draw( 28, 12, "UP:[W]" );
	s->draw( 28, 13, "DOWN:[Z]" );
	s->draw( 28, 14, "DECISION:[D]" );
	//カーソルを書く
	s->draw( 13, mCursorPosition + 2, ">" );
	

}

} //namespace Sequence