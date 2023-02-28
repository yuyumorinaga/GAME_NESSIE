#include "GameLib/Framework.h"
#include "GameState/State.h"
#include "StringRenderer.h"
#include "GameState/DynamicObject.h"
#include "SoundManager.h"
#include "Image.h"
using namespace GameLib;
#include <sstream>
using namespace std;

State::State() : 
mImage16size( 0 ),
mImageBackground( 0 ),
mImageBackground2( 0 ),
mImageNessie( 0 ),
mImageShadow( 0 ),
mDynamicObjects( 0 ),
mDynamicObjectNumber( 0 ),
mCount( 0 ),
mClearCount( 50 ){
	
	mImage16size = new Image( "data/image/16size.dds" );
	mImageBackground = new Image( "data/image/background.dds" );
	mImageBackground2 = new Image( "data/image/bg.dds" );
	mImageNessie = new Image("data/image/newnessie3.dds" );
	mImageShadow = new Image( "data/image/shadow2.dds" );
	
	

	//動的オブジェクトを確保
	int actorNumber = 6;
	int enemyNumber = 45;
	mDynamicObjectNumber = actorNumber + enemyNumber;
	mDynamicObjects = new DynamicObject[ mDynamicObjectNumber ];

	//一番下の背景をセット
	mDynamicObjects[ 0 ].set( 0, 0, DynamicObject::TYPE_BACKGROUND, 0 );

	//プレイヤーをセット
	mDynamicObjects[ 1 ].set( 10, 7, DynamicObject::TYPE_PLAYER, 8000 );

	//死体をセット
	mDynamicObjects[ 2 ].set( 8, -5, DynamicObject::TYPE_DEADMAN, 4000 );

	//影をセット
	mDynamicObjects[ 3 ].set( 6, -13, DynamicObject::TYPE_SHADOW, 64000 );

	//ネッシーをセット
	mDynamicObjects[ 4 ].set( 6, -13, DynamicObject::TYPE_NESSIE, 64000 );

	//一番上の背景をセット
	mDynamicObjects[ 5 ].set( 0, 0, DynamicObject::TYPE_BACKGROUND, 0 );

	/* 画面外の下方に障害物をつくる */
	Framework f = Framework::instance();
	int x = 0;
	int y = 0;
	for ( int i = 6; i < mDynamicObjectNumber; ++i ){
		x = f.getRandom( 14 ) + 3;
	    y =  f.getRandom( 20 ) + 16;

		/* 下記の分岐で、障害物と障害物の間を縦2マス分つくりたい。
		yが16のときに18、ｙが17のときに21、ｙが18のときに18、
		ｙが19のときに21、ｙが20のときに24…となるはず。
		できあがる数字は18、21、24…となり、障害物の間は２マス空くはず。
		しかし時間経過でなぜか２マス空かなくなる。*/
		if ( y % 3 == 0 ){
			mDynamicObjects[ i ].set( x, y, DynamicObject::TYPE_ROCK, 4000 );
		}else if ( y % 3 == 1 ){
			mDynamicObjects[ i ].set( x, y + 2, DynamicObject::TYPE_WOOD, 4000 );
		}else if ( y % 3 == 2 ){
			mDynamicObjects[ i ].set( x, y + 4, DynamicObject::TYPE_WOOD, 4000 );
		}
	}
	
}

State::~State(){
	SAFE_DELETE( mImage16size );
	SAFE_DELETE( mImageBackground );
	SAFE_DELETE( mImageBackground2 );
	SAFE_DELETE( mImageNessie );
	SAFE_DELETE( mImageShadow );
	
	SAFE_DELETE_ARRAY( mDynamicObjects );
}

void State::draw() const {
	
	//一番下の背景の描画
	mDynamicObjects[ 0 ].draw( mImageBackground );

	//障害物の描画
	for ( int i = 6; i < mDynamicObjectNumber; ++i ){
		mDynamicObjects[ i ].draw( mImage16size );
	}

	mDynamicObjects[ 1 ].draw( mImage16size );
	mDynamicObjects[ 2 ].draw( mImage16size );
	mDynamicObjects[ 3 ].draw( mImageShadow );
	mDynamicObjects[ 4 ].draw( mImageNessie );
	mDynamicObjects[ 5 ].draw( mImageBackground2 );
	
	ostringstream oss;
	oss << "Run " << mClearCount << "m!";
	StringRenderer* f = StringRenderer::instance();
	f->draw( 0, 0, oss.str().c_str() );
	
}

void State::update(){
	
	//プレイヤーが障害物に当たっていなければ
	if ( mDynamicObjects[ 1 ].mCollisionObstacle == false ){ 

		//一番下の背景を更新
		mDynamicObjects[ 0 ].update( &mDynamicObjects[ 1 ] );

		//プレイヤーを更新
		mDynamicObjects[ 1 ].update( &mDynamicObjects[ 1 ] );

		//障害物を更新
		for ( int i = 6; i < mDynamicObjectNumber; ++i ){
			mDynamicObjects[ i ].update( &mDynamicObjects[ 1 ] );
		}
		//一番上の背景を更新
		mDynamicObjects[ 5 ].update( &mDynamicObjects[ 1 ] );
	}
	//死体を更新
	mDynamicObjects[ 2 ].update( &mDynamicObjects[ 1 ] );

	//影を更新
	mDynamicObjects[ 3 ].update( &mDynamicObjects[ 1 ] );

	//ネッシーを更新
	mDynamicObjects[ 4 ].update( &mDynamicObjects[ 1 ] );
	

	//プレイヤーが無敵状態でなければ
	if ( mDynamicObjects[ 1 ].mMuteki == false ){

		//障害物との衝突判定
		for ( int i = 0; i < mDynamicObjectNumber; ++i ){
			for ( int j = i + 1; j < mDynamicObjectNumber; ++j ){
				mDynamicObjects[ i ].doCollisionReactionToDynamic( &mDynamicObjects[ j ] );
			}
		}
	}
	//ネッシーとの衝突判定
	mDynamicObjects[ 4 ].doCollisionReactionToDynamicForNessie( &mDynamicObjects[ 1 ] );

	mCount++;

	//mCountを秒に直す
	if ( mCount % 60 == 0 ){
		mClearCount--;
	}
}


bool State::hasCleared() const {
	//時間経過でクリア
	if ( mClearCount == 0 ){
		return true;
	}
	return false;
}

bool State::isAlive() const {
	for ( int i = 0; i < mDynamicObjectNumber; ++i ){
		if ( mDynamicObjects[ i ].mType == DynamicObject::TYPE_PLAYER ){
			return true;
		}
	}
	return false;
}
