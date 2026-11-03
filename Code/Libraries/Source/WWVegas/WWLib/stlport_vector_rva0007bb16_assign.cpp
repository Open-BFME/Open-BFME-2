// cl: /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??4?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z, retail 0x001522CF, 206 bytes.
// Vector Rva0007BB16Record assign via rowed allocate_and_copy 0x00151DCB plus
// rowed clear 0x0007C614 plus rowed copy 0x00151FCA plus rowed destroy
// 0x0007C2D7 plus rowed uninitialized_copy 0x0010E5DE. Evidence: same 3-path
// shape as B950F assign 0x000C084D (also 206B) and scalar8 assign 0x0031DC3C;
// retail mixes BfmeAssignRecord36 copy spelling with Rva0007BB16Record destroy
// spelling for the same 0x24 stride (EraseRange 0x0015229C precedent); idiv
// 0x24 stride throughout; callers 0x001524E3 0x001526CC.
struct BfmeAssignRecord36
{
	~BfmeAssignRecord36();
	unsigned char m_pad[36];
};
#include "Rva0007BB16Record.h"
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
			pointer tmp = _M_allocate_and_copy(xsize, (Rva0007BB16Record *)x.begin(), (Rva0007BB16Record *)x.end());
			_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			BfmeAssignRecord36 *new_finish = _STL::__copy_ptrs((BfmeAssignRecord36 *)x.begin(), (BfmeAssignRecord36 *)x.end(), (BfmeAssignRecord36 *)m_start, _STL::__false_type());
			_STL::_Destroy((Rva0007BB16Record *)new_finish, m_finish);
		}
		else
		{
			_STL::__copy_ptrs((BfmeAssignRecord36 *)x.begin(), (BfmeAssignRecord36 *)(x.begin() + size()), (BfmeAssignRecord36 *)m_start, _STL::__false_type());
			_STL::__uninitialized_copy((Rva0007BB16Record *)(x.begin() + size()), (Rva0007BB16Record *)x.end(), m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// operator= is a header inline: another unit emits a select-any copy of it,
// so a strong definition here was a duplicate symbol in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
template _STL::vector<Rva0007BB16Record, _STL::allocator<Rva0007BB16Record> > &_STL::vector<Rva0007BB16Record, _STL::allocator<Rva0007BB16Record> >::operator=(const _STL::vector<Rva0007BB16Record, _STL::allocator<Rva0007BB16Record> > &);
