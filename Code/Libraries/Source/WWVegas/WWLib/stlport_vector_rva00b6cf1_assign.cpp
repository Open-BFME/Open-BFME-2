// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@URva00B6CF1@@V?$allocator@URva00B6CF1@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x000C091B 180B: vector Rva00B6CF1 assign via B94D2 allocate_and_copy 0xBC72B plus B94D2 clear 0xC05CE plus Rva copy_ptrs 0xB67BC ABU pin plus Rva destroy 0xBDCD6 plus B94D2 uninitialized_copy 0xBBAA1. Evidence: same 180B sar 3 stride 8 shape as B94D2 assign 0x000C0799; same rowed helpers; caller 0x000C19A7.
#include "ascii_string.h"
#include "../../../../GameEngine/Include/Common/BfmeStringRecord000B94D2.h"
struct Rva00B6CF1
{
	AsciiString m_s0;
	AsciiString m_s1;
	Rva00B6CF1();
	Rva00B6CF1(const Rva00B6CF1 &other);
	~Rva00B6CF1();
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
  template <class ForwardIter>
  pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
  void _M_clear();
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};
template <>
class vector<BfmeStringRecord000B94D2, allocator<BfmeStringRecord000B94D2> >
{
	friend class vector<Rva00B6CF1, allocator<Rva00B6CF1> >;
protected:
	typedef BfmeStringRecord000B94D2 *pointer;
	typedef unsigned int size_type;
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
	void _M_clear();
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
			BfmeStringRecord000B94D2 *tmp = reinterpret_cast<_STL::vector<BfmeStringRecord000B94D2, _STL::allocator<BfmeStringRecord000B94D2> > *>(this)->_M_allocate_and_copy(xsize, reinterpret_cast<const BfmeStringRecord000B94D2 *>(x.begin()), reinterpret_cast<const BfmeStringRecord000B94D2 *>(x.end()));
			reinterpret_cast<_STL::vector<BfmeStringRecord000B94D2, _STL::allocator<BfmeStringRecord000B94D2> > *>(this)->_M_clear();
			m_start = reinterpret_cast<pointer>(tmp);
			m_endOfStorage = reinterpret_cast<pointer>(tmp) + xsize;
		}
		else if (size() >= xsize)
		{
			Rva00B6CF1 *new_finish = _STL::__copy_ptrs(const_cast<Rva00B6CF1 *>(reinterpret_cast<const Rva00B6CF1 *>(x.begin())), const_cast<Rva00B6CF1 *>(reinterpret_cast<const Rva00B6CF1 *>(x.end())), reinterpret_cast<Rva00B6CF1 *>(m_start), _STL::__false_type());
			_STL::_Destroy(new_finish, reinterpret_cast<Rva00B6CF1 *>(m_finish));
		}
		else
		{
			_STL::__copy_ptrs(const_cast<Rva00B6CF1 *>(reinterpret_cast<const Rva00B6CF1 *>(x.begin())), const_cast<Rva00B6CF1 *>(reinterpret_cast<const Rva00B6CF1 *>(x.begin() + size())), reinterpret_cast<Rva00B6CF1 *>(m_start), _STL::__false_type());
			_STL::__uninitialized_copy(reinterpret_cast<const BfmeStringRecord000B94D2 *>(x.begin() + size()), reinterpret_cast<const BfmeStringRecord000B94D2 *>(x.end()), reinterpret_cast<BfmeStringRecord000B94D2 *>(m_finish), _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// operator= is a header inline: another unit emits a select-any copy of it,
// so a strong definition here was a duplicate symbol in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
template _STL::vector<Rva00B6CF1, _STL::allocator<Rva00B6CF1> > &_STL::vector<Rva00B6CF1, _STL::allocator<Rva00B6CF1> >::operator=(const _STL::vector<Rva00B6CF1, _STL::allocator<Rva00B6CF1> > &);
