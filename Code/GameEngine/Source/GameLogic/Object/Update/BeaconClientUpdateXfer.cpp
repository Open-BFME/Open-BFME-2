// cl: /MD /DNDEBUG
//
// ?xfer@BeaconClientUpdate@@MAEXPAVXfer@@@Z, retail 0x004C95C9, 62 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0085EB30 (VA 0x00C5EB30, class of
// rowed ctor ??0BeaconClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z in
// PointDefenseLaserUpdateCtor.cpp): Version1 via rowed 0x000053EE then base
// ObjectModule xfer via rowed 0x00560AE1 then IsLightCRC early-out via Xfer
// slot 0x10 then ParticleSystemID at +0x0C via rowed XferParticleSystemID
// 0x0030600A then uint at +0x10 via Xfer slot 0x78. Layout is ObjectModule
// base 0x0C plus int at +0x0C plus uint at +0x10. Donor is ZH
// BeaconClientUpdate::xfer (xferVersion plus ClientUpdateModule base plus
// xferUser plus xferUnsignedInt); BFME2 uses Version1 plus ObjectModule base
// plus IsLightCRC guard plus helper plus operator==.

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

void XferParticleSystemID(Xfer *xfer, int *value);

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

class BeaconClientUpdate : public ObjectModule
{
public:
	BeaconClientUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_particleSystemID;
	unsigned int m_lastRadarPulse;
};

void BeaconClientUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	ObjectModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	XferParticleSystemID(xfer, &m_particleSystemID);
	*xfer == m_lastRadarPulse;
}
