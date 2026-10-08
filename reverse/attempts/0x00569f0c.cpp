// ??$_M_assign_aux@PBUBfmeStringRecord00568CE0@@@?$vector@UBfmeStringRecord00568CE0@@V?$allocator@UBfmeStringRecord00568CE0@@@_STL@@@_STL@@IAEXPBUBfmeStringRecord00568CE0@@0ABUforward_iterator_tag@1@@Z
// partial score=0.85 date=2026-10-08
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Assign-from-forward-range body of vector<BfmeStringRecord00568CE0> at RVA 0x00569F0C (167B,
// ret 12). STLport 4.5.3 _M_assign_aux shape: reallocate when the range exceeds capacity; copy
// and destroy the tail when the range fits within size; otherwise copy the head and
// uninitialized-copy the rest. Callees are the rowed allocate-copy, clear, copy, destroy and
// uninitialized-copy bodies in stlport_vector_stringrecord_568ce0_allocate_copy.cpp and the
// rowed copy at 0x00569450. Record and vector layout are the 20-byte view from that sibling.

int rva00569450(void *, void *, void *);

namespace _STL
{
struct __false_type {};
struct forward_iterator_tag {};
template <class T> class allocator {};

template <class T, class A> class vector
{
protected:
	template <class It> T *_M_allocate_and_copy(unsigned int n, It first, It last);
	void _M_clear();
	template <class It>
	void _M_assign_aux(It first, It last, const forward_iterator_tag &)
	{
		unsigned int len = (unsigned int)(last - first);
		if (len > (unsigned int)(_M_end_of_storage - _M_start)) {
			T *tmp = _M_allocate_and_copy(len, first, last);
			_M_clear();
			_M_start = tmp;
			_M_end_of_storage = tmp + len;
			_M_finish = _M_end_of_storage;
		} else if ((unsigned int)(_M_finish - _M_start) >= len) {
			T *i = (T *)rva00569450((void *)first, (void *)last, (void *)_M_start);
			_STL::_Destroy(i, _M_finish);
			_M_finish = i;
		} else {
			It mid = first + (_M_finish - _M_start);
			rva00569450((void *)first, (void *)mid, (void *)_M_start);
			_M_finish = _STL::__uninitialized_copy(mid, last, _M_finish, _STL::__false_type());
		}
	}
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};

template <class I, class O> O __uninitialized_copy(I first, I last, O result, const __false_type &);
template <class I> void _Destroy(I first, I last);
}




class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord00568CE0 {
    AsciiString text0, text1;
    unsigned int word0, word1;
    unsigned char flag;
    BfmeStringRecord00568CE0();
    BfmeStringRecord00568CE0(const BfmeStringRecord00568CE0 &o);
};



template void _STL::vector<BfmeStringRecord00568CE0, _STL::allocator<BfmeStringRecord00568CE0> >::_M_assign_aux<const BfmeStringRecord00568CE0 *>(const BfmeStringRecord00568CE0 *, const BfmeStringRecord00568CE0 *, const _STL::forward_iterator_tag &);
