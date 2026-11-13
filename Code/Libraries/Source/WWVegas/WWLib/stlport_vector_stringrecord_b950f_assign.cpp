// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@UBfmeStringRecord000B950F@@V?$allocator@UBfmeStringRecord000B950F@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x000C084D 206B: vector BfmeStringRecord000B950F assign via allocate_and_copy 0xBC6FE plus clear 0xC05EC plus copy 0x2CF830 plus destroy 0x331FF1 plus uninitialized_copy 0xBBB5D. Evidence: retail calls rowed allocate_and_copy plus rowed clear plus rowed copy plus rowed destroy plus rowed uninitialized_copy; idiv 0x0c stride 12 throughout; same 3-path shape as StringRecord assigns 0x002D0726 and 0x002D0927; caller 0x000C6C54.
#include "ascii_string.h"
struct BfmeStringRecord000B950F
{
	unsigned int word0;
	AsciiString text;
	unsigned int word1;
	BfmeStringRecord000B950F();
	BfmeStringRecord000B950F(const BfmeStringRecord000B950F &other);
	~BfmeStringRecord000B950F();
};
#include "Rva002DFC30.h"
#include "Rva000B435F.h"
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
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};
template <>
class vector<Rva002DFC30, allocator<Rva002DFC30> >
{
	friend class vector<BfmeStringRecord000B950F, allocator<BfmeStringRecord000B950F> >;
protected:
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
			pointer tmp = _M_allocate_and_copy(xsize, x.begin(), x.end());
			reinterpret_cast<_STL::vector<Rva002DFC30, _STL::allocator<Rva002DFC30> > *>(this)->_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			Rva000B435F *new_finish = _STL::__copy_ptrs(const_cast<Rva000B435F *>(reinterpret_cast<const Rva000B435F *>(x.begin())), const_cast<Rva000B435F *>(reinterpret_cast<const Rva000B435F *>(x.end())), reinterpret_cast<Rva000B435F *>(m_start), _STL::__false_type());
			_STL::_Destroy(reinterpret_cast<Rva002DFC30 *>(new_finish), reinterpret_cast<Rva002DFC30 *>(m_finish));
		}
		else
		{
			_STL::__copy_ptrs(const_cast<Rva000B435F *>(reinterpret_cast<const Rva000B435F *>(x.begin())), const_cast<Rva000B435F *>(reinterpret_cast<const Rva000B435F *>(x.begin() + size())), reinterpret_cast<Rva000B435F *>(m_start), _STL::__false_type());
			_STL::__uninitialized_copy(x.begin() + size(), x.end(), m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// operator= is a header inline: another unit emits a select-any copy of it,
// so a strong definition here was a duplicate symbol in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
template _STL::vector<BfmeStringRecord000B950F, _STL::allocator<BfmeStringRecord000B950F> > &_STL::vector<BfmeStringRecord000B950F, _STL::allocator<BfmeStringRecord000B950F> >::operator=(const _STL::vector<BfmeStringRecord000B950F, _STL::allocator<BfmeStringRecord000B950F> > &);
