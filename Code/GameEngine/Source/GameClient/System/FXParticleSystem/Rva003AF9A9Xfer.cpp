// cl: /MD
// ?xfer@Rva003AF9A9@@MAEXPAVXfer@@@Z retail 0x0055E5F6 64 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0081C81C (??_7Rva003AF9A9@@6B
// DefaultModuleHeadBase@@@, class of rowed copy ctor ??0Rva003AF9A9@@QAE@ABV0@@Z;
// ICF-shared with slot 3 of 0x0081CC10 and 0x0081D0F8): Version1, three
// GameClientRandomVariable members at +0x24/+0x30/+0x3C through the rowed
// xferRandomVariable 0x00306183, then the Real at +0x48 through Xfer slot 28
// (xferReal, as in xferRandomVariable.cpp). No base call. Precedent:
// Rva003AF22EXfer.cpp.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

// The two tables (data ledger): DefaultModuleHeadBase at +0 and the
// TerrainFireEmissionInfo table at +0x1C, both with xfer in slot 3; slot 3 of
// the second is the this-adjusting (sub ecx, 0x1C) thunk 0x003AC178.
class Rva003AF9A9HeadView
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
protected:
	virtual void xfer(Xfer *xfer) = 0;
private:
	char m_unmodelled04[0x1C - 0x04];
};

class Rva003AF9A9InfoView
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
protected:
	virtual void xfer(Xfer *xfer) = 0;
private:
	char m_unmodelled20[0x24 - 0x20];
};

struct EmitVtableTag;

class Rva003AF9A9 : public Rva003AF9A9HeadView, public Rva003AF9A9InfoView
{
public:
	Rva003AF9A9(EmitVtableTag *);
	GameClientRandomVariable m_var24;
	GameClientRandomVariable m_var30;
	GameClientRandomVariable m_var3C;
	float m_real48;

protected:
	virtual void xfer(Xfer *xfer);
};

void Rva003AF9A9::xfer(Xfer *xfer)
{
	xfer->Version1();
	xferRandomVariable(*xfer, m_var24);
	xferRandomVariable(*xfer, m_var30);
	xferRandomVariable(*xfer, m_var3C);
	*xfer == m_real48;
}

// Tag constructor with no retail counterpart: it only makes this TU emit the
// class's tables and with them the xfer thunk.
// ?<Rva003AF9A9::Rva003AF9A9> absent-from-retail
Rva003AF9A9::Rva003AF9A9(EmitVtableTag *)
{
}
