#include "SoundManager.h"
#include "GameLib/Framework.h"
using namespace GameLib;
#include <sstream>

SoundManager* SoundManager::mInstance = 0;

SoundManager* SoundManager::instance(){
	return mInstance;
}

void SoundManager::create(){
	ASSERT( !mInstance );
	mInstance = new SoundManager();
}

void SoundManager::destroy(){
	ASSERT( mInstance );
	SAFE_DELETE( mInstance );
}

SoundManager::SoundManager() :
mSePlayerPos( 0 ){
	const char* bgmFiles[] = {
		"nessie.wav" //BGM_GAME
	};
	const char* seFiles[] = {
		"nessieSE.wav",//SE_PROLOGUE
		"nessie0.wav",//SE_READY
	};
	std::ostringstream oss;
	for ( int i = 0; i < BGM_MAX; ++i ){
		oss.str( "" );
		oss << "data/sound/bgm/" << bgmFiles[ i ];
		mBgmWaves[ i ] = Sound::Wave::create( oss.str().c_str() );
	}
	for ( int i = 0; i < SE_MAX; ++i ){
		oss.str( "" );
		oss << "data/sound/se/" << seFiles[ i ];
		mSeWaves[ i ] = Sound::Wave::create( oss.str().c_str() );
	}

}

SoundManager::~SoundManager(){
}

void SoundManager::playBgm( Bgm bgm ){
	mBgmPlayer = Sound::Player::create( mBgmWaves[ bgm ] );
	mBgmPlayer.play( true );
}

void SoundManager::stopBgm(){
	if ( mBgmPlayer ){
		mBgmPlayer.stop();
	}
}

void SoundManager::playSe( Se se ){
	mSePlayers[ mSePlayerPos ] = Sound::Player::create( mSeWaves[ se ] );
	mSePlayers[ mSePlayerPos ].play();
	++mSePlayerPos;

	if ( mSePlayerPos == SE_PLAYER_MAX ){
		mSePlayerPos = 0;
	}
}