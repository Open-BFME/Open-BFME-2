// STLport 4.5.3 _Deque_base<Rva00056DEBElement> out-of-line members. Retail
// folds every element spelling of the base destructor onto 0x54FAAC and every
// element spelling of _M_destroy_nodes onto 0x4218F7: both bodies are element
// independent and byte-identical to the rowed deque<void*> copies. The
// deque<Rva00056DEBElement> destructor row at 0x579DE calls this destructor
// spelling by name.
// stlport
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
#include <deque>

struct Rva00056DEBElement { char bytes[1]; bool operator<(const Rva00056DEBElement&)const; bool operator==(const Rva00056DEBElement&)const; };

namespace _STL {
template<> _Deque_base<Rva00056DEBElement, allocator<Rva00056DEBElement> >::~_Deque_base()
{
  if (_M_map._M_data) {
    _M_destroy_nodes(_M_start._M_node, this->_M_finish._M_node + 1);
    _M_map.deallocate(_M_map._M_data, _M_map_size._M_data);
  }
}
}

// deque<OpaqueRefElement4>'s base destructor (W5): the same folded body, defined here as the fold proof of its pin
// on 0x54FAAC. MilesAudioManager.cpp's ~deque<OpaqueRefElement4> 0x579DE and its unwind funclet call it by name.
#include "../../../../GameEngine/Include/Common/OpaqueRefElement4.h"

namespace _STL {
template<> _Deque_base<OpaqueRefElement4, allocator<OpaqueRefElement4> >::~_Deque_base()
{
  if (_M_map._M_data) {
    _M_destroy_nodes(_M_start._M_node, this->_M_finish._M_node + 1);
    _M_map.deallocate(_M_map._M_data, _M_map_size._M_data);
  }
}
}
