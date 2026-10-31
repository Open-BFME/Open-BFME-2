// ?getSupplyBoxValue@Player@@QAEHXZ @ 0x002A9DAC (12B). Global-indirect
// dword getter. Evidence: mov eax,[0x009FE758]; mov eax,[eax+0xA5C]; ret.
// Callers at 0x003EA6E5 0x004A0F09 0x004C839D load ECX first (the player),
// so this is a member that ignores this; 0x003EA6E5 multiplies the result
// by a SupplyWarehouseDockUpdate box count, as Zero Hour's
// Player::getSupplyBoxValue (TheGlobalData->m_baseValuePerSupplyBox) is
// used. The int return is the consumers' spelling; offset 0xA5C is opaque.

extern class GlobalData *TheWritableGlobalData;

struct Rva002A9DACHolder
{
	char _pad[0xA5C];
	int m_value;
};

#define TheRva002A9DAC (*(Rva002A9DACHolder **)&TheWritableGlobalData)

#include "../../Include/Common/Player.h"

int Player::getSupplyBoxValue()
{
	return TheRva002A9DAC->m_value;
}
