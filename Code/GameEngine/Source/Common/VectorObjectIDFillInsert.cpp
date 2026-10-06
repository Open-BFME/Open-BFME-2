// cl: /DNDEBUG /MD /EHsc
// stlport

// De-lift: STLport vector<ObjectID>::_M_fill_insert, retail 0x002CCBD0,
// 251 bytes.  ObjectID is an enum, so this instantiates separately from the
// shared four-byte-POD siblings (vector<int>, vector<Object *>, vector<void *>).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ObjectID { INVALID_ID = 0 };

template class _STL::vector<ObjectID>;

// ??$copy_backward@PAW4ObjectID@@PAW41@@_STL@@YAPAW4ObjectID@@PAW41@00@Z RVA 0x005E42D3 size 27
// Evidence: callee __copy_backward_ptrs ObjectID rowed at 0x00583709; callers __linear_insert-like at 0x0040AE5E and 0x005E4862; explicit instantiation exact mod reloc.
template ObjectID* _STL::copy_backward<ObjectID*, ObjectID*>(ObjectID*, ObjectID*, ObjectID*);
