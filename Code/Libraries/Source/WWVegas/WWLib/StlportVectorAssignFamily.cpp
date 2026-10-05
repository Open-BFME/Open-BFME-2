// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::operator= for two element views, the same
// three-path 180B body as the rowed vector<BfmeStringRecord000B94D2> assign
// at 0x000C0799 (stlport_vector_stringrecord_b94d2_assign.cpp, whose flags
// and minimal vector model these are). Retail passes the source vector's
// non-const storage pointers straight through, hence the T* helper
// instantiations. Only the elements' copy constructor and destructor are
// declared; no layout beyond the stride (sar 3 / sar 2) is claimed.
//
//   operator=   stride  callees named for the element by the ledger
//   0x001D9D75   8      _M_allocate_and_copy 0x001D9AAC, _M_clear 0x001D9D57,
//                       __copy_ptrs 0x001D9B87, _Destroy 0x001D9CCC,
//                       __uninitialized_copy 0x001D9A61 (BfmeStringTailRecord156)
//   0x002B719C   4      __copy_ptrs 0x002B4410, _Destroy 0x002B61C5 (Rva0040DC56Element,
//                       whose erase is 0x0040DC56); allocate_and_copy 0x0040CAD3,
//                       the folded _M_clear 0x002B61DD and uninitialized copy
//                       0x003F74CF are pinned from this body's REL32s
class BfmeStringTailRecord156
{
public:
	BfmeStringTailRecord156(const BfmeStringTailRecord156 &other);
	~BfmeStringTailRecord156();
private:
	char m_pad[8];
};
struct Rva0040DC56Element
{
	Rva0040DC56Element(const Rva0040DC56Element &other);
	~Rva0040DC56Element();
private:
	char m_pad[4];
};
namespace _STL
{
struct __false_type
{
	__false_type()
	{
	}
};
template <class Type>
class allocator
{
};
template <class Type, class Allocator>
class vector
{
public:
	typedef Type *pointer;
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

template _STL::vector<BfmeStringTailRecord156, _STL::allocator<BfmeStringTailRecord156> > &
_STL::vector<BfmeStringTailRecord156, _STL::allocator<BfmeStringTailRecord156> >::operator=(const _STL::vector<BfmeStringTailRecord156, _STL::allocator<BfmeStringTailRecord156> > &);

template _STL::vector<Rva0040DC56Element, _STL::allocator<Rva0040DC56Element> > &
_STL::vector<Rva0040DC56Element, _STL::allocator<Rva0040DC56Element> >::operator=(const _STL::vector<Rva0040DC56Element, _STL::allocator<Rva0040DC56Element> > &);
