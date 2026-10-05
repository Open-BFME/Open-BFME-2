// ??0Rva00150D8A@@QAE@H@Z
// partial score=0.75 date=2026-10-05
// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00150D8A@@QAE@H@Z @0x00150D8A 87B (vft 0x00BD3A3C, memvft 0x00BD3854, cond 0x00150C97)
// ??0Rva00150DFD@@QAE@H@Z @0x00150DFD 87B (vft 0x00BD3A44, memvft 0x00BD385C, cond 0x00150CD0)
// ??0Rva00150F19@@QAE@H@Z @0x00150F19 87B (vft 0x00BD3A4C, memvft 0x00BD3864, cond 0x00150D09)
// One-arg constructors over (vtable, vector<BfmeE16> at +4, vtable-member at
// +0x10, int at +0x14), same recipe as rowed Rva002AC340Ctor.cpp: explicit
// init list, class vtable via pinned ??_7, vector member through rowed
// _Vector_base 0x00211E58, member vtable through the inline empty member
// constructor (no out-of-line call, hence absent-from-retail), int -1, then
// the pinned member call when the argument is positive. The init-list form
// is what sinks the vtable store below the vector argument setup exactly as
// retail shows. The three vtable pairs are 8 bytes apart with shared slot
// prefixes: three related classes. Element choice BfmeE16 reuses the rowed
// _Vector_base spelling; member layout beyond the observed stores and
// owner/conditional identities are unproven.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

struct Rva00150D8AMember
{
	virtual ~Rva00150D8AMember();
	inline Rva00150D8AMember();
};

class Rva00150D8A
{
public:
	Rva00150D8A(int n);
	virtual ~Rva00150D8A();
	void rva00150C97(int n);
private:
	_STL::vector<BfmeE16> m_vec04;
	Rva00150D8AMember m_mem10;
	int m_14;
};

// ?<Rva00150D8AMember::Rva00150D8AMember> absent-from-retail
inline Rva00150D8AMember::Rva00150D8AMember()
{
}

Rva00150D8A::Rva00150D8A(int n)
	: m_vec04()
	, m_mem10()
	, m_14(-1)
{
	if (n > 0)
		rva00150C97(n);
}

struct Rva00150DFDMember
{
	virtual ~Rva00150DFDMember();
	inline Rva00150DFDMember();
};

class Rva00150DFD
{
public:
	Rva00150DFD(int n);
	virtual ~Rva00150DFD();
	void rva00150CD0(int n);
private:
	_STL::vector<BfmeE16> m_vec04;
	Rva00150DFDMember m_mem10;
	int m_14;
};

// ?<Rva00150DFDMember::Rva00150DFDMember> absent-from-retail
inline Rva00150DFDMember::Rva00150DFDMember()
{
}

Rva00150DFD::Rva00150DFD(int n)
	: m_vec04()
	, m_mem10()
	, m_14(-1)
{
	if (n > 0)
		rva00150CD0(n);
}

struct Rva00150F19Member
{
	virtual ~Rva00150F19Member();
	inline Rva00150F19Member();
};

class Rva00150F19
{
public:
	Rva00150F19(int n);
	virtual ~Rva00150F19();
	void rva00150D09(int n);
private:
	_STL::vector<BfmeE16> m_vec04;
	Rva00150F19Member m_mem10;
	int m_14;
};

// ?<Rva00150F19Member::Rva00150F19Member> absent-from-retail
inline Rva00150F19Member::Rva00150F19Member()
{
}

Rva00150F19::Rva00150F19(int n)
	: m_vec04()
	, m_mem10()
	, m_14(-1)
{
	if (n > 0)
		rva00150D09(n);
}
