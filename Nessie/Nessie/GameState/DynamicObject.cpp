#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "GameState/DynamicObject.h"
#include "Image.h"
#include "Pad.h"
#include "GameLib/Math.h"
using namespace GameLib;

namespace {

static const int BACKGROUND_SPEED = 2000;
static const int PLAYER_SPEED = 1000;
static const int NESSIE_SPEED = 500;
static const int HALF_SIZE = 4001;
static const int HALF_NESSIE = 190000;


int convertCellToInner( int x, int r ){
	return x * 16000 + r;
}

int convertInnerToPixel( int x, int r ){
	return  ( x - r + 500 ) / 1000;
}

} //namespace{}

DynamicObject::DynamicObject() : 
mType( TYPE_NONE ),
mX( -1 ),
mY( -1 ),
mDirectionX( 0 ),
mDirectionY( 0 ),
mCollisionObstacle( false ),
mMuteki( false ),
mCount( 0 ),
mRadius( 0 ){
}

void DynamicObject::set( int x, int y, Type type, int r ){
	mX = convertCellToInner( x, r );
	mY = convertCellToInner( y, r );
	mType = type;
	mRadius = r;
	if ( mType == TYPE_BACKGROUND || mType == TYPE_WOOD || mType == TYPE_ROCK ){
		mDirectionX = mDirectionY = 0;
		mDirectionY = -1;
	}else if ( mType == TYPE_PLAYER ){
		mCollisionObstacle = false;
		mMuteki = false;
		mCount = 0;
	}else if ( mType == TYPE_NESSIE || mType == TYPE_SHADOW  || mType == TYPE_DEADMAN ){
		mDirectionX = mDirectionY = 0;
		mDirectionY = 1;
	}

}

void DynamicObject::draw( const Image* image ) {
	if ( isDead() ){
		return;
	}
	int dstX = convertInnerToPixel( mX, mRadius );
	int dstY = convertInnerToPixel( mY, mRadius );
	int srcX, srcY;
	srcX = srcY = -1;
	switch ( mType ){
		case TYPE_BACKGROUND:
			srcX = 0; srcY = 0;
			image->draw( dstX, dstY, srcX, srcY, 320, 480 );
			break;

		case TYPE_PLAYER: 
			if ( mCollisionObstacle == false ){
				srcX = 0; srcY = 0;
				image->draw( dstX, dstY, srcX, srcY, 16, 16 );
			}else if ( mCollisionObstacle == true && mCount <= 60 ){
				srcX = 16; srcY = 0;
				image->draw( dstX, dstY, srcX, srcY, 16, 16 );
				mCount++;
				if ( mCount >= 45 ){
					mCollisionObstacle = false;
					mCount = 0;
					mMuteki = true;
				}
			}
			break;

		case TYPE_WOOD: 
			srcX = 32; srcY = 0;
			image->draw( dstX, dstY, srcX, srcY, 16, 16 );
			break;

		case TYPE_ROCK:
			srcX = 48; srcY = 0;
			image->draw( dstX, dstY, srcX, srcY, 16, 16 );
			break;
        case TYPE_NESSIE:
			srcX = 0; srcY = 0;
			image->draw( dstX, dstY, srcX, srcY, 128, 128 );
			break;
		case TYPE_SHADOW:
			srcX = 0; srcY = 0;
			image->draw( dstX, dstY, srcX, srcY, 128, 256 );
			break;
		case TYPE_DEADMAN:
			srcX = 0; srcY = 16;
			image->draw( dstX, dstY, srcX, srcY, 16, 16 );
			break;
		default: HALT( "arienai" ); break;
	}
}

