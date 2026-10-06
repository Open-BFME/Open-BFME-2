// cl: /DNDEBUG /MD
//
// ?xfer@MissileUpdate@@MAEXPAVXfer@@@Z, retail 0x004A796A, 284 bytes.
// Slot 3 of ??_7MissileUpdate 0x00C5362C (slot-2 name getter returns
// "MissileUpdate"; installed by the rowed ctor 0x004A75B9). Version(1,1),
// the pinned BezierProjectileBehavior::xfer 0x0045CA8E, then the members in
// retail's order: Coord3Ds at +0xA0 and +0xB8 (the latter zeroed on load),
// an unsigned int at +0x8C, ObjectIDs at +0x90 and +0x94, a bool at +0xCD,
// an unsigned int at +0x98, a float at +0x9C, bools at +0xCE and +0xCC, a
// Coord3D at +0xAC, an unsigned int at +0xC4, and four raw bytes each at
// +0x88 and +0xC8 (Xfer slot 0x24). Member names not recovered.

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
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class BezierProjectileBehavior
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x88 - 0x04];
};

class MissileUpdate : public BezierProjectileBehavior
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_88;
	unsigned int m_8C;
	ObjectID m_90;
	ObjectID m_94;
	unsigned int m_98;
	float m_9C;
	Coord3DBase m_A0;
	Coord3DBase m_AC;
	Coord3DBase m_B8;
	unsigned int m_C4;
	int m_C8;
	bool m_CC;
	bool m_CD;
	bool m_CE;
};

// ?xfer@MissileUpdate@@MAEXPAVXfer@@@Z @0x004A796A
void MissileUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	BezierProjectileBehavior::xfer(xfer);

	*xfer == m_A0;
	*xfer == m_B8;
	if (xfer->IsLoading())
		m_B8.zero();
	*xfer == m_8C;
	XferObjectID(xfer, &m_90);
	XferObjectID(xfer, &m_94);
	*xfer == m_CD;
	*xfer == m_98;
	*xfer == m_9C;
	*xfer == m_CE;
	*xfer == m_CC;
	*xfer == m_AC;
	*xfer == m_C4;
	xfer->XferRawBytes(&m_88, sizeof(m_88));
	xfer->XferRawBytes(&m_C8, sizeof(m_C8));
}
