// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ScriptActions::doUnitGarrisonNearestBuilding, retail 0x003C8F86, 299 bytes
// (called from the action dispatcher 0x003CA4BE at 0x003CC1DF). Zero Hour's
// body without the money-hacker internet-centre switch and the locomotor
// reset, over BFME2's linked filters: walking objects of kinds 7 and 118
// that share the unit's map status from near to far, the unit enters (the
// AI command 0x0026C347) the first whose contain module (+0x250) is free or
// already entered by the unit's player, skipping one whose slot-1 record
// exists with +0xDE clear.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
#include "ascii_string.h"

class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08; // +0x08
	BfmeFixedStorage0004543D m_24; // +0x24
};

// vftable 0x00BF91BC, allow 0x002611BF.
#include "../../../Include/GameLogic/Rva002611BFFilter.h"

// A KindOfMaskType with two kinds set (0x0006EE7A).
struct Rva0006EE7A
{
	Rva0006EE7A(int unused, int bit1, int bit2);
	unsigned int m_bits[7];
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

#include "../../../Include/Common/Player.h"

struct Rva003C8F86Contained
{
	char m_pad000[0xDE];
	bool m_DE;	// +0xDE
};

// The +0x250 contain module interface; only the slots this action calls.
#include "../../../Include/GameLogic/Module/ContainModule.h"

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../Object/object.h"

#include "../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
protected:
	void doUnitGarrisonNearestBuilding(const AsciiString &unitName);
};

void ScriptActions::doUnitGarrisonNearestBuilding(const AsciiString &unitName)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit)
		return;

	AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
	if (!ai)
		return;

	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(theUnit->getPosition(), REALLY_FAR, 2,
		Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva0006EE7A(0, 7, 118),
			*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE).link(&Rva002611BFFilter(theUnit)), 1);

	Object *theBuilding;
	while ((theBuilding = iter.next()) != 0) {
		ContainModuleInterface *contain = theBuilding->getContain();
		if (!contain)
			continue;
		if (((const Rva003C8F86Contained *)contain->asOpenContain()) && !((const Rva003C8F86Contained *)contain->asOpenContain())->m_DE)
			continue;
		unsigned int player = theBuilding->getContain()->getPlayerWhoEntered();
		if (player != 0 && player != theUnit->getControllingPlayer()->getPlayerMask())
			continue;
		ai->rva0026C347(theBuilding, CMD_FROM_SCRIPT);
		return;
	}
}
