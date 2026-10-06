// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva00448FF2Record {
 Rva00448FF2Record(); Rva00448FF2Record(const Rva00448FF2Record&);
 ~Rva00448FF2Record(); Rva00448FF2Record&operator=(const Rva00448FF2Record&);
 char bytes[8];
};
bool operator<(const Rva00448FF2Record&,const Rva00448FF2Record&);


namespace _STL {
typedef _Rb_tree<Rva00448FF2Record,Rva00448FF2Record,_Identity<Rva00448FF2Record>,less<Rva00448FF2Record>,allocator<Rva00448FF2Record> > R3WideTree;
template<> R3WideTree::iterator R3WideTree::insert_unique(iterator __position,const Rva00448FF2Record& __v)
{
  if (__position._M_node == this->_M_header._M_data->_M_left) { // begin()

    // if the container is empty, fall back on insert_unique.
    if (size() <= 0)
      return insert_unique(__v).first;

    if ( _M_key_compare(_Identity<Rva00448FF2Record>()(__v), _S_key(__position._M_node)))
      return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    else
      {
	bool __comp_pos_v = _M_key_compare( _S_key(__position._M_node), _Identity<Rva00448FF2Record>()(__v) );
	
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
	if(_M_key_compare( _Identity<Rva00448FF2Record>()(__v), _S_key(__after._M_node) )) {
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
    if (_M_key_compare(_S_key(__rightmost), _Identity<Rva00448FF2Record>()(__v)))
      // pass along to _M_insert that it can skip comparing
      // v, Key ; since compare Key, v was true, compare v, Key must be false.
      return _M_insert(0, __rightmost, __v, __position._M_node); // Last argument only needs to be non-null
    else
      return insert_unique(__v).first;
  } else {
    iterator __before = __position;
    --__before;
    
    bool __comp_v_pos = _M_key_compare(_Identity<Rva00448FF2Record>()(__v), _S_key(__position._M_node));

    if (__comp_v_pos
      && _M_key_compare( _S_key(__before._M_node), _Identity<Rva00448FF2Record>()(__v) )) {

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
	if (!__comp_v_pos) __comp_pos_v = _M_key_compare(_S_key(__position._M_node), _Identity<Rva00448FF2Record>()(__v));
	
	if ( (!__comp_v_pos) // comp_v_pos true implies comp_v_pos false
	     && __comp_pos_v
	     && (__after._M_node == this->_M_header._M_data ||
	        _M_key_compare( _Identity<Rva00448FF2Record>()(__v), _S_key(__after._M_node) ))) {
	  
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
template class _STL::set<Rva00448FF2Record>;

// This caller's native REL32 already names the kept provider at 0x00448D3C.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??M@YA_NABURva00448FF2Record@@0@Z=??M@YA_NABUBfmeStringRecord00448113@@0@Z")
