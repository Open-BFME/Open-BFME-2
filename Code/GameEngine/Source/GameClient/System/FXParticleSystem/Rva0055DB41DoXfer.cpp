// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?DoXfer@Rva0055DB41@@UAEXAAVXfer@@@Z, retail 0x0055DB41 (146 bytes): the
// Snapshot DoXfer slot shared by three FX particle module tables (0x0081C6E8,
// 0x0081D0C8, 0x0081D798 minus the slot), placed after the lightning emission
// template parsers. Version 1 (rowed 0x000053EE), two Coord3D fields (+0x24,
// +0x30, Xfer slot 0x60 as in ParticleSystemInfo::DoXfer) and nine
// GameClientRandomVariables (+0x3C..+0x9C, rowed xferRandomVariable). The
// Xfer view is ParticleSystemInfoDoXfer.cpp's; owner name address-derived.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
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
class Rva0055DB41SnapshotView;

#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"

class Snapshot;
#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"


#include "../../../../Include/GameClient/GameClientRandomVariable.h"

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &v);

class Rva0055DB41SnapshotView
{
public:
	virtual ~Rva0055DB41SnapshotView() {}
	virtual const char *GetSnapshotName() = 0;
	virtual void LoadPostProcess() = 0;
	virtual void DoXfer(Xfer &xfer) = 0;
};

class Rva0055DB41 : public Rva0055DB41SnapshotView
{
public:
	virtual void DoXfer(Xfer &xfer);
private:
	unsigned char m_pad04[0x24 - 0x04];
	Coord3DBase m_24;
	Coord3DBase m_30;
	GameClientRandomVariable m_3C;
	GameClientRandomVariable m_48;
	GameClientRandomVariable m_54;
	GameClientRandomVariable m_60;
	GameClientRandomVariable m_6C;
	GameClientRandomVariable m_78;
	GameClientRandomVariable m_84;
	GameClientRandomVariable m_90;
	GameClientRandomVariable m_9C;
};

void Rva0055DB41::DoXfer(Xfer &xfer)
{
	xfer.Version1();
	xfer == m_24;
	xfer == m_30;
	xferRandomVariable(xfer, m_3C);
	xferRandomVariable(xfer, m_48);
	xferRandomVariable(xfer, m_54);
	xferRandomVariable(xfer, m_60);
	xferRandomVariable(xfer, m_6C);
	xferRandomVariable(xfer, m_78);
	xferRandomVariable(xfer, m_84);
	xferRandomVariable(xfer, m_90);
	xferRandomVariable(xfer, m_9C);
}
