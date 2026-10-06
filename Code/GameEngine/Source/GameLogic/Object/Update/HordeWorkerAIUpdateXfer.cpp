// cl: /DNDEBUG /MD
//
// ?xfer@HordeWorkerAIUpdate@@MAEXPAVXfer@@@Z, retail 0x0049AE07, 87 bytes.
// Slot 3 of ??_7HordeWorkerAIUpdate 0x00C508C8 (slot-2 name getter returns
// "HordeWorkerAIUpdate"; the rowed dtor 0x0049AC94 installs it). Version1,
// the rowed TransportAIUpdate::xfer 0x0049060D, three ObjectIDs at
// +0x3E8/+0x3EC/+0x3F0 and a bool at +0x3F4. Member names not recovered.

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class TransportAIUpdate
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x3E8 - 0x04];
};

class HordeWorkerAIUpdate : public TransportAIUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_3E8;
	ObjectID m_3EC;
	ObjectID m_3F0;
	bool m_3F4;
};

// ?xfer@HordeWorkerAIUpdate@@MAEXPAVXfer@@@Z @0x0049AE07
void HordeWorkerAIUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	TransportAIUpdate::xfer(xfer);
	XferObjectID(xfer, &m_3E8);
	XferObjectID(xfer, &m_3EC);
	XferObjectID(xfer, &m_3F0);
	*xfer == m_3F4;
}
