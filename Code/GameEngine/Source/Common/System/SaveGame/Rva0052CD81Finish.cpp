// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native copy constructor 0x0052CD81, 96B. Its range callee 52C987 calls
// Construct 52C3D7 and the existing Rva004E194E copy 52BE96; SaveMapPreview
// is a different 20B record. Reuse the actual LivingWorldCampaign record view.
// The 60B count base at 4FF36C uses the native malloc allocator configuration.
#include <vector>
#include "ascii_string.h"

class Rva004E194E
{
public:
	virtual ~Rva004E194E();
	Rva004E194E(const Rva004E194E &);
private:
	int m_04, m_08;
	AsciiString m_0C;
	unsigned char m_10;
};
typedef char RecordSizeCheck[sizeof(Rva004E194E) == 20 ? 1 : -1];

namespace _STL
{
template <> void _Construct<Rva004E194E, Rva004E194E>(Rva004E194E *, const Rva004E194E &);
}

class Rva0052CD81 : public _STL::_Vector_base<Rva004E194E, _STL::allocator<Rva004E194E> >
{
public:
	Rva0052CD81(const Rva0052CD81 &);
};

Rva0052CD81::Rva0052CD81(const Rva0052CD81 &x)
	: _STL::_Vector_base<Rva004E194E, _STL::allocator<Rva004E194E> >(
		x._M_finish - x._M_start,
		*(const _STL::allocator<Rva004E194E> *)&
		((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	_M_finish = _STL::__uninitialized_copy(x._M_start, x._M_finish, _M_start, _STL::__false_type());
}
