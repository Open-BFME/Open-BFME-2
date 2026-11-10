// cl: /DNDEBUG /MD
//
// ?xfer@SiegeDeployHordeSpecialPower@@MAEXPAVXfer@@@Z, retail 0x004C6416, 92 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0085DD94 (class of rowed ctor
// ??0SiegeDeployHordeSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at 0x004C6386
// and rowed dtor ??1SiegeDeployHordeSpecialPower@@UAE@XZ at 0x004C63EF).
// Base Rva00589079 xfer via rowed 0x00589215 then IsLightCRC early-out via
// Xfer slot 0x10 then Version(1,2) via Xfer slot 0x28 then ObjectID at +0x38
// via rowed XferObjectID 0x003060B2 plus Coord at +0x3C via Xfer slot 0x60
// plus version-gated int at +0x48 via Xfer slot 0x7C. Layout is the rowed
// 0x4C-byte class from SiegeDeployHordeSpecialPowerCtor.cpp (Rva00589079 base
// 0x38 plus ObjectID plus Vector3 plus int; +0x3C is the Vector3 copied by
// rowed vslot14 0x004C63DE). Donor pattern is LargeGroupBonusUpdateXfer plus
// InvisibilityUpdateXfer (IsLightCRC plus Version(1,2) plus gated tail).

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


#include "../../../../Include/Common/Rva00589079_E1.h"

class Rva00589079_E2
{
public:
	virtual void fe();
};

class Rva00589079 : public UpdateModule, public Rva00589079_E1, public Rva00589079_E2
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_28;
	int m_2C;
	unsigned int m_30;
	float m_34;
};

class SiegeDeployHordeSpecialPower : public Rva00589079
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_38;
	Coord3DBase m_3C;
	int m_48;
};

void SiegeDeployHordeSpecialPower::xfer(Xfer *xfer)
{
	Rva00589079::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	XferObjectID(xfer, &m_38);
	*xfer == m_3C;
	if (version.m_minimum >= 2) {
		*xfer == m_48;
	}
}
