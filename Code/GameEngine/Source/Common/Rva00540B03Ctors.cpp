// cl: /O1 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Three related non-polymorphic ctors, 69B each, differing only in the final
// member-init call (and the EH funclet id):
//   ??0Rva00540B03@@QAE@XZ @0x00540B03 -> rva00540A26 @0x00540A26
//   ??0Rva00542225@@QAE@XZ @0x00542225 -> rva00542067 @0x00542067
//   ??0Rva005422CF@@QAE@XZ @0x005422CF -> rva00542148 @0x00542148
// Each builds the Rva00330757Member head (+0, via rowed 0x00330757), the
// BfmeE16 vector (+0x10, via the rowed _Vector_base at 0x00211E58), zeroes
// +0x1c, then runs its own no-arg init (declared here, pinned in
// reverse/symbols.csv; identity unproven). Same member-EH idiom as the landed
// Rva00526275Ctor.cpp / Rva0033076E bodies: member dtors inline into the
// compiler's funclets, so no dtor rows are needed. Views copy the member TUs.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva00330757Member
{
public:
	Rva00330757Member();

private:
	_STL::vector<BfmeE16> m_items;
	int m_flags;
};

class Rva00540B03
{
public:
	Rva00540B03();
	void rva00540A26();
private:
	Rva00330757Member m_head;
	_STL::vector<BfmeE16> m_vec10;
	int m_1C;
};

Rva00540B03::Rva00540B03()
	: m_head(), m_vec10()
{
	m_1C = 0;
	rva00540A26();
}

class Rva00542225
{
public:
	Rva00542225();
	void rva00542067();
private:
	Rva00330757Member m_head;
	_STL::vector<BfmeE16> m_vec10;
	int m_1C;
};

Rva00542225::Rva00542225()
	: m_head(), m_vec10()
{
	m_1C = 0;
	rva00542067();
}

class Rva005422CF
{
public:
	Rva005422CF();
	void rva00542148();
private:
	Rva00330757Member m_head;
	_STL::vector<BfmeE16> m_vec10;
	int m_1C;
};

Rva005422CF::Rva005422CF()
	: m_head(), m_vec10()
{
	m_1C = 0;
	rva00542148();
}
