// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??4?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x002CD098 209B
// STLport 4.5.3 vector<Coord3D>::operator=: the trivially destructible
// three-path 209B body of the rowed vector<BfmeE12> assign at 0x004BF4CE
// (stlport_vector_e12_assign.cpp, whose flags and minimal vector model
// these are), except that retail passes the source vector's non-const
// storage pointers: __uninitialized_copy<Coord3D *> is rowed at 0x00346C2D and
// the allocate-and-copy at 0x000E016A is already rowed with Coord3D *
// parameters; the __copy_ptrs at 0x002CA86E and that allocate-and-copy are
// pinned under their STLport spellings from this body's REL32s. Caller
// 0x002CD700.
struct Coord3D { float x, y, z; };
namespace _STL {
struct __false_type { __false_type() {} };
template <class Type> class allocator {};
template <class Type, class Allocator> class vector {
public:
	typedef Type *pointer;
	typedef unsigned int size_type;
	vector &operator=(const vector &x);
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
template <class Type, class Allocator>
_STL::vector<Type, Allocator> &_STL::vector<Type, Allocator>::operator=(const vector &x)
{
	if (&x != this) {
		size_type xsize = x.size();
		if (xsize > capacity()) {
			pointer tmp = _M_allocate_and_copy(xsize, x.m_start, x.m_finish);
			if (m_start)
				free(m_start);
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		} else if (size() >= xsize) {
			_STL::__copy_ptrs(x.m_start, x.m_finish, m_start, _STL::__false_type());
		} else {
			_STL::__copy_ptrs(x.m_start, x.m_start + size(), m_start, _STL::__false_type());
			_STL::__uninitialized_copy(x.m_start + size(), x.m_finish, m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}
template _STL::vector<Coord3D, _STL::allocator<Coord3D> > &
_STL::vector<Coord3D, _STL::allocator<Coord3D> >::operator=(const _STL::vector<Coord3D, _STL::allocator<Coord3D> > &);
