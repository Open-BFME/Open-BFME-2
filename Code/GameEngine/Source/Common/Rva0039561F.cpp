// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0039561F@Rva0039561F@@QAEHPAVThingTemplate@@@Z @0x0039561F (93B).
// Guarded lookup storing unsigned float: controlling player of m_obj8 must
// exist, then rowed rva0033A69A via pin 0x0033A69A plus rowed withdraw
// 0x003B0CB3 drive the value; stores (float)(unsigned)v to +0x4c (2^32 fadd
// for negative) and returns v. Caller 0x00399CD2. Prev/next /O1.
class Player;
#include "../GameLogic/Object/object.h"

#include "../../Include/Common/ThingTemplate.h"

class Rva0039B795;
#include "../../Include/GameLogic/Module/Rva003B0D7C.h"

#include "../../Include/Common/Player.h"

class Rva0039561F
{
public:
	int rva0039561F(ThingTemplate *t);
private:
	char m_pad[8];
	Object *m_obj8;
	char m_pad0C[0x4c - 0x0c];
	float m_4c;
};

// ?rva0039561F@Rva0039561F@@QAEHPAVThingTemplate@@@Z
int Rva0039561F::rva0039561F(ThingTemplate *thingTemplate)
{
	Object *object = m_obj8;
	if (object == 0)
		return 0;
	Player *pl = object->getControllingPlayer();
	if (pl == 0)
		return 0;
	int v = thingTemplate->rva0033A69A((const class Player *)pl, 0, -1);
	((Rva003B0D7C *)((char *)pl + 0x90))->withdraw(v, (Rva0039B795 *)((char *)pl + 0x3bc), true);
	m_4c = (float)(unsigned int)v;
	return v;
}
