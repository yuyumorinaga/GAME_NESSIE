#ifndef INCLUDED_GAME_STATE_H
#define INCLUDED_GAME_STATE_H


class Image; 

class DynamicObject;

class State{
public:
	State();
	~State();
	void update();
	void draw() const;
	bool hasCleared() const;
	bool isAlive() const;
private:

	Image* mImage16size; //画像
	Image* mImageBackground;
	Image* mImageBackground2;
	Image* mImageShadow;
	Image* mImageNessie;

	//動くオブジェクト
	DynamicObject* mDynamicObjects;
	int mDynamicObjectNumber;

	int mCount;
	int mClearCount;
};

#endif

