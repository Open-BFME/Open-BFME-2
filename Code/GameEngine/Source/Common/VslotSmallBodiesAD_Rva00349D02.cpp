// cl: /DNDEBUG /MD
// Split from VslotSmallBodiesAD.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AD: each calls an unrowed (Ghidra-listed, larger) function, pinned in
// reverse/symbols.csv under an address-derived name with the arguments and
// return its call sites and ret show. As in VslotSmallBodiesA-AC, classes
// and methods are address-derived unless the ledger already names them,
// and model only what each body touches. Meanings are not recovered.

typedef int Int;
typedef float Real;

class Object;
enum ObjectStatusTypes
{
	OBJECT_STATUS_1C = 0x1C
};
enum KindOfType
{
	KINDOF_INVALID = -1
};
#include "../GameLogic/Object/object.h"
struct Rva00349D02Machine
{
	char m_pad00[0x14];
	Object *m_owner14;
};

// 0x00260E44: whether the object at VA 0x00DFECC4 exists and its pinned
// 0x00288CFA accepts the argument's +0x264 word.
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
// Slot 1 (allow) of partition filter vftable 0x00C5A99C.
// 0x0026156C: filter slot1 of native vftable C600A0. Its caller preserves
// Object::rva0029493F's AL result; the older void/int view dropped that ABI fact.
// The source Object at+8 and mode at+C match the notifier's native filter.
// 0x00349D02 (AI state tables): the result of the rowed
// AIAttackMeleeEngageState::updateInternal (0x003497E6, AIStates.cpp) on
// this, setting or clearing status 0x1C on the owner as it is -1.
#include "../../Include/Common/StateMachine.h"
class Rva00349D02;
class AIAttackMeleeEngageState
{
	friend class Rva00349D02;
	StateReturnType updateInternal();
};
class Rva00349D02
{
public:
	Int update();
private:
	char m_pad00[0x18];
	Rva00349D02Machine *m_18;
};
Int Rva00349D02::update()
{
	Object *owner = m_18->m_owner14;
	Int result = reinterpret_cast<AIAttackMeleeEngageState *>(this)->updateInternal();
	owner->setStatus(OBJECT_STATUS_1C, result == -1);
	return result;
}

// 0x00359729: HotKeyManager::translate (0x00359556, rowed in
// MessageStream/HotKey.cpp) of the manager at VA 0x00E01E28 with the
// argument, 0 without the manager.
class GameMessage;
enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};
#include "../../Include/GameClient/HotKeyManager.h"
extern HotKeyManager *TheHotKeyManager;
// 0x003AFE24 and 0x003AFE36: GPU resource access through the manager
// at VA 0x00DFDD04; return zero if it is absent. Providers are byte-verified
// in ParticleSystemManagerGetShaderSetup.cpp (1F4002 and 1F40AF).
struct IDirect3DVertexDeclaration9;
class DX8IndexBufferClass;
namespace FXParticleSystem {
#include "../../Include/GameClient/ParticleSys.h"
}
extern class ParticleSystemManager *TheParticleSystemManager;
// 0x003C35F7 lives beside its callee 0x003C35AA in ScriptGlueRva003C35AA.cpp.

// 0x0040E0C5: for the argument's +0x78 object in state 4 (+0x2C), the
// rowed ArmySummary 0x0040DF77 (ArmySummary.cpp) then the rowed 0x0040E02B;
// answers true.
#include "../../Include/GameLogic/ArmySummary.h"
class Rva0040E02B
{
public:
	void rva0040E02B();
};
class Rva0040DF77 : public Rva0040E02B
{
public:
	char m_pad00[0x2C];
	Int m_2C;
};
struct Rva0040E0C5Arg
{
	char m_pad00[0x78];
	Rva0040DF77 *m_78;
};
class Rva0040CFFF
{
public:
	virtual bool rva0040E0C5(Rva0040E0C5Arg *arg);
};
bool Rva0040CFFF::rva0040E0C5(Rva0040E0C5Arg *arg)
{
	Rva0040DF77 *armySummary = arg->m_78;
	if (armySummary && armySummary->m_2C == 4)
	{
		reinterpret_cast<ArmySummary *>(armySummary)->rva0040DF77();
		armySummary->rva0040E02B();
	}
	return true;
}

