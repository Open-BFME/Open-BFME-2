// ?rva00474431@Rva00474431@@QAEHABURva00474431Pair@@H@Z
// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva00474431@Rva00474431@@QAEHABURva00474431Pair@@H@Z, retail 0x00474431, 82 bytes.
//
// Build a 0x1C-byte stack record, push it into the vector at +0x188, return
// size-1. The record is a Rva004691A5 (ctor 0x004691A5, matched) reinterpreted
// as a Rva00064640Record (layout from the matched copy ctor at 0x00064640);
// the rowed push_back at 0x00473F4A is the explicit instantiation in
// stlport_vector_rva00064640_fill_n.cpp, which carries these same flags.
//
// Retail decodes as:
//   442 mov eax,[ebp+8]        eax = &p
//   445 mov ecx,[eax]          p.m_00
//   447 mov [ebp-0x10],ecx     m_0C = p.m_00
//   44a mov ecx,[eax+4]        p.m_04
//   44d mov [ebp-0xc],ecx      m_10 = p.m_04
//   450 mov ecx,[eax]          p.m_00   RELOAD
//   452 mov eax,[eax+4]        p.m_04   RELOAD
//   455 mov [ebp-0x14],eax     m_08 = p.m_04
//   458 mov eax,[ebp+0xc]      v
//   45b mov [ebp-0x1c],eax     m_00 = v
//   461 mov [ebp-0x18],ecx     m_04 = p.m_00
// so both pair fields are read TWICE: the second read is what /O1 leaves behind
// only when the loads are not common-subexpression eliminated, which a
// `const volatile` reference to the parameter pins.
//
// The residual wall in the banked 0.97 body (6 rows) was purely the register
// rotation in the reload block plus the resulting crossing of the last two
// stores. The rotation exists because p.m_00 lands in eax, and eax is clobbered
// by the `v` load and the `lea`, forcing the m_04 store early. Stating the
// three tail stores in the order m_04, m_08, m_00 makes /O1 assign p.m_00 to
// ecx -- the register that survives to the last store -- and the emitted
// schedule becomes byte-identical to retail. All 33 instructions match; the
// only differing bytes are the two call relocations, which build.py fills from
// retail. The reorder is semantics-preserving: every store lands at its retail
// frame slot and the record is not read until push_back.
#include <vector>

class Rva004691A5
{
public:
	Rva004691A5();
private:
	int m_00;
	char m_pad04[0x10];
	float m_14;
	int m_18;
};

class Rva00064640Record
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	unsigned int m_18;
};

struct Rva00474431Pair
{
	int m_00;
	int m_04;
};

class Rva00474431
{
public:
	int rva00474431(const Rva00474431Pair &p, int v);
	char m_pad[0x188];
	_STL::vector<Rva00064640Record> m_vec;
};

int Rva00474431::rva00474431(const Rva00474431Pair &p, int v)
{
	Rva004691A5 u;
	Rva00064640Record &r = *(Rva00064640Record *)&u;
	const volatile Rva00474431Pair &q = p;
	r.m_0C = q.m_00;
	*(int *)&r.m_10 = q.m_04;
	r.m_04 = q.m_00;
	r.m_08 = q.m_04;
	r.m_00 = v;
	m_vec.push_back(r);
	return m_vec.size() - 1;
}