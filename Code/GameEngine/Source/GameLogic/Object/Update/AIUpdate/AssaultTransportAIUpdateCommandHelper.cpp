// cl: /DNDEBUG /MD
//
// ?Rva0048F6EEHelper@AssaultTransportAIUpdate@@QAEXXZ, retail 0x0048F6EE
// (185 bytes). Dual-command passenger sweep over the +0x3E8 ObjectID array
// for the +0x43C count: each live passenger exposes its AIUpdateInterface at
// +0x258, a second lookup resolves the +0x430 member ID, and then either the
// target command (pinned 0x26C2D9) issues when the +0x441 flag is set with a
// live target, or the position command (pinned 0x295A0F) issues from the
// +0x424 triple when the +0x440 flag is set; either way the interface's
// +0x3C1 byte clears. The two commands are if/else chained (the target path
// jumps over the position check). Counter and cursor stay homed in stack
// slots while constants live in registers, matching the retail prologue.

#include "../../../../Common/GameLogicObjectLookupView.h"
enum NameKeyType;
enum CommandSourceType;
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

class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};


class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *target, int range, int source);
};


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
void AssaultTransportAIUpdate::Rva0048F6EEHelper()
{
	int index = 0;
	if (index >= m_currentMembers)
		return;
	ObjectID *idCursor = m_memberIDs;
	while (index < m_currentMembers)
	{
		Object *passenger = TheGameLogic->findObjectByID(*idCursor);
		AIUpdateInterface *commandInterface = passenger != 0 ? passenger->m_aiDirect : 0;
		if (passenger != 0 && commandInterface != 0)
		{
			Object *other = TheGameLogic->findObjectByID(m_designatedTarget);
			if (m_isAttackObject != 0 && other != 0)
				commandInterface->rva0026C2D9(other, 0x7FFFFFFF, (CommandSourceType)0);
			else if (m_isAttackMove != 0)
				((Rva00295A0FCommands *)(AICommandInterface *)commandInterface)->Rva00295A0FCommand(&m_attackMoveGoalPos.x, 0x7FFFFFFF, 0);
			commandInterface->m_byte3C1 = 0;
		}
		++index;
		++idCursor;
	}
}
