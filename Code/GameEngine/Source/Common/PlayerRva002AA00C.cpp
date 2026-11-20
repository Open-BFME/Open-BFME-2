// cl: /DNDEBUG /MD
// ?rva002AA00C@Player@@QAEEPAVThingTemplate@@H@Z RVA 0x002AA00C size 37
// Evidence: unlock lane; caller 0x003BCF2F passes Player in ecx with ThingTemplate void eax plus int 0; callee 0x0033A69A ThingTemplate const method pin-only; reads ecx+0x94 ret8 sbb-inc uchar.

#include "../../Include/Common/ThingTemplate.h"
#include "../../Include/Common/Player.h"
unsigned char Player::rva002AA00C(ThingTemplate *thingTemplate, int extra)
{
	int base = m_money.m_val04;
	int v = thingTemplate->rva0033A69A((const class Player *)this, 0, -1);
	return (unsigned char)((unsigned)(base + extra) >= (unsigned)v);
}
