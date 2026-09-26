// cl: /O1 /MD
//
// ?xfer@BridgeScaffoldBehavior@@MAEXPAVXfer@@@Z, retail 0x00458638,
// 115 bytes. Slot 3 (offset 0x0C) of vtable 0x00840C54 (class of rowed ctor
// ??0BridgeScaffoldBehavior@@QAE@PAVThing@@PBVModuleData@@@Z in
// BridgeScaffoldBehaviorCtor.cpp): base UpdateModule xfer via rowed
// 0x0044DF9F then IsLightCRC early-out via Xfer slot 0x10 then Version1 via
// rowed 0x000053EE then enum at +0x24 via rowed XferScaffoldTargetMotion
// 0x00305DFA then three coords at +0x28/+0x34/+0x40 via Xfer slot 0x60 plus
// two floats at +0x4C/+0x50 via Xfer slot 0x70 plus coord at +0x54 via slot
// 0x60. Layout is the rowed ctor shape (UpdateModule base 0x20 plus one
// interface vptr at +0x20 giving +0x24 start); donor is ZH
// BridgeScaffoldBehavior::xfer (xferVersion first plus xferUser/xferCoord3D/
// xferReal) with BFME2 base-first plus light-CRC plus Version1 order.

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

void XferScaffoldTargetMotion(Xfer *xfer, int *value);

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

enum ScaffoldTargetMotion
{
	STM_STILL,
	STM_RISE,
	STM_BUILD_ACROSS,
	STM_TEAR_DOWN_ACROSS,
	STM_SINK,
};

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
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);

private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions(const Coord3DBase *createPos, const Coord3DBase *riseToPos, const Coord3DBase *buildPos);
	virtual void setMotion(ScaffoldTargetMotion targetMotion);
	virtual ScaffoldTargetMotion getCurrentMotion();
	virtual void reverseMotion();
	virtual void setLateralSpeed(float lateralSpeed);
	virtual void setVerticalSpeed(float verticalSpeed);
};

class BridgeScaffoldBehavior : public UpdateModule,
			       public BridgeScaffoldBehaviorInterface
{
public:
	BridgeScaffoldBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	ScaffoldTargetMotion m_targetMotion;	// +0x24
	Coord3DBase m_createPos;		// +0x28
	Coord3DBase m_riseToPos;		// +0x34
	Coord3DBase m_buildPos;			// +0x40
	float m_lateralSpeed;			// +0x4C
	float m_verticalSpeed;			// +0x50
	Coord3DBase m_targetPos;		// +0x54
};

void BridgeScaffoldBehavior::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	XferScaffoldTargetMotion(xfer, (int *)&m_targetMotion);
	*xfer == m_createPos;
	*xfer == m_riseToPos;
	*xfer == m_buildPos;
	*xfer == m_lateralSpeed;
	*xfer == m_verticalSpeed;
	*xfer == m_targetPos;
}
