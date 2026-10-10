// ??0Rva00510D0C@@QAE@PAX@Z
// partial score=0.97 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00510D0C@@QAE@PAX@Z, retail 0x00510FDB..0x00511031 (86 bytes, EH,
// ret 4). The in-game tribute screen's constructor (class named by its
// deleting destructor 0x00511031; callbacks and registration in
// AptTributePageCallbacks.cpp and AptTributePageRegister.cpp): the Apt window
// base 0x0051268C, vtables 0x00C6568C / 0x00C65688, the page map at +0x27C
// (rowed empty-tree constructor), no current page at +0x288 and the screen
// singleton 0x00A046B4 (which the destructor clears).
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


class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	unsigned char m_pad004[0x58 - 4];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

class Rva00510D0CPage;
struct GlobalA046B4;
extern GlobalA046B4 *g_Va00A046B4;

class Rva00510D0C : public _bfme_AptGameWindow
{
public:
	Rva00510D0C(void *context);
	virtual ~Rva00510D0C();
private:
	typedef _STL::map<AsciiString, TreeHintRef0051030C> PageMap;
	PageMap m_pages;         // +0x27C
	Rva00510D0CPage *m_page; // +0x288
};

Rva00510D0C::Rva00510D0C(void *context)
	: _bfme_AptGameWindow(context), m_page(0)
{
	g_Va00A046B4 = (GlobalA046B4 *)this;
}
