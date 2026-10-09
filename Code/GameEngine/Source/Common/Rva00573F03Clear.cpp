// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00573F0E@Rva00573F03@@QAEXXZ @0x00573F0E 44B
// Chain lane: calls rowed 0x0055AFA3; vtable slot1 of 0x0086E2C8 (Rva00573F03)
// and 0x00870B38. Zeroes Coord +0x40 via stack temp then base clear.
// Layout from Rva00573F9FXfer.cpp (base ends 0x40, Coord +0x40) and
// Rva00573B23Dtor.cpp. Base rowed 0x0055AFA3 via Rva0055AFA3Clear.cpp.
#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

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
private:
	char m_pad2C[0x14];
};

class Rva00573F03 : public Rva00573B23
{
public:
	virtual void rva00573F0E();
private:
	Coord3DBase m_40;
};

void Rva00573F03::rva00573F0E()
{
	Coord3DBase zero = { 0.0f, 0.0f, 0.0f };
	m_40 = zero;
	Rva0055B0CC::rva0055AFA3();
}
