// cl: /DNDEBUG /MD /EHs
//
// ??0SupplyTruckAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A71A1
// (212 bytes). ZH donor SupplyTruckAIUpdate.cpp ctor; the name is the pinned
// ModuleFactory identity (friend_newModuleInstance 0x0024EED6 news it).
// Target evidence: the base is the pinned 0x0026E9BD AIUpdate ctor; the
// SupplyTruckAIInterface base at +0x3E4 has its own vtable (0x00C52EE8,
// stored by its implicit ctor) before the derived installs its table for it
// (0x00C52F38) -- the interface is therefore declared without novtable; the
// derived then installs its five AIUpdate tables (+0, +0xC, +0x10, +0x20,
// +0x24). BFME2 layout: state machine +0x3E8, preferred dock +0x3EC, a
// Coord3D at +0x3F0 zeroed through Coord3D::zero (xorps/movss), a bool at
// +0x3FC, box count +0x400, the two force flags +0x404/+0x405 (ZH has no
// +0x3F0 coord and no +0x3FC flag; their meaning is not asserted). The state
// machine is a plain new of 0x3C bytes (de-pooled) constructed by the pinned
// SupplyTruckStateMachine ctor 0x004A7010 on getObject(), then
// initDefaultState through StateMachine vslot +0x1C; the ZH tail that reads
// the depleted-supplies voice from the module data is absent in retail.
// The dtor 0x004A69BF (pinned as the slot-0 ??_G's callee) re-stores the
// six tables, then deletes the machine through its vslot-0 deleting dtor
// with flag 0 plus the global operator delete (the DozerAIUpdate dtor's
// ::delete shape) and clears the pointer before the pinned base dtor.
class Thing;
class ModuleData;
class Object;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum ObjectID { INVALID_ID = 0 };
typedef float Real;

struct Coord3D
{
	Real x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

struct AIBase00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct AIBase0C { virtual void f0C(); };
struct AIBase10 { virtual void f10(); unsigned char m_pad[12]; };
struct AIBase20 { virtual void f20(); };
struct AIBase24 { virtual void f24(); unsigned char m_pad[0x3E4 - 0x28]; };

class Rva0026E9BDBase
	: public AIBase00
	, public AIBase0C
	, public AIBase10
	, public AIBase20
	, public AIBase24
{
public:
	Rva0026E9BDBase(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0026E9BDBase();
	Object *getObject() { return m_object; }
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06();
	virtual void initDefaultState(); // +0x1C
};

class SupplyTruckStateMachine : public StateMachine
{
public:
	SupplyTruckStateMachine(Object *owner);
	virtual ~SupplyTruckStateMachine();
	unsigned char m_pad04[0x3C - 4];
};

class SupplyTruckAIInterface
{
public:
	virtual Int getNumberBoxes() const = 0;
	virtual Bool loseOneBox() = 0;
	virtual Bool gainOneBox( Int remainingStock ) = 0;
	virtual Bool isAvailableForSupplying() const = 0;
	virtual Bool isCurrentlyFerryingSupplies() const = 0;
	virtual Real getWarehouseScanDistance() const = 0;
	virtual void setForceWantingState(Bool v) = 0;
	virtual Bool isForcedIntoWantingState() const = 0;
	virtual void setForceBusyState(Bool v) = 0;
	virtual Bool isForcedIntoBusyState() const = 0;
	virtual ObjectID getPreferredDockID() const = 0;
	virtual UnsignedInt getActionDelayForDock( Object *dock ) = 0;
	virtual Int getUpgradedSupplyBoost() const = 0;
};

class SupplyTruckAIUpdate : public Rva0026E9BDBase, public SupplyTruckAIInterface
{
public:
	SupplyTruckAIUpdate( Thing *thing, const ModuleData* moduleData );
	virtual ~SupplyTruckAIUpdate();
 	virtual Int getNumberBoxes() const;
	virtual Bool loseOneBox();
	virtual Bool gainOneBox( Int remainingStock );
	virtual Bool isAvailableForSupplying() const;
	virtual Bool isCurrentlyFerryingSupplies() const;
	virtual Real getWarehouseScanDistance() const;
 	virtual void setForceWantingState(Bool v);
 	virtual Bool isForcedIntoWantingState() const;
 	virtual void setForceBusyState(Bool v);
 	virtual Bool isForcedIntoBusyState() const;
	virtual ObjectID getPreferredDockID() const { return m_preferredDock; }
	virtual UnsignedInt getActionDelayForDock( Object *dock );
	virtual Int getUpgradedSupplyBoost() const { return 0; }
private:
	SupplyTruckStateMachine *m_supplyTruckStateMachine; // +0x3E8
	ObjectID m_preferredDock;   // +0x3EC
	Coord3D m_3F0;              // +0x3F0
	Bool m_3FC;                 // +0x3FC
	Int m_numberBoxes;          // +0x400
	Bool m_forcePending;        // +0x404
	Bool m_forcedBusyPending;   // +0x405
};

SupplyTruckAIUpdate::SupplyTruckAIUpdate( Thing *thing, const ModuleData* moduleData ) : Rva0026E9BDBase( thing, moduleData )
{
	m_supplyTruckStateMachine = 0;
	m_preferredDock = INVALID_ID;
	m_3F0.zero();
	m_3FC = false;
	m_numberBoxes = 0;
	m_forcePending = false;
	m_forcedBusyPending = false;
	m_supplyTruckStateMachine = new SupplyTruckStateMachine( getObject() );
	m_supplyTruckStateMachine->initDefaultState();
}

SupplyTruckAIUpdate::~SupplyTruckAIUpdate()
{
	::delete m_supplyTruckStateMachine;
	m_supplyTruckStateMachine = 0;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f0C@AIBase0C@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
