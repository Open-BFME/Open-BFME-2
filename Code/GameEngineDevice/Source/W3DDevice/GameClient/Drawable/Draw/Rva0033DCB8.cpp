// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0033DCB8@Rva0033DCB8@@QBEPBVWeaponTemplateSet@@ABV?$BitFlags@$0BB@@@@Z, retail 0x0033DCB8, 25 bytes.
// Simple wrapper: return m_map.findBestInfo(m_vec, flags); m_vec at +0x370, m_map at +0x37C.
// Evidence: callee rowed 0x0033D4EA SparseMatchFinder WeaponTemplateSet BitFlags 17; sibling 0x0033DCD1 same recipe; callers 0x001D90A1 0x004BE1AE.
#include <vector>

class WeaponTemplateSet
{
	int m_dummy;
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
	const A *findBestInfo(const _STL::vector<A> &v, const B &b) const;
};

typedef BitFlags<17> WeaponSetFlags;

struct Rva0033DCB8
{
	char m_pad[0x370];
	_STL::vector<WeaponTemplateSet> m_vec;
	SparseMatchFinder<WeaponTemplateSet, WeaponSetFlags> m_map;
	const WeaponTemplateSet *rva0033DCB8(const WeaponSetFlags &flags) const;
};

const WeaponTemplateSet *Rva0033DCB8::rva0033DCB8(const WeaponSetFlags &flags) const
{
	return m_map.findBestInfo(m_vec, flags);
}
