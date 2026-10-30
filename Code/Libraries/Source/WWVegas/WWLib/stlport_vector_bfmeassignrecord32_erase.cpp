// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 range erase for the 32-byte render assignment record.
#include <vector>

struct BfmeAssignRecord32 {
    BfmeAssignRecord32();
    BfmeAssignRecord32(const BfmeAssignRecord32 &);
    ~BfmeAssignRecord32();
    BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &);
    char bytes[32];
};

// These helpers already have matched providers; keep their calls out of line.
namespace _STL {
template <> BfmeAssignRecord32 *__copy(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, const random_access_iterator_tag &, int *);
template <> void _Destroy(BfmeAssignRecord32 *, BfmeAssignRecord32 *);
}

// Emit the header's inline COMDAT for the ledger owner at 0x00173FB6.
template _STL::vector<BfmeAssignRecord32, _STL::allocator<BfmeAssignRecord32> >::iterator
_STL::vector<BfmeAssignRecord32, _STL::allocator<BfmeAssignRecord32> >::erase(BfmeAssignRecord32 *, BfmeAssignRecord32 *);
