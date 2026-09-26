// cl: /O1 /MD
//
// ?xfer@SlowDeathBehavior@@MAEXPAVXfer@@@Z, retail 0x0045D3CB, 142 bytes.
// SlowDeathBehavior xfer (slot 3 offset 0x0C of vtable 0x00842040, same primary
// as the rowed ctor 0x45D4B4): base UpdateModule xfer via rowed 0x44DF9F, then
// IsLightCRC early-out via Xfer slot 0x10, then Version1 via rowed 0x53EE,
// then 9 member transfers in retail order (4 uints at +0x28/+0x2C/+0x30/+0x34
// plus float at +0x38 plus uint at +0x3C plus bool at +0x48 plus uint at +0x4C
// plus bool at +0x40 last, skipping constant +0x44 99999) via Xfer slots 0x78
// uint 0x70 float 0x90 bool. Layout is the rowed 10-member 0x50-byte class
// (real UpdateModule base 0x20 plus 2 new interfaces for +0x20/+0x24 giving
// +0x28 start, reference thunk precedent); donor is BFME1 SlowDeathBehavior::
// xfer (5 members) plus old TU present-unmatched marker; BFME2 adds members
// and IsLightCRC/Version1 order so retail is followed. Callers (3 unclaimed
// inits) plus vtable slot prove xfer identity.

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
	unsigned int m_28; // +0x28
	unsigned int m_2C; // +0x2C
	unsigned int m_30; // +0x30
	unsigned int m_34; // +0x34
	float m_38; // +0x38
	unsigned int m_3C; // +0x3C
	bool m_40; // +0x40
	unsigned char m_pad41[3];
	unsigned int m_44; // +0x44 constant 99999 not xferred
	bool m_48; // +0x48
	unsigned char m_pad49[3];
	unsigned int m_4C; // +0x4C
};

// ?xfer@SlowDeathBehavior@@MAEXPAVXfer@@@Z @0x0045D3CB
void SlowDeathBehavior::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_28;
	*xfer == m_2C;
	*xfer == m_30;
	*xfer == m_34;
	*xfer == m_38;
	*xfer == m_3C;
	*xfer == m_48;
	*xfer == m_4C;
	*xfer == m_40;
}
