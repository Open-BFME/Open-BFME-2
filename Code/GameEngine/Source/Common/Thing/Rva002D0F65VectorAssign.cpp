// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@URva002D0EDCElement@@V?$allocator@URva002D0EDCElement@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x002D0F65 206B: vector Rva002D0EDCElement assign via allocate_and_copy 0x002D0EDC plus clear 0x002CFB90 plus CopyRange 0x002D0D5E plus Destroy 0x002CF891 plus uninitialized_copy 0x002D0D7B. Evidence: same 3-path 206B shape as ProductionPrerequisite assign 0x002D1033; idiv 0x5C stride 92; chain from 0x002D0D5E; caller 0x002D1266.
struct Rva002D0EDCElement
{
	Rva002D0EDCElement();
	Rva002D0EDCElement(const Rva002D0EDCElement &other);
	~Rva002D0EDCElement();
	Rva002D0EDCElement &operator=(const Rva002D0EDCElement &other);
private:
	void *m_unreconstructed[23];
};

typedef char Rva002D0EDCSizeCheck[sizeof(Rva002D0EDCElement) == 0x5C ? 1 : -1];

char *__cdecl Rva002D0D5ECopy(char *first, char *last, char *result, int dummy);
struct Rva002CF571Item;
void __cdecl Rva002CF891Wrap(struct Rva002CF571Item *first, struct Rva002CF571Item *last);
struct Rva002CFB90
{
	void rva002CFB90();
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
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &tag);
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
}

typedef void (__cdecl *RvaDestroyFn)(Rva002D0EDCElement *, Rva002D0EDCElement *);
typedef Rva002D0EDCElement *(__cdecl *RvaUninitFn)(Rva002D0EDCElement *, Rva002D0EDCElement *, Rva002D0EDCElement *, const _STL::__false_type &);

inline _STL::vector<Rva002D0EDCElement, _STL::allocator<Rva002D0EDCElement> > &_STL::vector<Rva002D0EDCElement, _STL::allocator<Rva002D0EDCElement> >::operator=(const vector &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		_STL::__false_type tag;
		if (xsize > capacity())
		{
			pointer tmp = _M_allocate_and_copy(xsize, x.begin(), x.end());
			((Rva002CFB90 *)this)->rva002CFB90();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			pointer new_finish = (pointer)Rva002D0D5ECopy((char *)const_cast<pointer>(x.begin()), (char *)const_cast<pointer>(x.end()), (char *)m_start, (int)((char *)&tag + 3));
			((RvaDestroyFn)&Rva002CF891Wrap)(new_finish, m_finish);
		}
		else
		{
			(pointer)Rva002D0D5ECopy((char *)const_cast<pointer>(x.begin()), (char *)const_cast<pointer>(x.begin() + size()), (char *)m_start, (int)((char *)&tag + 3));
			_STL::__uninitialized_copy(x.begin() + size(), x.end(), m_finish, *(_STL::__false_type *)((char *)&tag + 3));
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// operator= is a header inline in STLport (another unit emits a select-any
// copy), so a strong definition here was a duplicate in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva002D0EDCVectorAssign@@YAXPAV?$vector@URva002D0EDCElement@@V?$allocator@URva002D0EDCElement@@@_STL@@@_STL@@ABV12@@Z present-unmatched
void bfmeEmitRva002D0EDCVectorAssign(_STL::vector<Rva002D0EDCElement, _STL::allocator<Rva002D0EDCElement> > *p, const _STL::vector<Rva002D0EDCElement, _STL::allocator<Rva002D0EDCElement> > &x)
{
	*p = x;
}
#pragma inline_depth()
