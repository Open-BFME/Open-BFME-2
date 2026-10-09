// cl: /DNDEBUG /MD
//
// HordeAIUpdate's private-command overrides. Slots 13 and 23 of the vftable
// 0x00C505F8 whose slot-2 name getter returns "HordeAIUpdate" replace the
// AIUpdateInterface entries every other AI module keeps there (the rowed
// privateMoveToPosition 0x0026B487 and bfmePrivateCommand42 0x0026D56C);
// each runs the base command only when the owner has the provider at
// Object+0x250 answering slot 31 (the rowed Object::rva0028C197).
//
// ?privateMoveToPosition@HordeAIUpdate@@MAEXPBUCoord3D@@MW4CommandSourceType@@@Z, retail 0x0049A93B, 56 bytes.
// Slot 13 (HordeWorkerAIUpdate 0x00C508C8 inherits it); the provider test
// is inlined.

#include "../../../../Common/GameLogicObjectLookupView.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

// The command values are numbered only; the porcupine-formation tables below
// list every value from 0 through 0x53 except 0x52, which (as in the
// WorldBuilder build) falls to the DEBUG_CRASH default.
enum AICommandType
{
	AICMD_NUM_TESTED = 0x54
};

class Object;
class AIUpdateInterface;

struct AICommandParms
{
	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	Object *m_obj; // +0x14
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_5A = 0x5A
};

#define SLOT_GAP10(p, n) virtual void p##n##0(); virtual void p##n##1(); virtual void p##n##2(); virtual void p##n##3(); virtual void p##n##4(); \
	virtual void p##n##5(); virtual void p##n##6(); virtual void p##n##7(); virtual void p##n##8(); virtual void p##n##9();

// The horde contain answering Object+0x250's slot 31. Slot names are
// inferred from use, not from target symbols.
class HordeContainInterface
{
public:
	virtual void h000(); virtual void h001(); virtual void h002(); virtual void h003();
	virtual void refreshFormation(bool value); // slot 4 (+0x10)
	virtual void slot5(Object *target); // slot 5 (+0x14)
	virtual void h006(); virtual void h007(); virtual void h008(); virtual void h009();
	SLOT_GAP10(h, 1)
	virtual void h020(); virtual void h021(); virtual void h022();
	virtual bool slot23(); // slot 23 (+0x5C)
	virtual void slot24(); // slot 24 (+0x60)
	virtual void h025(); virtual void h026(); virtual void h027(); virtual void h028(); virtual void h029();
	virtual void h030(); virtual void h031(); virtual void h032(); virtual void h033(); virtual void h034();
	virtual void h035(); virtual void h036();
	virtual bool slot37(); // slot 37 (+0x94)
	virtual void h038(); virtual void h039();
	SLOT_GAP10(h, 4) SLOT_GAP10(h, 5)
	virtual bool slot60(); // slot 60 (+0xF0)
};

class Rva0028C197Provider
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual bool s04(); // slot 4 (+0x10)
	virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual HordeContainInterface *s31();
};

// Object+0x254's body module; slot 5 is compared against 1.0 (name not
// recovered).
class BodyModuleView
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03(); virtual void b04();
	virtual float slot5(); // slot 5 (+0x14)
};

class Object
{
public:
	__forceinline HordeContainInterface *providedEntry() const
	{
		Rva0028C197Provider *provider = m_250;
		return provider ? provider->s31() : 0;
	}
	Rva0028C197Provider *provider() const { return m_250; }
	BodyModuleView *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAI() const { return m_ai; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Object *object274() const { return m_274; }
	void *rva0028C197() const;
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
private:
	char m_unrecovered00[0x250];
	Rva0028C197Provider *m_250;
	BodyModuleView *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	char m_unrecovered25C[0x274 - 0x25C];
	Object *m_274;
	char m_unrecovered278[0x438 - 0x278];
	unsigned char m_privateStatus; // +0x438
};

// TheControlBar (0x00E01CFC); +0x28 is the UI-dirty flag other users set.
class ControlBar
{
public:
	void markUIDirty() { m_UIDirty = true; }
private:
	char m_unrecovered00[0x28];
	bool m_UIDirty;
};

extern ControlBar *TheControlBar;

class ActionManager
{
public:
	bool canRepairObject(const Object *obj, const Object *objectToRepair, CommandSourceType cmdSource);
};

extern ActionManager *TheActionManager;

extern GameLogic *TheGameLogic;

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	Object *getObject() const { return m_object; }
private:
	void *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_reserved1C; // +0x1C
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiIdle(CommandSourceType cmdSource);
};

