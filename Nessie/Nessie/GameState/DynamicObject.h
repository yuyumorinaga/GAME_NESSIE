#ifndef INCLUDED_GAME_DYNAMIC_OBJECT_H
#define INCLUDED_GAME_DYNAMIC_OBJECT_H

class Image;


class DynamicObject{
public:
	enum Type{
		TYPE_BACKGROUND,
		TYPE_PLAYER,
		TYPE_NESSIE,
		TYPE_WOOD,
		TYPE_ROCK,
		TYPE_SHADOW,
		TYPE_DEADMAN,

		TYPE_NONE, //Ž€‚ñ‚Å‚Ü‚·
	};
	DynamicObject();
	void set( int x, int y, Type, int );
	void draw( const Image* ) ;
	void update( DynamicObject* );
	void move();
	void doCollisionReactionToDynamic( DynamicObject* );
	void doCollisionReactionToDynamicForNessie( DynamicObject* );
	bool isIntersect( const DynamicObject& ) const;
	bool isIntersectForNessie( const DynamicObject& ) const;
	bool isPlayer() const;
	bool isObstacle() const;
	bool isNessie() const;
	void die();
	bool isDead() const;
	Type mType;
	bool mCollisionObstacle;
	bool mMuteki;

private:
	void getVelocity( int* dx, int* dy ) const;
	void getDirection( int* dx, int* dy ) const;
	double mX;
	double mY;
	int mDirectionX;
	int mDirectionY;
	int mRadius;	
	int mCount;
};

#endif