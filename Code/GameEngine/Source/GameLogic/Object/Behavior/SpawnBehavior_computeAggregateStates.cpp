// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?computeAggregateStates@SpawnBehavior@@QAEXXZ, retail 0x0045FE9A, 731 bytes.
// Identity: the statements follow Zero Hour's SpawnBehavior::computeAggregateStates
// less the veterancy and weapon-bonus propagation, as BFME 1's
// SpawnBehaviorComputeAggregateStates.cpp (retail 0x0020BAE0) has them: the
// SlavedUpdate isSelfTasking count, the averaged spawn position written as
// the health box offset, the selected-group message 0x3E9 through the
// message stream, the aggregate initial health and Object::maskObject.
// BFME 2 layout read from retail: m_aggregateHealth at SpawnBehavior +0x51,
// m_selfTaskingSpawnCount +0x58, spawn IDs +0x4C, module data spawn number
// +0x08; Object position +0x38, behavior modules +0x244, body module +0x254,
// health box offset +0x310; Drawable selected flag +0x43C; getDrawable is the
// pinned non-virtual 0x005508E2. Behavior interface slot 26 is
// getSlavedUpdateInterface and SlavedUpdate slot 4 isSelfTasking; body slots
// 4, 6 and 21 are getHealth, getMaxHealth and setInitialHealth (with a
// second Bool, pushed false); message stream slot 18 is appendMessage and
// InGameUI slots 66 and 103 are selectDrawable and setDisplayedMaxWarning.
//
// GameLogic::findObjectByID is declared as the header inline over the object
// hash map at +0xB4 (BFME 2's out-of-line copy 0x00049DC5 reads node +8, the
// pair's second). MSVC still calls the out-of-line copy, but as in BFME 1 only
// the inline declaration gives retail's second-loop register assignment
// (list cursor spilled to the frame, the spawn in EDI).

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

class GameMessage
{
public:
	void appendBooleanArgument(Bool arg);
	void appendObjectIDArgument(ObjectID arg);
};

class MessageStream
{
public:
#define MS_SLOT(n) virtual void messageStreamSlot##n();
	MS_SLOT(00) MS_SLOT(01) MS_SLOT(02) MS_SLOT(03) MS_SLOT(04) MS_SLOT(05)
	MS_SLOT(06) MS_SLOT(07) MS_SLOT(08) MS_SLOT(09) MS_SLOT(10) MS_SLOT(11)
	MS_SLOT(12) MS_SLOT(13) MS_SLOT(14) MS_SLOT(15) MS_SLOT(16) MS_SLOT(17)
#undef MS_SLOT
	virtual GameMessage *appendMessage(Int type);
};
extern MessageStream *MessageStreamSubsystem;

class Drawable
{
public:
	Bool isSelected() const { return m_selected; }

private:
	unsigned char m_pad000[0x43c];
	Bool m_selected;
};

class InGameUI
{
public:
#define UI_SLOT(n) virtual void inGameUISlot##n();
	UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04) UI_SLOT(05)
	UI_SLOT(06) UI_SLOT(07) UI_SLOT(08) UI_SLOT(09) UI_SLOT(10) UI_SLOT(11)
	UI_SLOT(12) UI_SLOT(13) UI_SLOT(14) UI_SLOT(15) UI_SLOT(16) UI_SLOT(17)
	UI_SLOT(18) UI_SLOT(19) UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23)
	UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29)
	UI_SLOT(30) UI_SLOT(31) UI_SLOT(32) UI_SLOT(33) UI_SLOT(34) UI_SLOT(35)
	UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39) UI_SLOT(40) UI_SLOT(41)
	UI_SLOT(42) UI_SLOT(43) UI_SLOT(44) UI_SLOT(45) UI_SLOT(46) UI_SLOT(47)
	UI_SLOT(48) UI_SLOT(49) UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53)
	UI_SLOT(54) UI_SLOT(55) UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59)
	UI_SLOT(60) UI_SLOT(61) UI_SLOT(62) UI_SLOT(63) UI_SLOT(64) UI_SLOT(65)
	virtual void selectDrawable(Drawable *draw);
	UI_SLOT(67) UI_SLOT(68) UI_SLOT(69) UI_SLOT(70) UI_SLOT(71)
	UI_SLOT(72) UI_SLOT(73) UI_SLOT(74) UI_SLOT(75) UI_SLOT(76) UI_SLOT(77)
	UI_SLOT(78) UI_SLOT(79) UI_SLOT(80) UI_SLOT(81) UI_SLOT(82) UI_SLOT(83)
	UI_SLOT(84) UI_SLOT(85) UI_SLOT(86) UI_SLOT(87) UI_SLOT(88) UI_SLOT(89)
	UI_SLOT(90) UI_SLOT(91) UI_SLOT(92) UI_SLOT(93) UI_SLOT(94) UI_SLOT(95)
	UI_SLOT(96) UI_SLOT(97) UI_SLOT(98) UI_SLOT(99) UI_SLOT(100) UI_SLOT(101)
	UI_SLOT(102)
