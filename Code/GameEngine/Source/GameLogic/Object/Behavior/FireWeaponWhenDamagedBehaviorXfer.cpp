// cl: /O1 /MD
//
// ?xfer@FireWeaponWhenDamagedBehavior@@MAEXPAVXfer@@@Z, retail 0x004A4EE9,
// 137 bytes. Slot 3 (offset 0x0C) of vtable 0x00852868 (class of rowed dtor
// ??1Rva004A4C19@@UAE@XZ in Rva0024A797Grandchildren.cpp with real-name pin
// ??1FireWeaponWhenDamagedBehavior@@UAE@XZ at 0x004A4C19; same primary as
// reloc-named ctor 0x004A4CC7 and deleting dtor 0x004A4D54). Base
// UpdateModule xfer via rowed 0x0044DF9F then IsLightCRC early-out via Xfer
// slot 0x10 then Version(1,2) via Xfer slot 0x28 reusing [ebp+8] then uint
// at +0x24 and uint at +0x28 via Xfer slot 0x78 plus 4 raw bytes at +0x2C
// via Xfer slot 0x24 plus float at +0x30 and float at +0x34 via Xfer slot
// 0x70 plus Coord3DBase at +0x3C via Xfer slot 0x60 plus version-gated float
// at +0x38 via Xfer slot 0x70. Layout is UpdateModule base 0x20 plus
// trailing vptr at +0x20 giving +0x24 start; member names are neutral
// (retail diverges from the BFME1 weapon donor which carries eight Weapon*
// plus UpgradeMux). Recipe is the Rva version-gated slot-3 pattern.

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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

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

class FireWeaponTrailing { public: virtual void trailingSlot(); };

class FireWeaponWhenDamagedBehavior : public UpdateModule, public FireWeaponTrailing
{
public:
	FireWeaponWhenDamagedBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	float m_30;
	float m_34;
	float m_38;
	Coord3DBase m_3C;
};

void FireWeaponWhenDamagedBehavior::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_24;
	*xfer == m_28;
	xfer->XferRawBytes(&m_2C, 4);
	*xfer == m_30;
	*xfer == m_34;
	*xfer == m_3C;
	if (version.m_minimum >= 2) {
		*xfer == m_38;
	}
}
