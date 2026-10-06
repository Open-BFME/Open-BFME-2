// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert@?$list@PAX...@QAE?AU?$_List_iterator@PAX...@2@U32@ABQAX@Z, retail 0x00525A87, 37 bytes.
// Evidence: frameless body that calls the rowed list<void*>::_M_create_node
// at 0x005258C0, links the node before the given position and returns the
// iterator through the hidden pointer (ret 0xc). The snapped-boundary queue
// measured it inside MilesAudioManagerInit3DSamplePools.cpp, whose /Oy- keeps
// a frame pointer retail does not have here, so it lives in its own TU. The
// masked body occurs 46 times in .text but once with this callee.
#include <list>

template _STL::list<void *, _STL::allocator<void *> >::iterator
	_STL::list<void *, _STL::allocator<void *> >::insert(iterator, void *const &);
