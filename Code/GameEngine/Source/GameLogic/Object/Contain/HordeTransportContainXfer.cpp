// cl: /DNDEBUG /MD /GX
// ?xfer@HordeTransportContain@@MAEXPAVXfer@@@Z, retail 0x0047714A, 59 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00845EB8 (class of
// ??0HordeTransportContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// HordeTransportContainCtor.cpp). Version1 via rowed 0x000053EE then
// rowed TransportContain::xfer 0x00466DBC then int at +0x120 via Xfer
// slot 0x7c and bool at +0x124 via Xfer slot 0x90 (same slots as
// TransportContain::xfer uses for int at +0x100 and bool at +0x10C).
// Layout from HordeTransportContainCtor (int -1000 at +0x120 and zero
// byte at +0x124); Xfer declaration copied verbatim from
// TransportContainXfer.cpp per xfer recipe.
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

#include "../../../../Include/Common/BfmeXfer.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class Object;
class DamageInfo;
class Xfer;
struct Rva0047727EObjectPositionView;
enum NameKeyType { NK_UNKNOWN = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum ExitDoorType { DOOR_1 = 0 };

class OpenContain {
public:
	virtual void exitObjectViaDoor(Object *,ExitDoorType);
protected:
	virtual void xfer(Xfer *xfer);
};

class TransportContain : public OpenContain {
public:
	virtual ~TransportContain();
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
};

// Retail stores no HordeTransportContain vptr (novtable): its dtor is a
// bare jmp to the TransportContain base dtor.
class __declspec(novtable) HordeTransportContain : public TransportContain {
public:
	virtual ~HordeTransportContain();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onDie(const DamageInfo *damageInfo);
	virtual void exitObjectViaDoor(Object *,ExitDoorType);
	void rva004779F9();
	void rva0047778B();
	void rva004776E7(const struct Rva004776E7UpgradeMask *,bool);
	void rva0047727E(Thing *object);
	void rva0047748E();
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char prefix04[4];
	Rva0047727EObjectPositionView *m_object;
};

// Saved state past the TransportContain base (offsets from the ctor's
// stores: int -1000 at +0x120, zero byte at +0x124), read through a view so
// the class keeps the shared polymorphic declaration.
struct HordeTransportContainXferView
{
	char m_unrecovered00[ 0x120 ];
	Int m_int120;
	Bool m_bool124;
};

void HordeTransportContain::xfer( Xfer *xfer )
{
	HordeTransportContainXferView *view = (HordeTransportContainXferView *)this;
	xfer->Version1();
	TransportContain::xfer( xfer );
	*xfer == view->m_int120;
	*xfer == view->m_bool124;
}
