// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::operator= three-path body for a 128-byte
// address-derived element view. The 186-byte target at 0x0032C0E3 uses the
// allocate-copy helper at 0x0032A3E1 the clear helper at 0x0032BF1B the
// copy worker at 0x0032A40E the destroy loop at 0x0032B580 and the uninitialized
// copy worker at 0x0032A37A. Those callees are independently rowed; their
// different type spellings leave the element's C++ identity unresolved.

namespace _STL {
struct __false_type
{
	__false_type() {}
};

template <class T>
class allocator {};

template <class T, class A>
class vector
{
public:
	typedef T *pointer;
	typedef unsigned int size_type;
	vector &operator=(const vector &x);
	size_type size() const { return size_type(m_finish - m_start); }
	size_type capacity() const { return size_type(m_endOfStorage - m_start); }

protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
	void _M_clear();

private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);

template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);

template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
}

struct Rva0032C0E3Element { unsigned char bytes[128]; };

template <class Type, class Allocator>
_STL::vector<Type, Allocator> &_STL::vector<Type, Allocator>::operator=(const vector &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		if (xsize > capacity())
		{
			pointer tmp = _M_allocate_and_copy(xsize, x.m_start, x.m_finish);
			_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			pointer new_finish = _STL::__copy_ptrs(x.m_start, x.m_finish, m_start, _STL::__false_type());
			_STL::_Destroy(new_finish, m_finish);
		}
		else
		{
			_STL::__copy_ptrs(x.m_start, x.m_start + size(), m_start, _STL::__false_type());
			_STL::__uninitialized_copy(x.m_start + size(), x.m_finish, m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

template _STL::vector<Rva0032C0E3Element, _STL::allocator<Rva0032C0E3Element> > &
_STL::vector<Rva0032C0E3Element, _STL::allocator<Rva0032C0E3Element> >::operator=(
	const _STL::vector<Rva0032C0E3Element, _STL::allocator<Rva0032C0E3Element> > &);
