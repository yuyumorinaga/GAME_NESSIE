#ifndef INCLUDED_SEQUENCE_PARENT_H
#define INCLUDED_SEQUENCE_PARENT_H

namespace Sequence{
class Child;
class Parent{
public:
	enum NextSequence{
		NEXT_TITLE,
		NEXT_PROLOGUE,
		NEXT_GAME,
		NEXT_GAMEOVER,
		NEXT_ENDING,

		NEXT_NONE,
	};
	void update();
	void moveTo( NextSequence );
	static Parent* instance();
	static void create();
	static void destroy();
private:
	Parent();
	~Parent();
	NextSequence mNextSequence;
	Child* mChild;
	static Parent* mInstance;
};
}
#endif;