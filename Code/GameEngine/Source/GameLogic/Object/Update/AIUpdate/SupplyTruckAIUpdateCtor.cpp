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
#include "../../../../Common/GameLogicObjectLookupView.h"
typedef float Real;

// Coord3D: shared header/view; no private copy.
#include "../../../../../../Libraries/Include/Lib/Coord3DInline.h"

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../../../Include/Common/StateMachineClass.h"

class State;
class SupplyTruckStateMachine : public StateMachine
{
public:
	SupplyTruckStateMachine(Object *owner);
	static Bool ownerIdle(State *thisState, void *userData);
	static Bool ownerDocking(State *thisState, void *userData);
	static Bool ownerRva004A6D15(State *thisState, void *userData);
	static Bool ownerAvailableForSupplying(State *thisState, void *userData);
	static Bool ownerNotDockingOrIdle(State *thisState, void *userData);
	static Bool isForcedIntoWantingState(State *thisState, void *userData);
	static Bool isForcedIntoBusyState(State *thisState, void *userData);
	virtual ~SupplyTruckStateMachine();
};

enum ObjectID;
#include "../../../../../Include/GameLogic/Module/SupplyTruckAIUpdate.h"


class SupplyTruckAIUpdate : public AIUpdateInterface, public SupplyTruckAIInterface
{
public:
	SupplyTruckAIUpdate( Thing *thing, const ModuleData* moduleData );
	virtual ~SupplyTruckAIUpdate();
	virtual UpdateSleepTime update();
    virtual int getNumberBoxes() const { return m_numberBoxes; } //0
    virtual int rva004A6E29() const;                          //1
    virtual bool loseOneBox();                               //2
    virtual bool gainOneBox(int remainingStock);              //3
    virtual bool isAvailableForSupplying() const { return true; } //4
    virtual bool isCurrentlyFerryingSupplies() const;          //5
    virtual unsigned char rva004A6FE5() const;                 //6
    virtual float rva004A6FEF() const;                        //7
    virtual int rva004A6FF9() const;                          //8
    virtual unsigned int rva004A7003() const;                 //9
    virtual float rva004A6FBF() const;                        //10
    virtual void rva00210CD3(bool value) { m_forcePending = value; } //11
    virtual bool isForcedIntoWantingState() const { return m_forcePending; } //12
    virtual void rva005975D7(bool value) { m_forcedBusyPending = value; } //13
    virtual bool isForcedIntoBusyState() const { return m_forcedBusyPending; } //14
    virtual ObjectID getPreferredDockID() const { return m_preferredDock; }              //15
    virtual unsigned char rva004A6A44(Coord3D *result) const { *result = m_3F0; return m_3FC; } //16
    virtual void rva0047A69C(unsigned int unusedWord) {}      //17
    virtual int rva000D43D0() const { return 0; }             //18
    virtual unsigned int getActionDelayForDock(Object *dock); //19
    virtual NameKeyType getModuleNameKey() const;
    virtual void *vslot094() const;
    virtual void *vslot095() const;
protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
    virtual void privateIdle(CommandSourceType source);
    virtual void privateDock(Object *dock, CommandSourceType source);
    virtual void privateHarvest(const Coord3D *position, CommandSourceType source);
    virtual AIStateMachine *makeStateMachine();
private:
	SupplyTruckStateMachine *m_supplyTruckStateMachine; // +0x3E8
	ObjectID m_preferredDock;   // +0x3EC
	Coord3D m_3F0;              // +0x3F0
	Bool m_3FC;                 // +0x3FC
	Int m_numberBoxes;          // +0x400
	Bool m_forcePending;        // +0x404
	Bool m_forcedBusyPending;   // +0x405
};

