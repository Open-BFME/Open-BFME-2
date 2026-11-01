// cl: /MD
// ?xfer@RespawnUpdate@@MAEXPAVXfer@@@Z @0x004AF00B (139B): slot 3 xfer via
// Version(1,1) slot 0x28 then base UpdateModule 0x0044DF9F plus helpers
// XferRespawnModeType 0x003060FA XferObjectID 0x003060B2 plus int at
// +0x34/+0x38/+0x3C via slot 0x7C plus bool at +0x40/+0x41 via slot 0x90
// plus float at +0x20 via slot 0x70. Layout from RespawnUpdateCtor (base
// 0x20 plus float 0x20 ints 0x24-0x3C bools 0x40-0x41). Recipe is the
// Rva003A4CAE Version-plus-base xfer with reverse-overload slots (uint
// 0x78 float 0x70 int 0x7C bool 0x90).
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

#include "../../../../Include/Common/XferVersion.h"

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, unsigned int frame);
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

enum ObjectID;
void __cdecl XferRespawnModeType(Xfer *x, int *v);
void __cdecl XferObjectID(Xfer *x, ObjectID *v);

class RespawnUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	bool m_40;
	bool m_41;
};

void RespawnUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	XferRespawnModeType(xfer, &m_2c);
	XferObjectID(xfer, (ObjectID *)&m_30);
	*xfer == m_34;
	*xfer == m_38;
	*xfer == m_40;
	*xfer == m_3c;
	*xfer == m_20;
	*xfer == m_41;
}
