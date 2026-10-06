// cl: /DNDEBUG /MD
//
// ?xfer@W3DRopeDraw@@MAEXPAVXfer@@@Z @0x000CA916 191B: W3DRopeDraw protected virtual xfer.
// Slot 3 (offset 0x0C) of vtable 0x007CBD60 (class of rowed ??1W3DRopeDraw@@UAE@XZ).
// Base DrawModule xfer via rowed 0x004CBF58 then IsLightCRC early-out via Xfer slot 0x10
// then Version1 via rowed 0x000053EE then 3 floats at +0x1C/+0x20/+0x24 via Xfer slot 0x70
// plus RGBColor at +0x28 via Xfer slot 0x3C plus 8 floats at +0x34/+0x38/+0x3C/+0x40/+0x44
// /+0x48/+0x4C/+0x50 via Xfer slot 0x70 plus IsLoading-gated tossSegments via rowed 0x000CA84D.
// Layout is ZH W3DRopeDraw.h (DrawModule base 0x0C plus RopeDrawInterface at +0x0C giving
// +0x10 start plus segments 0x0C plus curLen/maxLen/width/color/curSpeed/maxSpeed/accel/
// wobbleLen/wobbleAmp/wobbleRate/curPhase/curZOffset; total 0x54 matches FriendNew news 0x54).
// Donor is BFME1 W3DRopeDraw.cpp xfer (xferVersion plus base plus xferReal/xferRGBColor plus
// getXferMode LOAD toss); BFME2 repairs follow PoisonedBehaviorXfer slot-3 pattern
// (IsLightCRC plus Version1 plus operator==) plus UpdateModuleXfer IsLoading tail.

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
struct RGBColor
{
	float red;
	float green;
	float blue;
};
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

class DrawModule : public ObjectModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);
};

class RopeDrawInterface
{
public:
	virtual void ropeSlot();
};

class W3DRopeDraw : public DrawModule, public RopeDrawInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	void tossSegments();

	char m_pad10[12];
	float m_curLen;
	float m_maxLen;
	float m_width;
	RGBColor m_color;
	float m_curSpeed;
	float m_maxSpeed;
	float m_accel;
	float m_wobbleLen;
	float m_wobbleAmp;
	float m_wobbleRate;
	float m_curWobblePhase;
	float m_curZOffset;
};

void W3DRopeDraw::xfer(Xfer *xfer)
{
	DrawModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_curLen;
	*xfer == m_maxLen;
	*xfer == m_width;
	*xfer == m_color;
	*xfer == m_curSpeed;
	*xfer == m_maxSpeed;
	*xfer == m_accel;
	*xfer == m_wobbleLen;
	*xfer == m_wobbleAmp;
	*xfer == m_wobbleRate;
	*xfer == m_curWobblePhase;
	*xfer == m_curZOffset;
	if (xfer->IsLoading())
		tossSegments();
}
