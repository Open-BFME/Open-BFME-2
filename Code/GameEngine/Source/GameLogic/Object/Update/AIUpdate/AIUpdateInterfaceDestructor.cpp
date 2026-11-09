// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1AIUpdateInterface@@MAE@XZ, retail 0x0026E836..0x0026E93D (263 bytes, EH):
// BFME2's AIUpdateInterface::~AIUpdateInterface (pinned name; opaque base of
// the six Rva0026E836Derived.cpp destructors). As in Zero Hour it clears the
// locomotor set, forgets the current locomotor, halts and deletes the state
// machine, deletes and clears the turret AI (Zero Hour's MAX_TURRETS loop,
// one slot at +0x20C here; the loop shape is what places the shared clear),
// destroys the path (rowed destroyPath 0x00262A8A) and zeroes +0x220. Retail's unwind map then
// destroys the +0x2EC member (rowed 0x0026B03D), the +0x224 member (rowed
// 0x0026E7EA), the +0x214 string, the locomotor set (rowed 0x001E86D0), the
// sixteen 12-byte records at +0x74 (eh vector destructor iterator with the
// shared bare return 0x000B3FD0) and UpdateModule (rowed 0x0024A797). Own
// tables 0x00BFA480, 0x00BFA3C0 (+0xC), 0x00C53A98 (+0x10), 0x00C47B88
// (+0x20) and 0x00C52F88 (+0x24). The views below carry only that layout.
#include "ascii_string.h"

#include "../../../../../Include/GameLogic/Module/UpdateModule.h"

class AIUpdateInterfaceFourth
{
public:
	virtual void u0() = 0;
};

class AIUpdateInterfaceFifth
{
public:
	virtual void v0() = 0;
};

#include "../../../../../Include/Common/StateMachineClass.h"

class Rva0026E836Owned
{
public:
	virtual ~Rva0026E836Owned();
};

struct Rva0026E836Record
{
	~Rva0026E836Record();
	unsigned char m_data[0xC];
};

// The +0x74 record array's element destructor, which the dtor's __ehvec_dtor
// call takes as the ICF-folded empty body at 0x000B3FD0.
Rva0026E836Record::~Rva0026E836Record()
{
}

class AIUpdateInterface;

// LocomotorSet (0x24 bytes).
class Rva001E7087
{
	friend class AIUpdateInterface;
protected:
	virtual ~Rva001E7087();
private:
	void rvaClear();
	unsigned char m_pad04[0x24 - 4];
};

class Rva0026E7EA
{
public:
	virtual ~Rva0026E7EA();
private:
	unsigned char m_pad04[0xC8 - 4];
};

class Rva0026AFDAMember
{
public:
	~Rva0026AFDAMember();
private:
	unsigned char m_pad[0xC4];
};

class Locomotor;

class AIUpdateInterface : public UpdateModule, public AIUpdateInterfaceFourth, public AIUpdateInterfaceFifth
{
public:
	// BehaviorModuleInterface slots 1 and 19 (retail VA 0x00BFA3C0): AIUpdateInterface's
	// overrides, rowed at 0x003730FC and 0x004FA5F4 (header-inline in AIUpdate.h;
	// SupplyTruckAIUpdateCtor.cpp).
	virtual CollideModuleInterface *getCollide();
	virtual AIUpdateInterface *getAIUpdateInterface();
	// UpdateModuleInterface slots (retail +0x10 tables, e.g. VA 0x00C53A98): AIUpdateInterface's
	// update (0x0026E267) and getDisabledTypesToProcess (0x004A2D67), both rowed.
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;
	void destroyPath();
	virtual bool chooseLocomotorSet(int wst);
protected:
	virtual ~AIUpdateInterface();
private:
	int m_28;
	int m_2C;
	StateMachine *m_stateMachine;			// +0x30
	unsigned char m_pad34[0x74 - 0x34];
	Rva0026E836Record m_records[16];		// +0x74
	unsigned char m_pad134[0x1CC - 0x134];
	Rva001E7087 m_locomotorSet;			// +0x1CC
	Locomotor *m_curLocomotor;			// +0x1F0
	unsigned char m_pad1F4[0x20C - 0x1F4];
	Rva0026E836Owned *m_turretAI[1];		// +0x20C
	int m_210;
	AsciiString m_214;				// +0x214
	int m_218;
	int m_21C;
	int m_220;					// +0x220
	Rva0026E7EA m_224;				// +0x224
	Rva0026AFDAMember m_2EC;			// +0x2EC
public:
	// retail slot 4: the rowed ?getModuleNameKey@AIUpdateInterface@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

AIUpdateInterface::~AIUpdateInterface()
{
	m_locomotorSet.rvaClear();
	m_curLocomotor = 0;
	if (m_stateMachine)
	{
		m_stateMachine->halt();
		::delete m_stateMachine;
	}
	for (int i = 0; i < 1; i++)
	{
		if (m_turretAI[i])
			::delete m_turretAI[i];
		m_turretAI[i] = 0;
	}
	m_stateMachine = 0;
	destroyPath();
	m_220 = 0;
}
