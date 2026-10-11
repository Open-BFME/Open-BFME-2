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
#include "ascii_string.h"

class Rva005B3676Owner;
class AptExternHandler;
class AptCommandMap;
class AptScreenInitGadgets;
class GameWindow;

class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);

struct DelegateDesc
{
	template <class T, class M> DelegateDesc(T *object, M method)
		: m_object(reinterpret_cast<AptDelegateTarget *>(object))
		, m_method(reinterpret_cast<AptDelegateMethod>(method))
	{
	}

	AptDelegateTarget *m_object;
	AptDelegateMethod m_method;
};

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

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>);
};
void _bfme_setAptScreenRef(const AsciiString &, AptRef<AptScreenInitGadgets>);


class AptCreateAHero;

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
	void OnDeleteHero(const char *);
	void OnPlayGame(const char *);
	void OnSelectAward(const char *);
	void OnSortIcon(const char *);
	void OnSortName(const char *);
	void OnSortType(const char *);
	void OnMyPowerRollOver(const char *);
	void OnMyPowerRollOut(const char *);
	void InitGadgets(const char *, void *, GameWindow *);
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
#define BIND_COMMAND(handler, label) \
	{ AsciiString name(label); ((AptCommandMapAdder *)((AptCreateAHeroCommandsView *)owner)->m_commands)->AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, &Rva005B6B93::handler))); }
	BIND_COMMAND(OnDeleteHero, "AptCreateAHero::Manager::OnDeleteHero")
	BIND_COMMAND(OnPlayGame, "AptCreateAHero::Manager::OnPlayGame")
	BIND_COMMAND(OnSelectAward, "AptCreateAHero::Manager::OnSelectAward")
	BIND_COMMAND(OnSortIcon, "Mission::OnSortIcon")
	BIND_COMMAND(OnSortName, "Mission::OnSortName")
	BIND_COMMAND(OnSortType, "Mission::OnSortType")
	BIND_COMMAND(OnMyPowerRollOver, "AptCreateAHero::OnMyPowerRollOver")
	BIND_COMMAND(OnMyPowerRollOut, "AptCreateAHero::OnMyPowerRollOut")
	{ AsciiString name("CahManager::InitGadgets"); _bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(MakeDelegate(this, &Rva005B6B93::InitGadgets))); }
}
