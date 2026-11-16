// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?onEnter@Rva00342572@@QAEHXZ, retail 0x00342572, 46 bytes.
// Chain from 0x0033F8D4 (AIUpdateInterface::rva0033F8D4 FLT_MAX check).
// Gets AIUpdateInterface via this+0x18->+0x14->+0x258, calls the predicate;
// when false returns -1, when true copies its +0x1A0 float to +0x20 and
// returns 0. Callers none (leaf). Layout is pad to +0x18 plus pointer plus
// float at +0x20. Identity stays honest Rva.

#include "../../Include/GameLogic/Module/AIUpdate.h"

struct Mid00342572_14
{
	char m_pad00[0x258];
	AIUpdateInterface *m_258;
};

struct Mid00342572_18
{
	char m_pad00[0x14];
	Mid00342572_14 *m_14;
};

class Rva00342572
{
public:
	int onEnter();

private:
	char m_pad00[0x18];
	Mid00342572_18 *m_18;
	char m_pad1C[0x20 - 0x1C];
	float m_20;
};

int Rva00342572::onEnter()
{
	Mid00342572_14 *mid14 = m_18->m_14;
	AIUpdateInterface *ai = mid14->m_258;
	if (!ai->rva0033F8D4()) {
		return -1;
	}
	m_20 = ai->m_field1A0;
	return 0;
}
