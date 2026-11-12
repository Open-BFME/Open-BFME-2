// cl: /DNDEBUG /MD
//
// ?ScaleMoney@Player@@QAEHH@Z @0x002A9E36 118B: Player member that scales an
// amount by the living-world level of the player's linked entry. When the
// rowed TheGameLogic query 0x002034E9 holds and the id at +0x3AC is set, it
// looks the entry up through the rowed TheLivingWorldLogic find 0x002B51F8
// (0x00DFEF10) and returns ceil(value * (level * 0.01 + 1)) with the level from
// the rowed 0x002E0C2B, rounded through a fld/fistp REAL_TO_INT; otherwise
// the value is returned unchanged. Identity is address-derived.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <math.h>

#include "../../../Include/Common/Rva002034E9Host.h"
extern class GameLogic *TheGameLogic;

class Rva002E2903Player;

#include "../../../Include/GameLogic/Rva002BA8F1Logic.h"

#include "../../../Include/Common/Rva002E0C2B.h"

inline int Rva002A9E36RealToInt(float a)
{
	int b;
	__asm fld a
	__asm fistp b
	return b;
}

#include "../../../Include/Common/Player.h"

int Player::ScaleMoney(int value)
{
	if ((*(Rva002034E9Host **)&TheGameLogic)->rva002034E9() && m_3AC != -1)
	{
		Rva002E2903Player *entry = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(m_3AC, 0);
		if (entry)
		{
			int level = ((Rva002E0C2B *)entry)->rva002E0C2B();
			float factor = level * 0.01f + 1.0f;
			float amount = (float)value;
			// ceil(double) directly: the float overload emits ceil/ceilf COMDATs that lose the link.
			float scaled = (float)ceil((double)(amount * factor));
			return Rva002A9E36RealToInt(scaled);
		}
	}
	return value;
}
