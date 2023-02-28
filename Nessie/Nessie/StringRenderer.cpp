#include "StringRenderer.h"
#include "Image.h"
#include "GameLib/Framework.h"
using namespace GameLib;

//staticïœêîÇÕcppÇ…é¿ëÃÇ™ïKóv
StringRenderer* StringRenderer::mInstance = 0;

StringRenderer* StringRenderer::instance(){
	return mInstance;
}

StringRenderer::StringRenderer( const char* fontFileName ) : mImage( 0 ){
	mImage = new Image( fontFileName );
}

StringRenderer::~StringRenderer(){
	SAFE_DELETE( mImage );
}

void StringRenderer::create( const char* fontFileName ){

	STRONG_ASSERT( !mInstance );
	mInstance = new StringRenderer( fontFileName );
}

void StringRenderer::destroy(){
	SAFE_DELETE( mInstance );
}


void StringRenderer::draw( int x, int y, const char* str ) const {

	int dstX = x * 8;
	int dstY = y * 16;

	const int cWidth = 8;
	const int cHeight = 16;
	for ( unsigned i = 0; str[ i ] != '\0'; ++i ){
		int t = str[ i ];
		if ( t < 32 || t >= 128 ){
			t = 127;
		}
		t -= 32;
		int srcX = ( t % 16 ) * cWidth;
		int srcY = ( t / 16 ) * cHeight;
		mImage->draw( dstX, dstY, srcX, srcY, cWidth, cHeight );
		dstX += cWidth;
	}
}

void StringRenderer::draw( int x, int y, const char* str, int size ){

	int dstX = x * 8;
	int dstY = y * 16;

	const int cWidth = 8;
	const int cHeight = 16;
	for ( unsigned i = 0; str[ i ] != '\0'; ++i ){
		int t = str[ i ];
		if ( t < 32 || t >= 128 ){
			t = 127;
		}
		t -= 32;
		int srcX = ( t % 16 ) * cWidth;
		int srcY = ( t / 16 ) * cHeight;
		mImage->scalableDraw( dstX, dstY, srcX, srcY, cWidth, cHeight, size );
		dstX += cWidth;
	}
}