// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005EB8D6@@QAE@PAVRva005EBC74@@@Z
// Retail 0x005EB9F2..0x005EBC74 (642 bytes) thiscall RET 4.
// The strategic conflict results screen implementation constructor:
// WorldBuilder twin StrategicConflictResults::Impl::Impl
// (StrategicConflictResults.cpp:109) with the same members and bindings.
// Stores the owner (+0x00); level -1 (+0x04); clears +0x08/+0x0C; builds the
// command-map (+0x10) / extern-handler (+0x1C) / third name list (+0x28)
// through the folded vector ctor 0x001F81BF; the +0x34 owned record through
// the folded nulling ctor 0x00326BE6; two int maps (+0x38 / +0x44) through
// 0x0033C432. Then binds AptStrategicConflictResults::OnInitialized /
// OnFadeOut / Continue (0x0042D493 folded / 0x005EC0F6 / 0x005EC100),
// Player_%d_Color 0..5 to ExternPlayerColor 0x005EB955 and
// StrategicConflicResults::NumWinners (0) / NumPlayers (1) to ExternFunc
// 0x005EB77D through the delegate ctor 0x00579E47 and the rowed adders
// 0x0052458E / 0x005245F3; loads Apt\ StrategicConflictResults.apt through
// the Apt window manager (0x00DFE4CC virtual +0x50) into the level and
// registers StrategicConflictResultsTimer through the folded 0x0050B5F1.
// The retail destructor 0x005EB8D6 (Rva005EB8D6Dtor.cpp) undoes these members.
#include <map>
#include "ascii_string.h"

class StrategicConflictResults
{
public:
	class Impl;
};

// The handler methods (rowed or pinned under the WorldBuilder class name).
class StrategicConflictResults::Impl
{
public:
	void OnFadeOut(const char *unused);			// 0x005EC0F6
	void Continue(const char *unused);			// 0x005EC100
	void ExternPlayerColor(int index, char *value, bool set);	// 0x005EB955
	void ExternFunc(int index, char *value, bool set);	// 0x005EB77D
};

// The folded empty-state OnInitialized body shared with StrategicHUD's
// (0x0042D493: state 1 becomes 2).
namespace StrategicHUD
{
class HUD
{
public:
	class Impl
	{
	public:
		void OnInitialized(const char *unused);
	};
};
}

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

// Builds a delegate by value: the named result is copied out.
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
class AptCommandMap;class AptExternHandler;struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc &desc):Rva00579E47(desc){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};

class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);	// 0x0052458E

private:
	char m_pad[0xC];
};

// The extern-handler name list (ctor folded 0x001F81BF, dtor 0x005241B0).
class Rva005241B0
{
public:
	Rva005241B0();
	~Rva005241B0();

private:
	char m_pad[0xC];
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);	// 0x005245F3
};

class Rva005242D7
{
public:
	Rva005242D7();
	~Rva005242D7();

private:
	char m_pad[0xC];
};

// The +0x34 owned record pointer (nulling ctor folded at 0x00326BE6, its
// destructor is the guarded delete 0x005FA874).
class Rva005FA874
{
public:
	Rva005FA874();
	~Rva005FA874();

private:
	void *m_ptr;
};

// The timer registration folded to a false-returning stub (0x0050B5F1).
class Rva0050B5F1
{
public:
	bool rva0050B5F1(int a, int b);
};

// The Apt window manager's movie loader (virtual +0x50) returning the level.
class Rva005EB9F2AptLoader
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual int loadMovie(AsciiString directory, AsciiString file, int a, int b);
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva005EBC74;
class Rva005EB8D6
{
public:
	Rva005EB8D6(Rva005EBC74 *owner);
	~Rva005EB8D6();

private:
	Rva005EBC74 *m_owner;			// +0x00
	int m_level;				// +0x04
	int m_state;				// +0x08
	int m_0C;				// +0x0C
	AptCommandMapAdder m_commandMaps;	// +0x10
	Rva005241B0 m_externHandlers;		// +0x1C
	Rva005242D7 m_28;			// +0x28
	Rva005FA874 m_34;			// +0x34
	_STL::map<int, void *> m_38;		// +0x38
	_STL::map<int, void *> m_44;		// +0x44
};

Rva005EB8D6::Rva005EB8D6(Rva005EBC74 *owner)
	: m_owner(owner)
	, m_level(-1)
	, m_state(0)
	, m_0C(0)
{
	typedef StrategicConflictResults::Impl Impl;
	AptExternHandlerAdder *externHandlers = reinterpret_cast<AptExternHandlerAdder *>(&m_externHandlers);
	{
		AsciiString name("AptStrategicConflictResults::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, &StrategicHUD::HUD::Impl::OnInitialized)));
	}
	{
		AsciiString name("AptStrategicConflictResults::OnFadeOut");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, &Impl::OnFadeOut)));
	}
	{
		AsciiString name("AptStrategicConflictResults::Continue");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeDelegate(this, &Impl::Continue)));
	}
	AsciiString playerColor;
	int i = 0;
	{
		DelegateDesc playerColorHandler = MakeDelegate(this, &Impl::ExternPlayerColor);
		for (; i < 6; ++i)
		{
			playerColor.format("Player_%d_Color", i);
			externHandlers->AddExternHandler(playerColor, i, AptRef<AptExternHandler>(playerColorHandler));
		}
	}
	{
		AsciiString name("StrategicConflicResults::NumWinners");
		externHandlers->AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeDelegate(this, &Impl::ExternFunc)));
	}
	{
		AsciiString name("StrategicConflicResults::NumPlayers");
		externHandlers->AddExternHandler(name, 1, AptRef<AptExternHandler>(MakeDelegate(this, &Impl::ExternFunc)));
	}
	m_level = reinterpret_cast<Rva005EB9F2AptLoader *>(g_bfmeAptWindowManager)->loadMovie("Apt\\", "StrategicConflictResults.apt", 0, 0);
	{
		AsciiString name("StrategicConflictResultsTimer");
		reinterpret_cast<Rva0050B5F1 *>(&m_34)->rva0050B5F1(m_level, (int)&name);
	}
}
