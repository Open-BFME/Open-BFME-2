// cl: /O1 /MD
//
// ?xfer@Rva004CC63A@@MAEXPAVXfer@@@Z, retail 0x004CC72C, 105 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x0085F5A0 (class of rowed dtor
// ??1Rva004CC63A@@UAE@XZ in Rva0024A797Derived.cpp): Version(1,3) via Xfer
// slot 0x28 first then base UpdateModule xfer via rowed 0x44DF9F then two
// uints at +0x20/+0x24 via Xfer slot 0x78 with version-gated second uint
// (>=2 else IsLoading-zero) then ObjectID at +0x28 via rowed XferObjectID
// 0x3060B2 gated >=3. Layout is UpdateModule base 0x20. Identity is slot 3
// plus the UpdateModule base call; class name stays honest Rva address name.

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

class Rva004CC63A : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_20;
	unsigned int m_24;
	ObjectID m_28;
};

void Rva004CC63A::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	UpdateModule::xfer(xfer);
	*xfer == m_20;
	if (version.m_minimum >= 2) {
		*xfer == m_24;
	} else {
		if (xfer->IsLoading())
			m_24 = 0;
	}
	if (version.m_minimum >= 3) {
		XferObjectID(xfer, &m_28);
	}
}
