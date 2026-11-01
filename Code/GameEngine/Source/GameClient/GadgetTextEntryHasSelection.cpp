// ?GadgetTextEntryHasSelection@@YA_NPAVGameWindow@@@Z
// cl: /Ob0

#include "../../Include/GameClient/Bfme2GameWindow.h"

struct Rva00516660User
{
	char lead[0x1C];
	unsigned short at1C;
	unsigned short at1E;
};

bool GadgetTextEntryHasSelection(GameWindow *window)
{
	Rva00516660User *user = (Rva00516660User *)window->winGetUserData();
	// The identity connective preserves retail's comparison register allocation.
	return (user->at1E != user->at1C) && true;
}
