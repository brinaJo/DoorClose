#include "GM.h"

GM* GM::instance = NULL;

GM::GM()
{
	Sound = true;
	Effect = true;

	sound_on_off = true;

	Stage = false;

	isChaTouch = true;
	nPass.clear();
}

GM* GM::Getinstance()
{
	if (!instance)
	{
		instance = new GM;
	}
	return instance;
}
