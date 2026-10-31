// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /ICode /I.
// stlport
//
// ??0Rva0051F87B@@QAE@XZ @ 0x0051FAFC size 86.
// Default ctor for 0x50-byte record with vtable 0x0086745C at +0: UnicodeString
// at +4, int at +8, AsciiString at +0xC, int at +0x10, vector<SaveMapPreview>
// at +0x14 (Rva0051ECC3 view), vector<PrereqUnitRec> at +0x20 (Rva0051ED0A view),
// three vector<unsigned> at +0x2C/+0x38/+0x44. Evidence: same vtable as rowed
// copy 0x0051F87B; offsets from lea pairs; empty Vector_base folds to 0x00211E58.
#include <vector>
// vector<unsigned int>'s allocator constructor inlines at every use here;
// imported force-inline so this unit emits no COMDAT copy of it (its copy
// differs from retail's kept /Od body at 0x00025100). The vector base
// constructor stays a declared nothrow call to its kept copy (0x00211E58).
namespace _STL {
template <> _Vector_base<unsigned int,allocator<unsigned int> >::_Vector_base(const allocator<unsigned int> &) throw();
template <> __declspec(dllimport) __forceinline
vector<unsigned int, allocator<unsigned int> >::vector(const allocator<unsigned int> &__a)
	: _Vector_base<unsigned int, allocator<unsigned int> >(__a) {}
}

#include "ascii_string.h"
#include "unicode_string.h"

struct SaveMapPreview
{
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
};

// The census's consumers of vector<SaveMapPreview> take its base constructor and
// allocator proxy from this unit's COMDAT copies; retail folds them at 0x00211E58.
template _STL::_Vector_base<SaveMapPreview, _STL::allocator<SaveMapPreview> >::_Vector_base(const _STL::allocator<SaveMapPreview> &);

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

class Xfer0051FFF5;

class Rva0051F87B
{
public:
	virtual void Rva0051FFF5(Xfer0051FFF5 *x);
	Rva0051F87B();
	Rva0051F87B(const Rva0051F87B &other);
	Rva0051F87B &operator=(const Rva0051F87B &other);
private:
	UnicodeString m_04;
	int m_08;
	AsciiString m_0C;
	int m_10;
	Rva0039C151 m_14;
	Rva004EE501 m_20;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_2C;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_38;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_44;
};

Rva0051F87B::Rva0051F87B()
{
}