void DynamicObject::update( DynamicObject* d ){
	Framework f = Framework::instance();
	if ( mType == TYPE_BACKGROUND ){
		mX += mDirectionX * BACKGROUND_SPEED;
		mY += mDirectionY * BACKGROUND_SPEED;
		if ( mY <= -240000 ){
			mY = 0;
		}
	}else if ( mType == TYPE_PLAYER ){
		int x, y;
		move();	

		/* è·äQï®Ç…ìñÇΩÇ¡ÇΩÇ∆Ç´Ç…éüÇÃÉtÉåÅ[ÉÄÇ≈ìØàÍÇÃè·äQï®Ç…ìñÇΩÇÁÇ»Ç¢ÇÊÇ§Ç…
		  àÍíËéûä‘ÇÃñ≥ìGÇÇ¬Ç≠ÇÈ*/
		if ( mMuteki == true ){
			mCount++;
			if ( mCount >= 30 ){
				mMuteki = false;
				mCount = 0;
			}
		}
	}else if ( mType == TYPE_WOOD || mType == TYPE_ROCK ){
		mX += mDirectionX * BACKGROUND_SPEED;
		mY += mDirectionY * BACKGROUND_SPEED;
		if ( mY <= -8000 ){
			Framework f = Framework::instance();
	        int x = 0;
			int y = 0;
	        x = f.getRandom( 14 ) + 3;
			y =  f.getRandom( 20 ) + 16;
			if ( y % 3 == 0 ){
				set( x, y, DynamicObject::TYPE_ROCK, mRadius );
			}else if ( y % 3 == 1 ) {
				set( x, y + 2, DynamicObject::TYPE_WOOD, mRadius );
			}else if ( y % 3 == 2 ) {
				set( x, y + 4, DynamicObject::TYPE_WOOD, mRadius );
			}
		}
	}else if ( mType == TYPE_NESSIE || mType == TYPE_SHADOW || mType == TYPE_DEADMAN ){
		DynamicObject& p = *d;
		if ( d->mCollisionObstacle ){
			mY += mDirectionY * NESSIE_SPEED * 2;
		}
		if ( mX < p.mX ){
			mDirectionX = 1;
			mX += mDirectionX * NESSIE_SPEED;
		}else if ( mX > p.mX ){
			mDirectionX = -1;
			mX += mDirectionX * NESSIE_SPEED;
		}
	}
}


void DynamicObject::move(){
	int dx, dy;
	getVelocity( &dx, &dy );
	int movedX = mX + dx;
	int movedY = mY + dy;
	if ( movedX <= 86000 || movedX >= 232000 ){
		return;
	}
	mX = movedX;
	
}


void DynamicObject::getVelocity( int* dx, int* dy ) const {
	int speedX, speedY;
	if ( mType == TYPE_PLAYER ){
		speedX = PLAYER_SPEED;
		speedY = PLAYER_SPEED;
	}
	getDirection( dx, dy );
	*dx = *dx * speedX;
	*dy = *dy * speedY;
}

void DynamicObject::getDirection( int* dx, int* dy ) const {
	Framework f = Framework::instance();
	*dx = *dy = 0;
	if ( mType == TYPE_PLAYER ){
		if ( Pad::isOn( Pad::L ) ){
			*dx = -1;
		}else if ( Pad::isOn( Pad::R ) ){
			*dx = 1;
		}
		if ( Pad::isOn( Pad::U ) ){
			*dy = -1;
		}else if ( Pad::isOn( Pad::D ) ){
			*dy = 1;
		}
	}
}

void DynamicObject::doCollisionReactionToDynamic( DynamicObject* another ){
	
	if ( another->isDead() ){
		return;
	}
	DynamicObject& o1 = *this;
	DynamicObject& o2 = *another;
	if ( o1.isIntersect( o2 ) ){ 
		//ÉvÉåÉCÉÑÅ[ÇéEÇ∑
		if ( o1.isPlayer() && o2.isObstacle() ){
			mCollisionObstacle = true;
		}else if ( o1.isObstacle() && o2.isPlayer() ){
			o2.die();
		}
	}
}

void DynamicObject::doCollisionReactionToDynamicForNessie( DynamicObject* another ){
	
	DynamicObject& o1 = *this;
	DynamicObject& o2 = *another;
	if ( o1.isIntersectForNessie( o2 ) ){ 
		if ( o1.isPlayer() && o2.isNessie() ){
			mCollisionObstacle = true;
		}else if ( o1.isNessie() && o2.isPlayer() ){
			o2.die();
		}
	}
}

bool DynamicObject::isIntersect( const DynamicObject& o ) const {
	int al = mX - HALF_SIZE; 
	int ar = mX + HALF_SIZE; 
	int bl = o.mX - HALF_SIZE;
	int br = o.mX + HALF_SIZE;
	if ( ( al < br ) && ( ar > bl ) ){
		int at = mY - HALF_SIZE; 
		int ab = mY + HALF_SIZE; 
		int bt = o.mY - HALF_SIZE; 
		int bb = o.mY + HALF_SIZE; 
		if ( ( at < bb ) && ( ab > bt ) ){
			return true;
		}
	}
	return false;

}

bool DynamicObject::isIntersectForNessie( const DynamicObject& o ) const {
	double r = (( mX - o.mX ) * ( mX - o.mX )) + (( mY - o.mY ) * ( mY - o.mY ));
	if ( sqrt( r ) < mRadius + o.mRadius ){
		return true;
	}

	return false;

}


bool DynamicObject::isPlayer() const {
	return ( mType == TYPE_PLAYER );
}

bool DynamicObject::isObstacle() const {
	return ( mType == TYPE_WOOD || mType == TYPE_ROCK );
}

bool DynamicObject::isNessie() const {
	return ( mType == TYPE_NESSIE );
}

void DynamicObject::die(){
	mType = TYPE_NONE;
}

bool DynamicObject::isDead() const {
	return ( mType == TYPE_NONE );
}