#undef UI_SLOT
	virtual void setDisplayedMaxWarning(Bool selected);
};
extern InGameUI *TheInGameUI;

class BodyModuleInterface
{
public:
#define BODY_SLOT(n) virtual void bodyModuleSlot##n();
	BODY_SLOT(00) BODY_SLOT(01) BODY_SLOT(02) BODY_SLOT(03)
	virtual Real getHealth() const;
	BODY_SLOT(05)
	virtual Real getMaxHealth() const;
	BODY_SLOT(07) BODY_SLOT(08) BODY_SLOT(09) BODY_SLOT(10) BODY_SLOT(11)
	BODY_SLOT(12) BODY_SLOT(13) BODY_SLOT(14) BODY_SLOT(15) BODY_SLOT(16)
	BODY_SLOT(17) BODY_SLOT(18) BODY_SLOT(19) BODY_SLOT(20)
#undef BODY_SLOT
	virtual void setInitialHealth(Real initialPercent, Bool unused);
};

class SlavedUpdateInterface
{
public:
	virtual void slavedUpdateSlot00();
	virtual void slavedUpdateSlot01();
	virtual void slavedUpdateSlot02();
	virtual void slavedUpdateSlot03();
	virtual Bool isSelfTasking() const;
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	void *m_moduleData;
	void *m_object;
};

class BehaviorModuleInterface
{
public:
#define BMI_SLOT(n) virtual void behaviorModuleInterfaceSlot##n();
	BMI_SLOT(00) BMI_SLOT(01) BMI_SLOT(02) BMI_SLOT(03) BMI_SLOT(04) BMI_SLOT(05)
	BMI_SLOT(06) BMI_SLOT(07) BMI_SLOT(08) BMI_SLOT(09) BMI_SLOT(10) BMI_SLOT(11)
	BMI_SLOT(12) BMI_SLOT(13) BMI_SLOT(14) BMI_SLOT(15) BMI_SLOT(16) BMI_SLOT(17)
	BMI_SLOT(18) BMI_SLOT(19) BMI_SLOT(20) BMI_SLOT(21) BMI_SLOT(22) BMI_SLOT(23)
	BMI_SLOT(24) BMI_SLOT(25)
#undef BMI_SLOT
	virtual SlavedUpdateInterface *getSlavedUpdateInterface();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	void setHealthBoxOffset(const Coord3D &offset) { m_healthBoxOffset = offset; }

	Drawable *getDrawable() const;
	void maskObject(Bool mask);

private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad78[0x244 - 0x78];
	BehaviorModule **m_behaviors;
	unsigned char m_pad248[0x254 - 0x248];
	BodyModuleInterface *m_body;
	unsigned char m_pad258[0x310 - 0x258];
	Coord3D m_healthBoxOffset;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_ID)
			return 0;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad000[0xB4];
	ObjectPtrHash m_objHash;
};
extern GameLogic *TheGameLogic;

class SpawnBehaviorModuleData
{
public:
	unsigned char m_pad00[0x08];
	Int m_spawnNumberData;
};

class SpawnBehavior
{
public:
	void computeAggregateStates();

private:
	Object *getObject() const { return m_object; }
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const { return m_moduleData; }

