// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// ??1AutoAbilityBehavior@@UAE@XZ, retail 0x0045A37F, 73 bytes.
// AutoAbilityBehavior dtor over the rowed UpdateModule base 0x0024A797.
// Restores three vtables 0x00C4175C/+0x0C 0x007EFF90/+0x10 0x00C41750,
// destroys the AsciiString at +0x20 through the folded 0x00036410, then calls
// the base dtor. Layout follows the pinned ctor at 0x0045A78F (same three
// stores plus string null at +0x20) and the rowed UpdateModule ctor at
// 0x00253390 in UpdateModuleCtor.cpp (MI base with vptrs at +0/+0xC/+0x10
// plus scalars to 0x20). Called by the audited ??_G wrapper at 0x0045A560
// (slot 0 of 0x00C4175C). Shape follows Rva0024A797Derived MI precedent.
// BFME1 donor AutoAbilityBehaviorDestructorThunk.cpp:65 proves the string
// plus UpdateModule base; retail followed.

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class Rva0024A797 : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	virtual ~Rva0024A797();
};

#include "ascii_string.h"

struct Rva0045A6D3Arg
{
	char _pad[0x10];
	AsciiString m_10;
};

class AutoAbilityBehavior : public Rva0024A797
{
public:
	virtual ~AutoAbilityBehavior();
	int isAutoAbilityCommand(const Rva0045A6D3Arg *arg);

private:
	AsciiString m_str20; // +0x20
};

int AutoAbilityBehavior::isAutoAbilityCommand(const Rva0045A6D3Arg *arg)
{
	if (m_str20.isEmpty() || m_str20.compare(arg->m_10) != 0)
		return 0;
	return 1;
}

AutoAbilityBehavior::~AutoAbilityBehavior()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
