// cl: /Ireference/shims/bfme2_ascii /O1
// ??4?$vector@UBfmeAsciiScalarValue8@@V?$allocator@UBfmeAsciiScalarValue8@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x0031DC3C 180B: vector BfmeAsciiScalarValue8 assign via allocate_and_copy 0x31BD77 plus Rva002390CB clear 0x31C81A plus copy 0x31BDA4 plus Rva Destroy 0x31BDEE plus Rva uninit_copy 0x3399AD; sar 3 stride 8; same 3-path shape as NoCase assign 0x317EBB.
#include "ascii_string.h"
struct BfmeAsciiScalarValue8
{
public:
	BfmeAsciiScalarValue8();
	BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8 &);
	BfmeAsciiScalarValue8 &operator=(const BfmeAsciiScalarValue8 &);
	AsciiString text; // +0x00
	unsigned int value; // +0x04
};
class Rva002390CB
{
public:
	~Rva002390CB();
	char m_pad[8];
};
namespace _STL {
template <class ForwardIter> void _Destroy(ForwardIter first, ForwardIter last);
}
namespace _STL
{
template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
	pair();
	pair(const pair &other);
};
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
class vector<Rva002390CB, allocator<Rva002390CB> >
{
	friend class vector<BfmeAsciiScalarValue8, allocator<BfmeAsciiScalarValue8> >;
protected:
	void _M_clear();
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
			reinterpret_cast<_STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> > *>(this)->_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			BfmeAsciiScalarValue8 *new_finish = _STL::__copy_ptrs(x.begin(), x.end(), m_start, _STL::__false_type());
			_STL::_Destroy(reinterpret_cast<Rva002390CB *>(new_finish), reinterpret_cast<Rva002390CB *>(m_finish));
		}
		else
		{
			_STL::__copy_ptrs(x.begin(), x.begin() + size(), m_start, _STL::__false_type());
			_STL::__uninitialized_copy((const Rva002390CB *)(x.begin() + size()), (const Rva002390CB *)x.end(), (Rva002390CB *)m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// vector<BfmeAsciiScalarValue8>::operator= is a header inline in STLport: one
// other unit emits a select-any copy of it, so a strong definition here was a
// duplicate symbol in the linked build. This anchor only makes this unit emit
// its copy for the ledger row; it is not retail code.
template _STL::vector<BfmeAsciiScalarValue8, _STL::allocator<BfmeAsciiScalarValue8> > &_STL::vector<BfmeAsciiScalarValue8, _STL::allocator<BfmeAsciiScalarValue8> >::operator=(const _STL::vector<BfmeAsciiScalarValue8, _STL::allocator<BfmeAsciiScalarValue8> > &);

// The retail call in this body reads 0x0031BD77, an address the ledger already
// carries as ??$_M_allocate_and_copy@PBVRva002390CB@@@?$vector@VRva002390CB@@V?$allocator@VRva002390CB@@@_STL@@@_STL@@IAEPAVRva002390CB@@IPBV2@0@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??$_M_allocate_and_copy@PBUBfmeAsciiScalarValue8@@@?$vector@UBfmeAsciiScalarValue8@@V?$allocator@UBfmeAsciiScalarValue8@@@_STL@@@_STL@@IAEPAUBfmeAsciiScalarValue8@@IPBU2@0@Z=??$_M_allocate_and_copy@PBVRva002390CB@@@?$vector@VRva002390CB@@V?$allocator@VRva002390CB@@@_STL@@@_STL@@IAEPAVRva002390CB@@IPBV2@0@Z")
