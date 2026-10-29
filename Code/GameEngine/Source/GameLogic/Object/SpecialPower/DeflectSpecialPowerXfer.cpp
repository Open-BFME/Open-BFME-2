// cl: /DNDEBUG /MD
//
// ?xfer@DeflectSpecialPower@@MAEXPAVXfer@@@Z, retail 0x004C5571, 65 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0085DA7C (class of rowed ctor
// ??0DeflectSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z in
// DeflectSpecialPowerConstructorThunk.cpp). Base Rva00589079 xfer via rowed
// 0x00589215 then IsLightCRC early-out via Xfer slot 0x10 then Version1 via
// rowed 0x000053EE then bytes at +0x3C/+0x3D via Xfer slot 0x90. Layout is
// Rva00589079 base 0x38 plus pad to +0x3C plus two bytes (cf. rowed ctor
// zeroes m_byte3C/m_byte3D). Donor pattern is SiegeDeployHordeSpecialPowerXfer
// (IsLightCRC plus Version plus gated tail).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
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

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

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
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_28;
	int m_2C;
	unsigned int m_30;
	float m_34;
};

class DeflectSpecialPower : public Rva00589079
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_pad38;
	bool m_byte3C;
	bool m_byte3D;
	char m_pad3E[2];
};

void DeflectSpecialPower::xfer(Xfer *xfer)
{
	Rva00589079::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_byte3C;
	*xfer == m_byte3D;
}
