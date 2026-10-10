// cl: /O1 /DNDEBUG /MD
// ?update@HijackerUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004A40DB, 313 bytes.
// HijackerUpdate::update: keep hidden hijacker on hijacked vehicle while it
// lives, else restore/unhide and spawn parachute container. Evidence: table
// slot 0x008525D8 neighbours UpdateModule getDisabledTypesToProcess; prev row
// loadPostProcess in HijackerUpdate.cpp; callees rowed getTargetObject
// setPosition isSignificantlyAboveTerrain getDrawable setStatus maskObject
// aiIdle rva002D06CA memset newObject plus pin-only rva0028DCC4 and
// Rva002716Holder slots 0x98/0x9C via Payload v38/v39; BFME1 donor
// HijackerUpdateUpdate.cpp (no ExperienceTracker, rva001CA2E0, 4-arg
// newObject, direct +0x38 position) with BFME2 offsets team +0x304 AI +0x258
// contain +0x250 and names.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_3 = 3,
	OBJECT_STATUS_4 = 4
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

typedef int ObjectID;
enum
{
	INVALID_ID = 0
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class AsciiString;
class ThingTemplate;
class Team;
class Drawable;
class Object;

class Thing
{
public:
	void setPosition(const Coord3D *position);
	Drawable *getDrawable() const;
};

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
};

class Payload
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual bool v38(Object *obj, int a, int b);
	virtual void v39(Object *obj);
};

class Object
{
public:
	void rva0028DCC4();
	void setStatus(ObjectStatusTypes status, bool flag);
	void maskObject(bool masked);
	bool isSignificantlyAboveTerrain() const;
	int getID() const
	{
		return m_id;
	}
	Team *getTeam() const
	{
		return m_team;
	}
	Payload *getContain() const
	{
		return m_contain;
	}
private:
	char m_pad000[0x74];
	int m_id;
	char m_pad078[0x250 - 0x78];
	Payload *m_contain;
	char m_pad254[0x258 - 0x254];
	class RvaAI *m_aiPtr;
	char m_pad25C[0x304 - 0x25C];
	Team *m_team;
};

class RvaAIHead
{
private:
	char m_pad00[0x20];
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class RvaAI : public RvaAIHead, public AICommandInterface
{
};

class RvaHijackerModuleData
{
public:
	char m_pad00[0x0c];
	int m_parachuteNameOpaque;
};


class ThingFactory;
extern ThingFactory *TheThingFactory;

void __cdecl ji_006291ae();

struct CreateMask
{
	char m_data[0x10];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
};

class RvaModule
{
public:
	virtual ~RvaModule();
protected:
	const RvaHijackerModuleData *m_moduleData;
};

class RvaObjectModule : public RvaModule
{
public:
	virtual void onCapture(Object *oldTeam, Object *newTeam);
protected:
	Object *m_object;
};

class RvaBehaviorInterface
{
public:
	virtual void getBody();
	virtual void getCollide();
	virtual void getContain();
	virtual void getCreate();
	virtual void getDamage();
	virtual void getDestroy();
	virtual void getDie();
	virtual void getSpecialPower();
	virtual void getUpdate();
};

class RvaBehaviorModule : public RvaObjectModule, public RvaBehaviorInterface
{
};

class RvaUpdateInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class RvaUpdateModule : public RvaBehaviorModule, public RvaUpdateInterface
{
protected:
	UnsignedInt m_nextCallFrame;
	Int m_indexInLogic;
	Int m_pad;

	Object *getObject() const
	{
		return m_object;
	}
	const RvaHijackerModuleData *getModuleData() const
	{
		return m_moduleData;
	}
};

class HijackerUpdate : public RvaUpdateModule
{
public:
	virtual UpdateSleepTime update(void);
	Object *getTargetObject() const;
	void setTargetObject(const Object *object)
	{
		if (object)
			m_targetID = object->getID();
		else
			m_targetID = INVALID_ID;
	}
	void setIsInVehicle(UnsignedByte inVehicle)
	{
		m_isInVehicle = inVehicle;
	}
	void setUpdate(UnsignedByte update)
	{
		m_update = update;
	}
private:
	ObjectID m_targetID;
	Coord3D m_ejectPos;
	UnsignedByte m_update;
	UnsignedByte m_isInVehicle;
	UnsignedByte m_wasTargetAirborne;
};

// ?update@HijackerUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime HijackerUpdate::update(void)
{
	if (!m_update)
		return UPDATE_SLEEP_NONE;

	if (m_isInVehicle)
	{
		Object *obj = getObject();
		Object *target = getTargetObject();
		if (target)
		{
			Coord3D *position = reinterpret_cast<Coord3D *>(
				reinterpret_cast<UnsignedByte *>(target) + 0x38);
			((Thing *)obj)->setPosition(position);
			m_wasTargetAirborne = static_cast<UnsignedByte>(
				target->isSignificantlyAboveTerrain());
			m_ejectPos = *position;
		}
		else
		{
			obj->rva0028DCC4();

			if (((Thing *)obj)->getDrawable())
				((Thing *)obj)->getDrawable()->setDrawableHidden(false);

			obj->setStatus(OBJECT_STATUS_4, false);
			obj->maskObject(false);
			obj->setStatus(OBJECT_STATUS_3, false);

			RvaAI *ai = *reinterpret_cast<RvaAI **>(
				reinterpret_cast<UnsignedByte *>(obj) + 0x258);
			if (ai)
				ai->aiIdle(CMD_FROM_AI);

			if (m_wasTargetAirborne)
			{
				const ThingTemplate *putInContainerTmpl = TheThingFactory->findTemplate(*(reinterpret_cast<const AsciiString *>(&getModuleData()->m_parachuteNameOpaque)));
				if (putInContainerTmpl)
				{
					CreateMask mask;
					((void (__cdecl *)(void *, int, UnsignedInt))&ji_006291ae)(&mask, 0, 0x10);
					Object *container = TheThingFactory->newObject(
						putInContainerTmpl, obj->getTeam(), &mask, false);
					((Thing *)container)->setPosition(&m_ejectPos);
					if (container->getContain()->v38(obj, 1, 0))
					{
						container->getContain()->v39(obj);
					}
				}
			}

			setTargetObject(0);
			setIsInVehicle(0);
			setUpdate(0);
			m_wasTargetAirborne = false;
		}
	}
	else
	{
		m_wasTargetAirborne = false;
	}

	return UPDATE_SLEEP_NONE;
}
