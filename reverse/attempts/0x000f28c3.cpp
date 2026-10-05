// ?rva000F28C3@Rva000F28C3Holder@@QAEXXZ
// partial score=0.975 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE2
//
// ?rva000F28C3@Rva000F28C3Holder@@QAEXXZ at 0x000F28C3, 160 bytes.
// Lazy polygon-buffer build: when m_polys (+0x10) is still null, fill it
// either from the shared DynamicVectorClass at 0x00DEBE24 (flag +0x30 set:
// grow it with rowed Resize 0x000F0CF9 when its count trails, then borrow
// its Vector at 0x00DEBE28) or from a fresh new Poly[count] (array-ctor
// iterator), then per-polygon fill through 0x000F1D24 single-caller pin,
// and publish the buffer. Mirrors Rva000F1A32Ctor.cpp (same globals,
// devirtualized Resize) and the VectorClass<Vector3> twin ctor 0x000F0D2F
// (same new-T[n] plus iterator shape, 12-byte stride).
#include <new.h>

struct Rva000F28C3Poly
{
	Rva000F28C3Poly();
	float m_00;
	int m_04;
	int m_08;
};

class TCBSpline3DClass
{
public:
	class TCBClass;
};
class TCBSpline3DClass::TCBClass
{
	char _b[1];
};

template <class T> class DynamicVectorClass
{
public:
	virtual bool Resize(int len, const T *items);
};

extern DynamicVectorClass<TCBSpline3DClass::TCBClass> g_00DEBE24;
extern int g_00DEBE2C;
extern Rva000F28C3Poly *g_00DEBE28;

// g_00DEBE24/g_00DEBE2C/g_00DEBE28: matched references place them at VAs
// 0xdebe24/0xdebe2c/0xdebe28 (zero-filled .bss); defined here after the
// Rva000F1A32Ctor.cpp neighboring pattern so this TU's references resolve.
DynamicVectorClass<TCBSpline3DClass::TCBClass> g_00DEBE24;
int g_00DEBE2C;
Rva000F28C3Poly *g_00DEBE28;

class Rva000F28C3Holder
{
public:
	void rva000F28C3();
	void rva000F1D24(int index, Rva000F28C3Poly *elem);
private:
	char m_pad00[0x10];
	Rva000F28C3Poly *m_polys; // +0x10
	char m_pad14[8]; // +0x14
	int m_polyCount; // +0x1C
	char m_pad20[0x10]; // +0x20
	char m_flag30; // +0x30
};

void Rva000F28C3Holder::rva000F28C3()
{
	if (m_polys != 0)
		return;
	Rva000F28C3Poly *buf;
	if (m_flag30 != 0) {
		if (g_00DEBE2C < m_polyCount)
			g_00DEBE24.Resize(m_polyCount, 0);
		buf = g_00DEBE28;
	} else {
		buf = new Rva000F28C3Poly[m_polyCount];
	}
	for (int i = 0; i < m_polyCount; i++)
		rva000F1D24(i, &buf[i]);
	m_polys = buf;
}
