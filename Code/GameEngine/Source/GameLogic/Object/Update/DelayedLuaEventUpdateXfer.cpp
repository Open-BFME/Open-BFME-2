// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?xfer@DelayedLuaEventUpdate@@MAEXPAVXfer@@@Z, retail 0x004A8E0A, 113 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00853A5C, same primary as rowed ctor
// 0x004A8E7B and dtor 0x004A8D4A and deleting dtor 0x004A8EEF. Base
// UpdateModule xfer via rowed 0x0044DF9F, IsLightCRC early-out via Xfer slot
// 0x10, Version(1,1) via Xfer slot 0x28, float at +0x70 via slot 0x70, bools
// at +0x74/+0x75 via slot 0x90, uint at +0x20 via XferRawBytes slot 0x24,
// then member DelayedLuaEventList at +0x24 via its slot-3 xfer (rowed
// 0x003316D2). Layout is the rowed class (UpdateModule base 0x20 plus m_f20
// +0x20 plus events +0x24 size 0x4C plus m_f70 +0x70 plus flags +0x74/+0x75)
// from DelayedLuaEventUpdateCtor/Dtor. Recipe is the InvisibilityUpdateXfer
// slot-3 pattern with DelayedLuaEventListXfer Version(1,1) and float/bool
// slots.

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

class DelayedLuaEventList
{
public:
	virtual ~DelayedLuaEventList();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x48];
};

class DelayedLuaEventUpdate : public UpdateModule
{
public:
	DelayedLuaEventUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_f20;
	DelayedLuaEventList m_events;
	float m_f70;
	bool m_f74;
	bool m_f75;
};

void DelayedLuaEventUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_f70;
	*xfer == m_f74;
	*xfer == m_f75;
	xfer->XferRawBytes(&m_f20, 4);
	m_events.xfer(xfer);
}
