// cl: /O1 /DNDEBUG /MD /arch:SSE /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
//
// Three small byte-true bodies (dump range 1). Boundaries verified from
// retail bytes via the tools (ret-terminated extents). Names are honest
// address-derived CPMs; only the bytes, ABIs and displacements carry
// identity. Callees are all rowed (declared here by forward/mangled match);
// indirect virtual dispatches need no pins. No header edits, no STL
// (the _STL::__false_type below is name-matched, not an instantiation),
// no fallbacks.
//
// - 0x0007BA09 (44B): `if (m_08) m_08->s06(); if (m_0C) { r = h09();
//   if (r) { r->m_20 = m_0C; m_0C = 0; } }` with indirect vtable slots
//   0x18 (member type) and 0x24 (host). Slot counts follow the proven
//   no-dtor-slot rule (6/9 pure dummies put the workers at 0x18/0x24).
// - 0x0007B68E (94B): free triplet over Vector3/PlaneClass: SSE
//   differences via the rowed get_far_extent, then the rowed static
//   CollisionMath::Overlap_Test, returning (result == 1) through the
//   canonical dec/neg/sbb/inc lowering. The plane normal at offset0
//   supplies the extent direction; the point test also reads distance12.
// - 0x0007BF5A (29B): cdecl forwarder pushing (a, b, c, uninit flag, 0)
//   into the rowed Rva0007BF77Copy; the 1-byte flag local matches the
//   callee's const _STL::__false_type& parameter by address.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// Reuse the shared Vector3 view and donor34f59164f6 PlaneClass/CollisionMath.
// Native7B638 reads normal0/4/8 and distance12; native7B5C8 consumes the
// normal at offset0. No opaque96-byte PlaneClass or partial enum is needed.
#include "vector3.h"
#include "plane.h"
#include "colmath.h"

void get_far_extent(const Vector3 &a, const Vector3 &b, Vector3 *out);

struct Region2D
{
	float x;
	float y;
	float w;
	float h;
};

namespace _STL
{
struct __false_type
{
};
}

Region2D *Rva0007BF77Copy(Region2D *a, Region2D *b, Region2D *c, const _STL::__false_type &f, int i);

class Rva0007BA09Sub
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06();
};

struct Rva0007BA09Result
{
	unsigned char m_pad[0x20];
	Int m_20;
};

class Rva0007BA09Host
{
public:
	void rva0007BA09();
	virtual void h00() = 0;
	virtual void h01() = 0;
	virtual void h02() = 0;
	virtual void h03() = 0;
	virtual void h04() = 0;
	virtual void h05() = 0;
	virtual void h06() = 0;
	virtual void h07() = 0;
	virtual void h08() = 0;
	virtual void *h09();

	void *m_04;
	Rva0007BA09Sub *m_08;
	Int m_0C;
};

void Rva0007BA09Host::rva0007BA09()
{
	if (m_08)
		m_08->s06();
	if (m_0C)
	{
		void *r = h09();
		if (r)
		{
			((Rva0007BA09Result *)r)->m_20 = m_0C;
			m_0C = 0;
		}
	}
}

class Rva0007B68EObj
{
public:
	float x;
	float y;
	float z;
	Vector3 m_vec;
};

Bool rva0007B68E(const PlaneClass *p, const Rva0007B68EObj *o)
{
	const Vector3 *pv = &p->N;
	Vector3 t;
	get_far_extent(*pv, o->m_vec, &t);
	t.X = o->x - t.X;
	t.Y = o->y - t.Y;
	t.Z = o->z - t.Z;
	return CollisionMath::Overlap_Test(*p, t) == CollisionMath::POS;
}

void rva0007BF5A(Region2D *a, Region2D *b, Region2D *c)
{
	_STL::__false_type flag;
	Rva0007BF77Copy(a, b, c, flag, 0);
}
