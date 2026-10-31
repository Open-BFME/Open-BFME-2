// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??0Rva0052C8AB@@QAE@ABV0@@Z 0x0052C8AB 68B evidence: Vector_base 0x00421D73 row E16; get_allocator 0x0021983A row AsciiString; uninit-copy 0x0052C2CA row Rva003A6360Record; caller 0x0052D555; sibling Rva005386F5Copy same recipe
#include <vector>
#include "../../../Include/Lib/BfmeE16.h"
class Rva003A6360Record
{
public:
	Rva003A6360Record(const Rva003A6360Record &other) throw();

	int m_vtable;
	int m_word04;
	unsigned char m_byte08;
	int m_word0C;
};
// _Construct<Rva003A6360Record> is emitted by StlportConstructCopySiblings.cpp (0x0052BD28); here it only inlines.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<Rva003A6360Record, Rva003A6360Record>(Rva003A6360Record *p, const Rva003A6360Record &v) throw()
{ new (p) Rva003A6360Record(v); } }
class AsciiString;
namespace _STL { template <> _Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(unsigned int, allocator<BfmeE16> const &); }
namespace _STL { template <> allocator<AsciiString> vector<AsciiString, allocator<AsciiString> >::get_allocator() const; }
class Rva0052C8AB : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	Rva0052C8AB(const Rva0052C8AB &x);
};
Rva0052C8AB::Rva0052C8AB(const Rva0052C8AB &x)
	: _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >((x._M_finish - x._M_start), *(const _STL::allocator<BfmeE16> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	_M_finish = (BfmeE16 *)_STL::__uninitialized_copy((Rva003A6360Record *)x._M_start, (Rva003A6360Record *)x._M_finish, (Rva003A6360Record *)_M_start, _STL::__false_type());
}
