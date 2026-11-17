// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@UBfmeStringRecord002CF5B1@@V?$allocator@UBfmeStringRecord002CF5B1@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x002D0927 206B: vector BfmeStringRecord002CF5B1 assign via allocate_and_copy 0x002CFAFC plus PrereqUnitRec clear 0x002D044B plus copy 0x002CF594 plus destroy 0x002D02A8 plus uninitialized_copy 0x004F5097. Evidence: retail calls rowed allocate_and_copy plus rowed PrereqUnitRec clear plus rowed copy plus rowed destroy plus rowed StringRecord uninitialized_copy; idiv 0x0c stride 12 throughout; same 3-path shape as StringRecord 0x002D0726 and NoCase pair assign 0x00317EBB; caller ProductionPrerequisite assign 0x002D0C44.
#include "ascii_string.h"
#include "../../../../GameEngine/Include/Common/BfmeStringRecord002CF5B1.h"
class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned int m_first;
		unsigned int m_second;
		AsciiString m_name;
		~PrereqUnitRec();
	};
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
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};
template <>
class vector<ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> >
{
	friend class vector<BfmeStringRecord002CF5B1, allocator<BfmeStringRecord002CF5B1> >;
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
			reinterpret_cast<_STL::vector<ProductionPrerequisite::PrereqUnitRec, _STL::allocator<ProductionPrerequisite::PrereqUnitRec> > *>(this)->_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			ProductionPrerequisite::PrereqUnitRec *new_finish = _STL::__copy_ptrs(const_cast<ProductionPrerequisite::PrereqUnitRec *>(reinterpret_cast<const ProductionPrerequisite::PrereqUnitRec *>(x.begin())), const_cast<ProductionPrerequisite::PrereqUnitRec *>(reinterpret_cast<const ProductionPrerequisite::PrereqUnitRec *>(x.end())), reinterpret_cast<ProductionPrerequisite::PrereqUnitRec *>(m_start), _STL::__false_type());
			_STL::_Destroy(new_finish, reinterpret_cast<ProductionPrerequisite::PrereqUnitRec *>(m_finish));
		}
		else
		{
			_STL::__copy_ptrs(const_cast<ProductionPrerequisite::PrereqUnitRec *>(reinterpret_cast<const ProductionPrerequisite::PrereqUnitRec *>(x.begin())), const_cast<ProductionPrerequisite::PrereqUnitRec *>(reinterpret_cast<const ProductionPrerequisite::PrereqUnitRec *>(x.begin() + size())), reinterpret_cast<ProductionPrerequisite::PrereqUnitRec *>(m_start), _STL::__false_type());
			_STL::__uninitialized_copy(x.begin() + size(), x.end(), m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// vector<BfmeStringRecord002CF5B1>::operator= is a header inline in STLport:
// one other unit emits a select-any copy of it, so a strong definition here
// was a duplicate symbol in the linked build. This anchor only makes this unit
// emit its copy for the ledger row; it is not retail code.
template _STL::vector<BfmeStringRecord002CF5B1, _STL::allocator<BfmeStringRecord002CF5B1> > &_STL::vector<BfmeStringRecord002CF5B1, _STL::allocator<BfmeStringRecord002CF5B1> >::operator=(const _STL::vector<BfmeStringRecord002CF5B1, _STL::allocator<BfmeStringRecord002CF5B1> > &);