// Primary vftable 0x008505F8 (HordeAIUpdate's), slot 0 the destructor; the
// AICommandInterface at +0x20 uses vftable 0x00850528.
class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
protected:
	virtual void a001(); virtual void a002(); virtual void a003(); virtual void a004(); virtual void a005();
	virtual void a006(); virtual void a007(); virtual void a008(); virtual void a009(); virtual void a010();
	virtual void a011(); virtual void a012();
	virtual void privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource); // slot 13
	virtual void a014(); virtual void a015(); virtual void a016(); virtual void a017(); virtual void a018(); virtual void a019();
	virtual void a020(); virtual void a021(); virtual void a022();
	virtual void bfmePrivateCommand42(Object *obj, CommandSourceType cmdSource); // slot 23 (+0x5C)
	virtual void a024(); virtual void a025(); virtual void a026(); virtual void a027(); virtual void a028(); virtual void a029();
	SLOT_GAP10(a, 03)
	virtual void a040(); virtual void a041(); virtual void a042(); virtual void a043();
	virtual void privateRepair(Object *obj, CommandSourceType cmdSource); // slot 44 (+0xB0)
	virtual void a045(); virtual void a046(); virtual void a047(); virtual void a048(); virtual void a049();
	SLOT_GAP10(a, 05) SLOT_GAP10(a, 06)
	SLOT_GAP10(a, 07) SLOT_GAP10(a, 08) SLOT_GAP10(a, 09) SLOT_GAP10(a, 10)
public:
	virtual bool isIdle() const; // slot 110 (+0x1B8)
	virtual void a111(); virtual void a112(); virtual void a113(); virtual void a114();
	virtual void a115(); virtual void a116(); virtual void a117(); virtual void a118(); virtual void a119();
	virtual void a120(); virtual void a121(); virtual void a122(); virtual void a123(); virtual void a124();
	virtual void a125(); virtual void a126(); virtual void a127(); virtual void a128(); virtual void a129();
	SLOT_GAP10(a, 13)
protected:
	virtual void a140(); virtual void a141(); virtual void a142(); virtual void a143(); virtual void a144();
	virtual void a145(); virtual void a146(); virtual void a147();
	virtual bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const; // slot 148 (+0x250)
};

class HordeAIUpdate : public AIUpdateInterface
{
protected:
	virtual void bfmePrivateCommand42(Object *obj, CommandSourceType cmdSource);
public:
	virtual UpdateSleepTime update();
	virtual void aiDoCommand(const AICommandParms *parms);
	bool commandCancelsPorcupineFormation(const AICommandParms *parms);
	bool porcupineFormationIgnoresCommand(const AICommandParms *parms);
protected:
	virtual void privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource);
};

// Placeholder owners of two rowed HordeWorkerAIUpdate helpers whose names
// are not recovered: 0x0049ADB7 (the ObjectID check sibling of 0x0049AE5E)
// and 0x0049B0BF (the command 0x13 worker; its argument is the command's
// object). Both take the HordeWorkerAIUpdate as this.
class Rva0049AE5E
{
public:
	void rva0049AE5E();
	void rva0049ADB7();
};

struct Rva0049B0BFData;

class Rva0049B0BF
{
public:
	void rva0049B0BF(Rva0049B0BFData *arg, int arg2);
};

class ObjectIDView
{
public:
	ObjectID getID() const { return m_id; }
private:
	char m_unrecovered00[0x74];
	ObjectID m_id; // +0x74
};

// HordeWorkerAIUpdate (vftable 0x00C508C8) calls HordeAIUpdate::aiDoCommand
// directly, so it derives from HordeAIUpdate here. Member names are not
// recovered; +0x3E8/+0x3EC/+0x3F0 are the ObjectIDs its xfer saves.
class HordeWorkerAIUpdate : public HordeAIUpdate
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	virtual UpdateSleepTime update();
protected:
	virtual void bfmePrivateCommand42(Object *obj, CommandSourceType cmdSource);
private:
	char m_unrecovered24[0x3E8 - 0x24];
	ObjectID m_3E8;
	ObjectID m_3EC;
	ObjectID m_3F0;
};

