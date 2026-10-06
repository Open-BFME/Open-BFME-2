// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
//
// ??0?$vector@PAUBfmeE12@@V?$allocator@PAUBfmeE12@@@_STL@@@_STL@@QAE@PAPAUBfmeE12@@0ABV?$allocator@PAUBfmeE12@@@1@@Z @0x00422B0E (62B):
// vector<BfmeE12*> range ctor: count from (last-first)>>2, fresh map-style
// buffer via the rowed allocator<pointer> row, __copy_trivial, triple store
// start/finish/end_of_storage. No EH frame: pointer copy cannot throw.
// Evidence: unlock lane, both callees rowed, callers 0x00423082 (22B
// forwarder) and 0x00423519 (63B vector-ctor context), unblocks both.
#include <vector>
struct BfmeE12 { float x, y, z; };
template _STL::vector<BfmeE12 *, _STL::allocator<BfmeE12 *> >::vector(BfmeE12 **, BfmeE12 **, const _STL::allocator<BfmeE12 *> &);
