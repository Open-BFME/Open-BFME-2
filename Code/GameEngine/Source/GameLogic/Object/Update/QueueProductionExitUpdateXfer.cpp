// cl: /O1 /MD
//
// ?xfer@QueueProductionExitUpdate@@MAEXPAVXfer@@@Z, retail 0x004A0057, 107 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x008519C8 (class of rowed dtor
// ??1QueueProductionExitUpdate@@MAE@XZ at 0x0049FFF7). Base UpdateModule xfer
// via rowed 0x44DF9F then IsLightCRC early-out via Xfer slot 0x10 then
// Version1 via rowed 0x53EE then uint at +0x24 via Xfer slot 0x78 plus Coord
// at +0x28 via Xfer slot 0x60 plus bool at +0x34 via Xfer slot 0x90 plus float
// at +0x38 via Xfer slot 0x70 plus ObjectID at +0x40 via rowed XferObjectID
// 0x003060B2 plus uint at +0x3C via Xfer slot 0x78 last. Layout is the rowed
// 0x44-byte class from QueueProductionExitUpdateCtor.cpp 0x4A010E (UpdateModule
// base 0x20 plus ExitInterface vptr at +0x20 giving +0x24 start). Donor is ZH
// QueueProductionExitUpdate::xfer (5 members) plus BFME2 IsLightCRC and Version1
// order plus new ObjectID member. Recipe is SlowDeathBehaviorXfer slot-3 pattern.

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
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class ExitInterface
{
public:
	virtual void exitAnchor();
};

class QueueProductionExitUpdate : public UpdateModule, public ExitInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_currentDelay;
	Coord3DBase m_rallyPoint;
	bool m_rallyPointExists;
	unsigned char m_pad35[3];
	float m_creationClearDistance;
	unsigned int m_currentBurstCount;
	ObjectID m_objectID;
};

void QueueProductionExitUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_currentDelay;
	*xfer == m_rallyPoint;
	*xfer == m_rallyPointExists;
	*xfer == m_creationClearDistance;
	XferObjectID(xfer, &m_objectID);
	*xfer == m_currentBurstCount;
}
