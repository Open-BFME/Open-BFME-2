// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicHUD::RegionDetailsMovieClip::Impl (WorldBuilder
// StrategicHUDRegionDetailsMovieClip.cpp). Target facts: the ctor at
// 0x005E328A (ret 0x10) stores owner, level, a copy of the name and one more
// word; builds three 4-byte page references with the eh vector iterator
// (ctor 0x00326BE6 nulling, dtor the rowed 0x005F8F96); marks the three
// page-enabled flags; then binds "<_level%u.><name>_OnPageLoaded",
// "_OnPageUnloaded" and "_OnTabClicked" (retail strings) through the same
// command-map machinery as the HUD::Impl ctor (Common/Rva0042DB21Method.cpp).
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

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
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

// A released page reference; its nulling ctor is ICF-folded at 0x00326BE6
// (pinned; emitted here for the vector iterator), its dtor is the rowed
// 0x005F8F96.
class Rva005F8F96
{
public:
	Rva005F8F96() : m_ptr(0) {}
	~Rva005F8F96();

	TargetRef00217D4C *m_ptr;
};

// Page name to slot (rowed table lookups 0x005E2CFA and 0x005E2D8A).
void *__cdecl Rva005E2CFAGet(const char *name);
void *__cdecl Rva005E2D8AGet(const char *name);

// BfmePathLeafAfterMarker.cpp's path helpers and the pinned Apt parameter
// reader 0x004128F0.
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);
bool __cdecl Rva004128F0GetParam(const char *path, const char *key, AsciiString &value);

// The rowed TreeHintRef assignment (0x002174A4).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}

	TargetRef00217D4C *m_ptr;
};

// The rowed null-safe release of a page reference (0x002BED91).
class Rva002BED91
{
public:
	void clear();
};

// SetTabsState's helpers: the page id string (0x005E2D26, WorldBuilder
// PageSlotToID), the "<char><text>" node builder (0x002229E3) and the Apt
// call taking it (0x005E30E8), all rowed address-named.
const char *__cdecl Rva005E2D26Get(int slot);
struct Rva002229E3S12
{
	Rva002229E3S12() {}
	char m_c;
	const char *m_ptr;
	int m_len;
};
Rva002229E3S12 __cdecl Rva002229E3Build(const char &c, const char *s);
class Rva00222A8BTarget;
class Rva005E2D74;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva005E30E8AptCall(Rva00222A8BTarget *target, void *level, const char *mid, const char *function, Rva005E2D74 *obj);

namespace StrategicHUD {
class RegionDetailsMovieClip
{
public:
	class Impl;

	RegionDetailsMovieClip(int level, const AsciiString &name, int arg);
	virtual void v0();
	// Slot 1: builds the page movie for a slot.
	virtual TreeHintRef00217D4C CreatePage(int slot, int level, const AsciiString &name);
	// Slot 2: told the new current page (or -1).
	virtual void v2(int page);

private:
	Impl *m_impl; // +0x04
};
}

class StrategicHUD::RegionDetailsMovieClip::Impl
{
public:
	Impl(RegionDetailsMovieClip *owner, int level, const AsciiString &name, int arg);
	void OnPageLoaded(const char *path); // 0x005E2F49
	void OnPageUnloaded(const char *path); // 0x005E321E
	void OnTabClicked(const char *path); // 0x005E2D4B
	void SetCurrentPage(int page);
	void ShowPage(int page); // 0x005E2E91 (WorldBuilder name, pinned)
	void HidePage(int page); // 0x005E2EED (WorldBuilder name, pinned)
	void SetTabsState(int page);

private:
	RegionDetailsMovieClip *m_owner; // +0x00
	int m_level; // +0x04
	AsciiString m_name; // +0x08
	int m_0C;
	AptCommandMapAdder m_commandMaps; // +0x10
	Rva005F8F96 m_pages[3]; // +0x1C
	int m_currentPage; // +0x28
	int m_selectedTab; // +0x2C
	bool m_pageEnabled[3]; // +0x30
};

static __forceinline void FillFlags(bool *first, bool *last, bool value)
{
	for (; first != last; ++first)
		*first = value;
}

StrategicHUD::RegionDetailsMovieClip::Impl::Impl(RegionDetailsMovieClip *owner, int level, const AsciiString &name, int arg)
	: m_owner(owner), m_level(level), m_name(name), m_0C(arg), m_currentPage(-1), m_selectedTab(-1)
{
	FillFlags(m_pageEnabled, m_pageEnabled + 3, true);

	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnPageLoaded", DelegateDesc(this, &Impl::OnPageLoaded));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnPageUnloaded", DelegateDesc(this, &Impl::OnPageUnloaded));
	m_commandMaps.AddCommandMapDelegate(prefix + m_name + "_OnTabClicked", DelegateDesc(this, &Impl::OnTabClicked));
}

void StrategicHUD::RegionDetailsMovieClip::Impl::OnTabClicked(const char *path)
{
	int slot = (int)Rva005E2CFAGet(path);
	if (m_pages[slot].m_ptr != 0)
		m_selectedTab = slot;
}

void StrategicHUD::RegionDetailsMovieClip::Impl::OnPageUnloaded(const char *path)
{
	int slot = (int)Rva005E2D8AGet(path);
	Rva005F8F96 &page = m_pages[slot];
	if (page.m_ptr == 0)
	{
		((Rva002BED91 *)&page)->clear();
		if (m_currentPage == slot)
			SetCurrentPage(-1);
		if (m_selectedTab == slot)
			m_selectedTab = -1;
	}
}

void StrategicHUD::RegionDetailsMovieClip::Impl::OnPageLoaded(const char *path)
{
	int slot = (int)Rva005E2D8AGet(path);
	if (m_pages[slot].m_ptr != 0 || !m_pageEnabled[slot])
		return;

	AsciiString pageName;
	if (!Rva004128F0GetParam(path, "name", pageName))
		return;

	{
		AsciiString name(Rva00412845AfterLevel(pageName.str()));
		*(TreeHintRef00217D4C *)&m_pages[slot] = m_owner->CreatePage(slot, Rva004128BBGetLevel(pageName.str()), name);
	}
	if (slot == m_0C && m_currentPage == -1 && m_selectedTab == -1)
		m_selectedTab = m_0C;
}

// WorldBuilder Impl::SetTabsState: tells the clip "SetTabsState" with
// "_<page id>", or "_hide" for no page.
void StrategicHUD::RegionDetailsMovieClip::Impl::SetTabsState(int page)
{
	const char *id = page != -1 ? Rva005E2D26Get(page) : "hide";
	Rva005E30E8AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetTabsState", (Rva005E2D74 *)&(const Rva002229E3S12 &)Rva002229E3Build('_', id));
}

// WorldBuilder Impl::SetCurrentPage: hides the old page, updates the tabs,
// shows the new one and tells the owner (vtable slot 2).
void StrategicHUD::RegionDetailsMovieClip::Impl::SetCurrentPage(int page)
{
	if (page == m_currentPage)
		return;
	if (m_currentPage != -1)
		HidePage(m_currentPage);
	m_currentPage = page;
	SetTabsState(page);
	if (m_currentPage != -1)
		ShowPage(m_currentPage);
	m_owner->v2(m_currentPage);
}

// The owner's ctor 0x005E3463 (ret 0xC): vtable 0x00877BB4 and its Impl
// (new 0x34) built with this and the three arguments.
StrategicHUD::RegionDetailsMovieClip::RegionDetailsMovieClip(int level, const AsciiString &name, int arg)
	: m_impl(new Impl(this, level, name, arg))
{
}
