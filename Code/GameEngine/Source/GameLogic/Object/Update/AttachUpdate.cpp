// cl: /O1 /MD /GX /arch:SSE
//
// AttachUpdate (vftable 0x00C4DB20, UpdateModuleInterface view 0x00C4DB14;
// ctor 0x00491A0F, data AttachUpdateModuleData 0x00491968: ObjectFilter
// +0x08, ParentStatus +0x0C, ScanRange +0x1C, AlwaysTeleport +0x20, the
// attachment EVA events +0x24/+0x28/+0x2C, AttachFX +0x30, the died EVA
// events +0x34/+0x38/+0x3C).
//
//   0x00491AD0  attach to a parent (not converted yet; banked): with no +0x20
//               parent, the closest object in ScanRange over BFME2's
//               partition filter chain; remember its ID and keep the
//               owner/ally/enemy died EVA event in +0x24.
//
//   0x00491D2F  update (UpdateModuleInterface slot, vftable 0x00C4DB14):
//               attach; with a parent that is gone or effectively dead
//               (+0x438 bit 0) forget it, play the kept died event at this
//               object, kill it and sleep forever; otherwise move to
//               0x00491C84's anchor point when not there yet, teleporting
//               when AlwaysTeleport.

class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
	bool equals(const Coord3D &r) const;	// 0x00003702
};

enum ObjectID
{
	INVALID_ID = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum DamageType
{
	DAMAGE_RVA00491D2F_8 = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class Eva
{
public:
	void rva001DE2DA(int event, const Coord3D *pos, int flag);	// 0x001DE2DA
};
extern Eva *TheEva;

class Thing
{
public:
	void setPosition(const Coord3D *pos);	// 0x0030AA80
};

class Object : public Thing
{
public:
	void rva0029660C(const Coord3D *pos, int flag);	// 0x0029660C
	void kill(DamageType damageType, DeathType deathType);	// 0x002984D4
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x438 - 0x44];
	unsigned char m_438;	// +0x438 (bit 0: effectively dead)
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

struct AttachUpdateModuleData
{
	char m_pad00[0x20];
	bool m_alwaysTeleport;		// +0x20 AlwaysTeleport
};

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
	char m_pad14[0x20 - 0x14];
};

class AttachUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva00491AD0();	// 0x00491AD0
	void rva00491C84(Coord3D *out, const Object *parent);	// 0x00491C84
private:
	const AttachUpdateModuleData *getAttachUpdateModuleData() const
	{
		return (const AttachUpdateModuleData *)m_moduleData;
	}
	ObjectID m_parentID;	// +0x20
	int m_diedEvaEvent;	// +0x24
};

UpdateSleepTime AttachUpdate::update()
{
	rva00491AD0();
	if (m_parentID != INVALID_ID) {
		Object *parent = TheGameLogic->findObjectByID(m_parentID);
		Object *obj = m_object;
		if (!parent || (parent->m_438 & 1)) {
			m_parentID = INVALID_ID;
			TheEva->rva001DE2DA(m_diedEvaEvent, obj->getPosition(), 0);
			obj->kill(DAMAGE_RVA00491D2F_8, DEATH_NORMAL);
			return UPDATE_SLEEP_FOREVER;
		}
		Coord3D pos;
		rva00491C84(&pos, parent);
		if (!pos.equals(*obj->getPosition())) {
			if (getAttachUpdateModuleData()->m_alwaysTeleport)
				obj->rva0029660C(&pos, 0);
			else
				obj->setPosition(&pos);
		}
	}
	return UPDATE_SLEEP_NONE;
}
