// cl: /O1 /EHs /MD /G7 /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Native country population 56FEA8..5700A0 and subscript 56FE2C..56FEA8
// establish a Unicode key at node+10 and a four-byte locale at node+14.
// The int value is an ABI/semantic view; the original enum name is unknown.
// BFME1 34f59164 OnlineLoginPopulateCountryList.cpp supplies the map purpose.
// Existing retail-shaped hinted insertion is retained with Select1st of
// the established pair rather than an opaque eight-byte set record.
// The compiler emits 18 reachable bodies with exact bytes and call targets.
// _Destroy releases the pair's sole nontrivial member through its existing
// UnicodeString dtor owner. No alternate-name linker directives are needed.
#include <map>
#include "unicode_string.h"
// ?unicodeKeyLess present-unmatched
bool operator<(const UnicodeString &a,const UnicodeString &b) { return a.compare(b)<0; }
namespace _STL { template<> struct less<UnicodeString> {
 bool operator()(const UnicodeString &a,const UnicodeString &b)const {return a<b;}
}; }
typedef _STL::pair<const UnicodeString,int> CountryPair;
typedef _STL::map<UnicodeString,int> CountryMap;
typedef _STL::_Rb_tree<UnicodeString,CountryPair,_STL::_Select1st<CountryPair>,_STL::less<UnicodeString>,_STL::allocator<CountryPair> > CountryTree;
namespace _STL { template<> inline void _Destroy(CountryPair *p) {
    const_cast<UnicodeString &>(p->first).~UnicodeString();
} }
namespace _STL {
template<> pair<CountryTree::iterator,bool> CountryTree::insert_unique(const CountryPair& __v) {
 _Link_type __header = this->_M_header._M_data;
 _Link_type __y = __header;
 _Link_type __x = static_cast<_Link_type>(__header->_M_parent);
 bool __comp = true;
 while (__x != 0) {
  __y = __x;
  __comp = _M_key_compare(_Select1st<CountryPair>()(__v), _S_key(__x));
  __x = __comp ? _S_left(__x) : _S_right(__x);
 }
 iterator __j(__y);
 if (__comp && __j == iterator(static_cast<_Link_type>(__header->_M_left)))
  return _STL::pair<iterator,bool>(_M_insert(__y,__y,__v),true);
 if (__comp) --__j;
 if (_M_key_compare(_S_key(__j._M_node),_Select1st<CountryPair>()(__v)))
  return _STL::pair<iterator,bool>(_M_insert(__x,__y,__v),true);
 return _STL::pair<iterator,bool>(__j,false);
}

template<> CountryTree::iterator CountryTree::insert_unique(iterator __position,const CountryPair& __v)
{
  if (__position._M_node == this->_M_header._M_data->_M_left) { // begin()

    // if the container is empty, fall back on insert_unique.
    if (size() <= 0)
      return insert_unique(__v).first;

    if ( _M_key_compare(_Select1st<CountryPair>()(__v), _S_key(__position._M_node)))
      return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    else
      {
	bool __comp_pos_v = _M_key_compare( _S_key(__position._M_node), _Select1st<CountryPair>()(__v) );
	
	if (__comp_pos_v == false)  // compare > and compare < both false so compare equal
	  return __position;
	//Below __comp_pos_v == true

	// Standard-conformance - does the insertion point fall immediately AFTER
	// the hint?
	iterator __after = __position;
	++__after;

	// Check for only one member -- in that case, __position points to itself,
	// and attempting to increment will cause an infinite loop.
	if (__after._M_node == this->_M_header._M_data)
	  // Check guarantees exactly one member, so comparison was already
	  // performed and we know the result; skip repeating it in _M_insert
	  // by specifying a non-zero fourth argument.
	  return _M_insert(0, __position._M_node, __v, __position._M_node);
		
	
	// All other cases:
	
	// Optimization to catch insert-equivalent -- save comparison results,
	// and we get this for free.
	if(_M_key_compare( _Select1st<CountryPair>()(__v), _S_key(__after._M_node) )) {
	  if (_S_right(__position._M_node) == 0)
	    return _M_insert(0, __position._M_node, __v, __position._M_node);
	  else
	    return _M_insert(__after._M_node, __after._M_node, __v);
	} else {
	    return insert_unique(__v).first;
	}
      }

  } else if (__position._M_node == this->_M_header._M_data) { // end()
    _Link_type __rightmost = _M_rightmost();
    if (_M_key_compare(_S_key(__rightmost), _Select1st<CountryPair>()(__v)))
      // pass along to _M_insert that it can skip comparing
      // v, Key ; since compare Key, v was true, compare v, Key must be false.
      return _M_insert(0, __rightmost, __v, __position._M_node); // Last argument only needs to be non-null
    else
      return insert_unique(__v).first;
  } else {
    iterator __before = __position;
    --__before;
    
    bool __comp_v_pos = _M_key_compare(_Select1st<CountryPair>()(__v), _S_key(__position._M_node));

    if (__comp_v_pos
      && _M_key_compare( _S_key(__before._M_node), _Select1st<CountryPair>()(__v) )) {

      if (_S_right(__before._M_node) == 0)
        return _M_insert(0, __before._M_node, __v, __before._M_node); // Last argument only needs to be non-null
      else
        return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    } else
      {
	// Does the insertion point fall immediately AFTER the hint?
	iterator __after = __position;
	++__after;
	
	// Optimization to catch equivalent cases and avoid unnecessary comparisons
	bool __comp_pos_v = !__comp_v_pos;  // Stored this result earlier
	// If the earlier comparison was true, this comparison doesn't need to be
	// performed because it must be false.  However, if the earlier comparison
	// was false, we need to perform this one because in the equal case, both will
	// be false.
	if (!__comp_v_pos) __comp_pos_v = _M_key_compare(_S_key(__position._M_node), _Select1st<CountryPair>()(__v));
	
	if ( (!__comp_v_pos) // comp_v_pos true implies comp_v_pos false
	     && __comp_pos_v
	     && (__after._M_node == this->_M_header._M_data ||
	        _M_key_compare( _Select1st<CountryPair>()(__v), _S_key(__after._M_node) ))) {
	  
	  if (_S_right(__position._M_node) == 0)
	    return _M_insert(0, __position._M_node, __v, __position._M_node);
	  else
	    return _M_insert(__after._M_node, __after._M_node, __v);
	} else {
	  // Test for equivalent case
	  if (__comp_v_pos == __comp_pos_v)
	    return __position;
	  else
	    return insert_unique(__v).first;
	}
      }
  }
}
}
template class _STL::map<UnicodeString,int>;
template class _STL::_Rb_tree<UnicodeString,CountryPair,_STL::_Select1st<CountryPair>,_STL::less<UnicodeString>,_STL::allocator<CountryPair> >;
