// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva0031763A@@QAE@XZ @0x003175D1 105B, ??0Rva0031763A@@QAE@XZ @0x0031763A 127B,
// ??4Rva0031763A@@QAEAAV0@ABV0@@Z @0x00317779 115B. Honest-address ctor/dtor/copy-assign
// trio for the same 0x2C-byte value struct used as a local in FUN_007177ec and
// FUN_008115a9 (Apt/Window layout-block parsing): 5 dwords at +0x00..+0x10 zeroed,
// 5 AsciiStrings at +0x14..+0x24, _STL::list<int> at +0x28.
// - dtor destroys list via rowed _List_base dtor 0x4EC395 then 5 Strings via pinned
//   0x36410 (both ??1AsciiString and ??1StringBase fold there), EH states 4..0 + -1.
// - ctor mem-inits 5 ints to 0, 3 Strings from AsciiString::TheEmptyString (0x9E0878)
//   via pinned copy 0x365F0 (AsciiString and StringBase spellings fold there), 2 Strings
//   default-zeroed inline, list via rowed _List_base ctor 0x4EC36C, body clears list via
//   rowed 0x23DAA5; EH states mirror the dtor and the StringBase-forwarder gives the
//   retail lea-before-push order (probe-proven: simple AsciiString model misorders).
// - assign copies 5 dwords then 5 Strings via pinned assign 0x366F0 then list via rowed
//   list assign 0x2C54EE, ret 4.
// Identity: honest Rva0031763A (ctor address); class layout proven by the assign body
// (5x dword + 5x String assign + list assign) and by FUN_007177ec setting +0x14..+0x20
// to "APT:None" and inserting into +0x28. Callers: ctor from 0x3176D3/0x317843/
// 0x4116C0/0x411709, dtor from 0x317755/0x3179E6/0x4116F7/0x411746 plus Unwind funclets,
// assign sole-called from 0x317B1D. Flags: neighbour parseDrawCallback /O1 /DNDEBUG /MD
// /EHsc plus /D_STLP_USE_STATIC_LIB for list<int> (ProductionUpdateCtor precedent);
// shims with /D_CRTIMP=/bfmealloc/bfmelist collapse the dtor EH to max 3 (probe-proven).
// No BFME1 donor; non-virtual QAE (no vptr stores).

#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::_List_base(const allocator<int> &);
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::_Node *list<int, allocator<int> >::_M_create_node(const int &);
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#include "ascii_string.h"


class GameWindowManager;
class WindowLayout;
class Rva0031763A;
typedef WindowLayout *(__stdcall *NativeLayoutFactory)(Rva0031763A *);
class Rva0031763A
{
public:
	Rva0031763A();
	~Rva0031763A();
	Rva0031763A &operator=(const Rva0031763A &that);
 friend class GameWindowManager;
private:
	int m_unk00; // +0x00
	int m_unk04; // +0x04
	int m_unk08; // +0x08
	int m_unk0C; // +0x0C
	NativeLayoutFactory m_unk10; // +0x10
	AsciiString m_s14; // +0x14
	AsciiString m_s18; // +0x18
	AsciiString m_s1C; // +0x1C
	AsciiString m_s20; // +0x20
	AsciiString m_s24; // +0x24
	_STL::list<int, _STL::allocator<int> > m_list28; // +0x28
};

Rva0031763A::Rva0031763A() :
	m_unk00(0),
	m_unk04(0),
	m_unk08(0),
	m_unk0C(0),
	m_unk10(0),
	m_s14(AsciiString::TheEmptyString),
	m_s18(AsciiString::TheEmptyString),
	m_s1C(AsciiString::TheEmptyString)
{
	m_list28.clear();
}

// ??1Rva0031763A@@QAE@XZ @0x003175D1
Rva0031763A::~Rva0031763A()
{
}

Rva0031763A &Rva0031763A::operator=(const Rva0031763A &that)
{
	m_unk00 = that.m_unk00;
	m_unk04 = that.m_unk04;
	m_unk08 = that.m_unk08;
	m_unk0C = that.m_unk0C;
	m_unk10 = that.m_unk10;
	m_s14 = that.m_s14;
	m_s18 = that.m_s18;
	m_s1C = that.m_s1C;
	m_s20 = that.m_s20;
	m_s24 = that.m_s24;
	m_list28 = that.m_list28;
	return *this;
}

class WindowLayoutInfo
{
public:
	bool load(AsciiString filename);
	unsigned int m_version; // +0x00 +0x00
	void *m_init; // +0x04 +0x04
	void *m_update; // +0x08 +0x08
	void *m_shutdown; // +0x0C +0x0C
	void *m_classCallback; // +0x10 +0x10
	AsciiString m_initName; // +0x14 +0x14
	AsciiString m_updateName; // +0x18 +0x18
	AsciiString m_shutdownName; // +0x1C +0x1C
	AsciiString m_className; // +0x20 +0x20
	AsciiString m_filename; // +0x24 +0x24
	void *m_windowList; // +0x28 +0x28 list<GameWindow *> node (44-byte info, ctor 0x0031763A)
};
class BfmeQuickMatchScreenBase {
public:
 BfmeQuickMatchScreenBase();
 virtual void bfmeSlot0();
 virtual void bfmeSlot1();
 virtual void bfmeSlot2();
 virtual void bfmeSlot3();
 virtual void rva00538AB0(bool);
 virtual void slot5();
 virtual void add(void*);
private:
 unsigned char native04[0x20];
 void bfmeAttach(void *);
 friend class GameWindowManager;
};
#include "../../../Include/GameClient/GameWindowManager.h"
// Native3176B9..317779/192B; WB13A7060..13A71DE and the native
// manager vtable slot32 establish winCreateLayout. The existing44B info
// supplies a stdcall factory at10; its load and the36B layout constructor
// and private attach method are independently rowed. Catch(...) returns0.
// EH thunk77A69D -> FuncInfo9231CC -> try9231B8 -> catch entry9231A8
// identifies317717 as this parent's catch body; it is not an integer getter.
// ZH/BFME1 GameWindowManagerScript supplies the layout-loading semantic
// family; native and WB establish the BFME2 callback/exception extension.
WindowLayout *GameWindowManager::winCreateLayout(AsciiString filename)
{
    WindowLayout *layout;
    Rva0031763A info;
    if (!reinterpret_cast<WindowLayoutInfo *>(&info)->load(filename))
        return 0;
    if (info.m_unk10) {
        try {
            layout = info.m_unk10(&info);
        } catch (...) {
            return 0;
        }
    } else {
        layout = reinterpret_cast<WindowLayout *>(new BfmeQuickMatchScreenBase);
        reinterpret_cast<BfmeQuickMatchScreenBase *>(layout)->bfmeAttach(&info);
    }
    return layout;
}
