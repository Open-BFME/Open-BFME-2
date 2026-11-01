// cl: /DNDEBUG /MD
//
// ?xfer@MonsterDockUpdate@@MAEXPAVXfer@@@Z, retail 0x004A14C2, 85 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00851D74 (class of rowed ctor
// ??0MonsterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at 0x004A139A in
// MonsterDockUpdateCtor.cpp): base DockUpdate xfer via rowed 0x0058A410
// then IsLightCRC early-out via Xfer slot 0x10 then bool at +0x88 via Xfer
// slot 0x90 then int at +0x8C via Xfer slot 0x7C then bool at +0x89 via Xfer
// slot 0x90 then Version1 via rowed 0x000053EE last. Layout is DockUpdate
// base 0x88 plus two bools plus int (BFME1 donor
// MonsterDockUpdateConstructor.cpp: bool m_flag88 plus bool m_flag89 plus
// int m_value8c; ctor sets 1/0/0). Donor is BFME1 plus ZH.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"
class ICoord3D;
class Region3D;
class IRegion3D;
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
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

class __declspec(novtable) DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x88 - 4];
};

class MonsterDockUpdate : public DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_flag88;
	bool m_flag89;
	int m_value8C;
};

void MonsterDockUpdate::xfer(Xfer *xfer)
{
	DockUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_flag88;
	*xfer == m_value8C;
	*xfer == m_flag89;
	xfer->Version1();
}
