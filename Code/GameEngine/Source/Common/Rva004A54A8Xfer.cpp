// cl: /O1 /MD
//
// ?xfer@Rva004A54A8@@MAEXPAVXfer@@@Z, retail 0x004A58BD, 138 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00852A28 (class of rowed dtor
// ??1Rva004A54A8@@UAE@XZ in Rva0024A797Grandchildren.cpp): UpdateModule base
// xfer via rowed 0x0044DF9F then IsLightCRC early-out via Xfer slot 0x10
// then Version1 via rowed 0x000053EE then uint at +0x24 via Xfer slot 0x78
// then Coord2D at +0x28 via Xfer slot 0x50 then 4 raw bytes at +0x30 via
// XferRawBytes slot 0x24 then floats at +0x34/+0x38/+0x3C/+0x40 via Xfer
// slot 0x70 then int at +0x44 via Xfer slot 0x7C then Coord3DBase at +0x48
// via Xfer slot 0x60. Layout is UpdateModule base 0x20 plus 4 pad at +0x20
// (unxferred) giving +0x24 start; Coord2D is 8 bytes at +0x28-0x2F with no
// gap to +0x30.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
class ICoord3D;
class Region3D;
class IRegion3D;
struct Coord2D
{
	float x;
	float y;
};
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

class Rva004A54A8 : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_20;
	unsigned int m_24;
	Coord2D m_28;
	int m_30raw;
	float m_34;
	float m_38;
	float m_3C;
	float m_40;
	int m_44;
	Coord3DBase m_48;
};

void Rva004A54A8::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_24;
	*xfer == m_28;
	xfer->XferRawBytes(&m_30raw, 4);
	*xfer == m_34;
	*xfer == m_38;
	*xfer == m_3C;
	*xfer == m_40;
	*xfer == m_44;
	*xfer == m_48;
}
