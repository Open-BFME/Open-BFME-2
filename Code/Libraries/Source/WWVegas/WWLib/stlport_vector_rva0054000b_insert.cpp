// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ?insert@?$vector@VRva0054000B@@V?$allocator@VRva0054000B@@@_STL@@@_STL@@QAEPAVRva0054000B@@PAV3@ABV3@@Z @0x00540731 152B
// Vector single-insert striding 0x28 via rowed Construct 0x00540070 plus rowed copy 0x00540036 plus rowed overflow 0x00540412.
// Evidence: callees rowed except own copy_backward/assign emitted here; callers 0x00540A0C; sibling insert 0x00541D10 same 152B shape with /Os /G7.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class Rva0054000B
{
public:
	Rva0054000B();
	Rva0054000B(const Rva0054000B &other);
	Rva0054000B &operator=(const Rva0054000B &other);

private:
	char m_pad[40];
};

namespace _STL {
template<> void _Construct<Rva0054000B, Rva0054000B>(Rva0054000B *, const Rva0054000B &);
}

template Rva0054000B *_STL::vector<Rva0054000B>::insert(
	Rva0054000B *, const Rva0054000B &);
