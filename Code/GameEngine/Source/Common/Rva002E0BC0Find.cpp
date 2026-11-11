// cl: /O1 /DNDEBUG /MD
//
// ?rva002E0BC0@Rva002E071E@@QAEHH@Z @0x002E0BC0 43B: id-gated compare
// (thiscall, 1 int arg). Looks the id up through landed
// Rva002BA8F1Logic::find on g_00DFEF10 (null index); false on miss,
// else forwards the player to landed rva002E071E (player-to-other
// conversion unproven, explicit cast) and zero-extends its bool into the
// int result (retail movzx eax,al at 0x002E0BE0). Owner reuses Rva002E071E
// so the rowed call resolves. NOTE the return type is a one-way street: the
// three retail callers (0x0056B7A0, 0x005003DF, 0x0009C814) each test only
// AL after the call. A caller keeps that byte test by calling this int
// spelling and casting the result to unsigned char (Rva005003DF.cpp does);
// a byte-returning view of its own does not resolve.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E2903Player;

#include "../../Include/GameLogic/Rva002BA8F1Logic.h"

#include "../../Include/GameLogic/Rva002E071E.h"

// ?rva002E0BC0@Rva002E071E@@QAEHH@Z
int Rva002E071E::rva002E0BC0(int id)
{
	Rva002E2903Player *p = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(id, 0);
	if (p != 0) {
		return rva002E071E((const Rva002E071E *)p);
	}
	return 0;
}
