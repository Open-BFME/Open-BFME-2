// cl: /DNDEBUG /MD /GX
//
// FellBeastSwoopPower::triggerAbilityEffect, slot 17 (vftable 0x00C5DF80; the
// slot-17 name of 23 sibling special-ability tables), retail 0x004C6E06, 67
// bytes, on the primary this, and the two AICommandInterface commands it
// issues, which retail emits as copies in this unit beside it.
//
//   0x004C6E06  when the Object has an AI (+0x258): the Object TheGameLogic
//               finds for the ID at +0x40 gets command 0x3F from CMD_FROM_AI;
//               without one, the position at +0x44 gets command 0x40.
//   0x004C6D35  (101 bytes) AICommandParms 0x3F with the Object, then
//               aiDoCommand (slot 0).
//   0x004C6D9A  (108 bytes) AICommandParms 0x40 with the position, then
//               aiDoCommand.
// The commands build the stack AICommandParms through the rowed ctor
// 0x00351BD0 and free its coordinate buffer inline on the way out, the recipe
// of the rowed AICommandInterface commands (AICommandInterfaceAttackCommands.cpp,
// Rva00336B23AICommand.cpp). The commands keep address names.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;

#include "../../../../Include/Common/BfmeXfer.h"

enum AICommandType
{
	AICMD_BFME_3F = 0x3F,
	AICMD_BFME_40 = 0x40
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);	// 0x00351BD0
	~AICommandParms() { if (m_coordsStart) free(m_coordsStart); }

	AICommandType m_cmd;		// +0x00
	CommandSourceType m_cmdSource;	// +0x04
	Coord3D m_pos;			// +0x08
	Object *m_obj;			// +0x14
	Object *m_otherObj;		// +0x18
	const void *m_team;		// +0x1C
	void *m_coordsStart;		// +0x20
	void *m_coordsFinish;		// +0x24
	void *m_coordsEnd;		// +0x28
	char m_tail[0xC0 - 0x2C];
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	void rva004C6D35(Object *obj, CommandSourceType cmdSource);
	void aiAttackLevelPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

template <int N> class Rva004C6E49Slots : public Rva004C6E49Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C6E49Slots<0>
{
};

// The Object +0x258 AI interface: slots 110 and 116 are the bool queries
// update reads; the command interface sits at +0x20.
class AIUpdateInterface : public Rva004C6E49Slots<110>
{
public:
	virtual bool rva004C6E49Slot110() = 0;
	virtual void gap111() = 0;
	virtual void gap112() = 0;
	virtual void gap113() = 0;
	virtual void gap114() = 0;
	virtual void gap115() = 0;
	virtual bool rva004C6E49Slot116() = 0;
	AICommandInterface *getCommandInterface() { return &m_commandInterface; }
private:
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_commandInterface;	// +0x20
};

#include "../../../Common/GameLogicObjectLookupView.h"

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
	virtual ~GeometryInfo();
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14; // +0x14
	unsigned char m_pad18[0x5C - 0x18];
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual float getGroundHeight(float x, float y, Coord3D *normal) const;
};
extern TerrainLogic *TheTerrainLogic;

// Model-condition bits: the word array of the Object starts at +0x10C; a bit
// index is word*32 + bit. The accessors return the masked word.
class Rva0010CConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
	void rva0028AE6D();
	unsigned char m_pad000[0x38];
	float m_x; // +0x38
	float m_y; // +0x3C
	float m_z; // +0x40
	unsigned char m_pad044[0xA8 - 0x44];
	GeometryInfo m_geometryInfo; // +0xA8
	unsigned char m_pad104[0x10C - 0x104];
	Rva0010CConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai;	// +0x258
};

extern GameLogic *TheGameLogic;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class SpecialPowerUpdateInterface
{
public:
	virtual void specialPowerUpdateAnchor();
};

// Primary vftable 0x00C5DF80 (the FellBeastSwoopPower ctor 0x004C6C1E installs
// it): slot 3 xfer, slot 4 getModuleNameKey, slot 13 onExit (SpecialAbilityUpdate
// base 0x004502CE), slot 17 triggerAbilityEffect; the other slot names are not
// established.
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void slot01();
	virtual void slot02();
protected:
	virtual void xfer(Xfer *xfer);
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12();
protected:
	virtual void onExit(bool a, bool b);
public:
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void triggerAbilityEffect();
protected:
	unsigned char m_pad24[0x40 - 0x24];
	ObjectID m_targetID;		// +0x40
	Coord3D m_targetPos;		// +0x44
	unsigned char m_pad50[0x88 - 0x50];
};

class FellBeastSwoopPower : public SpecialAbilityUpdate
{
public:
	virtual ~FellBeastSwoopPower();
	virtual NameKeyType getModuleNameKey() const;
	virtual void triggerAbilityEffect();
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
	virtual void onExit(bool a, bool b);
private:
	bool m_88; // +0x88
};

void AICommandInterface::rva004C6D35(Object *obj, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_3F, cmdSource);
	parms.m_obj = obj;
	aiDoCommand(&parms);
}

void AICommandInterface::aiAttackLevelPosition(const Coord3D *pos, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_40, cmdSource);
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

void FellBeastSwoopPower::triggerAbilityEffect()
{
	AIUpdateInterface *ai = Object::getAI(m_object);
	if (ai == 0)
		return;
	const Coord3D *pos = &m_targetPos;
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	if (target)
		ai->getCommandInterface()->rva004C6D35(target, CMD_FROM_AI);
	else if (pos)
		ai->getCommandInterface()->aiAttackLevelPosition(pos, CMD_FROM_AI);
}
