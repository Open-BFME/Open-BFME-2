// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /I. /Ireference/shims/bfme2_bannerui /Ireference/shims/bfmealloc
// stlport
// ?erase@?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAEPAUBfmePod28@@PAU3@@Z retail 0x00216267 47 bytes
// Evidence: __copy_ptrs pin plus abuts next pair-ctor row 0x00216296 plus callers 0x00216664 plus 0x002167E9 plus single-erase branch for last element
#include <vector>
struct BfmePod28
{
	unsigned int slot;			// +0x00
	int bannerID;				// +0x04
	const void *typeEntry;		// +0x08, the type table's key/info pair
	int state;					// +0x0C
	int progress;				// +0x10
	int timer;					// +0x14
	bool pendingDelete;			// +0x18
	// The default less<> of __lower_bound 0x005413B0: signed, on the first word.
	__forceinline bool operator<(const BfmePod28 &o) const { return (int)slot < (int)o.slot; }
};

// Retail reaches the 29-byte forwarder 0x002161A5, whose tag travels by const reference.
namespace _STL {
template <> BfmePod28 *__copy_ptrs<BfmePod28 *, BfmePod28 *>(BfmePod28 *first, BfmePod28 *last, BfmePod28 *result, const __false_type &tag);
}
template BfmePod28 *_STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::erase(BfmePod28 *pos);
