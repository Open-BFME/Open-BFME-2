// ?rva0045A57C@AutoAbilityBehavior@@QAE_NXZ
// partial score=0.95 date=2026-10-09
// stlport
// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
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
class Object;

class BehaviorModuleBase
{
	virtual void unused();
protected:
	const ModuleData *m_data;
	Object *m_object;
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
	bool rva0045A57C();

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

// Retail 0x0045A63F is a cdecl lookup, not a member (no ECX use and RET).
// The object list at +0x244 is null terminated; each primary module vslot
// +0x10 returns its name key. AutoAbilityBehavior's class string supplies
// the cached key. The optional command name is the module data's +0x18
// AsciiString, independently established by its matched destructor.
// No donor establishes the original public name of this lookup.
enum NameKeyType { NK_UNKNOWN = 0 };
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct Rva0045A63FData
{
    char pad[0x18];
    StringBase<char> command;
};
class Rva0045A63FModule
{
public:
    virtual void slot0() = 0;
    virtual void slot4() = 0;
    virtual void slot8() = 0;
    virtual void slotC() = 0;
    virtual NameKeyType getModuleNameKey() const = 0;
    const Rva0045A63FData *data;
};
struct Rva0045A63FObject
{
    char pad[0x244];
    Rva0045A63FModule **modules;
};

Rva0045A63FModule *Rva0045A63F(const Rva0045A63FObject *obj, const AsciiString &command)
{
    static NameKeyType key = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
    Rva0045A63FModule *result = 0;
    for (Rva0045A63FModule **iter = obj->modules; *iter; ++iter)
    {
        if ((*iter)->getModuleNameKey() == key)
        {
            result = *iter;
            if (result->data->command.getLength() <= 0 || result->data->command.compare(*(const StringBase<char> *)&command) == 0)
                break;
            result = 0;
        }
    }
    return result;
}

namespace _STL { template <int N> struct _Base_bitset { bool _M_is_any() const; unsigned words[N]; }; }
class Rva00331682Holder
{
public:
    bool test(const void *) const;
};
class Rva00263546
{
public:
    bool rva00263546(const Rva00263546 *) const;
};
class CommandButton;
class ControlBar
{
public:
    const CommandButton *findCommandButton(const AsciiString &);
};
extern ControlBar *TheControlBar;
class CommandButton
{
public:
    bool isReady(const Object *) const;
    char pad[0x13C];
    Rva00263546 rejected;
};
enum ObjectStatusTypes { OBJECT_STATUS_RVA_4A = 0x4A };
struct Rva0045A57CAI { char pad[0x34]; unsigned value; };
class Object
{
public:
    bool rva002922D9(const CommandButton *);
    int rva0028F4EF();
    bool testStatus(ObjectStatusTypes) const;
    char pad0[0x94];
    unsigned status[4];
    char padA4[0x10C - 0xA4];
    unsigned model[19];
    char pad158[0x258 - 0x158];
    const Rva0045A57CAI *ai;
    bool testModel(unsigned bit) const { return (model[bit >> 5] >> (bit & 31)) & 1; }
};
struct Rva0045A57CData
{
    char pad[0x1C];
    _STL::_Base_bitset<4> allowed;
};
// BFME1 command-ready body supplies purpose; BFME2 adds module status
// exclusion, model bits 128/127/163, command mask and object status 74.
// ?rva0045A57C@AutoAbilityBehavior@@QAE_NXZ present-unmatched
bool AutoAbilityBehavior::rva0045A57C()
{
    const Rva0045A57CData *data = (const Rva0045A57CData *)m_data;
    Object *obj = m_object;
    if (data->allowed._M_is_any() && ((const Rva00331682Holder *)&data->allowed)->test(obj->status))
        return false;
    const CommandButton *button = TheControlBar->findCommandButton(m_str20);
    if (!button->isReady(obj) || !obj->rva002922D9(button))
        return false;
    if (obj->testModel(128) || obj->testModel(127) || obj->testModel(163))
        return false;
    if (!obj->rva0028F4EF())
        return false;
    if (((const Rva00263546 *)obj->model)->rva00263546(&button->rejected))
        return false;
    if (obj->testStatus(OBJECT_STATUS_RVA_4A))
        return false;
    const Rva0045A57CAI *ai = obj->ai;
    if (!ai || ai->value == 0)
        return true;
    return false;
}
