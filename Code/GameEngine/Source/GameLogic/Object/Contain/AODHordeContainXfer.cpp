// cl: /DNDEBUG /MD
//
// ?xfer@AODHordeContain@@MAEXPAVXfer@@@Z, retail 0x0047B2FB, 99 bytes.
// Slot 3 of ??_7AODHordeContain 0x00C46D28 (installed by the rowed ctor
// 0x0047B3DB). Version1, the pinned HordeContain::xfer 0x00474EA8, the
// tracked large unit's ObjectID at +0x318 (rowed XferObjectID), the float
// at +0x334, the int at +0x31C, a refresh through the rowed
// refreshTrackedLargeUnit 0x0047B2AA while the ID is set, then the tracked
// position at +0x320. Names from the AODHordeContainRefresh view.

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

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class HordeContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	unsigned char m_unrecovered04[0x30C - 0x04];
};

class AODHordeContain : public HordeContain
{
public:
	void refreshTrackedLargeUnit();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_vectorPad[12];
	ObjectID m_trackedLargeUnit;
	unsigned int m_31C;
	Coord3DBase m_trackedPosition;
	float m_largeUnitHeightFactor;
	float m_largeUnitHeight;
	float m_334;
};

// ?xfer@AODHordeContain@@MAEXPAVXfer@@@Z @0x0047B2FB
void AODHordeContain::xfer(Xfer *xfer)
{
	xfer->Version1();
	HordeContain::xfer(xfer);

	XferObjectID(xfer, &m_trackedLargeUnit);
	*xfer == m_334;
	*xfer == m_31C;
	if (m_trackedLargeUnit != INVALID_ID)
		refreshTrackedLargeUnit();
	*xfer == m_trackedPosition;
}
