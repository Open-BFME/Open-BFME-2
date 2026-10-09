// cl: /MD /ICode/Libraries/Include/Lib
// ?xfer@BoxEmissionVolumeModule@FXParticleSystem@@MAEXPAVXfer@@@Z
// retail 0x0055CFC3, 45 bytes: slot 3 (offset 0x0C) of the class's vtable
// 0x0081C784 (??_7BoxEmissionVolumeModule@FXParticleSystem@@6B
// DefaultModuleHeadBase@@@), whose slot 7 is the rowed box sample 0x0055D0D5
// over the same hollow flag (+0x20) and extents (+0x24). Version1, then the
// flag through xferBool (+0x90) and the extents through xferCoord3D (+0x60),
// the BFME 2 Xfer slots TerrainLogicXfer.cpp names. No base call.
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
	virtual void r28();
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

namespace FXParticleSystem
{

class BoxEmissionVolumeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad04[0x20 - 4];
	bool m_isHollow;		// +0x20
	Coord3D m_halfSize;		// +0x24
};

void BoxEmissionVolumeModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->xferBool(&m_isHollow);
	xfer->xferCoord3D(&m_halfSize);
}

}
