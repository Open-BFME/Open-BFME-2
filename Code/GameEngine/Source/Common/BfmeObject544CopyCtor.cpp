// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0BfmeObject544@@QAE@ABU0@@Z @0x004CAD61 103B.
// Copy ctor: three member copy ctors then scalar tail copies at +0x218/+0x21C.
// Evidence: pin names the copy ctor; caller _Construct at 0x004CADD1 in StlportObject544Vector.cpp copies through it; callees rowed 0x00045455 0x004151A3 0x0041559E; layout mirrors default ctor at 0x004CAD17.
#include <map>

#include "../../Include/Common/WeaponTemplateSetHead.h"

class BfmeOwnedRecordArray56
{
public:
	BfmeOwnedRecordArray56(const BfmeOwnedRecordArray56 &that);
	~BfmeOwnedRecordArray56();
private:
	char m_pad[0x1C0];
};

#include "../../Include/Common/BfmeStringRecord002CF550.h"

typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550,
	_STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>,
	_STL::allocator<BfmeStringRecord002CF550> > BfmeStringRecordTree900;

extern template BfmeStringRecordTree900::_Rb_tree(const BfmeStringRecordTree900 &);

struct BfmeObject544
{
	BfmeObject544(const BfmeObject544 &that);
private:
	WeaponTemplateSetHead m_00;
	BfmeOwnedRecordArray56 m_4C;
	BfmeStringRecordTree900 m_20C;
	int m_218;
	unsigned char m_21C;
	char m_tail[3];
};

// bfme link decl-only begin
namespace _STL { template <> void _Destroy<BfmeStringRecord002CF550>(BfmeStringRecord002CF550 *); }
namespace _STL { template <> _Rb_tree<BfmeStringRecord002CF550,BfmeStringRecord002CF550,_STL::_Identity<BfmeStringRecord002CF550>,_STL::less<BfmeStringRecord002CF550>,_STL::allocator<BfmeStringRecord002CF550> >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<BfmeStringRecord002CF550,BfmeStringRecord002CF550,_STL::_Identity<BfmeStringRecord002CF550>,_STL::less<BfmeStringRecord002CF550>,_STL::allocator<BfmeStringRecord002CF550> >::_M_erase(_STL::_Rb_tree_node<BfmeStringRecord002CF550> *); }
// bfme link decl-only end
BfmeObject544::BfmeObject544(const BfmeObject544 &that)
	: m_00(that.m_00),
	  m_4C(that.m_4C),
	  m_20C(that.m_20C),
	  m_218(that.m_218),
	  m_21C(that.m_21C)
{
}
