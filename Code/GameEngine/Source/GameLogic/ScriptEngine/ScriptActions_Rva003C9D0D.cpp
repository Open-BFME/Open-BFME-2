// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ?rva003C9D0D@ScriptActions@@QAEXABVAsciiString@@M@Z, retail 0x003C9D0D,
// 321 bytes (called from the action dispatcher 0x003CA4BE at 0x003CE56A).
// A BFME2 script action: walking the kind-7 objects that relate to the
// team's controlling player by flags 2 within the range of the team's
// centre (0x0039DA2A) from near to far, at the first whose body reports
// below 1 (body slot 5), every team member of kind bit 14 with an AI gets the
// AI command 0x0036F19B on it.
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

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
#include "../../../Include/GameLogic/Rva00261409Filter.h"

#include "../../../Include/GameLogic/Module/Rva00045411BitSet.h"
template<int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

// The +0x254 body module interface; only the slot this action calls.
#include "../../../Include/GameLogic/Module/BodyModule.h"

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../Include/Common/ThingTemplate.h"

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getAIUpdateInterface copy loses to the first-in-order copy. No flags touched.
	AIUpdateInterface *bfme_getAIUpdateInterface_de3c5() { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	char m_pad000[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x254 - 8];
	BodyModuleInterface *m_body;		// +0x254
	AIUpdateInterface *m_ai;		// +0x258
};

template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();						// 0x00263526
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	char m_pad[20];
};

#include "../../../Include/Common/TeamBFME2.h"

#include "../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
public:
	void rva003C9D0D(const AsciiString &teamName, float range);
};

void ScriptActions::rva003C9D0D(const AsciiString &teamName, float range)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	Coord3D center;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(team->rva0039DA2A(&center), range, 0,
		Rva00261409Filter(team->getControllingPlayer(), true, 2)
			.link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)), 1);

	Object *building;
	while ((building = iter.next()) != 0) {
		BodyModuleInterface *body = building->getBodyModule();
		if (body && body->getHealthRatio() < 1.0f) {
			for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
				Object *member = it.cur();
				if ((member->m_template->m_kindof[0] & (1u << 14)) && member->bfme_getAIUpdateInterface_de3c5())
					member->bfme_getAIUpdateInterface_de3c5()->rva0036F19B(building, CMD_FROM_SCRIPT);
			}
			break;
		}
	}
}
