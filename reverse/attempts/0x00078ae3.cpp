// ?rva00078AE3@Rva00078AE3@@QAEXPAV1@@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Four small byte-true bodies (dump range 1). Boundaries verified from retail
// bytes via the tools (ret-terminated extents). Names are honest
// address-derived CPMs; only the bytes, ABIs and displacements carry
// identity. No header edits, no STL, no fallbacks.
//
// - 0x00068119 (34B): `mov ecx,[ecx+0x3858]; test; je ret;` then float
//   shuffle (fld/fstp) building (ptr, ref, float) for the rowed
//   W3DPropBuffer::removePropsForConstruction (0x000EF154); ret 0xC.
//   Forward-declared param types reproduce the mangling; the callee row
//   supplies the address.
// - 0x00068441 (41B): body-ordered stores (byte 1 at +0x37D4, zero at
//   +0x3794/+0xD8/+0xDC) then the rowed W3DRoadBuffer::updateLighting
//   (0x000D4A4B) through the +0x386C member; one ignored stack arg, ret 4.
// - 0x00078AE3 (72B): masked three-round flag merge
//   (masks 7, 0x3FFFFFF8, 0x40000000) from src, then plain copies of
//   +4/+8/+0xC; early-out when src == this; ret 4.
// - 0x0007B851 (63B): 2D SSE distance with the value spilled to the dead
//   first-arg slot, x87 fsqrt through the fleet's proven WWMath::Sqrt
//   inline-asm helper (same codegen blocker as SphereClassAddSphere.cpp),
//   float return in ST0, plain ret.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct GeometryInfo
{
	unsigned char m_opaque[0x1C];
};

class W3DPropBuffer
{
public:
	void removePropsForConstruction(const Coord3D *a, const GeometryInfo &b, float f);
};

class W3DRoadBuffer
{
public:
	void updateLighting();
};

// ?Rva00068119::rva00068119 present-unmatched
class Rva00068119
{
public:
	void rva00068119(const Coord3D *a, const GeometryInfo *b, float f);
// (b rides as a pointer and is dereferenced at the call, matching the
// callee's const-ref parameter without moving any bytes)
	unsigned char m_pad[0x3858];
	W3DPropBuffer *m_buf;
};

// ?Rva00068119::rva00068119 present-unmatched
void Rva00068119::rva00068119(const Coord3D *a, const GeometryInfo *b, float f)
{
	W3DPropBuffer *buf = m_buf;
	if (buf)
		buf->removePropsForConstruction(a, *b, f);
}

// ?Rva00068441::rva00068441 present-unmatched
class Rva00068441
{
public:
	void rva00068441(Int ignored);
	unsigned char m_padD8[0xD8];
	Int m_D8;
	Int m_DC;
	unsigned char m_padE0[0x3794 - 0xE0];
	Int m_3794;
	unsigned char m_pad3798[0x37D4 - 0x3798];
	unsigned char m_37D4;
	unsigned char m_pad37D5[0x386C - 0x37D5];
	W3DRoadBuffer *m_road;
};

// ?Rva00068441::rva00068441 present-unmatched
void Rva00068441::rva00068441(Int ignored)
{
	(void)ignored;
	m_37D4 = 1;
	m_3794 = 0;
	m_D8 = 0;
	m_DC = 0;
	m_road->updateLighting();
}

// ?Rva00078AE3::rva00078AE3 present-unmatched
class Rva00078AE3
{
public:
	void rva00078AE3(Rva00078AE3 *src);
	UnsignedInt m_f;
	UnsignedInt m_4;
	UnsignedInt m_8;
	UnsignedInt m_C;
};

// ?Rva00078AE3::rva00078AE3 present-unmatched
void Rva00078AE3::rva00078AE3(Rva00078AE3 *src)
{
	if (this == src)
		return;
	m_f ^= (m_f ^ src->m_f) & 7;
	m_f ^= (m_f ^ src->m_f) & 0x3FFFFFF8;
	m_f ^= (m_f ^ src->m_f) & 0x40000000;
	m_4 = src->m_4;
	m_8 = src->m_8;
	m_C = src->m_C;
}

struct Rva0007B851Point
{
	float x;
	float y;
};

class Rva0007B851Math
{
public:
// ?Rva0007B851Math::Sqrt present-unmatched
	static __forceinline float Sqrt(float val)
	{
		float retval;
		__asm {
			fld val
			fsqrt
			fstp retval
		}
		return retval;
	}
};

float rva0007B851(const Rva0007B851Point *a, const Rva0007B851Point *b)
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	return Rva0007B851Math::Sqrt(dx * dx + dy * dy);
}
