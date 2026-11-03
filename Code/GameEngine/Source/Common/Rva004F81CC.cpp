// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// ?rva004F81CC@LivingWorldAutoResolveBattle@@QAEHH@Z @ 0x004F81CC (15B). Forward to rowed 0x004F7B42 with
// member at +0x7c as second arg. Evidence: push [ecx+0x7c] push [esp+8] call ret 4,
// callee rowed, caller 0x005EAB6D, chain from 0x004F7B42.
class Rva004F7B42
{
public:
	int rva004F7B42(int a1, int a2);
};

#include "../../Include/GameLogic/LivingWorldAutoResolveBattle.h"

int LivingWorldAutoResolveBattle::rva004F81CC(int a)
{
	return ((Rva004F7B42 *)this)->rva004F7B42(a, field7C);
}