SupplyTruckAIUpdate::SupplyTruckAIUpdate( Thing *thing, const ModuleData* moduleData ) : AIUpdateInterface( thing, moduleData )
{
	m_supplyTruckStateMachine = 0;
	m_preferredDock = INVALID_OBJECT_ID;
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

UpdateSleepTime SupplyTruckAIUpdate::update()
{
    int raw = (int)m_supplyTruckStateMachine->updateStateMachine();
    int n = raw > 0 ? raw : 1;
    int slept = (int)AIUpdateInterface::update();
    if (n < slept) slept = n;
    return (UpdateSleepTime)slept;
}

// Prefix-only module-data read view. Offsets and scalar widths are target
// facts; names, signedness and the complete dynamic type remain unresolved.
struct SupplyTruckModuleDataView {
    unsigned char field00[0x64];
    int field64;
    unsigned int field68;
    unsigned int field6C;
    float field70;
    unsigned char field74;
    unsigned char field75[3];
    float field78;
    int field7C;
    unsigned int field80;
};

int SupplyTruckAIUpdate::rva004A6E29() const
{
    return reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field64;
}

unsigned char SupplyTruckAIUpdate::rva004A6FE5() const
{
    return reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field74;
}

float SupplyTruckAIUpdate::rva004A6FEF() const
{
    return reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field78;
}

int SupplyTruckAIUpdate::rva004A6FF9() const
{
    return reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field7C;
}

unsigned int SupplyTruckAIUpdate::rva004A7003() const
{
    return reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field80;
}

bool SupplyTruckAIUpdate::isCurrentlyFerryingSupplies() const
{
    if (m_supplyTruckStateMachine)
    {
        switch (m_supplyTruckStateMachine->getCurrentStateID())
        {
        case 0:
        case 1:
            return false;
        case 2:
            return true;
        case 3:
            return false;
        case 4:
        case 5:
            return true;
        }
    }
    return false;
}

#include "../../../../Common/Thing/thing.h"

// Call-only view retaining the already-rowed broadcast symbol and argument ABI.
// It does not define Drawable or assert the broadcaster's original class name.
#include "../../../../../Include/GameClient/Rva002716Holder.h"

bool SupplyTruckAIUpdate::loseOneBox()
{
    if (m_numberBoxes == 0) return false;
    // Object's real Thing base is at offset zero; Object remains incomplete here.
    Thing *object = reinterpret_cast<Thing *>(getObject());
    --m_numberBoxes;
    Drawable *drawable = object->getDrawable();
    if (!drawable) return true;
    reinterpret_cast<Rva002716Holder *>(drawable)->Rva0027164EBroadcast(
        reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field64,
        m_numberBoxes);
    return true;
}

bool SupplyTruckAIUpdate::gainOneBox(int remainingStock)
{
    (void)remainingStock;
    const SupplyTruckModuleDataView *data =
        reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData());
    if (data && m_numberBoxes >= data->field64) return false;
    Thing *object = reinterpret_cast<Thing *>(getObject());
    ++m_numberBoxes;
    Drawable *drawable = object->getDrawable();
    if (!drawable) return true;
    reinterpret_cast<Rva002716Holder *>(drawable)->Rva0027164EBroadcast(
        reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field64,
        m_numberBoxes);
    return true;
}

#include "../../object.h"

// Target-bounded read view; original player field identity is unresolved.
struct SupplyTruckPlayerTypeView {
    unsigned char field00[0x5C];
    int field5C;
};

float SupplyTruckAIUpdate::rva004A6FBF() const
{
    Player *player = getObject()->getControllingPlayer();
    if (reinterpret_cast<const SupplyTruckPlayerTypeView *>(player)->field5C == 1)
    {
        float value = reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field70;
        return value + value;
    }
    return reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field70;
}

#include "../../../../../Include/Common/NameKeyGenerator.h"

unsigned int SupplyTruckAIUpdate::getActionDelayForDock(Object *dock)
{
    static NameKeyType keyWarehouse =
        TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
    if (dock->findUpdateModule(keyWarehouse) != 0)
        return reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field6C;
    static NameKeyType keyCenter =
        TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
    if (dock->findUpdateModule(keyCenter) != 0)
        return reinterpret_cast<const SupplyTruckModuleDataView *>(getModuleData())->field68;
    return 0;
}

void SupplyTruckAIUpdate::loadPostProcess()
{
    AIUpdateInterface::loadPostProcess();
}

const char *SupplyTruckAIUpdate::GetSnapshotName() const
{
    return "SupplyTruckAIUpdate";
}

void SupplyTruckAIUpdate::privateIdle(CommandSourceType source)
{
    // Zero is the measured player-command value.
    if (source == 0)
        rva005975D7(true);
    AIUpdateInterface::privateIdle(source);
}

void SupplyTruckAIUpdate::privateDock(Object *dock, CommandSourceType source)
{
    AIUpdateInterface::privateDock(dock, source);
    if (source == 0 && dock)
        m_preferredDock = dock->getID();
}

void SupplyTruckAIUpdate::privateHarvest(const Coord3D *position, CommandSourceType source)
{
    AIUpdateInterface::privateHarvest(position, source);
    if (source == 0 && position)
    {
        m_3F0 = *position;
        m_3FC = true;
    }
}

void *SupplyTruckAIUpdate::vslot094() const
{
    return static_cast<SupplyTruckAIInterface *>(const_cast<SupplyTruckAIUpdate *>(this));
}

void *SupplyTruckAIUpdate::vslot095() const
{
    return static_cast<SupplyTruckAIInterface *>(const_cast<SupplyTruckAIUpdate *>(this));
}
