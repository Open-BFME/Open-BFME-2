// cl: /DNDEBUG /MD /EHsc
// stlport

// ??$copy_backward@PAU?$pair@W4ObjectID@@I@_STL@@PAU12@@_STL@@YAPAU?$pair@W4ObjectID@@I@0@PAU10@00@Z RVA 0x004C72FE size 27
// Evidence: pinned name; callee __copy_backward_ptrs 8-byte POD folded at 0x0030B378; caller __linear_insert pair at 0x005672AA; explicit instantiation exact mod reloc.
// ??$__copy_backward_ptrs@PAU?$pair@W4ObjectID@@I@_STL@@PAU12@@_STL@@YAPAU?$pair@W4ObjectID@@I@0@PAU10@00ABU__false_type@0@@Z RVA 0x0030B378 size 29 ICF of BfmeE8 row
// ??$__copy_backward@PAU?$pair@W4ObjectID@@I@_STL@@PAU12@H@_STL@@YAPAU?$pair@W4ObjectID@@I@0@PAU10@00ABUrandom_access_iterator_tag@0@PAH@Z RVA 0x005B0505 size 50 ICF of BfmeE8 row
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ObjectID { INVALID_ID = 0 };

template _STL::pair<ObjectID, unsigned int>* _STL::copy_backward<_STL::pair<ObjectID, unsigned int>*, _STL::pair<ObjectID, unsigned int>*>(_STL::pair<ObjectID, unsigned int>*, _STL::pair<ObjectID, unsigned int>*, _STL::pair<ObjectID, unsigned int>*);
