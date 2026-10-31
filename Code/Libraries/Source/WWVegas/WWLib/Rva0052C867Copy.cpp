// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??0Rva0052C867@@QAE@ABV0@@Z 0x0052C867 68B evidence: Vector_base 0x00421D73 row E16; get_allocator 0x0021983A row AsciiString; uninit-copy 0x0052C2A4 row Rva004E18A2; caller 0x0052D627; sibling Rva0052C8ABCopy same recipe
#include <vector>
#include "../../../Include/Lib/BfmeE16.h"
class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
private:
	int m_00;
};

class Rva004E18A2
{
public:
	virtual ~Rva004E18A2();
	Rva004E18A2(const Rva004E18A2 &other);
private:
	int m_04;
	Rva0036CA00Str m_08;
	unsigned char m_0C;
};

namespace _STL { template <> void _Construct<Rva004E18A2, Rva004E18A2>(Rva004E18A2 *, const Rva004E18A2 &) throw(); }
class AsciiString;
namespace _STL { template <> _Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(unsigned int, allocator<BfmeE16> const &); }
namespace _STL { template <> allocator<AsciiString> vector<AsciiString, allocator<AsciiString> >::get_allocator() const; }
class Rva0052C867 : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	Rva0052C867(const Rva0052C867 &x);
};
Rva0052C867::Rva0052C867(const Rva0052C867 &x)
	: _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >((x._M_finish - x._M_start), *(const _STL::allocator<BfmeE16> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	_M_finish = (BfmeE16 *)_STL::__uninitialized_copy((Rva004E18A2 *)x._M_start, (Rva004E18A2 *)x._M_finish, (Rva004E18A2 *)_M_start, _STL::__false_type());
}
