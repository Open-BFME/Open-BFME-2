// cl: /O1 /DNDEBUG /MD
//
// ?xfer@EvaAnnounceClientCreate@@MAEXPAVXfer@@@Z, retail 0x004C9B44, 75 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0085ED50 (same primary as rowed ctor
// 0x004C99D4): Version(1,2) via Xfer slot 0x28 then base ObjectModule xfer
// via rowed 0x00560AE1 then bool at +0x14 via Xfer slot 0x90 then
// version-gated uint at +0x10 via Xfer slot 0x78. Layout is the rowed
// 0x18-byte class (opaque Rva00362EC7 base 0x0C like ObjectModule plus
// secondary vptr at +0x0C giving +0x10 start; factory 0x00252A50 news 0x18
// is sole caller of the ctor); recipe is InvisibilityUpdateXfer slot-3
// Version(1,2) gating over RandomSoundSelectorClientBehaviorXfer base
// ObjectModule plus bool uint order.

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
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class EvaAnnounceSecondary
{
public:
	virtual void secondarySlot();
};

class EvaAnnounceClientCreate : public ObjectModule, public EvaAnnounceSecondary
{
public:
	EvaAnnounceClientCreate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_10;
	bool m_14;
};

void EvaAnnounceClientCreate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	ObjectModule::xfer(xfer);
	*xfer == m_14;
	if (version.m_minimum >= 2) {
		*xfer == m_10;
	}
}
