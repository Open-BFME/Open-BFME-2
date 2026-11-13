// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::operator= three-path body for a 128-byte
// address-derived element view. The 186-byte target at 0x0032C0E3 uses the
// allocate-copy helper at 0x0032A3E1 the clear helper at 0x0032BF1B the
// copy worker at 0x0032A40E the destroy loop at 0x0032B580 and the uninitialized
// copy worker at 0x0032A37A. Those callees are independently rowed; their
// different type spellings leave the element's C++ identity unresolved.

// These are the rowed call owners at 0x0032B580 and 0x0032BF1B.
// The casts below bind the proven call targets without asserting element identity.
class Rva0032A3A9Element;
class Rva0032BF1B
{
public:
	~Rva0032BF1B();
private:
	Rva0032A3A9Element *m_start; // +0x00
	Rva0032A3A9Element *m_finish; // +0x04
};

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

#include "../../../../GameEngine/Include/GameLogic/Rva0032C0E3Element.h"

template <class Type, class Allocator>
_STL::vector<Type, Allocator> &_STL::vector<Type, Allocator>::operator=(const vector &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		if (xsize > capacity())
		{
			pointer tmp = _M_allocate_and_copy(xsize, x.m_start, x.m_finish);
			((Rva0032BF1B *)this)->~Rva0032BF1B();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			pointer new_finish = _STL::__copy_ptrs(x.m_start, x.m_finish, m_start, _STL::__false_type());
			_STL::_Destroy((Rva0032A3A9Element *)new_finish, (Rva0032A3A9Element *)m_finish);
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

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x0032A3E1 -> ??$_M_allocate_and_copy@PBUBfmePod128@@@?$vector@UBfmePod128@@V?$allocator@UBfmePod128@@@_STL@@@_STL@@IAEPAUBfmePod128@@IPBU2@0@Z
#pragma comment(linker, "/alternatename:??$_M_allocate_and_copy@PAURva0032C0E3Element@@@?$vector@URva0032C0E3Element@@V?$allocator@URva0032C0E3Element@@@_STL@@@_STL@@IAEPAURva0032C0E3Element@@IPAU2@0@Z=??$_M_allocate_and_copy@PBUBfmePod128@@@?$vector@UBfmePod128@@V?$allocator@UBfmePod128@@@_STL@@@_STL@@IAEPAUBfmePod128@@IPBU2@0@Z")
//   0x0032A40E -> ??$copy@PAVBuildListInfo@@PAV1@@_STL@@YAPAVBuildListInfo@@PAV1@00@Z
#pragma comment(linker, "/alternatename:??$__copy_ptrs@PAURva0032C0E3Element@@PAU1@@_STL@@YAPAURva0032C0E3Element@@PAU1@00ABU__false_type@0@@Z=??$copy@PAVBuildListInfo@@PAV1@@_STL@@YAPAVBuildListInfo@@PAV1@00@Z")
//   0x0032A37A -> ??$__uninitialized_copy@PBUBfmePod128@@PAU1@@_STL@@YAPAUBfmePod128@@PBU1@0PAU1@ABU__false_type@0@@Z
#pragma comment(linker, "/alternatename:??$__uninitialized_copy@PAURva0032C0E3Element@@PAU1@@_STL@@YAPAURva0032C0E3Element@@PAU1@00ABU__false_type@0@@Z=??$__uninitialized_copy@PBUBfmePod128@@PAU1@@_STL@@YAPAUBfmePod128@@PBU1@0PAU1@ABU__false_type@0@@Z")