// 0x00414B89 and 0x00415122: the pinned 0x00414B0A resp. 0x0041505B on
// every 0x30-byte entry of the [+0x10, +0x14) range.
// 0x00482134 and 0x00482152 (the latter through an interface at +0x20):
// the pinned 0x0035A292 of TheGameLogic's +0x170 object with the +0x08 word
// and the +0x04 object's +0x08 Real.
class GameLogic;
extern GameLogic *TheGameLogic;
// 0x004CDF00 and 0x004CDF1D: the rowed SpecialAbilityUpdate::onExit
// (0x004502CE, SpecialAbilityUpdate.cpp) with both arguments then the pinned
// 0x004CDDBA(1); resp. only the latter while +0x08 is set.
class ActivateModuleSpecialPower;
class SpecialAbilityUpdate
{
	friend class ActivateModuleSpecialPower;
protected:
	virtual void onExit(bool a, bool b);
};
class ActivateModuleSpecialPower
{
public:
	void onExit(bool a, bool b);
	void onObjectCreated();
	void SetWakeState(Int a);
private:
	Int m_00;
	Int m_04;
	Int m_08;
};
void ActivateModuleSpecialPower::onExit(bool a, bool b)
{
	reinterpret_cast<SpecialAbilityUpdate *>(this)->SpecialAbilityUpdate::onExit(a, b);
	SetWakeState(1);
}


// 0x004EF2FA (interface at +0x04): the pinned 0x004EEE38 of the complete
// object with the first argument.
// 0x00508925: whether the rowed 0x005075D6 (Rva005075D6TargetFilter.cpp)
// accepts both arguments on this.
#include "../../Include/GameLogic/Module/Rva00507823.h"

class Rva00508925
{
public:
	bool rva00508925(Int a, Int target);
};
bool Rva00508925::rva00508925(Int a, Int target)
{
	return (bool)reinterpret_cast<Rva00507823 *>(this)->rva005075D6((const void *)a, (Object *)target);
}

class Player;
// 0x003AFF06 (28B): a vtable slot that forwards both of its arguments to the
// ParticleSystem member at 0x001F9BA4 (rowed in Rva001F9BA4Generate.cpp as
// FXParticleSystem::ParticleSystem::rva001F9BA4(void *, int)) through the system
// held at +0x4, when one is held. The test goes through the conversion
// operator, the call through operator->, which falls back to the rowed
// null-system factory 0x001FCBD7 and re-reads +0x4 (volatile read), as the
// sibling ParticleSystem::destroy (0x001F462C) does. Class and method names
// are address-derived; the meaning is not recovered.
class ParticleSystem;
namespace FXParticleSystem {
class ParticleSystem
{
public:
	void rva001F9BA4(void *context, Int count);
};
}

ParticleSystem *Make001FCBD7(void);

class Rva003AFF06SystemPtr
{
public:
	operator ParticleSystem *(void) const
	{
		return m_target;
	}

	ParticleSystem *operator->(void) const
	{
		ParticleSystem *target = *(ParticleSystem *const volatile *)&m_target;
		if (!target)
			target = Make001FCBD7();
		return target;
	}

private:
	ParticleSystem *m_target;
};

#include "../../Include/Common/Rva003AFF06.h"

// ?rva003AFF06@Rva003AFF06@@UAEXPAX0@Z @0x003AFF06 (28B)
void Rva003AFF06::rva003AFF06(void *context, void *b)
{
	if (m_system != 0)
		reinterpret_cast<FXParticleSystem::ParticleSystem *>(m_system.operator->())->rva001F9BA4(context, (Int)b);
}
