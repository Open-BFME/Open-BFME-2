// STLport4.5.3 insert_unique, retaining the header loaded before the search.
// Target key ABI: two 32-bit words; TeamFactory callers establish pair<NameKeyType,NameKeyType>.
// TeamPrototype pointer value follows the pair key in the canonical TeamFactory map.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include "unicode_string.h"
#include <string>
#include <map>



class TeamPrototype;
namespace _STL { template<> bool operator< <int,int>(const pair<int,int>&,const pair<int,int>&); }
template<> _STL::_Rb_tree_iterator<_STL::pair<_STL::pair<int, int> const, TeamPrototype *>, _STL::_Nonconst_traits<_STL::pair<_STL::pair<int, int> const, TeamPrototype *> > > _STL::_Rb_tree<_STL::pair<int, int>, _STL::pair<_STL::pair<int, int> const, TeamPrototype *>, _STL::_Select1st<_STL::pair<_STL::pair<int, int> const, TeamPrototype *> >, _STL::less<_STL::pair<int, int> >, _STL::allocator<_STL::pair<_STL::pair<int, int> const, TeamPrototype *> > >::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, _STL::pair<_STL::pair<int, int> const, TeamPrototype *> const &, _STL::_Rb_tree_node_base *);
template<> _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<_STL::pair<int, int> const, TeamPrototype *>, _STL::_Nonconst_traits<_STL::pair<_STL::pair<int, int> const, TeamPrototype *> > >, bool> _STL::_Rb_tree<_STL::pair<int, int>, _STL::pair<_STL::pair<int, int> const, TeamPrototype *>, _STL::_Select1st<_STL::pair<_STL::pair<int, int> const, TeamPrototype *> >, _STL::less<_STL::pair<int, int> >, _STL::allocator<_STL::pair<_STL::pair<int, int> const, TeamPrototype *> > >::insert_unique(_STL::pair<_STL::pair<int, int> const, TeamPrototype *> const & __v) {
 _Link_type __header = this->_M_header._M_data;
 _Link_type __y = __header;
 _Link_type __x = static_cast<_Link_type>(__header->_M_parent);
 bool __comp = true;
 while (__x != 0) {
  __y = __x;
  __comp = _M_key_compare(__v.first, _S_key(__x));
  __x = __comp ? _S_left(__x) : _S_right(__x);
 }
 iterator __j(__y);
 if (__comp && __j == iterator(static_cast<_Link_type>(__header->_M_left)))
  return _STL::pair<iterator,bool>(_M_insert(__y,__y,__v),true);
 if (__comp) --__j;
 if (_M_key_compare(_S_key(__j._M_node),__v.first))
  return _STL::pair<iterator,bool>(_M_insert(__x,__y,__v),true);
 return _STL::pair<iterator,bool>(__j,false);
}
