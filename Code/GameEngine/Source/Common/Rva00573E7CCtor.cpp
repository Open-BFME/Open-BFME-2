// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva00573E7C@@QAE@XZ @0x00573E7C (60B).
// Ctor of Rva00573F03-family (vtable 0x0086E2C8): calls base Rva00573B23
// then zeroes Coord + init flags in retail order.
// Evidence: base row 0x00573A9B ??0Rva00573B23; same vtable as 0x00573F03
// dtor row; layout from Rva00573F9FXfer.cpp (Coord m_40 float m_4c int m_50
// bool m_54 uint m_58 m_5c); 5 callers; retail order 40/44/48/58/5C/4C/50/54.
#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Rva00573B23
{
public:
	Rva00573B23();
	virtual ~Rva00573B23();
private:
	char m_pad04[0x40 - 0x04];
};

class Rva00573E7C : public Rva00573B23
{
public:
	Rva00573E7C();
	virtual ~Rva00573E7C();
private:
	Coord3DBase m_40;
	float m_4c;
	int m_50;
	bool m_54;
	char m_pad55[0x58 - 0x55];
	unsigned int m_58;
	unsigned int m_5c;
};

Rva00573E7C::Rva00573E7C()
{
	m_40.x = 0.0f;
	m_40.y = 0.0f;
	m_40.z = 0.0f;
	_ReadWriteBarrier();
	m_58 = 0;
	m_5c = 0;
	m_4c = 0.0f;
	m_50 = 1;
	m_54 = true;
}
