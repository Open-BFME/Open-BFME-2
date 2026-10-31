// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /ICode /I.
// stlport
//
// ??4Rva0051F87B@@QAEAAV0@ABV0@@Z @0x0051F972 111B
// operator= for 0x50-byte record with vtable 0x0086745C at +0: UnicodeString
// at +4 via rowed StringBase@G set 0x00037150, int at +8, AsciiString at +0xC
// via rowed StringBase@D set 0x000366F0, int at +0x10, Rva0051F6DF at +0x14
// via rowed 0x0051F6DF, vector<Rva0051F7ADRecord> at +0x20 via rowed 0x0051F7AD,
// three vector<Rva0026F4F4Element> at +0x2C/+0x38/+0x44 via rowed 0x0026F4F4.
// Evidence: same layout as rowed copy 0x0051F87B and default ctor 0x0051FAFC;
// callers in stlport_asciistring_record_bodies and StlSweepW5Rva0051FC54;
// add edi 0x44 tail matches copy ctor.
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"
// Suppress this TU's non-retail copy of ??4?$vector@URva0026F4F4Element@@V?$allocator@URva0026F4F4Element@@@_STL@@@_STL@@QAEAAV01@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0026F4F4Element;
namespace _STL { template <> vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> > & vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> >::operator=(vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> > const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@URva0051F7ADRecord@@V?$allocator@URva0051F7ADRecord@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> void vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_M_allocate_and_copy@PBURva0051F7ADRecord@@@?$vector@URva0051F7ADRecord@@V?$allocator@U:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> template <> Rva0051F7ADRecord * vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::_M_allocate_and_copy<Rva0051F7ADRecord const *>(unsigned int,Rva0051F7ADRecord const *,Rva0051F7ADRecord const *); }
// Suppress this TU's non-retail copy of ??4?$vector@URva0051F7ADRecord@@V?$allocator@URva0051F7ADRecord@@@_STL@@@_STL@@QAEAAV01@AB:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> > & vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::operator=(vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> > const &); }
// Suppress this TU's non-retail copy of ??$__copy@PBURva0051F7ADRecord@@PAU1@H@_STL@@YAPAURva0051F7ADRecord@@PBU1@0PAU1@ABUrandom_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> Rva0051F7ADRecord * __copy<Rva0051F7ADRecord const *,Rva0051F7ADRecord *,int>(Rva0051F7ADRecord const *,Rva0051F7ADRecord const *,Rva0051F7ADRecord *,random_access_iterator_tag const &,int *); }

class Rva0039B893;

class Rva0051F6DF
{
public:
	Rva0051F6DF &operator=(const Rva0051F6DF &other);

private:
	Rva0039B893 *m_start;
	Rva0039B893 *m_finish;
	Rva0039B893 *m_end;
};

struct Rva0051F7ADRecord
{
	char bytes[12];
};
// vector<Rva0051F7ADRecord>::operator= is rowed at 0x0051F7AD
// (StlSweepR3Rva0051F7AD.cpp); declared only, so this unit emits no copy of it
// nor of the _Destroy and __uninitialized_copy it would pull in.
namespace _STL { template <> vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> > &vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> >::operator=(const vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> > &); }

struct Rva0026F4F4Element
{
	unsigned int m_value;
};

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

Rva0051F87B &Rva0051F87B::operator=(const Rva0051F87B &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	*reinterpret_cast<Rva0051F6DF *>(&m_14) = *reinterpret_cast<const Rva0051F6DF *>(&other.m_14);
	*reinterpret_cast<_STL::vector<Rva0051F7ADRecord> *>(&m_20) = *reinterpret_cast<const _STL::vector<Rva0051F7ADRecord> *>(&other.m_20);
	*reinterpret_cast<_STL::vector<Rva0026F4F4Element> *>(&m_2C) = *reinterpret_cast<const _STL::vector<Rva0026F4F4Element> *>(&other.m_2C);
	*reinterpret_cast<_STL::vector<Rva0026F4F4Element> *>(&m_38) = *reinterpret_cast<const _STL::vector<Rva0026F4F4Element> *>(&other.m_38);
	*reinterpret_cast<_STL::vector<Rva0026F4F4Element> *>(&m_44) = *reinterpret_cast<const _STL::vector<Rva0026F4F4Element> *>(&other.m_44);
	return *this;
}
