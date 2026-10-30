// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Retail evidence: 0x000CA2F3 is the 73-byte vector<Coord3D> two-argument
// resize body. Its identity is supported by the rowed one-argument forwarder
// at 0x000CA33C and the direct DockUpdate call. The body calls rowed 12-byte
// range erase 0x002A133B and the rowed fill insertion at 0x000CA1EE decoded
// from its REL32; both are called by their row names (the Coord3D erase name
// rows the distinct body at 0x00081A24). Coord3D uses the existing three-float
// codegen view; the body proves stride and calls, not the target's complete
// source layout.
#include "../../../Include/Lib/Coord3D.h"
#include <vector>
struct Gen_p12pod;
// Retail's resize takes Coord3D by value, unlike the vendored generic
// vector declaration. Keep this evidenced three-pointer specialization shared
// with the fill-insertion view. The inline helpers retain the vendored bodies.
namespace _STL {
template <> class vector<Coord3D, allocator<Coord3D> > {
public:
    typedef unsigned int size_type;
    typedef Coord3D *iterator;
    typedef Coord3D *pointer;
    size_type size() const { return size_type(this->_M_finish - this->_M_start); }
    void resize(size_type n, Coord3D value);
    void resize(size_type n);
protected:
    typedef __false_type _IsPODType;
    typedef __false_type _TrivialAss;
  // handles insertions on overflow
  void _M_insert_overflow(pointer __position, const Coord3D& __x, const __false_type&, 
			  size_type __fill_len, bool __atend = false) {
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    _STLP_TRY {
      __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
      // handle insertion
      if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
      } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
      if (!__atend)
        // copy remainder
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    }
    _STLP_UNWIND((_Destroy(__new_start,__new_finish), 
                  this->_M_end_of_storage.deallocate(__new_start,__len)));
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
  }

  void _M_clear() {
    //    if (this->_M_start) {
    _Destroy(this->_M_start, this->_M_finish);
    this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
    //    }
  }

  void _M_set(pointer __s, pointer __f, pointer __e) {
    this->_M_start = __s;
    this->_M_finish = __f;
    this->_M_end_of_storage._M_data = __e;
  }


    Coord3D *_M_start;
    Coord3D *_M_finish;
    _STLP_alloc_proxy<Coord3D*, Coord3D, allocator<Coord3D> > _M_end_of_storage;
};
}

class Rva000CA1EEVector : public _STL::vector<Coord3D> {
public:
	void fillInsert(Coord3D *position, unsigned int count, const Coord3D &value);
	void insertFill(Coord3D *position, unsigned int count, const Coord3D &value);
};
namespace _STL {
template <> vector<Gen_p12pod>::iterator
vector<Gen_p12pod>::erase(iterator first, iterator last);

void vector<Coord3D>::resize(size_type n, Coord3D value) {
	Coord3D *start = _M_start;
	Coord3D *finish = _M_finish;
	const size_type size = (size_type)(finish - start);
	if (n < size) {
		((vector<Gen_p12pod> *)this)->erase((Gen_p12pod *)(start + n), (Gen_p12pod *)finish);
	} else {
		((Rva000CA1EEVector *)this)->fillInsert(_M_finish, n - (size_type)(_M_finish - start), value);
	}
}
}
