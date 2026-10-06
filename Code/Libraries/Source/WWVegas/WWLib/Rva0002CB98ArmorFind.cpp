// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva0002CB98@Rva0002CB98@@QBE_NABV?$BitFlags@$0L@@@@Z @0x0002CB98 28B
// Wrapper that tests existence in a map<BitFlags<11>, ArmorTemplateSet*> member at +0x14.
// Evidence: calls the rowed _Rb_tree::_M_find at 0x0002C751 (ThingTemplate.cpp row);
// caller 0x0002D2C1; sibling 0x0002CBB4 same +0x14 honest-address recipe; host class opaque.
#include <map>

class ArmorTemplateSet
{
public:
	unsigned char m_data[12];
};

template <int Bits>
class BitFlags
{
public:
	unsigned int m_bits;
};

template <class A, class B>
class SparseMatchFinder
{
public:
	struct MapHelper
	{
		bool operator()(const B &a, const B &b) const;
	};
};

typedef BitFlags<11> ArmorSetFlags11;
typedef SparseMatchFinder<ArmorTemplateSet, ArmorSetFlags11>::MapHelper ArmorMapHelper11;

class Rva0002CB98
{
	unsigned char m_pad[0x14];
public:
	_STL::map<const ArmorSetFlags11, const ArmorTemplateSet *, ArmorMapHelper11, _STL::allocator<_STL::pair<const ArmorSetFlags11, const ArmorTemplateSet *> > > m_map;
	bool rva0002CB98(const ArmorSetFlags11 &a) const;
};

bool Rva0002CB98::rva0002CB98(const ArmorSetFlags11 &a) const
{
	return !(m_map.find(a) == m_map.end());
}
