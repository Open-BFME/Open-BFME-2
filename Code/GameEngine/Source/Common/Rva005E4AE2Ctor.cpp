// cl: /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// ??0Rva005E4AE2@@QAE@PAXPAU_Rva005E4AE2In@@H@Z @0x005E4AE2 141B.
// Constructor of a two-base object that registers its listener base with a
// holder's list through the rowed append 0x005A0B4C. Retail's unwind map:
// state 0 destroys the first polymorphic base through the vptr setter
// 0x005E394E, state 1 the +4 listener base through 0x005E3947, state 2 the
// map<int, void *> at +0x1C (ctor 0x0033C432). The +4 subobject first gets
// its own vtable 0x00C79544 and then this class's second vtable, the pattern
// of a second base. Its vtable differs from the listener base of
// Rva0057605DCtor.cpp, so it keeps its own address-derived name and is passed
// to the list as the list's pointer type. Replaces the banked 0.91 attempt,
// which wrote the vtable stores as volatile integers.
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<pair<int const, void *>, allocator<pair<int const, void *> > >::_Rb_tree_base(allocator<pair<int const, void *> > const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::_M_erase(_Rb_tree_node<pair<int const, void *> > *); }
// bfme link decl-only end
// Nothing this unit's row reaches releases the map's header node; declare the
// base destructor and node deallocate so the unit emits no copies of its own.
namespace _STL { template <> _Rb_tree_base<pair<int const, void *>, allocator<pair<int const, void *> > >::~_Rb_tree_base(); }
namespace _STL { template <> void allocator<_Rb_tree_node<pair<int const, void *> > >::deallocate(_Rb_tree_node<pair<int const, void *> > *, size_t) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
struct Rva002BA8F1Listener;
#include "../../Include/Common/Rva005E4AE2Listener.h"
// Preserve the original forced-inline construction path.
__forceinline Rva005E4AE2Listener::Rva005E4AE2Listener() {}
#include "../../Include/Common/Rva005A0B4CList.h"
struct Rva005E4AE2Holder
{
	Rva005A0B4CList m_list;
	// append's push_back 0x004DFCB0 uses the list's first 12 bytes; its header declares none.
	char m_listRest[0x0C - sizeof(Rva005A0B4CList)];
	char m_pad0C[8];
	int m_14;
};
struct _Rva005E4AE2In
{
	int m_00;
	int m_04;
	Rva005E4AE2Holder *m_08;
};
#include "../../Include/Common/Rva005E4AE2Base.h"
class Rva005E4AE2 : public Rva005E4AE2Base, public Rva005E4AE2Listener
{
public:
	Rva005E4AE2(void *a1, _Rva005E4AE2In *a2, int a3);
	virtual ~Rva005E4AE2();
private:
	void *m_08;
	int m_0C;
	int m_10;
	Rva005E4AE2Holder *m_14;
	int m_18;
	_STL::map<int, void *> m_1C;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
};
Rva005E4AE2::Rva005E4AE2(void *a1, _Rva005E4AE2In *a2, int a3)
	: m_08(a1)
	, m_0C(a2->m_00)
	, m_10(a2->m_04)
	, m_14(a2->m_08)
	, m_18(a3)
	, m_1C()
{
	m_28 = 0;
	m_2C = 0;
	m_2D = (a2->m_08->m_14 != 0);
	m_14->m_list.append((Rva002BA8F1Listener *)static_cast<Rva005E4AE2Listener *>(this));
}
