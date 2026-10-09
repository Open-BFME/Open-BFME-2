// cl: /MD /ICode/Libraries/Include/Lib
// Two Rva003AF7FE slots (vtable 0x0081C7EC, ??_7Rva003AF7FE@@6B
// ModuleInfoHeadBase@@@; rowed copy ctor ??0Rva003AF7FE@@QAE@ABV0@@Z with its
// line-volume info base). Both are shared with the same slots of 0x0081CBE4
// and of the derived Rva003AF7D1 (0x0081D094). Method names stay address-
// derived; the Xfer slot names follow the BFME 2 views already rowed
// (xferCoord3D +0x60 and xferBool +0x90 as in TerrainLogicXfer.cpp, xferReal
// +0x70 as in xferRandomVariable.cpp).
#include "Coord3D.h"

class Xfer
{
public:
	virtual void r0();
	virtual void r1();
	virtual void r2();
	virtual void r3();
	virtual void r4();
	virtual void r5();
	virtual void r6();
	virtual void r7();
	virtual void r8();
	virtual void r9();
	virtual void r10();
	virtual void r11();
	virtual void r12();
	virtual void r13();
	virtual void r14();
	virtual void r15();
	virtual void r16();
	virtual void r17();
	virtual void r18();
	virtual void r19();
	virtual void r20();
	virtual void r21();
	virtual void r22();
	virtual void r23();
	virtual void xferCoord3D(Coord3D *value);	// +0x60
	virtual void r25();
	virtual void r26();
	virtual void r27();
	virtual void xferReal(float *value);		// +0x70
	virtual void r29();
	virtual void r30();
	virtual void r31();
	virtual void r32();
	virtual void r33();
	virtual void r34();
	virtual void r35();
	virtual void xferBool(bool *value);		// +0x90

	void Version1();
};

class Rva003AF7FE
{
public:
	virtual ~Rva003AF7FE();
	virtual void rva0055D616();
	virtual void s02();

protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[0x20 - 4];
	bool m_flag20;
	float m_real24;
	float m_real28;
	float m_real2C;
	Coord3D m_coord30;
};

// ?rva0055D616@Rva003AF7FE@@UAEXXZ retail 0x0055D616 34 bytes, slot 1: adds
// +0x28 to +0x24 and keeps the sum at least 0.1.
void Rva003AF7FE::rva0055D616()
{
	m_real24 += m_real28;
	if (m_real24 < 0.1f)
		m_real24 = 0.1f;
}

// ?xfer@Rva003AF7FE@@MAEXPAVXfer@@@Z retail 0x0055D638 78 bytes, slot 3:
// Version1, the bool at +0x20, three Reals at +0x24/+0x28/+0x2C and the
// Coord3D at +0x30. No base call.
void Rva003AF7FE::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->xferBool(&m_flag20);
	xfer->xferReal(&m_real24);
	xfer->xferReal(&m_real28);
	xfer->xferReal(&m_real2C);
	xfer->xferCoord3D(&m_coord30);
}
