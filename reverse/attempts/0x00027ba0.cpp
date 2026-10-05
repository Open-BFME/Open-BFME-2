// ??4?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEAAV01@ABV01@@Z
// partial score=0.3 date=2026-10-05
// cl: /Od /Ob1 /MD /D_STLP_USE_STATIC_LIB
// vector<void*> copy assignment at 0x00027BA0 (407B): self-check, size vs
// capacity via sar 2, allocate_and_copy plus clear plus 3x __copy_trivial,
// same 3-path shape as scalar8 assign but trivial (no Destroy).
namespace _STL {
template <class T> class allocator {};
template <class T, class A> class vector {
public:
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef unsigned int size_type;
	vector &operator=(const vector &x);
	pointer begin() { return m_start; }
	const_pointer begin() const { return m_start; }
	pointer end() { return m_finish; }
	const_pointer end() const { return m_finish; }
	size_type size() const { return size_type(m_finish - m_start); }
	size_type capacity() const { return size_type(m_endOfStorage - m_start); }
protected:
	pointer _M_allocate_and_copy(size_type n, const_pointer first, const_pointer last);
	void _M_clear();
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};
void* __copy_trivial(const void* first, const void* last, void* result);
}
inline _STL::vector<void*, _STL::allocator<void*> > &_STL::vector<void*, _STL::allocator<void*> >::operator=(const vector &x)
{
	if (&x != this) {
		size_type xsize = x.size();
		if (xsize > capacity()) {
			pointer tmp = _M_allocate_and_copy(xsize, x.begin(), x.end());
			_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		} else if (size() >= xsize) {
			__copy_trivial(x.begin(), x.end(), m_start);
		} else {
			__copy_trivial(x.begin(), x.begin() + size(), m_start);
			__copy_trivial(x.begin() + size(), x.end(), m_finish);
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// This anchor only makes this unit emit its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitstlport_vector_voidptr_assign@@YAXPAV?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@ABV12@@Z present-unmatched
void bfmeEmitstlport_vector_voidptr_assign(_STL::vector<void*, _STL::allocator<void*> > *p, const _STL::vector<void*, _STL::allocator<void*> > &x)
{
  p->operator=(x);
}
#pragma inline_depth()
