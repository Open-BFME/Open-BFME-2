// cl: /MD
// ?xfer@DefaultUpdateModuleInfo@FXParticleSystem@@UAEXPAVXfer@@@Z, retail 0x0055F67C, 148 bytes.
// Evidence: vtable slot 3 of 0x0081BCE0 (DefaultUpdateModuleInfo) DoXfer;
//   8 GameClientRandomVariable plus rotation-typed extra at +0x40.

#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
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

class Xfer::Version
{
public:
	unsigned char current;
	unsigned char minimum;
};

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);
void XferRotationType(Xfer *xfer, int *value);

namespace FXParticleSystem
{

class DefaultUpdateModuleInfo : public Snapshot
{
public:
	DefaultUpdateModuleInfo();
	virtual ~DefaultUpdateModuleInfo();
	// Complete the canonical Snapshot contract for the embedded info below.
	// This TU owns only transfer bodies; the other slots remain out of line.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void xfer(Xfer *xfer);
private:
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	GameClientRandomVariable m_var3;
	GameClientRandomVariable m_var4;
	int m_extra;
	GameClientRandomVariable m_var5;
	GameClientRandomVariable m_var6;
	GameClientRandomVariable m_var7;
};

}

void FXParticleSystem::DefaultUpdateModuleInfo::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	union Ver { int i; Xfer::Version value; } ver;
	ver.value.current = 1;
	ver.value.minimum = 2;
	*xfer == ver.value;
	xferRandomVariable(*xfer, m_var0);
	xferRandomVariable(*xfer, m_var1);
	xferRandomVariable(*xfer, m_var2);
	xferRandomVariable(*xfer, m_var3);
	xferRandomVariable(*xfer, m_var4);
	XferRotationType(xfer, &m_extra);
	if (ver.value.minimum < 2)
		return;
	xferRandomVariable(*xfer, m_var5);
	xferRandomVariable(*xfer, m_var6);
	xferRandomVariable(*xfer, m_var7);
}

class Rva0055F710
{
public:
	virtual void rva0055F710(Xfer *xfer);
private:
	unsigned char m_pad[0x18];
	FXParticleSystem::DefaultUpdateModuleInfo m_info;
};

void Rva0055F710::rva0055F710(Xfer *xfer)
{
	xfer->Version1();
	m_info.FXParticleSystem::DefaultUpdateModuleInfo::xfer(xfer);
}

namespace FXParticleSystem
{
class DefaultPhysicsModuleInfoX
{
public:
	virtual void xfer(Xfer *xfer);
};
}

class Rva0055F76C
{
public:
	virtual void xfer(Xfer *xfer);
private:
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	int m_1c;
	float m_angleXY;
	float m_angularRateXY;
	float m_angularDampingXY;
};

void Rva0055F76C::xfer(Xfer *xfer)
{
	union Ver { int i; Xfer::Version value; } ver;
	ver.value.current = 1;
	ver.value.minimum = 2;
	*xfer == ver.value;
	*xfer == m_04;
	*xfer == m_08;
	*xfer == m_0c;
	*xfer == m_10;
	*xfer == m_14;
	*xfer == m_18;
	XferRotationType(xfer, &m_1c);
	if (ver.value.minimum < 2)
		return;
	*xfer == m_angleXY;
	*xfer == m_angularRateXY;
	*xfer == m_angularDampingXY;
}

class Rva0055F805
{
public:
	virtual void rva0055F805(Xfer *xfer);
private:
	unsigned char m_pad[0x08];
	Rva0055F76C m_info;
};

void Rva0055F805::rva0055F805(Xfer *xfer)
{
	xfer->Version1();
	m_info.Rva0055F76C::xfer(xfer);
}
