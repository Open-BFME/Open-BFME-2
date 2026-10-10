// cl: /O1 /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??4?$vector@UBfmeVectorRecord00319C84@@V?$allocator@UBfmeVectorRecord00319C84@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z retail 0x00319BCA 186B: vector record assign via STLport operator equal shape with rowed Rva copy helpers.
// Evidence: calls rowed _M_allocate_and_copy 0x00319304 and rowed _M_clear 0x00565A60 plus rowed Rva0031968ACopy 0x0031968A plus pin Destroy 0x00319784 plus rowed Rva00318D75Copy 0x00318D75; retail pushes caller tag to the 3-arg wrapper so the wrapper is called through a 4-arg pointer like StringRecord assign 0x002D0726; same 3-path shape as STLport _vector.c operator equal.
#include "ascii_string.h"
// Target correction: _Destroy at 0x00319784 calls the complete 26-byte loop
// at 0x00319331, whose slot-0 virtual destruction (flag 0) and +0x10 stride
// prove a virtual destructor and 16-byte extent. Other fields and the original
// element identity remain unknown; the former AsciiString/vector view was a
// size-only guess. BF1 575ba2b Q4VectorDtorPolymorphic.cpp supplies the same
// evidence-backed STLport virtual-element pattern, not the target identity.
struct BfmeVectorRecord00319C84
{
	virtual ~BfmeVectorRecord00319C84();
	char m_body[12];
};
class Rva00318B5C
{
	char _m[0x10];
public:
	Rva00318B5C(const Rva00318B5C &that);
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
template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
}
Rva00318B5C *Rva0031968ACopy(const Rva00318B5C *first, const Rva00318B5C *last, Rva00318B5C *result);
Rva00318B5C *Rva00318D75Copy(Rva00318B5C *first, Rva00318B5C *last, Rva00318B5C *result, const _STL::__false_type &tag);
typedef Rva00318B5C *(__cdecl *RvaCopyTagFn)(const Rva00318B5C *, const Rva00318B5C *, Rva00318B5C *, const _STL::__false_type &);
inline _STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > &_STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >::operator=(const vector &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		if (xsize > capacity())
		{
			pointer tmp = _M_allocate_and_copy<pointer>(xsize, const_cast<pointer>(x.begin()), const_cast<pointer>(x.end()));
			_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			Rva00318B5C *new_finish = ((RvaCopyTagFn)&Rva0031968ACopy)(reinterpret_cast<const Rva00318B5C *>(x.begin()), reinterpret_cast<const Rva00318B5C *>(x.end()), reinterpret_cast<Rva00318B5C *>(m_start), _STL::__false_type());
			_STL::_Destroy(reinterpret_cast<pointer>(new_finish), m_finish);
		}
		else
		{
			((RvaCopyTagFn)&Rva0031968ACopy)(reinterpret_cast<const Rva00318B5C *>(x.begin()), reinterpret_cast<const Rva00318B5C *>(x.begin() + size()), reinterpret_cast<Rva00318B5C *>(m_start), _STL::__false_type());
			Rva00318D75Copy(const_cast<Rva00318B5C *>(reinterpret_cast<const Rva00318B5C *>(x.begin() + size())), const_cast<Rva00318B5C *>(reinterpret_cast<const Rva00318B5C *>(x.end())), reinterpret_cast<Rva00318B5C *>(m_finish), _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// operator= is a header inline in STLport: other units emit select-any copies,
// so a strong definition here was a duplicate in the linked build. This anchor
// keeps this unit emitting its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitstlport_vector_record_319bca_assign@@YAXPAV?$vector@UBfmeVectorRecord00319C84@@V?$allocator@UBfmeVectorRecord00319C84@@@_STL@@@_STL@@ABV12@@Z present-unmatched
void bfmeEmitstlport_vector_record_319bca_assign(_STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > *p, const _STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > &x)
{
	p->operator=(x);
}
#pragma inline_depth()
