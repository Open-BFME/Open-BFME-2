// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native1EC1B4..1EC311 RET10,349B. Target ECX is a12B carryover vector;
// three pointer parameters delimit position/source range; the fourth tag is unused.
// Ghidra callers1ECB78/1ECD19, strideAC and helpers1EBA30/1EB831/1EBACF/1EB9C8
// identify STLport4.5.3 vector forward-range insertion. The original record name
// and concrete campaign-vector template name remain unknown; address owner retained.
// Adapted from _vector.h at donor cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
// Modifications: existing physical copy-provider spellings, with explicit pointer
// casts preserving argument evaluation. The visible noinline backward-copy bodies
// preserve unused tag analysis; both54B loop1EB262 and29B wrapper1EB831 are exact.
// The second structural element view has verified172B stride here; the historical
// provider TU's9B view is not adopted. Assignment uses the actual84B record owner.
// This unit adds no pins, addresses, aliases or assembly. It does not establish
// a source-level application identity for either existing structural record name.
/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */


// Keep the already-inlined unsigned comparison local: this TU's standalone
// max<unsigned int> copy differs from the retail provider.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
 return a < b ? b : a;
}
}
#include <vector>
struct BfmeAssignRecord172
{
public:
	BfmeAssignRecord172(const BfmeAssignRecord172 &);
	~BfmeAssignRecord172();
	BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &);
	int a[43];
};
struct BfmePod172
{
	int a[43];
};
struct Rva001EB831Element { unsigned char bytes[172]; Rva001EB831Element&operator=(const Rva001EB831Element&); };
namespace _STL {
template<> void _Destroy<BfmeAssignRecord172*>(BfmeAssignRecord172*,BfmeAssignRecord172*);
template<> __declspec(noinline) inline Rva001EB831Element*__copy_backward<Rva001EB831Element*,Rva001EB831Element*,int>(Rva001EB831Element*first,Rva001EB831Element*last,Rva001EB831Element*result,const random_access_iterator_tag&,int*) {
 for(int n=last-first;n>0;--n) *(BfmeAssignRecord172*)--result=*(const BfmeAssignRecord172*)--last;
 return result;
}

template<> __declspec(nothrow) void _Construct<BfmePod172,BfmePod172>(BfmePod172*,const BfmePod172&);

template<> __declspec(noinline) inline Rva001EB831Element *__copy_backward_ptrs<Rva001EB831Element*,Rva001EB831Element*>(Rva001EB831Element*a,Rva001EB831Element*b,Rva001EB831Element*c,const __false_type&) { return __copy_backward(a,b,c,random_access_iterator_tag(),(int*)0); }
template<> BfmeAssignRecord172 *copy<BfmeAssignRecord172*,BfmeAssignRecord172*>(BfmeAssignRecord172*,BfmeAssignRecord172*,BfmeAssignRecord172*);
}
#define carryoverUninitializedCopy(a,b,c,t) ((BfmeAssignRecord172*)_STL::__uninitialized_copy((const BfmePod172*)(a),(const BfmePod172*)(b),(BfmePod172*)(c),t))
#define carryoverCopyBackward(a,b,c,t) ((BfmeAssignRecord172*)_STL::__copy_backward_ptrs((Rva001EB831Element*)(a),(Rva001EB831Element*)(b),(Rva001EB831Element*)(c),t))
class Rva001EC1B4:public _STL::vector<BfmeAssignRecord172> {
public:void rva001EC1B4(BfmeAssignRecord172*,BfmeAssignRecord172*,BfmeAssignRecord172*,char*);
};
void Rva001EC1B4::rva001EC1B4(BfmeAssignRecord172*__position,BfmeAssignRecord172*__first,BfmeAssignRecord172*__last,char*) {
    if (__first != __last) {
      size_type __n = _STL::distance(__first, __last);

      if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
        const size_type __elems_after = this->_M_finish - __position;
        pointer __old_finish = this->_M_finish;
        if (__elems_after > __n) {
          carryoverUninitializedCopy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _STL::__false_type());
          this->_M_finish += __n;
          carryoverCopyBackward(__position, __old_finish - __n, __old_finish, _STL::__false_type());
          _STL::copy(__first, __last, __position);
        }
        else {

          pointer __mid = __first;
          _STL::advance(__mid, __elems_after);

          carryoverUninitializedCopy(__mid, __last, this->_M_finish, _STL::__false_type());
          this->_M_finish += __n - __elems_after;
          carryoverUninitializedCopy(__position, __old_finish, this->_M_finish, _STL::__false_type());
          this->_M_finish += __elems_after;
          _STL::copy(__first, __mid, __position);
        } /* elems_after */
      }
      else {
        const size_type __old_size = size();
        const size_type __len = __old_size + (_STL::max)(__old_size, __n);
        pointer __new_start = this->_M_end_of_storage.allocate(__len);
        pointer __new_finish = __new_start;
        _STLP_TRY {
          __new_finish = carryoverUninitializedCopy(this->_M_start, __position, __new_start, _STL::__false_type());
          __new_finish = carryoverUninitializedCopy(__first, __last, __new_finish, _STL::__false_type());
          __new_finish = carryoverUninitializedCopy(__position, this->_M_finish, __new_finish, _STL::__false_type());
        }
        _STLP_UNWIND((_Destroy(__new_start,__new_finish), 
                      this->_M_end_of_storage.deallocate(__new_start,__len)));
        _M_clear();
        _M_set(__new_start, __new_finish, __new_start + __len);
      }
    }
  }