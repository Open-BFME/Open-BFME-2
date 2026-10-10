// ?rva002C58B3@Rva002C589B@@QAEXXZ
// partial score=0.985 date=2026-10-10
// ?rva002C58B3@Rva002C589B@@QAEXXZ
// partial score=0.95 date=2026-09-29
// ?rva002C58B3@Rva002C589B@@QAEXXZ
// partial score=0.95 date=2026-09-29
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva002C58B3@Rva002C589B@@QAEXXZ @0x002C58B3 92B
// Reset method of Rva002C589B (layout from Rva002C589BDtor.cpp): int at +8 to
// -1, floats at +0xC/+0x10/+0x14 to 0, bytes at +0x18/+0x19 and int at +0x1C
// to 0, 12 zero bytes at m_ptr+0x554 via Vec3 temp copy, rowed clear
// 0x003ECB0B on m_ptr, int at +0x34 to 0. Caller 0x002C5D02.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Vec3 { float x, y, z; };
class Rva003ECB0BDwordClearer {
public:
	void clear();
	char m_pad[0x554];
	Vec3 m_vec;
};
class Rva002C589B {
private:
	char m_pad[8];
	int m_08;
	float m_0C, m_10, m_14;
	bool m_18, m_19;
	char m_pad1A[2];
	int m_1C;
	char m_pad20[4];
	Rva003ECB0BDwordClearer *m_ptr;
	char m_pad28[12];
	int m_34;
public:
	void rva002C58B3();
};
void Rva002C589B::rva002C58B3()
{
	m_08 = -1;
	m_1C = 0;
	m_19 = 0;
	m_18 = 0;
	m_0C = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	_ReadWriteBarrier();
	Vec3 tmp = { 0.0f, 0.0f, 0.0f };
	m_ptr->m_vec = tmp;
	m_ptr->clear();
	m_34 = 0;
}
