// cl: /DNDEBUG /MD
// ?xfer@RadiusDecalUpdate@@MAEXPAVXfer@@@Z, retail 0x003915AE, 60 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0081A018 (class of ??1RadiusDecalUpdate
// rowed at 0x003913E4 in RadiusDecalUpdateCtorThunk.cpp). Base
// UpdateModule::xfer via rowed 0x0044DF9F, IsLightCRC early-out via Xfer
// slot 0x10, Version1 via rowed 0x000053EE, RadiusDecal at +0x20 via rowed
// rva00330F7D 0x00330F7D, bool at +0x30 via Xfer slot 0x90. Layout is the
// rowed class from RadiusDecalUpdateCtorThunk.cpp (UpdateModule base 0x20
// plus RadiusDecal 0x10 plus bool). Recipe is the OneRingPenaltyUpdateXfer
// slot-3 pattern.
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
class RadiusDecal
{
public:
	RadiusDecal();
	~RadiusDecal();
	void clear();
	void rva00330F7D(Xfer *xfer);
private:
	const void *m_template;
	void *m_decal;
	unsigned char m_empty;
	unsigned char m_pad[4];
};
class RadiusDecalUpdate : public UpdateModule
{
public:
	RadiusDecalUpdate(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void xfer(Xfer *xfer);
private:
	RadiusDecal m_deliveryDecal;
	bool m_30;
};
void RadiusDecalUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	m_deliveryDecal.rva00330F7D(xfer);
	*xfer == m_30;
}
