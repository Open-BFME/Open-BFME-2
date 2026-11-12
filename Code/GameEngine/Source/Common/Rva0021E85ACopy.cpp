// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
// ??0Rva0021E85A@@QAE@ABV0@@Z @0x0021E85A 250B: copy ctor with five StringBase plus ints plus hero map plus two Science vectors plus int-int map plus long-LadderPref map plus FixedStorage plus 108B tail; caller 0x0021EF82
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <vector>
#include <map>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_Rb_tree(_Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > > const &); }
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_copy(_Rb_tree_node<pair<int const, int> > *, _Rb_tree_node<pair<int const, int> > *); }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_copy(_Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > *, _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > *); }
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_create_node(pair<int const, vector<unsigned int, allocator<unsigned int> > > const &); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::clear(); }
// bfme link decl-only end

enum ScienceType
{
	SCIENCE_INVALID = 0
};

// Retail's member at +0x54 is a set of this record: 0x0021DBBA calls _M_copy 0x0021D7CF, whose nodes copy through 0x0021AAE1,
// and the dtor at 0x0021E50F tears it down through 0x0021D61F.
#include <set>
#include "../../../Libraries/Source/WWVegas/WWLib/BfmeStringRecord00219B0B.h"
struct BfmeStringRecord0021A940
{
	unsigned int word0;
	BfmeStringRecord00219B0B rec;
	BfmeStringRecord0021A940(const BfmeStringRecord0021A940 &source);
	~BfmeStringRecord0021A940();
};
typedef _STL::_Rb_tree<BfmeStringRecord0021A940, BfmeStringRecord0021A940, _STL::_Identity<BfmeStringRecord0021A940>, _STL::less<BfmeStringRecord0021A940>, _STL::allocator<BfmeStringRecord0021A940> > Rva0021E85ARecordTree;
namespace _STL {
template <> Rva0021E85ARecordTree::_Rb_tree(const Rva0021E85ARecordTree &);
template <> Rva0021E85ARecordTree::~_Rb_tree();
}

#include "../../Include/Common/BfmeFixedStorage002CF0F0.h"

struct Tail108
{
	int w[27];
};

class Rva0021E85A
{
public:
	Rva0021E85A(const Rva0021E85A &other);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	AsciiString m_20;
	_STL::map<int, _STL::vector<unsigned int> > m_24;
	_STL::vector<ScienceType> m_30;
	_STL::vector<ScienceType> m_3c;
	_STL::map<int, int> m_48;
	_STL::set<BfmeStringRecord0021A940> m_54;
	unsigned char m_60;
	char m_pad61[3];
	int m_64;
	BfmeFixedStorage002CF0F0 m_68;
	Tail108 m_6c;
};

Rva0021E85A::Rva0021E85A(const Rva0021E85A &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_1c(other.m_1c)
	, m_20(other.m_20)
	, m_24(other.m_24)
	, m_30(other.m_30)
	, m_3c(other.m_3c)
	, m_48(other.m_48)
	, m_54(other.m_54)
	, m_60(other.m_60)
	, m_64(other.m_64)
	, m_68(other.m_68)
	, m_6c(other.m_6c)
{
}

template _STL::set<BfmeStringRecord0021A940>::set(const _STL::set<BfmeStringRecord0021A940> &);
