// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Apt callbacks of the in-game screen that holds the "TributePage" and
// "StatusPage" pages (destructor 0x00510D0C, so the class keeps the name
// its rowed deleting destructor gives it). Its registration, vtable slot 12
// 0x005111FA, binds them as member pointers under "_level<n>" plus
// "_TributeEnabled" and "_ReturnToGame"; that binding is their only
// reference. The methods carry the suffix as their name.

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

extern "C" char *__cdecl strcpy(char *destination, const char *source);

// Rva0050E9D3Enable.cpp's one-shot enabler on this screen's instance
// (g_Va00A046B4, which the destructor clears).
void Rva0050E9D3Enable(void);

// BfmeAskRV.cpp's player predicate.
class BfmeMemberRV
{
public:
	bool bfmeAskRV();
};

// ThePlayerList's local player at +0x10.
class PlayerList;
extern PlayerList *ThePlayerList;

struct AptTributePlayerList
{
	unsigned char m_pad00[0x10];
	BfmeMemberRV *m_local; // +0x10
};

// The rowed 0x005748AD, the base window's input handler (VtableConstant
// Predicates.cpp's view).
class Rva005748AD
{
public:
	int rva005748AD(int message, int key, int state);
};

// The rowed 0x0051274F base handler for vtable slot 2 (LINK BONUS name
// rva0051274F@Rva0051274F@@QAEHHHH@Z).
class Rva0051274F
{
public:
	int rva0051274F(int message, int key, int state);
};

