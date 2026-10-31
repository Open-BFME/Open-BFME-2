// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /ICode /I.
// stlport
// ??0Rva0039C151@@QAE@ABV0@@Z @0x0051ECC3 71B vector copy ctor via rowed Vector_base Rva0054103E get_allocator AsciiString uninit-copy Rva0039BA22
// Evidence: caller 0x0051F87B member at +0x14; stride 0x14; callees 0x0021983A row AsciiString 0x004FF36C pin Rva0054103E 0x0039BA22 row Rva0039B893; precedent Rva005386F5Copy.cpp
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

class Rva0039B893
{
public:
	Rva0039B893 &operator=(const Rva0039B893 &other);
	virtual ~Rva0039B893();
	int m_field04; // +0x04
	int m_field08; // +0x08
	short m_field0C; // +0x0C
	short m_field0E; // +0x0E
	short m_field10; // +0x10
	char m_pad12[0x2];
};

Rva0039B893 *__cdecl Rva0039BA22UninitCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const _STL::__false_type &tag) throw();

class Rva0054103E
{
public:
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
};

struct PrereqUnitRec
{
	unsigned int m_data[3];
};

// Declared only: the rowed bases 0x00211E58, 0x004FF36C and 0x005C8C37 serve these calls.
namespace _STL {
template <> _Vector_base<Rva0054103E, allocator<Rva0054103E> >::_Vector_base(const allocator<Rva0054103E> &) throw();
template <> _Vector_base<Rva0054103E, allocator<Rva0054103E> >::_Vector_base(size_t, const allocator<Rva0054103E> &) throw();
template <> _Vector_base<PrereqUnitRec, allocator<PrereqUnitRec> >::_Vector_base(const allocator<PrereqUnitRec> &) throw();
template <> _Vector_base<PrereqUnitRec, allocator<PrereqUnitRec> >::_Vector_base(size_t, const allocator<PrereqUnitRec> &) throw();
}

class Rva0039C151 : public _STL::_Vector_base<Rva0054103E, _STL::allocator<Rva0054103E> >
{
public:
	__forceinline Rva0039C151() : _STL::_Vector_base<Rva0054103E, _STL::allocator<Rva0054103E> >(_STL::allocator<Rva0054103E>()) {}
	Rva0039C151(const Rva0039C151 &x);
	~Rva0039C151();
};

class Rva004EE501 : public _STL::_Vector_base<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >
{
public:
	__forceinline Rva004EE501() : _STL::_Vector_base<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >(_STL::allocator<PrereqUnitRec>()) {}
	Rva004EE501(const Rva004EE501 &x);
	~Rva004EE501();
};

// The copy tag argument: an empty temporary the compiler leaves uninitialized.
struct UninitCopyTag : _STL::__false_type { UninitCopyTag() {} };

// Declared only: the rowed get_allocator 0x0021983A serves the call.
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::allocator_type vector<AsciiString, allocator<AsciiString> >::get_allocator() const; }

Rva0039C151::Rva0039C151(const Rva0039C151 &x)
	: _STL::_Vector_base<Rva0054103E, _STL::allocator<Rva0054103E> >((x._M_finish - x._M_start), *(const _STL::allocator<Rva0054103E> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	_M_finish = (Rva0054103E *)Rva0039BA22UninitCopy((Rva0039B893 *)x._M_start, (Rva0039B893 *)x._M_finish, (Rva0039B893 *)_M_start, UninitCopyTag());
}
