// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ?xfer@Rva004C908B@@MAEXPAVXfer@@@Z, retail 0x004C9505, 142 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0085EA8C (same primary as rowed ctor
// 0x004C908B): base ObjectModule xfer via rowed 0x00560AE1 then IsLightCRC
// early-out via Xfer slot 0x10 then Version1 via rowed 0x000053EE then five
// floats at +0x0C/+0x10/+0x14/+0x18/+0x1C via Xfer slot 0x70 then short at
// +0x20 via Xfer slot 0x84 then bool at +0x22 via Xfer slot 0x90 then floats
// at +0x24/+0x28 via Xfer slot 0x70. Layout is the rowed 0x2C-byte class
// (opaque Rva00362EC7 base 0x0C like ObjectModule plus 0x20 bytes per the
// ctor which inits m_w20 -1 plus five zero floats plus m_b22 1 plus two zero
// floats; factory 0x0025298F news 0x2C). Recipe is SlowDeathBehaviorXfer
// base plus lightCRC plus Version1 plus member runs.

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
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class Rva004C908B : public ObjectModule
{
public:
	Rva004C908B(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	float m_f0C;
	float m_f10;
	float m_f14;
	float m_f18;
	float m_f1C;
	short m_w20;
	bool m_b22;
	unsigned char m_b23;
	float m_f24;
	float m_f28;
};

void Rva004C908B::xfer(Xfer *xfer)
{
	ObjectModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_f0C;
	*xfer == m_f10;
	*xfer == m_f14;
	*xfer == m_f18;
	*xfer == m_f1C;
	*xfer == m_w20;
	*xfer == m_b22;
	*xfer == m_f24;
	*xfer == m_f28;
}
