// cl: /O1 /DNDEBUG /MD
//
// ?xfer@AIGateUpdate@@MAEXPAVXfer@@@Z, retail 0x004B095C, 139 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00856480 (class of rowed ctor
// ??0AIGateUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at 0x004B08E8):
// Version(1,2) via Xfer slot 0x28 then base UpdateModule xfer via rowed
// 0x44DF9F then bool at +0x31 via 0x90 then int at +0x28 via 0x7C then int
// at +0x2C via 0x7C then bool at +0x30 via 0x90 then int at +0x24 via 0x7C
// then IsLoading clear of +0x30 then version-gated int global at 0xA03D80
// via 0x7C. Layout is UpdateModule base 0x20 plus members per rowed ctor.

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

int Rva00A03D80;

class AIGateUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	bool m_30;
	bool m_31;
};

void AIGateUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	*xfer == m_31;
	*xfer == m_28;
	*xfer == m_2c;
	*xfer == m_30;
	*xfer == m_24;
	if (xfer->IsLoading()) {
		m_30 = false;
	}
	if (version.m_minimum >= 2) {
		*xfer == Rva00A03D80;
	}
}
