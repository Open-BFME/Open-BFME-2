// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native5FA3B1..5FA7EB RET16, 1082B. The existing named owner/callbacks,
// nine registration strings, region-name setter and AddAlly establish the
// BattlePrompt Impl identity. WB160AA50 provides the matching sequence.
// Target stores and native FuncInfo95EE94 prove 19 cleanup states and the
// flat64B layout: no destructible word18 and no flag-owner subobject60.
// The existing home TU proves property records are12B (Unicode+8), page
// handles4B, and page objects have48B storage with reference count4.
// Actual STLport4.5.3 template types and proper Rva579E47 construction
// restore frame9C/prefix+8/saved-this-18; flags stay ordinary initializers.
// RegistryAsciiPath supplies the string-node semantic guide, and the
// existing BattlePrompt home supplies the property/page types. The two
// counted tab-window holders clear through the rowed0AD6F4 provider.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
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

class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);void*m_ptr;};
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc&d):Rva00579E47(d){}~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}};
static __forceinline DelegateDesc MakeBinding(void(AptCommandTarget::*method)(const char*),AptCommandTarget*object){DelegateDesc d(object,method);return d;}
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
		AddCommandMap(name, desc);
	}

private:
	_STL::vector<AsciiString> m_names;
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

inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}


// The four tab lists (+0x20/+0x30 property records and +0x40/+0x50 page
// handles) use the existing home TU types and stock STLport construction.
// The independent +0x4C/+0x5C page selections are -1 in retail; the
// +0x2C/+0x3C tab-window holders are separately destructible owners.
#include <vector>
struct BfmeStringRecord005F93E3 {unsigned word0,word1;UnicodeString text;~BfmeStringRecord005F93E3();};
class Rva005FA0C9;
struct Rva005FA197Element {Rva005FA0C9*ptr;Rva005FA197Element(const Rva005FA197Element&);~Rva005FA197Element();};
class Rva005FA0F7;
struct Rva005FA1CEElement {Rva005FA0F7*ptr;Rva005FA1CEElement(const Rva005FA1CEElement&);~Rva005FA1CEElement();};
namespace _STL {
template<> vector<BfmeStringRecord005F93E3>::~vector();
template<> vector<Rva005FA197Element>::~vector();
template<> vector<Rva005FA1CEElement>::~vector();
}
// Actual19-state native unwind map has no destructor at18 or60.
// +2C/+3C owning slots call canonical29B clear0AD6F4; +20/+30
// vector cleanup5F97D4, +40/+50 page vectors5F9813 are separate states.
class Rva000AD6F4 {
public: Rva000AD6F4():ptr(0){} ~Rva000AD6F4(); void clear();
private: void *ptr;
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
    void *m_18; // +0x18
    UnicodeString m_cachedName; // +0x1C
    _STL::vector<BfmeStringRecord005F93E3> m_allyTabs; Rva000AD6F4 m_allySlot; // +0x20
    _STL::vector<BfmeStringRecord005F93E3> m_enemyTabs; Rva000AD6F4 m_enemySlot; // +0x30
    _STL::vector<Rva005FA197Element> m_40; int m_selectedAlly; // +0x40
    _STL::vector<Rva005FA1CEElement> m_50; int m_selectedEnemy; // +0x50
    bool m_flag60, m_flag61, m_flag62; // +0x60; sizeof 0x64 (the owner ctor's new)
};
// The Impl ctor 0x005FA3B1 (ret 0x10): owner, level and the name copy;
// binds nine "<_level%u.><name>_On..." command maps (retail strings; the
// bound 0x005F9904 is WorldBuilder's Impl::OnAllyTabsLoaded), blanks the
// region name and adds the ally.
StrategicHUD::BattlePromptMovieClip::Impl::Impl(BattlePromptMovieClip *owner, int level, const AsciiString &name, const Rva005F91F3Src &ally)
	: m_owner(owner), m_level(level), m_name(name),m_18(0),m_selectedAlly(-1),m_selectedEnemy(-1),m_flag60(false),m_flag61(false),m_flag62(false)
{
	{
		AsciiString prefix;

		prefix.format("_level%u.", m_level);
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnAllyTabsLoaded", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnAllyTabsLoaded),(AptCommandTarget*)this));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnAllyTabsUnloaded", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnAllyTabsUnloaded),(AptCommandTarget*)this));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnEnemyTabsLoaded", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnEnemyTabsLoaded),(AptCommandTarget*)this));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnEnemyTabsUnloaded", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnEnemyTabsUnloaded),(AptCommandTarget*)this));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnOpen", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnOpen),(AptCommandTarget*)this));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnClosed", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnClosed),(AptCommandTarget*)this));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnAutoResolveButtonClicked", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnAutoResolveButtonClicked),(AptCommandTarget*)this));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRealTimeButtonClicked", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnRealTimeButtonClicked),(AptCommandTarget*)this));
		m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnRetreatButtonClicked", MakeBinding(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(&Impl::OnRetreatButtonClicked),(AptCommandTarget*)this));
		SetRegionNameString(UnicodeString::TheEmptyString);
		AddAlly(ally);
	}
}
