// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4Rva001DE727@@QAEAAV0@ABV0@@Z, retail 0x001DE727 85B chain.
// Evidence: 5 dwords + Rb_tree set at +0x14 via rowed assign 0x001DDC52 +
// 4-byte vector at +0x20 via rowed assign 0x0021C21B + 3 bytes at +0x2C.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
#include <vector>
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@UBfmeRecord001DD3BC@@U1@U?$_Identity@UBfmeRecord001DD3BC@@@_STL@@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeRecord001DD3BC;
namespace _STL { template <> void _Rb_tree<BfmeRecord001DD3BC,BfmeRecord001DD3BC,_Identity<BfmeRecord001DD3BC>,less<BfmeRecord001DD3BC>,allocator<BfmeRecord001DD3BC> >::_M_erase(_Rb_tree_node<BfmeRecord001DD3BC> *); }
// The 4-byte vector's assignment is the rowed body at 0x0021C21B
// (StlSweepW5Rva0021C21B.cpp); call it by that row's name.
#include "Rva0021C21BElement.h"
namespace _STL { template <> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &); }

struct BfmeRecord001DD3BC
{
	unsigned char m_data[8];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<BfmeRecord001DD3BC>(BfmeRecord001DD3BC *p) { typedef BfmeRecord001DD3BC BfmeDestroyT; p->~BfmeDestroyT(); } }

bool operator<(const BfmeRecord001DD3BC &a, const BfmeRecord001DD3BC &b);

typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > BfmeRecord001DD3BCSetTree;

class Rva001DE727
{
public:
	Rva001DE727 &operator=(const Rva001DE727 &that);

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	BfmeRecord001DD3BCSetTree m_set14; // +0x14
	_STL::vector<Rva0021C21BElement> m_vec20; // +0x20
	unsigned char m_2C;
	unsigned char m_2D;
	unsigned char m_2E;
};

Rva001DE727 &Rva001DE727::operator=(const Rva001DE727 &that)
{
	m_00 = that.m_00;
	m_04 = that.m_04;
	m_08 = that.m_08;
	m_0C = that.m_0C;
	m_10 = that.m_10;
	m_set14 = that.m_set14;
	m_vec20 = that.m_vec20;
	m_2C = that.m_2C;
	m_2D = that.m_2D;
	m_2E = that.m_2E;
	return *this;
}