// ?privateMoveToPosition@HordeAIUpdate@@MAEXPBUCoord3D@@MW4CommandSourceType@@@Z @0x0049A93B
void HordeAIUpdate::privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource)
{
	if (getObject()->providedEntry())
		AIUpdateInterface::privateMoveToPosition(pos, speed, cmdSource);
}

// ?commandCancelsPorcupineFormation@HordeAIUpdate@@QAE_NPBUAICommandParms@@@Z @0x0049A6DC
// WorldBuilder names it (HordeAIUpdate.cpp, DEBUG_CRASH default at line 476);
// its only caller is the unrowed command dispatcher at 0x0049A9A9.
bool HordeAIUpdate::commandCancelsPorcupineFormation(const AICommandParms *parms)
{
	switch (parms->m_cmd)
	{
	case 46:
	case 48:
		return true;

	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 58:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
	case 83:
		return parms->m_cmdSource == CMD_FROM_PLAYER;

	case 5:
	case 21:
	case 22:
	case 38:
	case 39:
	case 45:
	case 47:
	case 59:
	case 67:
		return false;

	default:
		return false;
	}
}

// WorldBuilder names it; called from the same dispatcher at 0x0049A9A9.
bool HordeAIUpdate::porcupineFormationIgnoresCommand(const AICommandParms *parms)
{
	switch (parms->m_cmd)
	{
	case 38:
	case 39:
	case 45:
	case 47:
	case 59:
	case 67:
		return true;

	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 46:
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 58:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
	case 83:
		return true;

	case 11:
		return false;

	default:
		return false;
	}
}

// ?aiDoCommand@HordeAIUpdate@@UAEXPBUAICommandParms@@@Z @0x0049A9A9
// Slot 0 of the AICommandInterface vftable 0x00850528 (this is +0x20);
// HordeWorkerAIUpdate's override calls it directly (0x0049B279). Control flow
// follows the WorldBuilder body, which calls both porcupine tests above and
// ends in AIUpdateInterface::aiDoCommand (pinned 0x002673F6).
void HordeAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	if (!isAllowedToRespondToAiCommands(parms))
		return;

	Object *obj = getObject();

	bool containerAnswers = false;
	Object *other = obj->object274();
	if (other)
	{
		Rva0028C197Provider *contain = other->provider();
		if (contain)
			containerAnswers = contain->s04();
	}

	HordeContainInterface *horde = static_cast<HordeContainInterface *>(obj->rva0028C197());
	if (horde && horde->slot60())
	{
		if (horde->slot23() && commandCancelsPorcupineFormation(parms))
		{
			horde->slot24();
			TheControlBar->markUIDirty();
		}
		else if (porcupineFormationIgnoresCommand(parms))
		{
			return;
		}
	}

	bool forward = false;
	Object *target = 0;
	switch (parms->m_cmd)
	{
	case 0:
	case 1:
	case 3:
	case 4:
	case 6:
	case 7:
	case 8:
	case 9:
	case 14:
	case 15:
	case 23:
	case 24:
	case 36:
	case 50:
	case 51:
	case 52:
	case 54:
	case 56:
	case 65:
	case 66:
	case 78:
		forward = true;
		break;

	case 11:
	case 12:
		forward = true;
		target = parms->m_obj;
		break;

	default:
		forward = false;
		break;
	}

	if (forward && !containerAnswers)
	{
		HordeContainInterface *hordeContain = obj->providedEntry();
		if (hordeContain)
		{
			if (obj->testStatus(OBJECT_STATUS_5A))
				obj->setStatus(OBJECT_STATUS_5A, false);
			hordeContain->slot5(target);
		}
	}

	AIUpdateInterface::aiDoCommand(parms);
}

// ?aiDoCommand@HordeWorkerAIUpdate@@UAEXPBUAICommandParms@@@Z @0x0049B231
// Slot 0 of HordeWorkerAIUpdate's AICommandInterface vftable (this is
// +0x20). Control flow follows the WorldBuilder body: a repair (0x13) of the
// object already held at +0x3EC is ignored; otherwise the rowed 0x0049ADB7
// runs, repair goes to the rowed 0x0049B0BF, command 0x42 to primary slot 23
// and everything else to HordeAIUpdate::aiDoCommand.
void HordeWorkerAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	if (!isAllowedToRespondToAiCommands(parms))
		return;

	if (parms->m_cmd == 0x13 && parms->m_obj
		&& m_3EC == reinterpret_cast<const ObjectIDView *>(parms->m_obj)->getID())
		return;

	reinterpret_cast<Rva0049AE5E *>(this)->rva0049ADB7();

	switch (parms->m_cmd)
	{
	case 0x13:
		reinterpret_cast<Rva0049B0BF *>(this)->rva0049B0BF(
			reinterpret_cast<Rva0049B0BFData *>(parms->m_obj), parms->m_cmdSource);
		break;

	case 0x42:
		bfmePrivateCommand42(parms->m_obj, parms->m_cmdSource);
		break;

	default:
		HordeAIUpdate::aiDoCommand(parms);
		break;
	}
}

