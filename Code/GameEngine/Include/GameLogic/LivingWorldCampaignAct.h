// Target facts (code addresses are RVAs; table addresses are VAs): ParseEnableRegion 0x004E1579 builds an
// EnableRegionRecord on the stack, fills it through the field table at VA 0x00C61A50 ("Region" at +4) and
// hands it by reference to the act's append thunk 0x00566527. The record is eight bytes: the vftable
// VA 0x00C61A20 at +0 and an AsciiString at +4. Its destructor 0x004E156B releases the string; its copy
// constructor 0x0052BD3A copies the vftable and the string, and is compiler-generated (emitted where a
// record is copied, through _Construct 0x0052C2F3 and the act's vector<EnableRegionRecord>).
// The record is an entry of a LivingWorld campaign act (LivingWorldCampaignAct.cpp's keyword table names
// ParseEnableRegion beside ForceBattle, SpawnArmy and MoveArmy). Its name is a blind-agreed recovery
// (nr-0da3866284da5687290c2342), not a retail symbol.
#pragma once

#ifndef BFME2_GAMELOGIC_LIVINGWORLDCAMPAIGNACT_H
#define BFME2_GAMELOGIC_LIVINGWORLDCAMPAIGNACT_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class EnableRegionRecord
{
public:
	virtual ~EnableRegionRecord() {}

private:
	AsciiString m_name;
};

#endif // BFME2_GAMELOGIC_LIVINGWORLDCAMPAIGNACT_H
