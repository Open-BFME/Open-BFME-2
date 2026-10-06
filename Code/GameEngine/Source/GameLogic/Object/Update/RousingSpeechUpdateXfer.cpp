// cl: /DNDEBUG /MD
//
// ?xfer@RousingSpeechUpdate@@MAEXPAVXfer@@@Z, retail 0x004AD2AF, 132 bytes.
// Slot 3 of the vftable 0x00C54FE8 whose slot-2 name getter returns
// "RousingSpeechUpdate" (the rowed dtor 0x004ACE96 installs it). The rowed
// SpecialAbilityUpdate::xfer 0x0044F996, the light-CRC out, Version(1,2),
// the ObjectID list at +0x88 (pinned xferSTLObjectIDList 0x00331F2D), a bool
// at +0x90, an unsigned int at +0x8C and from version 2 floats at +0x94 and
// +0x98 (the GloriousChargeUpdateXfer shape). Member names not recovered.

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

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_previous;
	ObjectID m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	void push_back(const ObjectID &value);
	BridgeBehaviorObjectIDNode *m_node;
};

Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list);

class SpecialAbilityUpdate
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x88 - 0x04];
};

class RousingSpeechUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	BridgeBehaviorObjectIDList m_88;
	unsigned int m_8C;
	bool m_90;
	float m_94;
	float m_98;
};

// ?xfer@RousingSpeechUpdate@@MAEXPAVXfer@@@Z @0x004AD2AF
void RousingSpeechUpdate::xfer(Xfer *xfer)
{
	SpecialAbilityUpdate::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	xferSTLObjectIDList(xfer, &m_88);
	*xfer == m_90;
	*xfer == m_8C;
	if (version.m_minimum >= 2)
	{
		*xfer == m_94;
		*xfer == m_98;
	}
}
