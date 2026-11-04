// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva00510D0C@@UAE@XZ, retail 0x00510D0C..0x00510D87 (123 bytes, EH).
// The in-game tribute screen's destructor (class named by its deleting
// destructor 0x00511031; callbacks and registration in
// AptTributePageCallbacks.cpp and AptTributePageRegister.cpp; vtables
// 0x00C6568C / 0x00C65688): clears the screen singleton 0x00A046B4, hides the
// in-game UI menu (vslot 94) and the shell, then the page map at +0x27C and the
// Apt window base go. The opaque pin of the deleting destructor stays.
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

#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
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


namespace _STL
{
// The tree destructor is the rowed 0x0051097F (stlport_rb_tree_dtor_twins.cpp),
// and the base constructor the copy stlport_rb_tree_hint_005109b7.cpp compiles.
typedef pair<const AsciiString, TreeHintRef0051030C> TreeHintPair0051030C;
template <>
_Rb_tree<AsciiString, TreeHintPair0051030C, _Select1st<TreeHintPair0051030C>, less<AsciiString>,
	allocator<TreeHintPair0051030C> >::~_Rb_tree();
template <>
_Rb_tree_base<TreeHintPair0051030C, allocator<TreeHintPair0051030C> >::_Rb_tree_base(
	const allocator<TreeHintPair0051030C> &);
}

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../../../Include/GameClient/Rva005248D0.h"

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


#include "../../../../../Include/GameClient/Shell.h"
extern Shell *TheShell;

#include "../../../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

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


Rva00510D0C::~Rva00510D0C()
{
	g_Va00A046B4 = 0;
	if (TheInGameUI)
		TheInGameUI->rva0029AC03(false);
	if (TheShell)
		TheShell->rva0035BF4C(false);
}

Rva00510D0C::Rva00510D0C(void *context)
	: _bfme_AptGameWindow(context), m_page(0)
{
	g_Va00A046B4 = (GlobalA046B4 *)this;
}
