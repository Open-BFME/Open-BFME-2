// cl: /O1 /DNDEBUG /MD /arch:SSE
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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

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

class SiegeDeploySpecialPower : public Rva00589079
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_38;
	unsigned int m_3C;
	ObjectID m_40;
	ObjectID m_44;
	Coord3DBase m_48;
	Coord3DBase m_54;
	bool m_60;
	char m_pad61[3];
	Coord3DBase m_64;
	bool m_70;
};

void SiegeDeploySpecialPower::xfer(Xfer *xfer)
{
	Rva00589079::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	xfer->XferRawBytes(&m_38, 4);
	*xfer == m_3C;
	XferObjectID(xfer, &m_40);
	XferObjectID(xfer, &m_44);
	*xfer == m_48;
	*xfer == m_70;
	*xfer == m_60;
	if (version.m_minimum >= 2) {
		*xfer == m_54;
		*xfer == m_64;
	}
}
