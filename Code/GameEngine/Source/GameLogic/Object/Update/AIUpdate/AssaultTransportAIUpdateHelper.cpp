// cl: /DNDEBUG /MD
//
// ?Rva0048F365Helper@AssaultTransportAIUpdate@@QAEXXZ, retail 0x0048F365
// (93 bytes). Loop-zeroing helper over three count-sized arrays plus scalar
// tails: clears the dword run at +0x3E8 plus the byte runs at +0x410 and
// +0x41A for the +0x43C count, zeroes the count, zeroes the three floats at
// +0x424/+0x428/+0x42C, zeroes the ints at +0x430/+0x434/+0x438 plus the
// byte stores at +0x440/+0x441/+0x442. Called at member position by the behavior ctor plus the
// dispatcher methods. Row supersedes the helper pin.

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
void AssaultTransportAIUpdate::Rva0048F365Helper() throw()
{
	for (int i = 0; i < m_currentMembers; ++i)
	{
		m_memberIDs[i] = (ObjectID)0;
		m_memberHealing[i] = 0;
		m_array41A[i] = 0;
	}
	m_currentMembers = 0;
	float *floats424 = &m_attackMoveGoalPos.x;
	floats424[0] = 0.0f;
	floats424[1] = 0.0f;
	floats424[2] = 0.0f;
	m_designatedTarget = (ObjectID)0;
	m_state = IDLE;
	m_framesRemaining = 0;
	m_isAttackMove = 0;
	m_isAttackObject = 0;
	m_bfmeFlag442 = 0;
}
