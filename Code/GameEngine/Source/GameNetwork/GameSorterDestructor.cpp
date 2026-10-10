// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// GameSorter constructor580842 and WB1562BC0 bind its five named sort
// callbacks; target stores primary4/previous8 at0C/10, flags14/15 and cycle18.
// 580B40 appends the LAN/online GameInfo pointers, 58113D indexes and sorts
// them, and 580182 changes the sort fields. Vector storage is12B, object28B.
// The automatic destructor has the full14-byte free-first-pointer shape at
// 7FAB3 called by AptLanLobby::~AptLanLobby44455C and its EH cleanup.
// Keep this provider separate: whole-TU exception analysis otherwise removes
// the caller's state2 transition. No public exception guarantee is inferred.
#include <vector>
#include "ascii_string.h"
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

// 0x00579E47 is rowed as the delegate-wrapper constructor ??0Rva00579E47@@QAE@ABUDelegateDesc@@@Z
// (built in place as the by-value AddCommandMap argument); AptRef<T> builds through it.
class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc); // 0x00579E47
protected:
	Rva00579E47() {}
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, &desc);
	}

private:
	char m_pad[0xC];
};


class GameInfo;
class Rva005248D0 { public: virtual ~Rva005248D0(); AptCommandMapAdder maps; };
class GameSorter {
public:
 GameSorter(Rva005248D0 *registry);
 ~GameSorter();
 void OnSortStatus(const char*);
 void OnSortName(const char*);
 void OnSortMap(const char*);
 void OnSortPlayers(const char*);
 void OnSortPing(const char*);

private:
 _STL::vector<GameInfo*> m_games;
 int m_primarySort;
 int m_previousSort;
 bool m_changed;
 bool m_sorted;
 int m_cycle;
};
GameSorter::~GameSorter() {}

// Native580842..5809DB constructs the pointer vector and five registered
// sort callbacks. The callback strings and their corresponding code pointers
// independently establish the GameSorter identity; target stores prove fields.
// Registration follows the existing verified StrategicHUD delegate pattern.
GameSorter::GameSorter(Rva005248D0 *registry) : m_primarySort(4),m_previousSort(8),m_changed(false),m_sorted(true),m_cycle(0) {
 { AsciiString name("GameSorter::OnSortStatus");registry->maps.AddCommandMapDelegate(name,DelegateDesc(this,&GameSorter::OnSortStatus)); }
 { AsciiString name("GameSorter::OnSortName");registry->maps.AddCommandMapDelegate(name,DelegateDesc(this,&GameSorter::OnSortName)); }
 { AsciiString name("GameSorter::OnSortMap");registry->maps.AddCommandMapDelegate(name,DelegateDesc(this,&GameSorter::OnSortMap)); }
 { AsciiString name("GameSorter::OnSortPlayers");registry->maps.AddCommandMapDelegate(name,DelegateDesc(this,&GameSorter::OnSortPlayers)); }
 { AsciiString name("GameSorter::OnSortPing");registry->maps.AddCommandMapDelegate(name,DelegateDesc(this,&GameSorter::OnSortPing)); }
}

// The existing state-change provider has the same receiver and field layout.
class Rva00580172 { public: void rva00580182(int); };

// Constructor580842 binds native5801C0 to GameSorter::OnSortName.
// Its complete10B body forwards selector1 to580182 and returns RET4.
void GameSorter::OnSortName(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(1);
}

// Constructor580842 binds native5801CA to GameSorter::OnSortMap.
// Its complete10B body forwards selector2 to580182 and returns RET4.
void GameSorter::OnSortMap(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(2);
}

// Constructor580842 binds native5801D4 to GameSorter::OnSortPlayers.
// Its complete10B body forwards selector4 to580182 and returns RET4.
void GameSorter::OnSortPlayers(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(4);
}

// Constructor580842 binds native5801DE to GameSorter::OnSortPing.
// Its complete10B body forwards selector8 to580182 and returns RET4.
void GameSorter::OnSortPing(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(8);
}

// Constructor580842 binds native5801E8 to GameSorter::OnSortStatus.
// Its complete10B body forwards selector16 to580182 and returns RET4.
void GameSorter::OnSortStatus(const char *)
{
 reinterpret_cast<Rva00580172*>(this)->rva00580182(16);
}
