#include "Pad.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
using namespace GameLib;

bool Pad::isOn( Button b, int pid ){
	Input::Manager im = Input::Manager::instance();
	Input::Keyboard kb = im.keyboard();
	bool ret = false;
	if ( pid == 0 ){
		int table[] = { 'd', 'x', 'w', 'z', 'a', 's', 'q' };
		ret = kb.isOn( table[ b ] );
	}
	return ret;
}

bool Pad::isTriggered( Button b, int pid ){
	Input::Manager im = Input::Manager::instance();
	Input::Keyboard kb = im.keyboard();
	bool ret = false;
	if ( pid == 0 ){
		int table[] = { 'd', 'x', 'w', 'z', 'a', 's', 'q' };
		ret = kb.isTriggered( table[ b ] );
	}
	return ret;
}