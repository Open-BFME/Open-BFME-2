// cl: /MD
// ?xfer@RespawnUpdate@@MAEXPAVXfer@@@Z @0x004AF00B (139B): slot 3 xfer via
// Version(1,1) slot 0x28 then base UpdateModule 0x0044DF9F plus helpers
// XferRespawnModeType 0x003060FA XferObjectID 0x003060B2 plus int at
// +0x34/+0x38/+0x3C via slot 0x7C plus bool at +0x40/+0x41 via slot 0x90
// plus float at +0x20 via slot 0x70. Layout from RespawnUpdateCtor (base
// 0x20 plus float 0x20 ints 0x24-0x3C bools 0x40-0x41). Recipe is the
// Rva003A4CAE Version-plus-base xfer with reverse-overload slots (uint
// 0x78 float 0x70 int 0x7C bool 0x90).
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

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, unsigned int frame);
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

enum ObjectID;
void __cdecl XferRespawnModeType(Xfer *x, int *v);
void __cdecl XferObjectID(Xfer *x, ObjectID *v);

class RespawnUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	bool m_40;
	bool m_41;
};

void RespawnUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	XferRespawnModeType(xfer, &m_2c);
	XferObjectID(xfer, (ObjectID *)&m_30);
	*xfer == m_34;
	*xfer == m_38;
	*xfer == m_40;
	*xfer == m_3c;
	*xfer == m_20;
	*xfer == m_41;
}
