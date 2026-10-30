// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00573F0E@Rva00573F03@@UAEXXZ @0x00573F0E 44B
// Chain lane: calls rowed 0x0055AFA3; vtable slot1 of 0x0086E2C8 (Rva00573F03)
// and 0x00870B38. Zeroes Coord +0x40 via stack temp then base clear.
// Layout from Rva00573F9FXfer.cpp (base ends 0x40, Coord +0x40) and
// Rva00573B23Dtor.cpp. Base rowed 0x0055AFA3 via Rva0055AFA3Clear.cpp.
#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

// Dispatch-only view: the native ground-height call uses byte slot 0x18.
// The preceding slots are opaque and this unit emits no TerrainLogic vtable.
class TerrainLogic
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual float getGroundHeight(float x, float y, int dummy) const;
};
extern TerrainLogic *TheTerrainLogic;

class Rva0055B0CC
{
public:
	virtual ~Rva0055B0CC();
	void rva0055AFA3();
private:
	char m_pad04[0x28];
};

class Rva00573B23 : public Rva0055B0CC
{
protected:
	char m_pad2C[4];
	Coord3DBase m_30;
	char m_pad3C[4];
};

class Rva00573F03 : public Rva00573B23
{
public:
	virtual void rva00573F0E();
	void rva00573F3A(Coord3DBase *out);
private:
	Coord3DBase m_40;
};

void Rva00573F03::rva00573F0E()
{
	Coord3DBase zero = { 0.0f, 0.0f, 0.0f };
	m_40 = zero;
	Rva0055B0CC::rva0055AFA3();
}

// Native 0x00573F3A..0x00573F9F, RET4: add the x/y coordinates at +0x30
// and +0x40, query ground height, and fill the result buffer. WB 0x015079F0
// confirms the coordinate-copy/add/height sequence and a hidden result buffer.
// This neutral view preserves the observed result-buffer ABI; original names
// and the source return type remain unasserted.
void Rva00573F03::rva00573F3A(Coord3DBase *out)
{
	float position[3];
	float ax = m_30.x;
	float bx = m_40.x;
	float ay = m_30.y;
	_ReadWriteBarrier();
	position[0] = ax + bx;
	float &y = position[1];
	y = m_40.y + ay;
	float z = TheTerrainLogic->getGroundHeight(position[0], position[1], 0);
	out->z = z;
	out->x = position[0];
	out->y = position[1];
}
