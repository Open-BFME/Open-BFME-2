// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// stlport
//
// EXACT (457 of 457 bytes)
// ?initiateIntentToDoSpecialPower@SiegeDeployHordeSpecialPower@@UAEXPBVSpecialPowerTemplate@@PBVObject@@PBUCoord3D@@IPBVWaypoint@@@Z
// retail 0x004C6588..0x004C6751 (457 bytes EH RET 0x14). It is slot 0 of
// the vftable ??_7SiegeDeployHordeSpecialPower@@6BSiegeDeployHordeSpecialPower_S3@@@
// (0x0085DD64; the interface at +0x20, so this-0x20 is the module). WB
// 0x01265FD0 is the same body (unnamed; it still uses AICommandParms for
// the leader).
// What it does:
// - Module data +0x18 off: setWakeFrame(getObject(), 1).
// - Otherwise take the object's contain (rowed Object::rva0028C197) and get
//   its contained list (slot 66).
// - Pick the first member whose template has KindOf bit 93, remove it
//   (slot 14), deselect it (rowed deselectObject 0xFFFFF true), idle its AI
//   (rowed aiIdle CMD_FROM_AI) and fire the pinned Object::rva0028E01F
//   (template / target / options / 0).
// - Then for every contained object (slot 126 into a vector<Object*> through
//   the pinned _Vector_base ctor): idle it, fire it, look up its
//   "SiegeDeployHordeSpecialPower" module (static NameKeyType) and hand it the
//   leader's ID (slot 13) and the target's position (slot 14). Finally the
//   rowed AICommandInterface::rva0045003E(0 / CMD_FROM_AI).
// /EHs keeps retail's state -1 store and the C++ free call before the vector
// buffer free.
// The contained-items holder comes back by value (hidden return slot) and
// releases its lock in an inline destructor at the end of the leader search
// block: with no call inside that block it needs no unwind state, and cl then
// schedules the contain vtable load for removeFromContain before the
// `lock = 0` store, as retail does (a plain statement store stays first).
#include <vector>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
class SpecialPowerTemplate;
class Waypoint;
class Module;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(Int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[28];						// +0x108
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void rva0045003E(Int value, CommandSourceType cmdSource);
};

class AIUpdateInterfaceHead
{
	unsigned char m_pad00[0x20];
};

class AIUpdateInterface : public AIUpdateInterfaceHead, public AICommandInterface
{
};

class SiegeDeployHordeSpecialPower;

class Object
{
	friend class SiegeDeployHordeSpecialPower;
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	void *rva0028C197() const;
	void rva0028E01F(const SpecialPowerTemplate *spt, Object *target, Int commandOptions, Int extra);
protected:
	Module *findModule(NameKeyType key) const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template;				// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;								// +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;									// +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai;						// +0x258
};

extern GameLogic *TheGameLogic;

struct SiegeDeployHordeListNode
{
	SiegeDeployHordeListNode *m_next;
	SiegeDeployHordeListNode *m_prev;
	Object *m_data;
};

struct SiegeDeployHordeList
{
	SiegeDeployHordeListNode *m_head;
};

struct SiegeDeployHordeContainedItems
{
	void *m_lock;
	const SiegeDeployHordeList *m_list;
	~SiegeDeployHordeContainedItems() { m_lock = 0; }
};

class SiegeDeployHordeContainView
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13)
	virtual void removeFromContain(Object *obj);								// slot 14
	V(15) V(16) V(17) V(18) V(19) V10(2) V10(3) V10(4) V10(5)
	V(60) V(61) V(62) V(63) V(64) V(65)
	virtual SiegeDeployHordeContainedItems getContainedItems();		// slot 66
	V(67) V(68) V(69) V10(7) V10(8) V10(9) V10(10) V10(11)
	V(120) V(121) V(122) V(123) V(124) V(125)
	virtual void getContainedObjects(_STL::vector<Object *> *objects);			// slot 126
#undef V10
#undef V
};

class SiegeDeployHordeModuleView
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12)
#undef V
	virtual void setTargetObjectID(ObjectID id);								// slot 13
	virtual void setTargetPosition(const Coord3D *pos);						// slot 14
};

struct SiegeDeployHordeSpecialPowerModuleData
{
	unsigned char m_pad00[0x18];
	Bool m_deployHorde;													// +0x18
};

class UpdateModule
{
protected:
	virtual ~UpdateModule();
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	Object *getObject() const { return m_object; }
	const void *m_moduleData;												// +0x04
	Object *m_object;														// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class SpecialPowerUpdateInterface
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way) = 0;
};

class SiegeDeployHordeSpecialPower : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way);
private:
	const SiegeDeployHordeSpecialPowerModuleData *getSiegeDeployHordeSpecialPowerModuleData() const
	{
		return (const SiegeDeployHordeSpecialPowerModuleData *)m_moduleData;
	}
};

void SiegeDeployHordeSpecialPower::initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
	const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way)
{
	if (getSiegeDeployHordeSpecialPowerModuleData()->m_deployHorde)
	{
		SiegeDeployHordeContainView *contain = (SiegeDeployHordeContainView *)getObject()->rva0028C197();
		if (contain == 0)
			return;

		Object *leader;
		{
		SiegeDeployHordeContainedItems items = contain->getContainedItems();
		leader = 0;
		SiegeDeployHordeListNode *head = items.m_list->m_head;
		for (SiegeDeployHordeListNode *node = head->m_next; node != head; node = node->m_next)
		{
			Object *obj = node->m_data;
			if (obj->getTemplate()->isKindOf(93))
			{
				leader = obj;
				break;
			}
		}
		}

		contain->removeFromContain(leader);
		TheGameLogic->deselectObject(leader, 0xFFFFF, true);
		leader->getAIUpdateInterface()->aiIdle(CMD_FROM_AI);
		leader->rva0028E01F(specialPowerTemplate, (Object *)targetObj, commandOptions, 0);

		_STL::vector<Object *> objects;
		((SiegeDeployHordeContainView *)getObject()->rva0028C197())->getContainedObjects(&objects);
		for (UnsignedInt i = 0; i < objects.size(); ++i)
		{
			objects[i]->getAIUpdateInterface()->aiIdle(CMD_FROM_AI);
			objects[i]->rva0028E01F(specialPowerTemplate, (Object *)targetObj, commandOptions, 0);
			static const NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDeployHordeSpecialPower");
			SiegeDeployHordeModuleView *module = (SiegeDeployHordeModuleView *)objects[i]->findModule(key);
			if (module)
			{
				module->setTargetObjectID(leader->getID());
				module->setTargetPosition(targetObj->getPosition());
			}
			objects[i]->getAIUpdateInterface()->rva0045003E(0, CMD_FROM_AI);
		}
	}
	else
	{
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
	}
}
