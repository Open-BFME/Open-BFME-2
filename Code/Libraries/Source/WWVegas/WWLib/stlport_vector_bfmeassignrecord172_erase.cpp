// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// ?erase@?$vector@UBfmeAssignRecord172@@V?$allocator@UBfmeAssignRecord172@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord172@@PAU3@0@Z
// @ 0x001EBDFA (51B): range erase over vector<BfmeAssignRecord172>. Shifts
// the tail down with __copy_ptrs (29B wrapper emitted here as duplicate of
// the rowed 0x001EBA13 via the rowed __copy at 0x001EB86E) then destroys
// the vacated tail with the rowed _Destroy at 0x001EB1B3, stores the new
// finish and returns first. Follows BfmeAssignRecord32 erase (0x00173FB6 51B)
// and VectorAsciiStringErase shape: prvalue __false_type tag forces
// the EBP frame with tag at [ebp+0xb].
struct BfmeAssignRecord172
{
public:
	BfmeAssignRecord172(const BfmeAssignRecord172 &);
	~BfmeAssignRecord172();
	BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &);
	int a[43]; // +0x00
};

// Use STLport's vector layout and helper declarations, as the destination TU
// does. The kept out-of-line copy and destroy providers are rowed separately.
#include <vector>

namespace _STL {
template <> BfmeAssignRecord172 *__copy<BfmeAssignRecord172 *, BfmeAssignRecord172 *, int>(
    BfmeAssignRecord172 *, BfmeAssignRecord172 *, BfmeAssignRecord172 *,
    const random_access_iterator_tag &, int *);
template <> void _Destroy<BfmeAssignRecord172 *>(BfmeAssignRecord172 *, BfmeAssignRecord172 *);
}

template _STL::vector<BfmeAssignRecord172, _STL::allocator<BfmeAssignRecord172> >::iterator
_STL::vector<BfmeAssignRecord172, _STL::allocator<BfmeAssignRecord172> >::erase(iterator, iterator);
