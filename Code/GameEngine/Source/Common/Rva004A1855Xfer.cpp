// cl: /MD
//
// ?xfer@Rva004A1855@@MAEXPAVXfer@@@Z, retail 0x004A1B54, 169 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00851F1C (class of rowed dtor
// ??1Rva004A1855@@UAE@XZ in Rva0024A797Grandchildren.cpp): base UpdateModule
// xfer via rowed 0x0044DF9F then IsLightCRC early-out via Xfer slot 0x10
// then Version(1,3) via Xfer slot 0x28 then ObjectID at +0x24 via rowed
// XferObjectID 0x003060B2 then Coord3DBase at +0x28 via Xfer slot 0x60 then
// int at +0x34 via Xfer slot 0x7C then 4 raw bytes at +0x38 via XferRawBytes
// slot 0x24 then bool at +0x3C via Xfer slot 0x90 then version>=2 ObjectID
// at +0x40 via rowed 0x003060B2 then version>=3 bools at +0x44/+0x45 via
// Xfer slot 0x90. Layout is UpdateModule base 0x20 plus E1 vptr at +0x20
// giving +0x24 start (cf. rowed dtor four vptrs). Identity is slot 3 plus
// the UpdateModule base call; class name stays honest Rva address name.

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
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
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class Rva004A1855_E1
{
public:
	virtual void fe();
};

class Rva004A1855 : public UpdateModule, public Rva004A1855_E1
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_24;
	Coord3DBase m_28;
	int m_34;
	unsigned int m_38raw;
	bool m_3C;
	ObjectID m_40;
	bool m_44;
	bool m_45;
};

void Rva004A1855::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 3);
	*xfer == version;
	XferObjectID(xfer, &m_24);
	*xfer == m_28;
	*xfer == m_34;
	xfer->XferRawBytes(&m_38raw, 4);
	*xfer == m_3C;
	if (version.m_minimum >= 2) {
		XferObjectID(xfer, &m_40);
	}
	if (version.m_minimum >= 3) {
		*xfer == m_44;
		*xfer == m_45;
	}
}
