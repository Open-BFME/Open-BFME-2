// ??0Impl@BattlePromptMovieClip@StrategicHUD@@QAE@PAV12@HABVAsciiString@@ABURva005F91F3Src@@@Z
// partial score=0.85 date=2026-10-09
// ??0Impl@BattlePromptMovieClip@StrategicHUD@@QAE@PAV12@HABVAsciiString@@ABURva005F91F3Src@@@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
// V1 bank: native entry 0x005FA3B1, 1082 bytes. Ordinary C++ hot body
// also emits 1082 bytes, but frame is 0xA4 rather than native 0x9C;
// prefix uses [ebp+0xC] rather than [ebp+8], saved this uses -0x20 vs -0x18.
// Native handler 0x007A5D55 -> FuncInfo 0x0095EE94 proves 19 states:
// name +8, maps +0xC, cached Unicode +0x1C, vector +0x20, owner +0x2C,
// vector +0x30, owner +0x3C, vector +0x40, vector +0x50, prefix, nine temps.
// This object's compiled cleanup map has that order and those 19 states.
// Native +0x18 is a plain word; +0x60..62 are plain bool flags. The old
// bank's destructible +0x18 and flag wrapper were artificial lifetime changes.
// Owning holders use the existing Rva000AD6F4 destructor spelling/pin.
// The three opaque vector element identities still need reconciliation with
// the home TU and matched storage/destructor providers. No new alias pin is
// justified just because _Vector_base at 0x00211E58 has identical storage.
// No Code/ admission: remaining frame/temp ownership and provider-type gaps.
// Target layout is independently established by stores and cleanup actions;
// WorldBuilder BattlePrompt source supplies purpose/name, not byte proof.
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

// Actual19-state native unwind map has no destructor at18 or60.
// +2C/+3C owning slots call canonical29B clear0AD6F4; +20/+30
// vector cleanup5F97D4, +40/+50 page vectors5F9813 are separate states.
class Rva000AD6F4 {
public: Rva000AD6F4():ptr(0){} ~Rva000AD6F4(); void clear();
private: void *ptr;
};
struct BattlePromptRecord;
struct BattlePromptAllyPage;
struct BattlePromptEnemyPage;

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
    void *m_18; // +0x18
    UnicodeString m_cachedName; // +0x1C
    _STL::vector<BattlePromptRecord> m_allyTabs; Rva000AD6F4 m_allySlot; // +0x20
    _STL::vector<BattlePromptRecord> m_enemyTabs; Rva000AD6F4 m_enemySlot; // +0x30
    _STL::vector<BattlePromptAllyPage> m_40; int m_selectedAlly; // +0x40
    _STL::vector<BattlePromptEnemyPage> m_50; int m_selectedEnemy; // +0x50
    bool m_flag60, m_flag61, m_flag62; // +0x60; sizeof 0x64 (the owner ctor's new)
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
	: m_owner(owner), m_level(level), m_name(name),m_18(0),m_selectedAlly(-1),m_selectedEnemy(-1),m_flag60(false),m_flag61(false),m_flag62(false)
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
