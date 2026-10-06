// cl: /DNDEBUG /MD /GX
//
// ?xfer@FireWeaponCollide@@MAEXPAVXfer@@@Z, retail 0x004BB85C, 94 bytes.
// FireWeaponCollide xfer (slot 3 offset 0x0C of vtable 0x0085A0FC, class of
// rowed dtor ??1FireWeaponCollide@@UAE@XZ at 0x004BB6A7): base CollideModule
// xfer via rowed Rva004CE56D 0x004CE56D (Version1 plus BehaviorModule base,
// vslot 3 for CollideModule), then IsLightCRC early-out via Xfer slot 0x10,
// then Version1 via rowed 0x000053EE, then weapon-present bool via Xfer slot
// 0x90, weapon Snapshot via Xfer slot 0x30, ever-fired bool at +0x18 via slot
// 0x90. Layout is the rowed 0x1C-byte class from FireWeaponCollideCtor.cpp
// (CollideModule base 0x14 plus Weapon* at +0x14 plus bool at +0x18).
// Donor is BFME1 FireWeaponCollide::xfer (xferVersion, base xfer, bool,
// Snapshot, bool) plus SlowDeathBehaviorXfer/AODCrushCollideXfer Xfer
// spelling (IsLightCRC 0x10, Snapshot 0x30, bool 0x90).

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

class Rva004CE56D
{
public:
	void xfer(Xfer *xfer);
};

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class CollideModuleInterface
{
public:
	virtual void collideSlot();
};

class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData);
	virtual ~CollideModule();
};

class Weapon : public Snapshot
{
};

class FireWeaponCollide : public CollideModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Weapon *m_collideWeapon; // +0x14
	bool m_everFired; // +0x18
};

void FireWeaponCollide::xfer(Xfer *xfer)
{
	((Rva004CE56D *)this)->xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	bool present = m_collideWeapon != 0;
	*xfer == present;
	if (present)
		*xfer == (Snapshot &)*m_collideWeapon;
	*xfer == m_everFired;
}