// ?bfmePrivateCommand42@HordeWorkerAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z @0x0049B1CB
// Slot 23 of vftable 0x00C508C8 (Ghidra missed the body, 0x0049B1CB..
// 0x0049B231). A damaged target (body slot 5 below 1.0) that
// TheActionManager lets the worker repair is remembered at +0x3F0 and handed
// to the rowed 0x0049B0BF; with nothing remembered it falls back to
// HordeAIUpdate's slot 23 (0x0049AC5F).
void HordeWorkerAIUpdate::bfmePrivateCommand42(Object *obj, CommandSourceType cmdSource)
{
	BodyModuleView *body = obj->getBodyModule();
	if (body && body->slot5() < 1.0f
		&& TheActionManager->canRepairObject(getObject(), obj, cmdSource))
	{
		m_3F0 = reinterpret_cast<const ObjectIDView *>(obj)->getID();
		reinterpret_cast<Rva0049B0BF *>(this)->rva0049B0BF(
			reinterpret_cast<Rva0049B0BFData *>(obj), cmdSource);
	}

	if (m_3F0 == INVALID_OBJECT_ID)
		HordeAIUpdate::bfmePrivateCommand42(obj, cmdSource);
}

// ?update@HordeWorkerAIUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0049AEA4
// Slot 0 of the UpdateModuleInterface vftable 0x008508BC (this is +0x10).
// The rowed 0x0049AE5E first drops ObjectIDs whose objects are gone; then a
// pending repair (+0x3E8 set, target +0x3EC) is issued once the AI is idle,
// a held repair target (+0x3EC) is released when fully healed or gone, and
// a remembered slot-23 target (+0x3F0) is handed to HordeAIUpdate's slot
// 23. Otherwise HordeAIUpdate::update runs.
UpdateSleepTime HordeWorkerAIUpdate::update()
{
	Object *obj = getObject();
	if (!obj)
		return UPDATE_SLEEP_FOREVER;

	HordeContainInterface *horde = static_cast<HordeContainInterface *>(obj->rva0028C197());
	if (!horde)
		return UPDATE_SLEEP_FOREVER;

	reinterpret_cast<Rva0049AE5E *>(this)->rva0049AE5E();

	if (m_3E8 != INVALID_OBJECT_ID)
	{
		Object *target = TheGameLogic->findObjectByID(m_3EC);
		if (target == 0 || target->isEffectivelyDead())
		{
			obj->getAI()->aiIdle(CMD_FROM_AI);
			m_3E8 = INVALID_OBJECT_ID;
			return UPDATE_SLEEP_NONE;
		}

		if (obj->getAI()->isIdle() && !horde->slot37())
		{
			Object *repairTarget = TheGameLogic->findObjectByID(m_3EC);
			if (repairTarget)
				privateRepair(repairTarget, CMD_FROM_AI);
			m_3E8 = INVALID_OBJECT_ID;
			return UPDATE_SLEEP_NONE;
		}

		return HordeAIUpdate::update();
	}

	if (m_3EC != INVALID_OBJECT_ID)
	{
		Object *target = TheGameLogic->findObjectByID(m_3EC);
		if (target == 0 || target->isEffectivelyDead()
			|| target->getBodyModule()->slot5() == 1.0f)
		{
			horde->refreshFormation(true);
			m_3EC = INVALID_OBJECT_ID;
		}
		return UPDATE_SLEEP_NONE;
	}

	if (m_3F0 != INVALID_OBJECT_ID)
	{
		Object *target = TheGameLogic->findObjectByID(m_3F0);
		if (target)
			HordeAIUpdate::bfmePrivateCommand42(target, CMD_FROM_AI);
		m_3F0 = INVALID_OBJECT_ID;
		return UPDATE_SLEEP_NONE;
	}

	return HordeAIUpdate::update();
}
