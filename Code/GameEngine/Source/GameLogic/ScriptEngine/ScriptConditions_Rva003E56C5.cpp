// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ScriptConditions::evaluateEnemySighted, retail 0x003E56C5, 422 bytes (caller
// 0x003EAE77 in the condition dispatcher 0x003EA9AF). Zero Hour's
// evaluateEnemySighted made BFME2: for each player of the parameter's player
// mask (0x00357B82), whether anything that player owns, in the alliance
// relationship (0x003E40AF) to the named unit, alive, not of KindOf bits 89
// or 134, lies within the unit's vision range through BFME2's partition
// filter chain (the view AIStructureCreepTactic.cpp documents).
#include "ascii_string.h"

class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a
// player, +0x0C whether a hit allows.
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
#include "../../../Include/GameLogic/Rva0026119DFilter.h"

// vftable 0x00BF8FE4, allow 0x0026109D; the out-of-line ctor 0x00261058.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);	// 0x00261058
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00C0719C, allow 0x00261513: +0x08 an object, +0x0C a flag,
// +0x10 a float.
class Rva00261513Filter : public Rva000421C8
{
public:
	Rva00261513Filter(const Object *obj, bool flag, float value)
		: m_obj(obj), m_flag(flag), m_value(value) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	bool m_flag;
	float m_value;
};

// vftable 0x00BF91BC, allow 0x002611BF.
#include "../../../Include/GameLogic/Rva002611BFFilter.h"

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C
// relationship flags, +0x10 whether a hit allows.
#include "../../../Include/GameLogic/Rva00260EB1Filter.h"

// The 224-bit KindOf mask; the (unused, bit, bit) constructor is 0x0006EE7A.
struct Rva0006EE7A
{
	unsigned m_bits[7];
	Rva0006EE7A(int unused, int b1, int b2) throw();	// 0x0006EE7A
};

#include "../../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#include "../Object/object.h"

#include "../../../Include/GameLogic/ScriptParameter.h"

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluateEnemySighted(const AsciiString &unitName, Parameter *allianceParm, Parameter *playerParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unitName);
	if (!theObj)
		return false;
	int relationDescriber = rva003E40AF(allianceParm->getInt());
	int mask = TheScriptEngine->rva00357B82(playerParm);
	if (!mask)
		return false;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (ThePartitionManager->getClosestObject(theObj->getPosition(), theObj->getVisionRange(), 0,
				Rva0026137EFilter(player, true).link(Rva00260EB1Filter(theObj, relationDescriber, false).link(
					Rva0026119DFilter().link(Rva00261058(theObj, false).link(Rva002611BFFilter(theObj).link(
						Rva00261513Filter(theObj, true, -1.0f).link(
							&Rva0004584D(*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
								(const BfmeFixedStorage0004543D &)Rva0006EE7A(0, 0x59, 0x86))))))))) != 0)
			return true;
	} while (mask);
	return false;
}
