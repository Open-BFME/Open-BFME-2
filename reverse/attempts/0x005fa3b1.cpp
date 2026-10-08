// ??0Impl@BattlePromptMovieClip@StrategicHUD@@QAE@PAV12@HABVAsciiString@@ABURva005F91F3Src@@@Z
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// BANK NOTE (0x005FA3B1 BattlePromptMovieClip::Impl ctor, 1082 B): this
// body compiles to 1082 B and differs only by four unresolved pins
// (_Vector_base<Rva005FA3B1Element> -> 0x00211E58, AddAlly 0x005FA205; the
// nine callbacks are DIR32) and the order of the prefix's zeroing against
// the three flag stores (retail zeroes [ebp+8] first). It is NOT the
// WorldBuilder layout: WorldBuilder has +0x18 a plain word, +0x2C / +0x3C
// EH-tracked holders after the ally / enemy tab vectors, +0x4C / +0x5C plain
// -1 words after the other two vectors, and plain flags (retail EH states:
// name 0, maps 1, cached name 2, vectors and holders 3..8, prefix 9). That
// faithful layout (members in that order, bools in the init list) matches
// the state numbering and the flag order but packs the prefix into
// [ebp+0xC] (frame 0xA4 vs 0x9C): the allocator temps at [ebp+0xB] block
// the owner's home unless an EH-tracked object is built after the last
// vector, which is why this banked variant carries a stateful +0x18 holder
// and a stateful flag struct. The real separator is still unknown; the
// prefix also needs its own block scope here.
// StrategicHUD::BattlePromptMovieClip::Impl::SetRegionNameString @ 0x005F9364 103B
// (WorldBuilder name, StrategicHUDBattlePromptMovieClip.cpp line 788: the
// APT:_level%u.%s_RegionName key and SetText); twin of 0x005FB770 PlayerName.
// 0x005F960C (its cached-compare caller) keeps its address name.
// Target evidence: 103B retail, EH_prolog, format string
// "APT:_level%u.%s_RegionName" at VA 0x008758D4, rowed AsciiString::format
// 0x00038150, pinned bfmeSetText 0x00225301, rowed releaseBuffer 0x00036410,
// manager at VA 0x009FE4CC, default %s at VA 0x007BAC1C, callers 0x005F960C 0x005FA7BD.
template <typename T> struct BfmeStringData
{
    int refCount;
    unsigned short length;
    unsigned short capacity;
    T text[1];
};
#include "ascii_string.h"
#include "unicode_string.h"
class BfmeAptWindowManager
{
public:
    void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
struct TeamNameHolder
{
    char m_pad[8];
    const char *m_name;
};
struct TargetRef00217D4C;
// The Apt command-map machinery of the HUD::Impl ctor
// (Common/Rva0042DB21Method.cpp) and the concat nodes of
// System/RegistryAsciiPath.cpp, as in the sibling Impl ctors.
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

template <class T> class AptRef
{
public:
	AptRef(const DelegateDesc *desc) { rva00579E47(desc); }
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
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

class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src); // 0x000B3F84

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}


// The four tab lists (+0x20, +0x30, +0x40, +0x50): an STLport vector (base
// ctor the folded 0x00211E58, pinned) and a selection word, zero for the
// ally / enemy tabs and -1 for the other two (WorldBuilder builds them with
// three inline ctors; element and member types unknown).
struct Rva005FA3B1Element;
namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a) throw();
	~_Vector_base();

protected:
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};

template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
{
public:
	__forceinline vector() : _Vector_base<T, A>(A()) {}
	~vector();
};
}

// +0x18: a zeroed word with an EH state (a reference holder; type unknown).
struct Rva005FA3B1Ref
{
	Rva005FA3B1Ref() : m_ptr(0) {}
	~Rva005FA3B1Ref();

	void *m_ptr;
};

// +0x60..+0x62: three cleared flags with an EH state (type unknown).
struct Rva005FA3B1Flags
{
	Rva005FA3B1Flags() : m_0(false), m_1(false), m_2(false) {}
	~Rva005FA3B1Flags();

	bool m_0;
	bool m_1;
	bool m_2;
};

struct Rva005FA3B1Tabs
{
	__forceinline Rva005FA3B1Tabs() : m_selected(0) {}
	~Rva005FA3B1Tabs();

	_STL::vector<Rva005FA3B1Element> m_tabs;
	int m_selected;
};

struct Rva005FA3B1List
{
	__forceinline Rva005FA3B1List() : m_selected(-1) {}
	~Rva005FA3B1List();

	_STL::vector<Rva005FA3B1Element> m_items;
	int m_selected;
};

// The ally / enemy record AddAlly copies through the rowed converting copy
// 0x005F91F3 (address-named; WorldBuilder asserts allyData.pageFactory).
struct Rva005F91F3Src;

namespace StrategicHUD
{
class BattlePromptMovieClip
{
public:
	class Impl;

