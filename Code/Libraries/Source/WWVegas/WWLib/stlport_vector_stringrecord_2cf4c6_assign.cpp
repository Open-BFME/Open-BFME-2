// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@UBfmeStringRecord002CF4C6@@V?$allocator@UBfmeStringRecord002CF4C6@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x002D0726 206B: vector BfmeStringRecord002CF4C6 assign via allocate_and_copy 0x002CFC4E plus clear pin 0x002D02C1 plus copy row 0x002CF2B8 plus destroy dup 0x002D028F plus uninitialized_copy 0x0033BF10. Evidence: retail calls rowed allocate_and_copy plus pinned clear plus rowed Nugget copy plus dup destroy plus rowed StringRecord uninitialized_copy; idiv 0x14 stride 20 throughout; same 3-path shape as NoCase pair assign 0x00317EBB.
#include "ascii_string.h"
struct BfmeStringRecord002CF4C6
{
	AsciiString text0;
	AsciiString text1;
	unsigned int word0;
	unsigned int word1;
	unsigned char flag0;
	unsigned char flag1;
	char m_pad[2];
	BfmeStringRecord002CF4C6();
	BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &other);
	~BfmeStringRecord002CF4C6();
};
#include "../../../../GameEngine/Include/Common/ModuleInfoClass.h"
void __cdecl dup_002d028f(void);
typedef void (__cdecl *NuggetDestroyFn)(ModuleInfo::Nugget *, ModuleInfo::Nugget *);
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
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
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
			_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			ModuleInfo::Nugget *new_finish = _STL::__copy_ptrs(const_cast<ModuleInfo::Nugget *>(reinterpret_cast<const ModuleInfo::Nugget *>(x.begin())), const_cast<ModuleInfo::Nugget *>(reinterpret_cast<const ModuleInfo::Nugget *>(x.end())), reinterpret_cast<ModuleInfo::Nugget *>(m_start), _STL::__false_type());
			((NuggetDestroyFn)&dup_002d028f)(new_finish, reinterpret_cast<ModuleInfo::Nugget *>(m_finish));
		}
		else
		{
			_STL::__copy_ptrs(const_cast<ModuleInfo::Nugget *>(reinterpret_cast<const ModuleInfo::Nugget *>(x.begin())), const_cast<ModuleInfo::Nugget *>(reinterpret_cast<const ModuleInfo::Nugget *>(x.begin() + size())), reinterpret_cast<ModuleInfo::Nugget *>(m_start), _STL::__false_type());
			_STL::__uninitialized_copy(x.begin() + size(), x.end(), m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// operator= is a header inline in STLport: other units emit select-any copies,
// so a strong definition here was a duplicate in the linked build. This anchor
// keeps this unit emitting its copy for the ledger row; it is not retail code.
template _STL::vector<BfmeStringRecord002CF4C6, _STL::allocator<BfmeStringRecord002CF4C6> > &_STL::vector<BfmeStringRecord002CF4C6, _STL::allocator<BfmeStringRecord002CF4C6> >::operator=(const _STL::vector<BfmeStringRecord002CF4C6, _STL::allocator<BfmeStringRecord002CF4C6> > &);
