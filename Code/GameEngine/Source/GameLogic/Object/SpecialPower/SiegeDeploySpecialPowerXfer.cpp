// cl: /DNDEBUG /MD
//
// ?xfer@SiegeDeploySpecialPower@@MAEXPAVXfer@@@Z, retail 0x004C5B39, 170 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0085DCFC (class of rowed ctor
// ??0SiegeDeploySpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at 0x004C56BA).
// Base Rva00589079 xfer via rowed 0x00589215 then IsLightCRC early-out via
// Xfer slot 0x10 then Version(1,2) via Xfer slot 0x28 then int at +0x38 via
// XferRawBytes slot 0x24 then int at +0x3C via Xfer slot 0x78 then ObjectIDs
// at +0x40/+0x44 via rowed XferObjectID 0x003060B2 plus float at +0x48 via
// Xfer slot 0x60 plus bools at +0x70/+0x60 via Xfer slot 0x90 plus
// version-gated floats at +0x54/+0x64 via Xfer slot 0x60. Layout is the rowed
// 0x74-byte class from SiegeDeploySpecialPowerCtor.cpp (Rva00589079 base
// 0x38 plus ints/ObjectIDs/floats/bools). Donor pattern is
// SiegeDeployHordeSpecialPowerXfer plus DeflectSpecialPowerXfer (IsLightCRC
// plus Version plus gated tail).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"
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

#include "../../../../Include/Common/XferVersion.h"

#include "../../../Common/GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class Rva00589079_E1
{
public:
	virtual void fe();
};

class Rva00589079_E2
{
public:
	virtual void fe();
};

class Rva00589079 : public UpdateModule, public Rva00589079_E1, public Rva00589079_E2
{
	friend class SiegeDeploySpecialPower;
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_28;
	int m_2C;
	unsigned int m_30;
	float m_34;
};

class SiegeDeploySpecialPower : public Rva00589079
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_phase;
	unsigned int m_frame;
	ObjectID m_dockID;
	ObjectID m_44;
	Coord3DBase m_48;
	Coord3DBase m_approachPoint;
	bool m_docked;
	char m_pad61[3];
	Coord3DBase m_dockPosition;
	bool m_stop;
};

void SiegeDeploySpecialPower::xfer(Xfer *xfer)
{
	((Rva00589079 *)this)->Rva00589079::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	xfer->XferRawBytes(&m_phase, 4);
	*xfer == m_frame;
	XferObjectID(xfer, &m_dockID);
	XferObjectID(xfer, &m_44);
	*xfer == m_48;
	*xfer == m_stop;
	*xfer == m_docked;
	if (version.m_minimum >= 2) {
		*xfer == (Coord3DBase &)m_approachPoint;
		*xfer == (Coord3DBase &)m_dockPosition;
	}
}
