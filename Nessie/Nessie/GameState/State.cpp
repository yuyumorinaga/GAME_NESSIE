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
	
	

	//���I�I�u�W�F�N�g���m��
	int actorNumber = 6;
	int enemyNumber = 45;
	mDynamicObjectNumber = actorNumber + enemyNumber;
	mDynamicObjects = new DynamicObject[ mDynamicObjectNumber ];

	//��ԉ��̔w�i���Z�b�g
	mDynamicObjects[ 0 ].set( 0, 0, DynamicObject::TYPE_BACKGROUND, 0 );

	//�v���C���[���Z�b�g
	mDynamicObjects[ 1 ].set( 10, 7, DynamicObject::TYPE_PLAYER, 8000 );

	//���̂��Z�b�g
	mDynamicObjects[ 2 ].set( 8, -5, DynamicObject::TYPE_DEADMAN, 4000 );

	//�e���Z�b�g
	mDynamicObjects[ 3 ].set( 6, -13, DynamicObject::TYPE_SHADOW, 64000 );

	//�l�b�V�[���Z�b�g
	mDynamicObjects[ 4 ].set( 6, -13, DynamicObject::TYPE_NESSIE, 64000 );

	//��ԏ�̔w�i���Z�b�g
	mDynamicObjects[ 5 ].set( 0, 0, DynamicObject::TYPE_BACKGROUND, 0 );

	/* ��ʊO�̉����ɏ�Q�������� */
	Framework f = Framework::instance();
	int x = 0;
	int y = 0;
	for ( int i = 6; i < mDynamicObjectNumber; ++i ){
		x = f.getRandom( 14 ) + 3;
	    y =  f.getRandom( 20 ) + 16;

		/* ���L�̕���ŁA��Q���Ə�Q���̊Ԃ��c2�}�X�����肽���B
		y��16�̂Ƃ���18�A����17�̂Ƃ���21�A����18�̂Ƃ���18�A
		����19�̂Ƃ���21�A����20�̂Ƃ���24�c�ƂȂ�͂��B
		�ł������鐔����18�A21�A24�c�ƂȂ�A��Q���̊Ԃ͂Q�}�X�󂭂͂��B
		���������Ԍo�߂łȂ����Q�}�X�󂩂Ȃ��Ȃ�B*/
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
	
	//��ԉ��̔w�i�̕`��
	mDynamicObjects[ 0 ].draw( mImageBackground );

	//��Q���̕`��
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
	
	//�v���C���[����Q���ɓ������Ă��Ȃ����
	if ( mDynamicObjects[ 1 ].mCollisionObstacle == false ){ 

		//��ԉ��̔w�i���X�V
		mDynamicObjects[ 0 ].update( &mDynamicObjects[ 1 ] );

		//�v���C���[���X�V
		mDynamicObjects[ 1 ].update( &mDynamicObjects[ 1 ] );

		//��Q�����X�V
		for ( int i = 6; i < mDynamicObjectNumber; ++i ){
			mDynamicObjects[ i ].update( &mDynamicObjects[ 1 ] );
		}
		//��ԏ�̔w�i���X�V
		mDynamicObjects[ 5 ].update( &mDynamicObjects[ 1 ] );
	}
	//���̂��X�V
	mDynamicObjects[ 2 ].update( &mDynamicObjects[ 1 ] );

	//�e���X�V
	mDynamicObjects[ 3 ].update( &mDynamicObjects[ 1 ] );

	//�l�b�V�[���X�V
	mDynamicObjects[ 4 ].update( &mDynamicObjects[ 1 ] );
	

	//�v���C���[�����G��ԂłȂ����
	if ( mDynamicObjects[ 1 ].mMuteki == false ){

		//��Q���Ƃ̏Փ˔���
		for ( int i = 0; i < mDynamicObjectNumber; ++i ){
			for ( int j = i + 1; j < mDynamicObjectNumber; ++j ){
				mDynamicObjects[ i ].doCollisionReactionToDynamic( &mDynamicObjects[ j ] );
			}
		}
	}
	//�l�b�V�[�Ƃ̏Փ˔���
	mDynamicObjects[ 4 ].doCollisionReactionToDynamicForNessie( &mDynamicObjects[ 1 ] );

	mCount++;

	//mCount��b�ɒ���
	if ( mCount % 60 == 0 ){
		mClearCount--;
	}
}


bool State::hasCleared() const {
	//���Ԍo�߂ŃN���A
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
