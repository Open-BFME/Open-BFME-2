// ?rva000858EE@@YAXPAURva000858EEVec@@U1@1@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
//
// Two byte-true bodies (dump range 1). Boundaries verified from retail bytes
// via the tools (ret-terminated extents). Names are honest address-derived
// CPMs; only the bytes, ABIs and displacements carry identity. No header
// edits, no STL, no fallbacks.
//
// - 0x0006EE27 (31B): `m_slot = p; vfunc(); m_slot = 0;` where vfunc is an
//   inherited virtual of the second MI base (sitting at +0x108), giving the
//   `add ecx,0x108` adjustment plus the indirect slot-0x30 dispatch. Slot
//   counts follow the proven no-dtor-slot rule (12 pure dummies put the
//   worker at 0x30). The trailing `m_slot = 0` uses the same /O1 `and`
//   zeroing the 0x00062B17 TU proved.
// - 0x000858EE (89B): out = a + (b - a) * k over three floats with
//   k = 0.0625f from a TU-local constant (retail reads VA 0x00BC747C,
//   which has no ledger owner; the float-ref gate matches by value).
//   By-value Vec3 params explain the 7 stack slots (ret 0x1C).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// --- 0x0006EE27 family ---
class Pad6EE27
{
	char m_pad[0x108];
};

// ?Target6EE27::vfunc present-unmatched
class Target6EE27
{
public:
	virtual void d00() = 0;
	virtual void d01() = 0;
	virtual void d02() = 0;
	virtual void d03() = 0;
	virtual void d04() = 0;
	virtual void d05() = 0;
	virtual void d06() = 0;
	virtual void d07() = 0;
	virtual void d08() = 0;
	virtual void d09() = 0;
	virtual void d10() = 0;
	virtual void d11() = 0;
	virtual void vfunc();
};

// ?Host6EE27::rva0006EE27 present-unmatched
class Host6EE27 : public Pad6EE27, public Target6EE27
{
public:
	void rva0006EE27(void *p);

	unsigned char m_pad10C[0x118 - 0x10C];
	void *m_slot; ///< +0x118
};

// ?Host6EE27::rva0006EE27 present-unmatched
void Host6EE27::rva0006EE27(void *p)
{
	m_slot = p;
	vfunc();
	m_slot = 0;
}

struct Rva000858EEVec
{
	float x;
	float y;
	float z;
};

static const float kRva000858EEFactor = 0.0625f;

// ?rva000858EE present-unmatched
void rva000858EE(Rva000858EEVec *out, Rva000858EEVec a, Rva000858EEVec b)
{
	out->x = a.x + (b.x - a.x) * kRva000858EEFactor;
	out->y = a.y + (b.y - a.y) * kRva000858EEFactor;
	out->z = a.z + (b.z - a.z) * kRva000858EEFactor;
}
