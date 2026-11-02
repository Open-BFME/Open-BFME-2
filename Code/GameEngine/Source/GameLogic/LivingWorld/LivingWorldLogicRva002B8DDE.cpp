// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva002B8DDE@LivingWorldLogic@@QAEXH@Z retail 0x002B8DDE (30B): remove the
// player with this id: the rowed id lookup (0x002B51F8, spelled
// Rva002BA8F1Logic::find(int, unsigned int *) in Rva002BA8F1Lookups.cpp, no
// index wanted) and, when it finds one, the rowed
// LivingWorldLogic::RemovePlayer (0x002B7DE6). Both are thiscall on the same
// LivingWorldLogic; the method's own name is not recovered.

class LivingWorldPlayer;
class Rva002E2903Player;

#include "../../../Include/GameLogic/Rva002BA8F1Logic.h"

#include "../../../Include/GameLogic/LivingWorldLogic.h"

void LivingWorldLogic::rva002B8DDE(int id)
{
	Rva002E2903Player *player = ((Rva002BA8F1Logic *)this)->find(id, 0);
	if (player)
		RemovePlayer((LivingWorldPlayer *)player);
}
