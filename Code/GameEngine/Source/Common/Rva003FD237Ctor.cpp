// cl: /O1 /arch:SSE /G7 /MD /Oy- /Ob1 /GX- -DNDEBUG
// ??0Rva003FD2C2@@QAE@IPBUCoord3D@@MID@Z @0x003FD237 71B: constructor of the class
// whose vtable is 0x007FE058 (Xfer slot 0x003FD2C2, slot 4 0x003FD27E): pinned base
// ctor 0x003FD199, own vtable, the Coord at +0x0C copied dword-wise, the float at
// +0x18 and the unsigned*0.03f scaled value (static 0x00503E4F, arg in EAX) at
// +0x1C. Layout from the rowed Rva003FD2C2Xfer.cpp / Rva003FD27E.cpp. No /EHsc:
// retail carries no unwind state here.
static unsigned rva003BB860Scale(unsigned w)
{
	return (int)((float)w * 0.03f);
}

#include "../../../Libraries/Include/Lib/Coord3D.h"

class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned w, char f);
	virtual ~BfmeBaseVNH();
	virtual void handle();

	unsigned m_bfme04;
	char m_bfme08;
};

class Rva003FD2C2 : public BfmeBaseVNH
{
public:
	Rva003FD2C2(unsigned w, const Coord3D *pos, float angle, unsigned x, char f);
	virtual ~Rva003FD2C2();
	Coord3D m_pos;		// +0x0C
	float m_angle;		// +0x18
	unsigned m_scaled;	// +0x1C
};

Rva003FD2C2::Rva003FD2C2(unsigned w, const Coord3D *pos, float angle, unsigned x, char f)
	: BfmeBaseVNH(w, f)
{
	m_pos.x = pos->x;
	m_pos.y = pos->y;
	m_pos.z = pos->z;
	m_angle = angle;
	m_scaled = rva003BB860Scale(x);
}
