// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ??0Class@AptCreateAHero@@QAE@PAURva005B3676Owner@@@Z, retail 0x005B57FA..0x005B59FD
// (also OnMapLoaded 0x005B59FD, below)
// (515 bytes, EH, ret 4). The create-a-hero class page (WB
// AptCreateAHero::Class::Class; the class keeps its address name Rva005B5420
// from its rowed dtor 0x005B5420, vtable 0x00C73450). Native evidence: stores
// the owner at +4 (base), +0x14 flag, +0x18 word, +0x1C hero list (rowed ctor
// 0x0040A530), binds CahClass::InitGadgets, the two translated descriptions
// (APT:CahClassDescription / APT:CahTypeDescription), runs the rowed
// CreateDefaultHeroes 0x005B566B, registers the NumClassTypes / NumClasses
// extern handlers (rowed ExternFunc 0x005B5485) and the SetClassAndType
// command (rowed Run 0x005B57C6). Callback targets and the InitGadgets slot
// are DIR32 references. Pattern follows AptCreateAHeroPowers.cpp.
#include "ascii_string.h"

class Rva005B3676Owner;
class AptExternHandler;
class AptCommandMap;
class AptScreenInitGadgets;
class GameWindow;

class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);

#include "../../../../../Include/Common/DelegateDesc.h"

template <class T, class M> __forceinline DelegateDesc MakeDelegate(T *object, M method)
{
	DelegateDesc desc(object, method);
	return desc;
}

// Link: the AptRef lineage fork. The wrapper spelling used here emitted a
// census-losing dtor copy (a jmp to an extern base dtor, digest e67a72158686);
// retail keeps the majority TU's inline-release copy (digest 361dbf55f6ea).
// Adopt the majority spelling (ArmyCommandPointsMovieClipConstructor.cpp):
// trivial base (no declared dtor; the copy ctor stays declared so the implicit
// AptRef copy ctor is non-trivial and the by-value temp convention is kept),
// public ptr, inline release dtor. Only the COMDAT body changes to retail's.
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47 &other);void*ptr;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc &desc):Rva00579E47(desc){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};
#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"
void _bfme_setAptScreenRef(const AsciiString &, AptRef<AptScreenInitGadgets>);

#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005B3676Owner
{
	char m_pad00[0x21C];
	AptCommandMapAdder m_adder; // +0x21C
	char m_externs[1];
};
#include "../../../../../Include/Common/Rva005B566B.h"

class Rva0040A530
{
public:
	Rva0040A530(bool flag);
	~Rva0040A530();
private:
	char m_pad[0x14];
};

class Rva005B5420Base
{
public:
	Rva005B5420Base(Rva005B3676Owner *owner) : m_owner(owner) {}
	virtual ~Rva005B5420Base() {}
protected:
	// Inline owner read: written as a plain m_owner read, cl keeps the +0x21C
	// command-map offset in EDI across both registrations in OnMapLoaded.
	Rva005B3676Owner *getOwner() const { return m_owner; }
	Rva005B3676Owner *m_owner;
};

class Rva005B57C6Box
{
public:
	void Run(char *);
};

// The Exit callback 0x005B5418 keeps its rowed address-class name (the class
// Rva005B5420Dtor.cpp views; only the method is needed here).
class Rva005B5420
{
public:
	void rva005B5418(const char *);
};

namespace AptCreateAHero
{
class Class : public Rva005B5420Base
{
public:
	Class(Rva005B3676Owner *owner);
	virtual ~Class() {}
	void OnMapLoaded();
	// The OnMapClick delegate target is retail's shared empty ret-4 stub at
	// RVA 0x0047A69C.
	void OnMapClick(const char *) {}
	// The InitGadgets delegate target is retail's shared empty ret-0xC stub
	// at RVA 0x000D1407.
	void rva000D1407(const char *, void *, GameWindow *) {}
	void ExternFunc(int, char *, bool);
private:
	char m_pad08[0x14 - 0x08];
	bool m_flag14;
	char m_pad15[3];
	int m_word18;
	Rva0040A530 m_heroes;
};
}

AptCreateAHero::Class::Class(Rva005B3676Owner *owner)
	: Rva005B5420Base(owner), m_flag14(false), m_word18(0), m_heroes(true)
{
	{ AsciiString name("CahClass::InitGadgets"); _bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(MakeDelegate(this, &Class::rva000D1407))); }
	{ AsciiString value(" "); AsciiString key("APT:CahClassDescription"); g_bfmeAptWindowManager->rva00225375(key, value, false); }
	{ AsciiString value(" "); AsciiString key("APT:CahTypeDescription"); g_bfmeAptWindowManager->rva00225375(key, value, false); }
	((Rva005B566B *)this)->rva005B566B();
	{ AsciiString name("CahClass::NumClassTypes"); ((AptExternHandlerAdder *)owner->m_externs)->AddExternHandler(name, 1, AptRef<AptExternHandler>(MakeDelegate(this, &Class::ExternFunc))); }
	{ AsciiString name("CahClass::NumClasses"); ((AptExternHandlerAdder *)owner->m_externs)->AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeDelegate(this, &Class::ExternFunc))); }
	{ AsciiString name("AptCreateAHero::Class::SetClassAndType"); owner->m_adder.AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate((Rva005B57C6Box *)this, &Rva005B57C6Box::Run))); }
}

// 0x005B59FD..0x005B5AAF (178 bytes, EH): WB 0x0157BFF0
// AptCreateAHero::Class::OnMapLoaded. Registers the Exit (0x005B5418) and
// OnMapClick command maps on the owner's command-map adder (+0x21C), reusing
// one delegate descriptor; the owner is re-read for each registration.
void AptCreateAHero::Class::OnMapLoaded()
{
	DelegateDesc desc;
	{ AsciiString name("AptCreateAHero::Class::Exit"); desc = MakeDelegate((Rva005B5420 *)this, &Rva005B5420::rva005B5418); getOwner()->m_adder.AddCommandMap(name, AptRef<AptCommandMap>(desc)); }
	{ AsciiString name("AptCreateAHero::Class::OnMapClick"); desc = MakeDelegate(this, &Class::OnMapClick); getOwner()->m_adder.AddCommandMap(name, AptRef<AptCommandMap>(desc)); }
}
