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
	TreeHintRef0051030C(const TreeHintRef0051030C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
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
};

class Rva00510D0C
{
public:
	void TributeEnabled(int query, char *result, bool skip);
	void ReturnToGame(const char *unused);
	// Vtable slot 1, the input handler. Name unknown.
	int rva0050EBC5(int message, int key, int state);
	void OnPageUnloaded(const char *name);

private:
	typedef _STL::map<AsciiString, TreeHintRef0051030C> PageMap;
	unsigned char m_pad000[0x27C];
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

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