// The page map's mapped value: stlport_rb_tree_hint_005109b7.cpp's
// reference-counted pointer, whose pointee has a virtual destroy slot and a
// reference count at +4. That tree's insert, erase and destructor are rowed.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef0051030C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef0051030C() : m_ptr(0) {}
	TreeHintRef0051030C(TargetRef00217D4C *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	TreeHintRef0051030C(const TreeHintRef0051030C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	TreeHintRef0051030C &operator=(const TreeHintRef0051030C &other);
	__forceinline ~TreeHintRef0051030C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

// A page: the map's pointee, held raw as the current page (+0x288). The
// selection handlers call vslot 1 on the page being shown and vslot 2 on
// the one being left; vslot 3 offers it the input first.
class Rva00510D0CPage : public TargetRef00217D4C
{
public:
	virtual void v01();
	virtual void v02();
	virtual int v03(int message, int key, int state);
	virtual int v04(int message, int key, int state);
};

class Rva00510D0C
{
public:
	void TributeEnabled(int query, char *result, bool skip);
	void ReturnToGame(const char *unused);
	// Vtable slot 1, the input handler. Name unknown.
	int rva0050EBC5(int message, int key, int state);
	// Vtable slot 2 of 0x00C6568C, retail 0x0050F5DF. Name unknown.
	int rva0050F5DF(int message, int key, int state);
	void OnPageUnloaded(const char *name);
	void OnPageSelected(const char *name);
	void OnPageLoaded(const char *params);

private:
	typedef _STL::map<AsciiString, TreeHintRef0051030C> PageMap;
	unsigned char m_pad000[0x274];
	int m_level;
	unsigned char m_pad278[0x27C - 0x278];
	PageMap m_pages;         // +0x27C, pages by name
	Rva00510D0CPage *m_page; // +0x288
};

// Retail 0x0050E98A, 67 bytes: "_TributeEnabled", an Apt query answering
// "1" when the local player passes the predicate.
void Rva00510D0C::TributeEnabled(int query, char *result, bool skip)
{
	if (query == 0 && result && !skip)
	{
		BfmeMemberRV *player = ((AptTributePlayerList *)ThePlayerList)->m_local;
		strcpy(result, player && player->bfmeAskRV() ? "1" : "0");
	}
}

// Retail 0x0050EBBD, 8 bytes: "_ReturnToGame".
void Rva00510D0C::ReturnToGame(const char *unused)
{
	Rva0050E9D3Enable();
}

// Retail 0x0050EBC5, 95 bytes. Name unknown. The current page gets the
// input first; key message 0x15 with key 1 or 0x0F returns to the game on
// the press; everything else goes to the base handler.
int Rva00510D0C::rva0050EBC5(int message, int key, int state)
{
	if (m_page && m_page->v03(message, key, state) == 1)
		return 1;
	switch (message)
	{
	case 0x15:
		switch ((unsigned char)key)
		{
		case 0x01:
		case 0x0F:
			if (state & 1)
				Rva0050E9D3Enable();
			return 1;
		}
		break;
	}
	return ((Rva005748AD *)this)->rva005748AD(message, key, state);
}

// rva0050F5DF@Rva00510D0C@@QAEHHHH@Z, retail 0x0050F5DF, 124 bytes.
// Vtable slot 2 of 0x00C6568C. The current page gets the message first
// via vslot 4, then every other page in the map, then the base handler
// 0x0051274F. Evidence: vtable neighbours slot1 0x0050EBC5 slot3 draw
//; callers none (REF via table slot 0x00865694); callees rowed
// _M_increment 0x00024250 plus pin 0x0051274F; offsets 0x27C map 0x288 page.
int Rva00510D0C::rva0050F5DF(int message, int key, int state)
{
	if (m_page && m_page->v04(message, key, state) == 1)
		return 1;
	PageMap::iterator it = m_pages.begin();
	PageMap::iterator end = m_pages.end();
	for (; it != end; ++it)
	{
		Rva00510D0CPage *page = (Rva00510D0CPage *)it->second.m_ptr;
		if (page == m_page)
			continue;
		if (page->v04(message, key, state) == 1)
			return 1;
	}
	return ((Rva0051274F *)this)->rva0051274F(message, key, state);
}

// Retail 0x00510ECC, 117 bytes: "_OnPageUnloaded". Drops the named page,
// leaving it first when it is the current one.
void Rva00510D0C::OnPageUnloaded(const char *name)
{
	AsciiString key(name);
	PageMap::iterator it = m_pages.find(key);
	if (it != m_pages.end())
	{
		TargetRef00217D4C *page = it->second.m_ptr;
		if (m_page == page)
		{
			m_page->v02();
			m_page = 0;
		}
		m_pages.erase(it);
	}
}

// Retail 0x00510F41, 125 bytes: "_OnPageSelected". Leaves the current
// page and shows the named one; an unknown name leaves no page current.
void Rva00510D0C::OnPageSelected(const char *name)
{
	AsciiString key(name);
	PageMap::iterator it = m_pages.find(key);
	if (it != m_pages.end())
	{
		Rva00510D0CPage *page = (Rva00510D0CPage *)it->second.m_ptr;
		if (page != m_page)
		{
			if (m_page)
				m_page->v02();
			m_page = page;
			page->v01();
		}
	}
	else
	{
		if (m_page)
			m_page->v02();
		m_page = 0;
	}
}

// The two page kinds, named by their rowed destructors. Their constructors
// are pinned by the factory below; both forward the level and path to the
// rowed refcounted base.
class Rva005105D7 : public TargetRef00217D4C
{
public:
	Rva005105D7(int level, const AsciiString &path);
	unsigned char m_pad08[0xD0 - 0x08];
};

class Rva00510CC3 : public TargetRef00217D4C
{
public:
	Rva00510CC3(int level, const AsciiString &path);
	unsigned char m_pad08[0x28 - 0x08];
};

class Rva0050EE23;
int __cdecl rva0050F841(Rva0050EE23 *a, const char *b);
const char *__cdecl Rva00412845AfterLevel(const char *path);
bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
int __cdecl Rva004128BBGetLevel(const char *path);

class RvaMapView
{
public:
	TreeHintRef0051030C &operator[](const AsciiString &key);
};
#pragma comment(linker, "/alternatename:??ARvaMapView@@QAEAAUTreeHintRef0051030C@@ABVAsciiString@@@Z=??A?$map@VAsciiString@@UTreeHintRef0051030C@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintRef0051030C@@@_STL@@@4@@_STL@@QAEAAUTreeHintRef0051030C@@ABVAsciiString@@@Z")

static TreeHintRef0051030C Rva00510D98CreatePage(const AsciiString &type, int level, const AsciiString &name)
{
	if (rva0050F841((Rva0050EE23 *)&type, "StatusPage") == 0)
		return TreeHintRef0051030C(new Rva005105D7(level, AsciiString(Rva00412845AfterLevel(name.str()))));
	if (rva0050F841((Rva0050EE23 *)&type, "TributePage") == 0)
		return TreeHintRef0051030C(new Rva00510CC3(level, AsciiString(Rva00412845AfterLevel(name.str()))));
	return TreeHintRef0051030C();
}

// ?OnPageLoaded@Rva00510D0C@@QAEXPBD@Z present-unmatched
void Rva00510D0C::OnPageLoaded(const char *params)
{
	AsciiString name;
	if (!Rva004128F0GetParam(params, "name", name))
		return;
	int level = Rva004128BBGetLevel(name.str());
	if (level == m_level)
	{
		AsciiString type;
		if (Rva004128F0GetParam(params, "type", type))
		{
			TreeHintRef0051030C page = Rva00510D98CreatePage(type, level, name);
			if (page.m_ptr)
				(*(RvaMapView *)&m_pages)[name] = page;
		}
	}
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
