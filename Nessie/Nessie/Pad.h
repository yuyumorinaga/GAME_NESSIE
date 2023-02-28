#ifndef INCLUDED_PAD_H
#define INCLUDED_PAD_H

class Pad{
public:
	enum Button{
		A,
		B,
		U,
		D,
		L,
		R,
		Q,
	};

	static bool isOn( Button, int playerID = 0 );
	static bool isTriggered( Button, int playerID = 0 );
};

#endif