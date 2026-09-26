// cl: /O1 /DNDEBUG /MD
//
// ?xfer@BridgeTowerBehavior@@MAEXPAVXfer@@@Z, retail 0x004587CD,
// 62 bytes. Slot 3 (offset 0x0C) of vtable 0x00840D64 (class of rowed ctor
// ??0BridgeTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z in
// BridgeTowerBehaviorCtor.cpp): Version1 via rowed 0x000053EE then base
// BehaviorModule xfer via rowed 0x004C9C7D then IsLightCRC early-out via
// Xfer slot 0x10 then ObjectID at +0x1C via rowed XferObjectID 0x003060B2
// then tower type at +0x20 via rowed XferBridgeTowerType 0x0030609A.
// Layout is the rowed ctor shape (BehaviorModule base 0x10 plus three
// secondary slots at +0x10/+0x14/+0x18 giving +0x1C start); donor is ZH
// BridgeTowerBehavior::xfer (xferVersion plus xferObjectID plus xferUser)
// with BFME2 Version1-first plus light-CRC plus labelled-enum order.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);
void XferBridgeTowerType(Xfer *xfer, int *value);

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
};

class BridgeTowerBehavior : public BehaviorModule
{
public:
	BridgeTowerBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	const void *m_10;
	const void *m_14;
	const void *m_18;
	ObjectID m_bridgeID;	// +0x1C
	int m_type;		// +0x20 BridgeTowerType
};

void BridgeTowerBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	BehaviorModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	XferObjectID(xfer, &m_bridgeID);
	XferBridgeTowerType(xfer, &m_type);
}
