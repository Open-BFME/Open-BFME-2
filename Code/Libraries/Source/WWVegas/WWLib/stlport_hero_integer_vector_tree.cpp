// cl: /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 copy family for CreateAHeroData member0x74.
// Retail insertion at0x21D203 uses signed key comparisons. Node0x21D159
// allocates32 bytes; value copy0x795C1 copies the int key then the established
// vector<unsigned int> copy0x2CFAB9. These calls anchor the complete family.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
typedef _STL::vector<unsigned int> HeroVector;
typedef _STL::pair<const int, HeroVector> HeroValue;
typedef _STL::_Rb_tree<int, HeroValue, _STL::_Select1st<HeroValue>, _STL::less<int>, _STL::allocator<HeroValue> > HeroTree;
template HeroTree::_Rb_tree(const HeroTree &);

// Retail21DD0E calls the held typed clear21DB91 and copy21DC9B.
template HeroTree &HeroTree::operator=(const HeroTree &);

// Whole-class instantiation of this tree. It reproduces _M_insert (retail 0x0021D17B)
// and the hinted insert_unique (retail 0x0021D6A9)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<int,_STL::pair<int const ,_STL::vector<unsigned int,_STL::allocator<unsigned int> > >,_STL::_Select1st<_STL::pair<int const ,_STL::vector<unsigned int,_STL::allocator<unsigned int> > > >,_STL::less<int>,_STL::allocator<_STL::pair<int const ,_STL::vector<unsigned int,_STL::allocator<unsigned int> > > > >;

// Native21C5BE..21C671 cdecl179B: four-at-a-time linear find over
// 16-byte records, followed by a three/two/one remainder. All seven calls
// target the independently recovered22B predicate21BBDC: it compares the
// record's +8 AsciiString through rowed StringBase compare69D6.
// Rva0040ABA5Find is the target sibling used as the control-flow guide;
// its payload types are not transferred. Only the measured stride is
// represented here; the other record fields and original type are unknown.
class AsciiString;
bool Rva0021BBDCEqual(const void *record, const AsciiString &key);
struct Rva0021C5BEItem
{
    unsigned int word00, word04, word08, word0C;
};

const Rva0021C5BEItem *Rva0021C5BEFind(const Rva0021C5BEItem *first, const Rva0021C5BEItem *last, const AsciiString *val, int tag)
{
	(void)tag;
	const Rva0021C5BEItem *f = first;
	const char *e = (const char *)last;
	int n = (int)((const char *)last - (const char *)first) >> 6;
	while (n > 0) {
		if (Rva0021BBDCEqual((const void *)f, *val))
			return f;
		++f;
		if (Rva0021BBDCEqual((const void *)f, *val))
			return f;
		++f;
		if (Rva0021BBDCEqual((const void *)f, *val))
			return f;
		++f;
		if (Rva0021BBDCEqual((const void *)f, *val))
			return f;
		++f;
		--n;
	}
	switch ((int)(e - (const char *)f) >> 4) {
	case 3:
		if (Rva0021BBDCEqual((const void *)f, *val))
			return f;
		++f;
	case 2:
		if (Rva0021BBDCEqual((const void *)f, *val) == false) {
			++f;
		} else {
			return f;
		}
	case 1:
		if (Rva0021BBDCEqual((const void *)f, *val))
			return f;
	}
	return last;
}
