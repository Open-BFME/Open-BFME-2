// cl: /O1 /DNDEBUG /MD
//
// ?xfer@CritterEmitterUpdate@@MAEXPAVXfer@@@Z, retail 0x004C8E42, 65 bytes.
// CritterEmitterUpdate xfer (slot 3 offset 0x0C of vtable 0x0085E8E8, same
// primary as rowed ctor 0x004C8D86 and dtor 0x004C8D1B with ??_G 0x004C8DC6):
// base UpdateModule xfer via rowed 0x0044DF9F, IsLightCRC early-out via Xfer
// slot 0x10, Version1 via rowed 0x000053EE, then two bool runs at +0x24/+0x25
// via Xfer slot 0x90. Layout is the rowed dtor TU (real UpdateModule base
// 0x20 plus trailing iface at +0x20 giving +0x24 start) plus the ctor TU's
// m_24/m_25 bytes as bool; donor is BFME1 CritterEmitterUpdateDestructor
// (protected MAE) plus SlowDeathBehaviorXfer slot-3 pattern (Version1 plus
// bool runs, no Version gating).


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
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class CritterEmitterUpdateIface
{
public:
	virtual void trailingAnchor();
};

class CritterEmitterUpdate : public UpdateModule, public CritterEmitterUpdateIface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_24;
	bool m_25;
};

void CritterEmitterUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_24;
	*xfer == m_25;
}
