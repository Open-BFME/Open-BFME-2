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


class Shell
{
public:
	void rva0035BF4C(bool shutdownImmediate);
};
extern Shell *TheShell;

class InGameUI
{
public:
#define UI_SLOT(N) virtual void slot##N();
	UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04) UI_SLOT(05) UI_SLOT(06) UI_SLOT(07)
	UI_SLOT(08) UI_SLOT(09) UI_SLOT(10) UI_SLOT(11) UI_SLOT(12) UI_SLOT(13) UI_SLOT(14) UI_SLOT(15)
	UI_SLOT(16) UI_SLOT(17) UI_SLOT(18) UI_SLOT(19) UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23)
	UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29) UI_SLOT(30) UI_SLOT(31)
	UI_SLOT(32) UI_SLOT(33) UI_SLOT(34) UI_SLOT(35) UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39)
	UI_SLOT(40) UI_SLOT(41) UI_SLOT(42) UI_SLOT(43) UI_SLOT(44) UI_SLOT(45) UI_SLOT(46) UI_SLOT(47)
	UI_SLOT(48) UI_SLOT(49) UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53) UI_SLOT(54) UI_SLOT(55)
	UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59) UI_SLOT(60) UI_SLOT(61) UI_SLOT(62) UI_SLOT(63)
	UI_SLOT(64) UI_SLOT(65) UI_SLOT(66) UI_SLOT(67) UI_SLOT(68) UI_SLOT(69) UI_SLOT(70) UI_SLOT(71)
	UI_SLOT(72) UI_SLOT(73) UI_SLOT(74) UI_SLOT(75) UI_SLOT(76) UI_SLOT(77) UI_SLOT(78) UI_SLOT(79)
	UI_SLOT(80) UI_SLOT(81) UI_SLOT(82) UI_SLOT(83) UI_SLOT(84) UI_SLOT(85) UI_SLOT(86) UI_SLOT(87)
	UI_SLOT(88) UI_SLOT(89) UI_SLOT(90) UI_SLOT(91) UI_SLOT(92) UI_SLOT(93)
#undef UI_SLOT
	virtual void slot94(bool visible);
};
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
		TheInGameUI->slot94(false);
	if (TheShell)
		TheShell->rva0035BF4C(false);
}

Rva00510D0C::Rva00510D0C(void *context)
	: _bfme_AptGameWindow(context), m_page(0)
{
	g_Va00A046B4 = (GlobalA046B4 *)this;
}
