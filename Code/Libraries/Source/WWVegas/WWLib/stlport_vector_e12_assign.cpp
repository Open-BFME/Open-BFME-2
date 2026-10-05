// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@UBfmeE12@@V?$allocator@UBfmeE12@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x004BF4CE 209B
// Evidence: calls rowed E12 allocate_and_copy 0x0029B297 plus __copy_ptrs 0x000B6569 plus __uninitialized_copy 0x000766F5 plus _free 0x00030830; caller ActiveBody ctor 0x004BF779.
struct BfmeE12 { float x, y, z; };
namespace _STL {
struct __false_type { __false_type() {} };
template <class Type> class allocator {};
template <class Type, class Allocator> class vector {
public:
	typedef Type *pointer;
	typedef const Type *const_pointer;
	typedef unsigned int size_type;
	vector &operator=(const vector &x);
	pointer begin() { return m_start; }
	const_pointer begin() const { return m_start; }
	pointer end() { return m_finish; }
	const_pointer end() const { return m_finish; }
	size_type size() const { return size_type(m_finish - m_start); }
	size_type capacity() const { return size_type(m_endOfStorage - m_start); }
protected:
	template <class ForwardIter> pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};
template <class InputIter, class OutputIter> OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class InputIter, class OutputIter> OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}
extern "C" void __cdecl free(void *);
inline _STL::vector<BfmeE12, _STL::allocator<BfmeE12> > &_STL::vector<BfmeE12, _STL::allocator<BfmeE12> >::operator=(const vector &x)
{
	if (&x != this) {
		size_type xsize = x.size();
		if (xsize > capacity()) {
			pointer tmp = _M_allocate_and_copy(xsize, x.begin(), x.end());
			if (m_start)
				free(m_start);
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		} else if (size() >= xsize) {
			_STL::__copy_ptrs(x.begin(), x.end(), m_start, _STL::__false_type());
		} else {
			_STL::__copy_ptrs(x.begin(), x.begin() + size(), m_start, _STL::__false_type());
			_STL::__uninitialized_copy(x.begin() + size(), x.end(), m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}
#pragma inline_depth(0)
// ?bfmeEmitstlport_vector_e12_assign@@YAXPAV?$vector@UBfmeE12@@V?$allocator@UBfmeE12@@@_STL@@@_STL@@ABV12@@Z present-unmatched
void bfmeEmitstlport_vector_e12_assign(_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *p, const _STL::vector<BfmeE12, _STL::allocator<BfmeE12> > &x)
{
	*p = x;
}
#pragma inline_depth()
