// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva00082D6A@Rva00082D6A@@QAEXXZ @0x00082D6A 168B.
// Rebuilds the point list at +0x14 from the provider at +0x0C: the provider is an
// object with a virtual base (vbptr at +0x18) whose virtual slots 2 and 0 give the
// shared height and the point count; the list is resized to the count (the
// resize wrapper 0x00082C98 receives an uninitialised Vector3 filler by value) and
// every element takes its x and y from the indexed query (thunk 0x0007E016, out
// pointer plus index) and the shared height as z. Finally clears the byte at +0x20.
// Layout views are neutral; identities are open.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

class Vector3
{
public:
	Vector3() {}
	// The uninitialised by-value filler is inlined; do not export this empty copy.
	__declspec(dllimport) __forceinline Vector3(const Vector3 &) {}
	float X, Y, Z;
};

class Rva00082C98Host
{
public:
	void rva00082C98(unsigned int count, Vector3 filler);
	void resize(unsigned int count);
	Coord3D *m_begin;
	Coord3D *m_end;
	Coord3D *m_capacity;
};

class Rva0007E016
{
public:
	virtual int slot0();
	virtual void slot1(int a0, int a1);
	virtual int slot2();
	int rva0007E016(int a0, int a1);
};

struct Rva00082D6APad18 { char m_bytes[0x18]; };

class Rva00082D6AOwner : public Rva00082D6APad18, public virtual Rva0007E016
{
};

class Rva00082D6A
{
public:
	void rva00082D6A();
private:
	char m_pad00[0x0C];
	Rva00082D6AOwner *m_owner;
	int m_10;
	Rva00082C98Host m_points;
	unsigned char m_cleared;
};

struct Rva00082D6APoint
{
	float x;
	float y;
};

void Rva00082D6A::rva00082D6A()
{
	Rva00082D6APoint point;
	float height = static_cast<float>(m_owner->slot2());
	int count = m_owner->slot0();
	Vector3 filler;
	m_points.rva00082C98(count, filler);
	for (int i = 0; i < count; ++i)
	{
		m_owner->rva0007E016(reinterpret_cast<int>(&point), i);
		m_points.m_begin[i].x = point.x;
		m_points.m_begin[i].y = point.y;
		m_points.m_begin[i].z = height;
	}
	m_cleared = 0;
}

// 0x00082D2A 15B: resizes to the given count with an uninitialised filler (same
// empty-copy-ctor Vector3 by value as the caller above).
void Rva00082C98Host::resize(unsigned int count)
{
	Vector3 filler;
	rva00082C98(count, filler);
}
