// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?update@HordeAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// retail 0x0049AB10, 335 bytes.
//
// Identity: WorldBuilder HordeAIUpdate::update (HordeAIUpdate.cpp, assert
// "hordeContain != NULL" at line 76); same call graph as the retail body
// (testStatus, isMoving, the frame compare through 0x0028AF76,
// aiMoveToPosition, and AIUpdateInterface::update 0x0026E267 at both exits).
// The release build drops the null-contain assert and early return, the
// debug state-name log and the debug Coord3D initializer; the status clear
// calls Object::setStatus(status, bool) 0x0023DB0E directly.
//
// Target layout: update is reached through the UpdateModuleInterface at
// +0x10 (object at this-8, primary vtable at this-0x10, isIdle in primary
// slot 110 / +0x1B8). Object: contain module +0x250 (horde contain through
// slot 31 / +0x7C, contained-by query through slot 69 / +0x114), AI +0x258
// with its AICommandInterface at +0x20. Horde contain slots used: 4 (+0x10)
// formation refresh, 38 (+0x98) member notify, 39 (+0x9C), 40 (+0xA0), 41
// (+0xA4), 55 (+0xDC) per-frame update, 75 (+0x12C) and 146 (+0x248) the
// rally position. Slot names are inferred from use, not from target symbols.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0
#define TRUE 1
#define FALSE 0

#include "../../../../Common/GameLogicObjectLookupView.h"

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

class ModuleData;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_3 = 3,
	OBJECT_STATUS_5A = 0x5A
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

// LogicFramesPerSecond.
extern int g_Va00DBA4E4;
#define LogicFramesPerSecond g_Va00DBA4E4

#define SLOT_GAP10(p, n) virtual void p##n##0(); virtual void p##n##1(); virtual void p##n##2(); virtual void p##n##3(); virtual void p##n##4(); \
	virtual void p##n##5(); virtual void p##n##6(); virtual void p##n##7(); virtual void p##n##8(); virtual void p##n##9();

class Object;

class HordeContainInterface
{
public:
	virtual void h000(); virtual void h001(); virtual void h002(); virtual void h003();
	virtual void refreshFormation(Bool value); // slot 4
	virtual void h005(); virtual void h006(); virtual void h007(); virtual void h008(); virtual void h009();
	SLOT_GAP10(h, 1) SLOT_GAP10(h, 2)
	virtual void h030(); virtual void h031(); virtual void h032(); virtual void h033(); virtual void h034();
	virtual void h035(); virtual void h036(); virtual void h037();
	virtual void notifyMember(Object *member); // slot 38
	virtual Bool slot39(); // slot 39
	virtual Bool slot40(); // slot 40
	virtual Bool isReady(); // slot 41
	virtual void h042(); virtual void h043(); virtual void h044(); virtual void h045(); virtual void h046();
	virtual void h047(); virtual void h048(); virtual void h049();
	virtual void h050(); virtual void h051(); virtual void h052(); virtual void h053(); virtual void h054();
	virtual void update(); // slot 55
	virtual void h056(); virtual void h057(); virtual void h058(); virtual void h059();
	SLOT_GAP10(h, 6)
	virtual void h070(); virtual void h071(); virtual void h072(); virtual void h073(); virtual void h074();
	virtual Bool slot75(); // slot 75
	virtual void h076(); virtual void h077(); virtual void h078(); virtual void h079();
	SLOT_GAP10(h, 8) SLOT_GAP10(h, 9) SLOT_GAP10(h, 10) SLOT_GAP10(h, 11) SLOT_GAP10(h, 12) SLOT_GAP10(h, 13)
	virtual void h140(); virtual void h141(); virtual void h142(); virtual void h143(); virtual void h144();
	virtual void h145();
	virtual Bool getRallyPosition(Coord3D *pos); // slot 146
};

class ContainModuleInterface
{
public:
	SLOT_GAP10(c, 0) SLOT_GAP10(c, 1) SLOT_GAP10(c, 2)
	virtual void c030();
	virtual HordeContainInterface *getHordeContainInterface(); // slot 31
	virtual void c032(); virtual void c033(); virtual void c034(); virtual void c035(); virtual void c036();
	virtual void c037(); virtual void c038(); virtual void c039();
	SLOT_GAP10(c, 4) SLOT_GAP10(c, 5)
	virtual void c060(); virtual void c061(); virtual void c062(); virtual void c063(); virtual void c064();
	virtual void c065(); virtual void c066(); virtual void c067(); virtual void c068();
	virtual Object *getContainer(Int value); // slot 69
};

class AIUpdateInterface;

extern GameLogic *TheGameLogic;

class Object
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, Bool set);
	Int rva0028AF76() const;

private:
	char m_unknown00[0x250];
	ContainModuleInterface *m_contain; // +0x250
	char m_unknown254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	virtual UpdateSleepTime update();
	// Primary vtable slots 1..109 (slot 0 is BehaviorModuleBase's).
	SLOT_GAP10(a, 0) SLOT_GAP10(a, 1) SLOT_GAP10(a, 2) SLOT_GAP10(a, 3) SLOT_GAP10(a, 4)
	SLOT_GAP10(a, 5) SLOT_GAP10(a, 6) SLOT_GAP10(a, 7) SLOT_GAP10(a, 8) SLOT_GAP10(a, 9)
	virtual void a100(); virtual void a101(); virtual void a102(); virtual void a103(); virtual void a104();
	virtual void a105(); virtual void a106(); virtual void a107(); virtual void a108();
	virtual Bool isIdle() const; // slot 110

	Bool isMoving() const;
};

class HordeAIUpdate : public AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();
};

//-------------------------------------------------------------------------------------------------
UpdateSleepTime HordeAIUpdate::update( void )
{
	Object *obj = getObject();
	HordeContainInterface *hordeContain = obj->getContain()->getHordeContainInterface();

	if (hordeContain->slot75() == TRUE)
		return AIUpdateInterface::update();

	Object *container = obj->getContain()->getContainer(0);
	Bool ready = hordeContain->isReady();
	if (container == NULL && isIdle() && ready
		&& !obj->testStatus(OBJECT_STATUS_3) && !obj->testStatus(OBJECT_STATUS_5A))
	{
		hordeContain->notifyMember(obj);
	}

	if (!isMoving())
	{
		if ((UnsignedInt)getObject()->rva0028AF76() < TheGameLogic->getFrame() - LogicFramesPerSecond)
		{
			Bool formationValue = TRUE;
			Bool refresh = TRUE;
			if (obj->testStatus(OBJECT_STATUS_5A) && !hordeContain->slot40())
			{
				formationValue = FALSE;
				obj->setStatus(OBJECT_STATUS_5A, FALSE);
				Coord3D pos;
				if (hordeContain->getRallyPosition(&pos))
				{
					hordeContain->refreshFormation(FALSE);
					obj->getAI()->aiMoveToPosition(&pos, CMD_FROM_AI);
					refresh = FALSE;
				}
			}
			if (hordeContain->slot39() && refresh)
				hordeContain->refreshFormation(formationValue);
		}
	}

	hordeContain->update();
	return AIUpdateInterface::update();
}
