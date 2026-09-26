// cl: /O1 /MD
//
// ?xfer@GiantBirdSlowDeathBehavior@@MAEXPAVXfer@@@Z, retail 0x00461F34, 75 bytes.
// GiantBirdSlowDeathBehavior xfer (slot 3 offset 0x0C of vtable 0x00842E64,
// same primary as the rowed ctor 0x461E58): Version1 via rowed 0x53EE, then
// SlowDeathBehavior base xfer via rowed 0x45D3CB, then 4 member transfers in
// retail order (uint at +0x50 via slot 0x78 plus bool at +0x64 via slot 0x90
// plus Coord3DBase at +0x54 via slot 0x60 plus float at +0x60 via slot 0x70).
// Layout is the rowed 0x50-byte SlowDeathBehavior base (real UpdateModule
// 0x20 plus 2 interfaces) plus uint/Coord/float/bool to 0x68 (rowed factory
// 0x24B599 news 0x68). Donor is BFME1 Jet/Heli SlowDeath xfer pattern
// (Version1 then base then members); BFME2 adds members so retail is followed.
// Callers: none. Vtable slot proves xfer identity.

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

class SlowDeathBehaviorInterface { public: virtual void slowDeathSlot(); };
class DieModuleInterface { public: virtual void dieSlot(); };

class SlowDeathBehavior : public UpdateModule,
	public SlowDeathBehaviorInterface, public DieModuleInterface
{
public:
	SlowDeathBehavior(Thing *, const ModuleData *);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	float m_38;
	unsigned int m_3C;
	bool m_40;
	unsigned char m_pad41[3];
	unsigned int m_44;
	bool m_48;
	unsigned char m_pad49[3];
	unsigned int m_4C;
};

class GiantBirdSlowDeathBehavior : public SlowDeathBehavior
{
public:
	GiantBirdSlowDeathBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_50;
	Coord3DBase m_54;
	float m_60;
	bool m_64;
};

void GiantBirdSlowDeathBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	SlowDeathBehavior::xfer(xfer);
	*xfer == m_50;
	*xfer == m_64;
	*xfer == m_54;
	*xfer == m_60;
}
