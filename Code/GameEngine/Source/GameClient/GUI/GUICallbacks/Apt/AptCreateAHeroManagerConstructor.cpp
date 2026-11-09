// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ??0Rva005B6B93@@QAE@PAVAptCreateAHero@@@Z, retail 0x005B6B93..0x005B6E32
// (671 bytes, EH, ret 4). The create-a-hero manager page (WB
// AptCreateAHero::Manager::Manager; the class keeps its address name), built
// by the screen constructor 0x005142B0 (new 0x28, pinned until now). Native
// evidence: vtable 0x00C735C0, the owner at +4, an empty 3-pointer list at
// +8, a flag +0x14 set, selection +0x24 = -1; registers the OnDeleteHero,
// OnPlayGame, OnSelectAward, the three Mission::OnSort* and the two power
// rollover commands through the owner's command map adder (+0x21C) and
// binds CahManager::InitGadgets. Callback targets are DIR32 references.
// Pattern follows AptCreateAHeroClassConstructor.cpp.
//
// The nine callback DIR32s at 0x005B6B93's binding sites name these retail
// bodies (read from retail's operands; ledger names as rowed):
//   OnDeleteHero      0x005B6A5E ?rva005B6A5E@Manager@AptCreateAHero@@QAEXH@Z
//   OnPlayGame        0x005B5B0C ?Run@Rva005B5B0CBox@@QAEXH@Z
//   OnSelectAward     0x005B5E2D ?OnSelectAward@Manager@AptCreateAHero@@QAEXPBD@Z
//   OnSortIcon        0x005B6A31 ?rva005B6A31@Manager@AptCreateAHero@@QAEXPAX@Z
//   OnSortName        0x005B6A40 ?rva005B6A40@Manager@AptCreateAHero@@QAEXPAX@Z
//   OnSortType        0x005B6A4F ?rva005B6A4F@Manager@AptCreateAHero@@QAEXPAX@Z
//   OnMyPowerRollOver 0x005B5B39 ?OnMyPowerRollOver@Manager@AptCreateAHero@@QAEXPAD@Z
//   OnMyPowerRollOut  0x005B5B92 ?rva005B5B92@Rva005B5B92@@QAEXPBD@Z
//   InitGadgets       0x005B6967 ?InitGadgets@Manager@AptCreateAHero@@QAEXPADH0@Z
// The relocations are masked, so empty local stand-ins matched the bytes while
// every button did nothing in the image (P102). The views below declare only
// those methods, so each binding resolves to the rowed body.
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

// Link (AptRef lineage fork): the wrapper dtor copy (digest e67a72158686)
// lost to the majority inline-release copy (361dbf55f6ea, = rowed
// ??1Rva005F8F96 at 0x005F8F96 via the 0x7DEEF pin). Trivial base (no declared
// dtor; copy ctor kept declared) + inline release dtor emit retail's bytes.
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47 &other);void*ptr;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc &desc):Rva00579E47(desc){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};

#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"
void _bfme_setAptScreenRef(const AsciiString &, AptRef<AptScreenInitGadgets>);


#include "../../../../../Include/Common/AptCreateAHero.h"

class AptCreateAHero::Manager
{
public:
	void rva005B6A5E(int);
	void OnSelectAward(const char *);
	void rva005B6A31(void *);
	void rva005B6A40(void *);
	void rva005B6A4F(void *);
	void OnMyPowerRollOver(char *);
	void InitGadgets(char *, int, char *);
};
class Rva005B5B92 {public: void rva005B5B92(const char *);};
struct Rva005B5B0CBox {void Run(int);};

class Rva005B6B93Base
{
public:
	Rva005B6B93Base(AptCreateAHero *owner) : m_owner(owner) {}
	virtual ~Rva005B6B93Base() {}
protected:
	AptCreateAHero *m_owner;
};

struct AptCreateAHeroCommandsView
{
	char m_pad00[0x21C];
	char m_commands[1];
};

class Rva005B6B93 : public Rva005B6B93Base
{
public:
	Rva005B6B93(AptCreateAHero *owner);
	virtual ~Rva005B6B93();
private:
	void *m_list08;
	void *m_list0C;
	void *m_list10;
	bool m_flag14;
	bool m_flag15;
	bool m_flag16;
	char m_pad17[0x24 - 0x17];
	int m_selected24;
};

Rva005B6B93::Rva005B6B93(AptCreateAHero *owner)
	: Rva005B6B93Base(owner), m_list08(0), m_list0C(0), m_list10(0), m_flag14(true), m_flag15(false), m_flag16(false), m_selected24(-1)
{
#define BIND_COMMAND(method, label) \
	{ AsciiString name(label); ((AptCommandMapAdder *)((AptCreateAHeroCommandsView *)owner)->m_commands)->AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, method))); }
	BIND_COMMAND(&AptCreateAHero::Manager::rva005B6A5E, "AptCreateAHero::Manager::OnDeleteHero")
	BIND_COMMAND(&Rva005B5B0CBox::Run, "AptCreateAHero::Manager::OnPlayGame")
	BIND_COMMAND(&AptCreateAHero::Manager::OnSelectAward, "AptCreateAHero::Manager::OnSelectAward")
	BIND_COMMAND(&AptCreateAHero::Manager::rva005B6A31, "Mission::OnSortIcon")
	BIND_COMMAND(&AptCreateAHero::Manager::rva005B6A40, "Mission::OnSortName")
	BIND_COMMAND(&AptCreateAHero::Manager::rva005B6A4F, "Mission::OnSortType")
	BIND_COMMAND(&AptCreateAHero::Manager::OnMyPowerRollOver, "AptCreateAHero::OnMyPowerRollOver")
	BIND_COMMAND(&Rva005B5B92::rva005B5B92, "AptCreateAHero::OnMyPowerRollOut")
	{ AsciiString name("CahManager::InitGadgets"); _bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(MakeDelegate(this, &AptCreateAHero::Manager::InitGadgets))); }
}

// ?Rva005B6B93::~Rva005B6B93 present-unmatched
Rva005B6B93::~Rva005B6B93() {}
