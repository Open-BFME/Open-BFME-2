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
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	bool rva0029493F(Object *victim, int mode);
	bool isKindOf(KindOfType t) const;
};
struct Rva00349D02Machine
{
	char m_pad00[0x14];
	Object *m_owner14;
};

// 0x00260E44: whether the object at VA 0x00DFECC4 exists and its pinned
// 0x00288CFA accepts the argument's +0x264 word.
class Rva00288CFA
{
public:
	bool rva00288CFA(Int a);
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
struct Rva00260E44Arg
{
	char m_pad00[0x264];
	Int m_264;
};
// Slot 1 (allow) of partition filter vftable 0x00C5A99C.
class Rva00260E44Filter
{
public:
	virtual ~Rva00260E44Filter();
	virtual bool allow(Object *obj);
};


// 0x0026156C: filter slot1 of native vftable C600A0. Its caller preserves
// Object::rva0029493F's AL result; the older void/int view dropped that ABI fact.
// The source Object at+8 and mode at+C match the notifier's native filter.
class Rva000421C8
{
public:
 virtual ~Rva000421C8();
 virtual bool allow(Object *)=0;
 virtual int getPlayerMask();
 Rva000421C8 *m_next;
};
class Rva0026156C:public Rva000421C8
{
public:
 virtual bool allow(Object *candidate);
private:
 Object *m_object;
 int m_mode;
};


// 0x00349D02 (AI state tables): the result of the rowed
// AIAttackMeleeEngageState::updateInternal (0x003497E6, AIStates.cpp) on
// this, setting or clearing status 0x1C on the owner as it is -1.
enum StateReturnType
{
	STATE_CONTINUE = 0
};
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
class HotKeyManager
{
public:
	GameMessageDisposition translate(const GameMessage *msg);
};
extern HotKeyManager *TheHotKeyManager;
class HotKeyTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *a);
};


// 0x003AFE24 and 0x003AFE36: GPU resource access through the manager
// at VA 0x00DFDD04; return zero if it is absent. Providers are byte-verified
// in ParticleSystemManagerGetShaderSetup.cpp (1F4002 and 1F40AF).
struct IDirect3DVertexDeclaration9;
class DX8IndexBufferClass;
namespace FXParticleSystem {
class ParticleSystemManager {
public:
	IDirect3DVertexDeclaration9 *GetVertexDeclaration();
	DX8IndexBufferClass *rva001F40AF();
};
}
extern class ParticleSystemManager *TheParticleSystemManager;
class Rva003AFE24
{
public:
	Int rva003AFE24();
	Int rva003AFE36();
};



// 0x003C35F7 lives beside its callee 0x003C35AA in ScriptGlueRva003C35AA.cpp.

// 0x0040E0C5: for the argument's +0x78 object in state 4 (+0x2C), the
// rowed ArmySummary 0x0040DF77 (ArmySummary.cpp) then the rowed 0x0040E02B;
// answers true.
class ArmySummary
{
public:
	void rva0040DF77();
};
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
class Rva00414B0A
{
public:
	void rva00414B0A();
	void rva0041505B();
private:
	char m_pad00[0x30];
};
class Rva00414B89
{
public:
	void rva00414B89();
	void rva00415122();
private:
	char m_pad00[0x10];
	Rva00414B0A *m_start;
	Rva00414B0A *m_finish;
};



// 0x00482134 and 0x00482152 (the latter through an interface at +0x20):
// the pinned 0x0035A292 of TheGameLogic's +0x170 object with the +0x08 word
// and the +0x04 object's +0x08 Real.
class Rva0035A292
{
public:
	void rva0035A292(Int a, Real b);
};
struct Rva00482134Logic
{
	char m_pad00[0x170];
	Rva0035A292 *m_170;
};
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva00482134Data
{
	Int m_00;
	Int m_04;
	Real m_08;
};
class Rva00482134
{
public:
	void rva00482134();
private:
	Int m_00;
	Rva00482134Data *m_04;
	Int m_08;
};

class Rva00482152Primary
{
public:
	virtual void primarySlot();
protected:
	Rva00482134Data *m_04;
	Int m_08;
	char m_pad0C[0x14];
};
class Rva00482152Iface
{
public:
	virtual void rva00482152(Int unused) = 0;
};
class Rva00482152 : public Rva00482152Primary, public Rva00482152Iface
{
public:
	void rva00482152(Int unused);
};


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
class LivingWorldScoreKeeper
{
public:
	virtual void primarySlot();
	void collectEndOfTurnStats(Int a);
};
class Rva004EF2FAIface
{
public:
	virtual void rva004EF2FA(Int a, Int unused) = 0;
};
class Rva004EF2FA : public LivingWorldScoreKeeper, public Rva004EF2FAIface
{
public:
	void rva004EF2FA(Int a, Int unused);
};


// 0x00508925: whether the rowed 0x005075D6 (Rva005075D6TargetFilter.cpp)
// accepts both arguments on this.
class Rva00507823
{
public:
	unsigned char rva005075D6(const void *arg, Object *target);
};

class Rva00508925
{
public:
	bool rva00508925(Int a, Int target);
};
bool Rva00508925::rva00508925(Int a, Int target)
{
	return (bool)reinterpret_cast<Rva00507823 *>(this)->rva005075D6((const void *)a, (Object *)target);
}

class Rva00508F1E : public Rva00507823
{
public:
	bool rva00508F1E(const void *arg, Object *target);
};


class Rva002CA9CA
{
public:
	bool rva002CAA59(int target, const void *arg);
};

class Rva005092D4 : public Rva00507823
{
public:
	bool rva005092D4(const void *arg, Object *target);
private:
	char m_pad00[0x128];
	Rva002CA9CA *m_128;
};


class Player;
struct Rva2225E0Filter
{
	bool accepts(Object *, Player *);
};

class Rva0050B92D : public Rva00507823
{
public:
	unsigned char rva0050B92D(const void *arg, Object *target);
private:
	char m_pad00[0x128];
	Rva2225E0Filter m_filter128;
};


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

class Rva003AFF06
{
public:
	virtual void rva003AFF06(void *a, void *b);

private:
	Rva003AFF06SystemPtr m_system;				///< +0x4
};

// ?rva003AFF06@Rva003AFF06@@UAEXPAX0@Z @0x003AFF06 (28B)
void Rva003AFF06::rva003AFF06(void *a, void *b)
{
	if (m_system != 0)
		reinterpret_cast<FXParticleSystem::ParticleSystem *>(m_system.operator->())->rva001F9BA4(a, (Int)b);
}