	void *m_vptr;
	const SpawnBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x4c - 0x0c];
	_STL::list<ObjectID> m_spawnIDs;
	unsigned char m_pad50;
	Bool m_aggregateHealth;
	unsigned char m_pad52[0x58 - 0x52];
	UnsignedInt m_selfTaskingSpawnCount;
};

// Zero Hour's Coord3D member operations; the canonical Coord3D header is
// fields only. Retail keeps the scaled y and z in registers, which the member
// form reproduces and per-field arithmetic on a plain Coord3D does not.
struct SpawnCoord3D : public Coord3D
{
	void set(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
	void scale(Real s) { x *= s; y *= s; z *= s; }
};

enum
{
	MSG_CREATE_SELECTED_GROUP = 0x3E9
};

// ?computeAggregateStates@SpawnBehavior@@QAEXXZ
void SpawnBehavior::computeAggregateStates()
{
	if (!m_aggregateHealth) // sanity
		return;

	Object *obj = getObject();
	const SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();

	Int spawnCount = 0;
	Int spawnCountMax = md->m_spawnNumberData;
	SpawnCoord3D avgSpawnPos;

	avgSpawnPos.set(0, 0, 0);
	Real acrHealth = 0.0f;
	Real avgHealthMax = 0.0f;

	Bool SomebodyIsSelected = false;
	Bool SomebodyIsNotSelected = false;

	Drawable *spawnDraw = NULL;
	Object *currentSpawn = NULL;

	m_selfTaskingSpawnCount = 0;

	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		currentSpawn = TheGameLogic->findObjectByID(*iter);

		if (currentSpawn)
		{
			for (BehaviorModule **update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != NULL)
				{
					m_selfTaskingSpawnCount += sdu->isSelfTasking();
					break;
				}
			}

			avgSpawnPos.add(currentSpawn->getPosition());

			BodyModuleInterface *body = currentSpawn->getBodyModule();
			acrHealth += body->getHealth();
			avgHealthMax += body->getMaxHealth();

			spawnDraw = currentSpawn->getDrawable();

			if (spawnDraw->isSelected())
				SomebodyIsSelected = true;
			else
				SomebodyIsNotSelected = true;

			spawnCount++;
		}
	}

	if (SomebodyIsSelected && (!obj->getDrawable()->isSelected() || SomebodyIsNotSelected))
	{
		GameMessage *teamMsg = MessageStreamSubsystem->appendMessage(MSG_CREATE_SELECTED_GROUP);
		teamMsg->appendBooleanArgument(false); // not creating new team so pass false

		if (SomebodyIsNotSelected) // lets select everybody
		{
			for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
			{
				currentSpawn = TheGameLogic->findObjectByID(*iter);

				if (currentSpawn)
				{
					spawnDraw = currentSpawn->getDrawable();

					if (!spawnDraw->isSelected())
					{
						TheInGameUI->selectDrawable(spawnDraw);
						TheInGameUI->setDisplayedMaxWarning(false);
						teamMsg->appendBooleanArgument(false); // not creating new team so pass false
						teamMsg->appendObjectIDArgument(currentSpawn->getID());
					}
				}
			}
		}
		// if somebody is selected then I sure need to be!
		if (!obj->getDrawable()->isSelected())
		{
			TheInGameUI->selectDrawable(obj->getDrawable());
			TheInGameUI->setDisplayedMaxWarning(false);
			teamMsg->appendBooleanArgument(false); // not creating new team so pass false
			teamMsg->appendObjectIDArgument(obj->getID());
		}
	}

	// pick a centered, average spot to draw the health box
	avgSpawnPos.scale(1.0f / spawnCount);
	avgSpawnPos.sub(obj->getPosition());
	obj->setHealthBoxOffset(avgSpawnPos);

	// make my health an aggregate of all my spawns' healths
	if (spawnCount)
	{
		avgHealthMax /= spawnCount;
		Real perfectTotalHealth = avgHealthMax * spawnCountMax;
		Real actualHealth = acrHealth / perfectTotalHealth;
		obj->getBodyModule()->setInitialHealth(100.0f * actualHealth, false);
	}
	else
	{
		obj->getBodyModule()->setInitialHealth(0, false); // I been sick <
	}

	// make sure no enemies are shooting at the nexus, since it doesn't 'exist'
	obj->maskObject(true);
}
