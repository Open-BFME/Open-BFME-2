// cl: /DNDEBUG /MD
//
// ?Rva0048F690Helper@AssaultTransportAIUpdate@@QAEXXZ, retail 0x0048F690
// (94 bytes). Passenger-AI sweep over the +0x3E8 ObjectID array for the
// +0x43C count: each ID resolves through TheGameLogic->findObjectByID, the
// live ones expose their AIUpdateInterface at +0x258, and interfaces whose
// +0x274 word is clear get the 2-param AI command (0x26C347, pinned
// Rva-addressed) with the +0x08 member and constant 2. Layout matches the
// rowed Rva0048F365Helper TU (IDs at +0x3E8, count at +0x43C). The bound is
// checked against the zeroed index up front so the cursor setup stays below
// the branch, reproducing the retail split prologue.
// AIUpdateInterface's +0x20 command subobject is the AICommandInterface
// receiver; the pointer/int thiscall signature and target pin agree.

#include "../../../../Common/GameLogicObjectLookupView.h"
enum NameKeyType;
enum CommandSourceType;
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

#include "../../../../../Include/GameLogic/Module/UpdateModule.h"

struct AICommandParms;
struct Coord3D;
class Coord3DBase
{
public:
    float x;
    float y;
    float z;
};

enum AssaultStateTypes
{
    IDLE
};

class AICommandInterface
{
public:
    virtual void aiDoCommand(const AICommandParms *parms) = 0;
    void rva0026C347(Object *target, CommandSourceType source);
    void rva0026C2D9(Object *target, int range, CommandSourceType source);
};

class Rva0026E836_M4
{
public:
    virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public Rva0026E836_M4
{
public:
    AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
    virtual void xfer(Xfer *xfer);
    virtual void aiDoCommand(const AICommandParms *parms);
    virtual UpdateSleepTime update();
    virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
    unsigned char m_pad28[0x3C1 - 0x28];
    unsigned char m_byte3C1;
    unsigned char m_pad3C2[0x3E4 - 0x3C2];
protected:
    virtual ~AIUpdateInterface();
    void wakeUpNow();
};

class AssaultTransportAIInterface
{
public:
    virtual void beginAssault(const Object *designatedTarget) const = 0;
};

#include "../../../../Common/GameLogicObjectLookupView.h"



enum ObjectStatusTypes;
class AIUpdateInterface;
class Object
{
public:
	ObjectID getID() const { return m_id; }
	bool testStatus(ObjectStatusTypes bit) const;
	char m_pad00[0x74];
private:
	ObjectID m_id; // +0x74
	char m_pad78[0x1E0];
public:
	AIUpdateInterface *m_aiDirect; // +0x258
	char m_pad25C[0x18];
	int m_bfme274; // +0x274
};


extern GameLogic *TheGameLogic;

class AssaultTransportAIUpdate : public AIUpdateInterface, public AssaultTransportAIInterface
{
public:
    AssaultTransportAIUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~AssaultTransportAIUpdate();
    virtual NameKeyType getModuleNameKey() const;
    virtual void beginAssault(const Object *designatedTarget) const;
    virtual void aiDoCommand(const AICommandParms *parms);
    virtual UpdateSleepTime update();
    void Rva0048F365Helper() throw();
    bool isAttackPointless() const;
    bool rva0048F64E(void *arg);
    void Rva0048F690Helper();
    void Rva0048F6EEHelper();
protected:
    virtual void xfer(Xfer *xfer);
private:
    ObjectID m_memberIDs[10]; // +0x3E8
    bool m_memberHealing[10]; // +0x410
    unsigned char m_array41A[10]; // +0x41A
    Coord3DBase m_attackMoveGoalPos; // +0x424
    mutable ObjectID m_designatedTarget; // +0x430
    AssaultStateTypes m_state; // +0x434
    unsigned int m_framesRemaining; // +0x438
    int m_currentMembers; // +0x43C
    bool m_isAttackMove; // +0x440
    bool m_isAttackObject; // +0x441
    bool m_bfmeFlag442; // +0x442
};
void AssaultTransportAIUpdate::Rva0048F690Helper()
{
	int index = 0;
	if (index >= m_currentMembers)
		return;
	ObjectID *idCursor = m_memberIDs;
	while (index < m_currentMembers)
	{
		Object *passenger = TheGameLogic->findObjectByID(*idCursor);
		AIUpdateInterface *commandInterface = passenger != 0 ? passenger->m_aiDirect : 0;
		if (passenger != 0 && commandInterface != 0 && passenger->m_bfme274 == 0)
			commandInterface->rva0026C347(m_object, (CommandSourceType)2);
		++index;
		++idCursor;
	}
}
