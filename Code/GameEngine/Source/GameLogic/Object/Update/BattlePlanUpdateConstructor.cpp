// cl: /DNDEBUG /MD /GX
//
// ??0BattlePlanUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00497ED0,
// 261 bytes. Zero Hour's BattlePlanUpdate::BattlePlanUpdate (GeneralsMD
// GameLogic/Object/Update/BattlePlanUpdate.cpp), reshaped by BFME 2.
// Target evidence: the body runs the rowed UpdateModule ctor 0x00253390 and
// the implicit ctor of the abstract interface at +0x20 (vtable 0x0086F248,
// every slot _purecall 0x0003B810), then stores the vtables the rowed dtor
// 0x004978A3 restores: 0x0084FBAC primary, whose slot 0 is the rowed
// deleting dtor 0x00497FD7 and slot 2 the rowed BattlePlanUpdate name
// getter 0x0049795A, 0x0084FBA0 for UpdateModuleInterface and 0x0084FB7C
// at +0x20. The member order and the stores follow ZH: plan and status
// fields at +0x24..+0x34, the special power module at +0x38, the two flags
// at +0x3C/+0x3D, the bonuses record at +0x40 allocated with operator new
// (0x4C bytes, the rowed record ctor 0x002AA14D) and filled from the
// module data's kind-of masks at +0x54/+0x70, the vision object ID at
// +0x88. BFME 2 replaces ZH's audio events with sixteen ref-counted
// handles at +0x44 (element ctor at the ICF-folded 0x00326BE6 nulls the
// pointer, element dtor 0x0010F149 releases it, both through __ehvec_ctor)
// and adds an int at +0x84 initialised to 1, the value the rowed dtor
// passes to TheAudio.
typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
#define NULL 0

class Thing;
class ModuleData;
class Object;
class SpecialPowerModuleInterface;

enum ObjectID
{
	INVALID_ID = 0
};

enum BattlePlanStatus
{
	PLANSTATUS_NONE
};

enum TransitionStatus
{
	TRANSITIONSTATUS_IDLE
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

// The abstract interface at +0x20 (ZH's SpecialPowerUpdateInterface slot).
class SpecialPowerUpdateInterface
{
public:
	virtual void slot00() = 0;
};

// The 0x1C-byte kind-of mask; its ctor is the rowed clear at 0x0024C7B3.
class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

// The bonuses record, rowed under its ctor's address name.
class Rva002AA14DBonuses
{
public:
	Rva002AA14DBonuses() throw();

	Real m_armorScalar; // +0x00
	Int m_bombardment; // +0x04
	Int m_searchAndDestroy; // +0x08
	Int m_holdTheLine; // +0x0C
	Real m_sightRangeScalar; // +0x10
	Rva0024C7B3Member m_validKindOf; // +0x14
	Rva0024C7B3Member m_invalidKindOf; // +0x30
};

// The ref-counted handle BFME 2 keeps sixteen of; named after its
// destructor's address.
class Rva0010F149Handle
{
public:
	Rva0010F149Handle();
	~Rva0010F149Handle();
private:
	void *m_ptr;
};

class BattlePlanUpdateModuleData
{
public:
	unsigned char m_pad00[0x54];
	Rva0024C7B3Member m_validMemberKindOf; // +0x54
	Rva0024C7B3Member m_invalidMemberKindOf; // +0x70
};

class BattlePlanUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	BattlePlanUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BattlePlanUpdate();
	virtual void slot00();
private:
	const BattlePlanUpdateModuleData *getBattlePlanUpdateModuleData() const { return (const BattlePlanUpdateModuleData *)m_moduleData; }

	BattlePlanStatus m_currentPlan; // +0x24
	BattlePlanStatus m_desiredPlan; // +0x28
	BattlePlanStatus m_planAffectingArmy; // +0x2C
	TransitionStatus m_status; // +0x30
	UnsignedInt m_nextReadyFrame; // +0x34
	SpecialPowerModuleInterface *m_specialPowerModule; // +0x38
	Bool m_invalidSettings; // +0x3C
	Bool m_centeringTurret; // +0x3D
	Rva002AA14DBonuses *m_bonuses; // +0x40
	Rva0010F149Handle m_handles[16]; // +0x44
	Int m_84; // +0x84
	ObjectID m_visionObjectID; // +0x88
};

BattlePlanUpdate::BattlePlanUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_bonuses(NULL)
	, m_84(1)
{
	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();

	m_status = TRANSITIONSTATUS_IDLE;
	m_currentPlan = PLANSTATUS_NONE;
	m_desiredPlan = PLANSTATUS_NONE;
	m_planAffectingArmy = PLANSTATUS_NONE;
	m_nextReadyFrame = 0;
	m_invalidSettings = false;
	m_centeringTurret = false;

	//Default the bonuses to no change.
	m_bonuses = new Rva002AA14DBonuses;
	m_bonuses->m_armorScalar = 1.0f;
	m_bonuses->m_sightRangeScalar = 1.0f;
	m_bonuses->m_bombardment = 0;
	m_bonuses->m_searchAndDestroy = 0;
	m_bonuses->m_holdTheLine = 0;
	m_bonuses->m_validKindOf = data->m_validMemberKindOf;
	m_bonuses->m_invalidKindOf = data->m_invalidMemberKindOf;

	m_visionObjectID = INVALID_ID;

	m_specialPowerModule = NULL;
}
