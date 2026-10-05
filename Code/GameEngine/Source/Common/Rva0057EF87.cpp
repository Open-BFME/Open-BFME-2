// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0057EF87@Rva0057EE5C@@QAEXXZ @0x0057EF87 123B
// Shutdown of the MpGameSetup +0xD0 member: refresh via pinned 0x0057EF18,
// clear +0x58 target +8, resize Drawable vector +0x7C to 10, rowed clear
// 0x0052493F, close AptMpGameRules::InitGadgets screen, erase voidptr vectors
// +0x64/+0x70. Evidence: pin name, caller 0x0043DE41 in MpGameSetup::rva0043DE19,
// prev/next Rva0057EE5C.cpp // cl: /O1 /DNDEBUG /MD /GX, all callees rowed/pinned.
#include "ascii_string.h"

class Drawable;

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	T *erase(T *first, T *last);
	void resize(unsigned int n, T x);
};
}

struct TargetRef00217D4C
{
	int m_00;
	int m_04;
	int m_08;
};

struct ReleaseHolder0057EE5C
{
	TargetRef00217D4C *m_ptr;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class AptMpGameRules
{
public:
	void rva0057EF18();
};

class Rva0052493F
{
public:
	void rva0052493F();
};

void _bfme_closeAptScreen(const AsciiString &name);

class Rva0057EE5C : public Rva005248D0
{
public:
	void rva0057EF87();
private:
	char m_pad04[0x58 - 4]; // +0x04..+0x57
	ReleaseHolder0057EE5C m_58; // +0x58
	char m_pad5C[0x60 - 0x5C]; // +0x5C..+0x5F
	int m_60; // +0x60
	_STL::vector<void *, _STL::allocator<void *> > m_64; // +0x64
	_STL::vector<void *, _STL::allocator<void *> > m_70; // +0x70
	_STL::vector<Drawable *, _STL::allocator<Drawable *> > m_7C; // +0x7C
};

void Rva0057EE5C::rva0057EF87()
{
	((AptMpGameRules *)this)->rva0057EF18();
	m_58.m_ptr->m_08 = 0;
	m_7C.resize(10, (Drawable *)0);
	((Rva0052493F *)this)->rva0052493F();
	_bfme_closeAptScreen(AsciiString("AptMpGameRules::InitGadgets"));
	_STL::vector<void *, _STL::allocator<void *> > &v64 = m_64;
	v64.erase(v64.begin(), v64.end());
	_STL::vector<void *, _STL::allocator<void *> > &v70 = m_70;
	v70.erase(v70.begin(), v70.end());
}
