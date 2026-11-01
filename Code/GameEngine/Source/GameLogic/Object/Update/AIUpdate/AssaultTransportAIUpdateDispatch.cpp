// cl: /DNDEBUG /MD
//
// ?aiDoCommand@AssaultTransportAIUpdate@@UAEXPBUAICommandParms@@@Z
// retail 0x0048F7A7 (129 bytes). Slot 0 of AssaultTransportAIUpdate's
// +0x20 AICommandInterface vftable 0x00C4CC8C, which the rowed dtor
// 0x0048F3E0 and ctor 0x0048F5A3 store. The override keeps that base's
// this, so the class members are reached 0x20 below their offsets and every
// helper call adjusts it back with its own lea. Commands from the AI
// (source 2) skip straight to the base; otherwise the command selects helper
// work before always delegating to AIUpdateInterface::aiDoCommand (0x002673F6,
// slot 0 of its +0x20 vftable). Command 5 zeroes the +0x430 word then runs
// both helpers; commands 0xB and 0x39 run the reset helper and raise the
// +0x441 flag; command 0xF runs the reset helper, copies the 12-byte position
// into the +0x424 triple and raises the +0x440 flag; any other command just
// runs the reset helper. The +0x424/+0x430/+0x440 tail is proven by the rowed
// Rva0048F365Helper TU. Case order in source is load-bearing for the
// compiler's block layout.

#include "../../../../Common/GameLogicObjectLookupView.h"
enum NameKeyType;
enum CommandSourceType;
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

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


struct AICommandParms
{
	int m_cmd;
	int m_cmdSource;
	Coord3DBase m_pos;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};






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
void AssaultTransportAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	if (parms->m_cmdSource != 2)
	{
		switch (parms->m_cmd)
		{
		case 5:
			m_designatedTarget = (ObjectID)0;
			Rva0048F690Helper();
			Rva0048F365Helper();
			break;
		case 0xB:
		case 0x39:
			Rva0048F365Helper();
			m_isAttackObject = 1;
			break;
		case 0xF:
			Rva0048F365Helper();
			m_attackMoveGoalPos = parms->m_pos;
			m_isAttackMove = 1;
			break;
		default:
			Rva0048F365Helper();
			break;
		}
	}
	AIUpdateInterface::aiDoCommand(parms);
}
