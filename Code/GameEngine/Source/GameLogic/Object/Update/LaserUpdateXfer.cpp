// cl: /DNDEBUG /MD /GX
//
// ?xfer@LaserUpdate@@MAEXPAVXfer@@@Z, retail 0x00362FF8, 238 bytes.
// Slot 3 (offset 0x0C) of vtable 0x008170E0 (class of ??0LaserUpdate rowed at
// 0x00362EEE in LaserUpdateCtor.cpp).
//
// Donor: BFME1 LaserUpdateDestructorAndRadius.cpp / ZH LaserUpdate.h xfer
// pattern plus PoisonedBehaviorXfer.cpp slot-3 recipe (base xfer, IsLightCRC
// early-out via Xfer slot 0x10, Version(1,2) via Xfer slot 0x28, then Coords
// via slot 0x60, bools via slot 0x90, uints via slot 0x78, float via slot
// 0x70, ParticleSystemID/DrawableID helpers, version-gated trailing uint).
// Layout follows the rowed LaserUpdateCtor.cpp TU (opaque 0x0C base plus
// derived Coords at +0x0C/+0x18, bool at +0x24, IDs at +0x28/+0x2C, bools at
// +0x30/+0x31, uints/float/uints at +0x34..+0x44, DrawableIDs at +0x4C/+0x50
// with version-2 uint at +0x48 transferred last).

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
class DamageInfo;

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
	Version(unsigned char major, unsigned char minor) : m_major(major), m_minor(minor) {}
	unsigned char m_major;
	unsigned char m_minor;
};

void XferParticleSystemID(Xfer *xfer, int *value);
void XferDrawableID(Xfer *xfer, int *value);

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	void xfer(Xfer *xfer);
protected:
	unsigned int m_04;
	unsigned int m_08;
};

class LaserUpdate : public ObjectModule
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Coord3DBase m_0C;
	Coord3DBase m_18;
	bool m_24;
	char m_pad25[3];
	int m_28;
	int m_2C;
	bool m_30;
	bool m_31;
	char m_pad32[2];
	unsigned int m_34;
	unsigned int m_38;
	float m_3C;
	unsigned int m_40;
	unsigned int m_44;
	unsigned int m_48;
	int m_4C;
	int m_50;
};

void LaserUpdate::xfer(Xfer *xfer)
{
	ObjectModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_0C;
	*xfer == m_18;
	*xfer == m_24;
	XferParticleSystemID(xfer, &m_28);
	XferParticleSystemID(xfer, &m_2C);
	*xfer == m_30;
	*xfer == m_31;
	*xfer == m_34;
	*xfer == m_38;
	*xfer == m_3C;
	*xfer == m_40;
	*xfer == m_44;
	XferDrawableID(xfer, &m_4C);
	XferDrawableID(xfer, &m_50);
	if (version.m_minor >= 2)
		*xfer == m_48;
}
