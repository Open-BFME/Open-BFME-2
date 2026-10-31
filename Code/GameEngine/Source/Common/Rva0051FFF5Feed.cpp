// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /ICode /I.
// stlport
// Range-27 xfer feed sequence.
// ?Rva0051FFF5@Rva0051F87B@@UAEXPAVXfer0051FFF5@@@Z @0x0051FFF5 125B
// Thiscall feeds holder fields to an Xfer-like object's virtual slots
// 0x68/0x7C/0x6C/0x7C (TU-local vtable view, slots positional), preserves
// m_10 across a temp, then runs five cdecl out-param helpers: pinned
// 0x0039C4F7 and 0x004EE9E9 plus the rowed 0x0040E269 Xfer vector helper
// three times (local cdecl spellings via pins). The trailing out-param
// reuses dead this with an in-place +0x44 adjust.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

class Xfer0051FFF5
{
public:
	virtual ~Xfer0051FFF5();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26(void *out);
	virtual void slot27(void *out);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31(void *out);
};

void Rva0039C4F7(Xfer0051FFF5 *x, void *out);
void Rva004EE9E9(Xfer0051FFF5 *x, void *out);
void Rva0040E269(Xfer0051FFF5 *x, void *out);

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

void Rva0051F87B::Rva0051FFF5(Xfer0051FFF5 *xfer)
{
	xfer->slot26(&m_04);
	xfer->slot31(&m_08);
	xfer->slot27(&m_0C);
	int tmp = m_10;
	xfer->slot31(&tmp);
	m_10 = tmp;
	Rva0039C4F7(xfer, &m_14);
	Rva004EE9E9(xfer, &m_20);
	Rva0040E269(xfer, &m_2C);
	Rva0040E269(xfer, &m_38);
	char *tail = (char *)this + 0x44;
	Rva0040E269(xfer, tail);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0040E269 reads ?Rva0040E269Xfer@@YAPAVXfer@@PAV1@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z
#pragma comment(linker, "/alternatename:?Rva0040E269@@YAXPAVXfer0051FFF5@@PAX@Z=?Rva0040E269Xfer@@YAPAVXfer@@PAV1@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z")
//   0x004EE9E9 reads ?Rva004EE9E9XferVector@@YAPAVXfer@@PAV1@PAVRva004EE6D0@@@Z
#pragma comment(linker, "/alternatename:?Rva004EE9E9@@YAXPAVXfer0051FFF5@@PAX@Z=?Rva004EE9E9XferVector@@YAPAVXfer@@PAV1@PAVRva004EE6D0@@@Z")
//   0x0039C4F7 reads ?Rva0039C4F7XferSnapshotVector@@YAPAVXfer@@PAV1@PAVRva0039C1C3@@@Z
#pragma comment(linker, "/alternatename:?Rva0039C4F7@@YAXPAVXfer0051FFF5@@PAX@Z=?Rva0039C4F7XferSnapshotVector@@YAPAVXfer@@PAV1@PAVRva0039C1C3@@@Z")
