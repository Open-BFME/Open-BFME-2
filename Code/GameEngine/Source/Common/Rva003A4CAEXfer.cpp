// cl: /O1 /MD
//
// ?xfer@Rva003A4CAE@@MAEXPAVXfer@@@Z, retail 0x003A4DC0, 154 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x0081B164 (class of rowed dtor
// ??1Rva003A4CAE@@UAE@XZ in Rva0024A797Derived.cpp): Version(1,3) via Xfer
// slot 0x28 then base UpdateModule xfer via rowed 0x0044DF9F then IsLightCRC
// early-out via Xfer slot 0x10 then version>=2 coords at +0x20/+0x2C via
// slot 0x60 plus float at +0x38 via slot 0x70 plus int at +0x3C via slot
// 0x7C through a stack temp then version>=3 bool at +0x40 via slot 0x90
// then version>=4 uint at +0x44 via slot 0x78. Layout is UpdateModule base
// 0x20 giving +0x20 start. Identity is slot 3 plus the UpdateModule base
// call; class name stays honest Rva address name.

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

class Rva003A4CAE : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Coord3DBase m_20;
	Coord3DBase m_2C;
	float m_38;
	int m_3C;
	bool m_40;
	unsigned int m_44;
};

void Rva003A4CAE::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	if (version.m_minimum >= 2) {
		*xfer == m_20;
		*xfer == m_2C;
		*xfer == m_38;
		int tmp = m_3C;
		*xfer == tmp;
		m_3C = tmp;
	}
	if (version.m_minimum >= 3) {
		*xfer == m_40;
	}
	if (version.m_minimum >= 4) {
		*xfer == m_44;
	}
}