	BattlePromptMovieClip(int level, const AsciiString &name, const Rva005F91F3Src &ally);
	virtual ~BattlePromptMovieClip();

private:
	Impl *m_impl; // +0x04
};
}
class StrategicHUD::BattlePromptMovieClip::Impl
{
public:
    Impl(BattlePromptMovieClip *owner, int level, const AsciiString &name, const Rva005F91F3Src &ally);
    void SetRegionNameString(const UnicodeString &regionName);
    void rva005F960C(const UnicodeString &regionName);
    void AddAlly(const Rva005F91F3Src &ally); // 0x005FA205 (pinned)
    void OnAllyTabsLoaded(const char *path); // 0x005F9904 (pinned)
    void OnAllyTabsUnloaded(const char *path); // 0x005F8F80 (pinned)
    void OnEnemyTabsLoaded(const char *path); // 0x005F9A1B (pinned)
    void OnEnemyTabsUnloaded(const char *path); // 0x005F8F8B (pinned)
    void OnOpen(const char *path); // 0x005F8E7D (pinned)
    void OnClosed(const char *path); // 0x005F8E94 (pinned)
    void OnAutoResolveButtonClicked(const char *path); // 0x005F8EAA (pinned)
    void OnRealTimeButtonClicked(const char *path); // 0x005F8EBA (pinned)
    void OnRetreatButtonClicked(const char *path); // 0x005F8ECA (pinned)
private:
    BattlePromptMovieClip *m_owner; // +0x00
    unsigned int m_level; // +0x04
    AsciiString m_name; // +0x08
    AptCommandMapAdder m_commandMaps; // +0x0C
    Rva005FA3B1Ref m_18; // +0x18
    UnicodeString m_cachedName; // +0x1C
    Rva005FA3B1Tabs m_allyTabs; // +0x20
    Rva005FA3B1Tabs m_enemyTabs; // +0x30
    Rva005FA3B1List m_40; // +0x40
    Rva005FA3B1List m_50; // +0x50
    Rva005FA3B1Flags m_60; // +0x60; sizeof 0x64 (the owner ctor's new)
};
void StrategicHUD::BattlePromptMovieClip::Impl::SetRegionNameString(const UnicodeString &regionName)
{
    AsciiString key;
    const char *teamName;
    TeamNameHolder *team = *(TeamNameHolder **)&m_name;
    if (team)
        teamName = (const char *)((char *)team + 8);
    else
        teamName = "";
    key.format("APT:_level%u.%s_RegionName", m_level, teamName);
    ((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, regionName, true);
}
void StrategicHUD::BattlePromptMovieClip::Impl::rva005F960C(const UnicodeString &regionName)
{
    if (regionName.compare(m_cachedName) != 0)
    {
        SetRegionNameString(regionName);
        m_cachedName.set(regionName);
    }
}
class Rva005F9775
{
public:
    void rva005F9775(const UnicodeString &regionName);
private:
    char m_pad[4];
    StrategicHUD::BattlePromptMovieClip::Impl *m_member;
};
void Rva005F9775::rva005F9775(const UnicodeString &regionName)
{
    m_member->rva005F960C(regionName);
}

// The Impl ctor 0x005FA3B1 (ret 0x10): owner, level and the name copy;
// binds ten "<_level%u.><name>_On..." command maps (retail strings; the
// bound 0x005F9904 is WorldBuilder's Impl::OnAllyTabsLoaded), blanks the
// region name and adds the ally.
StrategicHUD::BattlePromptMovieClip::Impl::Impl(BattlePromptMovieClip *owner, int level, const AsciiString &name, const Rva005F91F3Src &ally)
	: m_owner(owner), m_level(level), m_name(name)
{
	{
		AsciiString prefix;
		prefix.format("_level%u.", m_level);
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnAllyTabsLoaded", DelegateDesc(this, &Impl::OnAllyTabsLoaded));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnAllyTabsUnloaded", DelegateDesc(this, &Impl::OnAllyTabsUnloaded));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnEnemyTabsLoaded", DelegateDesc(this, &Impl::OnEnemyTabsLoaded));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnEnemyTabsUnloaded", DelegateDesc(this, &Impl::OnEnemyTabsUnloaded));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnOpen", DelegateDesc(this, &Impl::OnOpen));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnClosed", DelegateDesc(this, &Impl::OnClosed));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnAutoResolveButtonClicked", DelegateDesc(this, &Impl::OnAutoResolveButtonClicked));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRealTimeButtonClicked", DelegateDesc(this, &Impl::OnRealTimeButtonClicked));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRetreatButtonClicked", DelegateDesc(this, &Impl::OnRetreatButtonClicked));
		SetRegionNameString(UnicodeString::TheEmptyString);
		AddAlly(ally);
	}
}

// The owner's ctor 0x005FA7EB (ret 0xC): vtable 0x008078DC and its Impl
// (new 0x64; ctor 0x005FA3B1, pinned: it binds the WorldBuilder-named
// _OnAllyTabsLoaded / _OnEnemyTabsLoaded handlers, blanks the region name
// through SetRegionNameString and adds the ally) built with this and the
// arguments.
StrategicHUD::BattlePromptMovieClip::BattlePromptMovieClip(int level, const AsciiString &name, const Rva005F91F3Src &ally)
	: m_impl(new Impl(this, level, name, ally))
{
}
