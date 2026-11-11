// cl: /MD
//
// ?xfer@SpecialPowerCompletionDie@@MAEXPAVXfer@@@Z, retail 0x00486AC2 63B: slot-3 xfer of vtable 0x0084AE88
// (class of dtor ??1SpecialPowerCompletionDie@@MAE@XZ 0x004869FC, defined in SpecialPowerCompletionDie.cpp;
// rowed ctor 0x00486A74, rowed setCreator 0x00486A1B and pool key 0x00486A2F prove SpecialPowerCompletionDie).
// Base DieModule xfer via rowed 0x004CE56D then IsLightCRC early-out via Xfer slot 0x10
// then Version1 via rowed 0x000053EE then ObjectID at +0x14 via rowed XferObjectID 0x003060B2
// then bool at +0x18 via Xfer slot 0x90. Layout is DieModule base 0x14 giving +0x14 start
// (cf. rowed ctor zeroing +0x14 and byte +0x18). ZH donor SpecialPowerCompletionDie.cpp
// proves the ObjectID-plus-bool shape; BFME2 adds the IsLightCRC guard and base-first order
// (cf. CreateModule xfer precedent).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva004CE56D
{
public:
	virtual void baseAnchor();
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x14 - 4];
};

class SpecialPowerCompletionDie : public Rva004CE56D
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_creatorID;
	bool m_creatorSet;
};

void SpecialPowerCompletionDie::xfer(Xfer *xfer)
{
	Rva004CE56D::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	XferObjectID(xfer, &m_creatorID);
	*xfer == m_creatorSet;
}
