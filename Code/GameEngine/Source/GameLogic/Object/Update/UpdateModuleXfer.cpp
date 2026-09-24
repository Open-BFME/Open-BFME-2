// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ?xfer@UpdateModule@@QAEXPAVXfer@@@Z retail 0x0044DF9F
// 62 bytes. UpdateModule base xfer used by every behavior-side xfer in the
// file-unit vein (DynamicShroudClearingRangeUpdate::xfer rowed over its pin;
// row supersedes that pin here).
//
// Shape from retail plus the Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Update/UpdateModule.cpp):
// Version1, BehaviorModule base xfer (pinned), light-CRC early-out, one
// unsigned run over the next-call frame/phase slot, and a load-gated
// all-ones store to the logic-index slot. The Xfer declaration is the
// SkirmishGameInfoXfer proven spelling (IsLoading slot 1, IsLightCRC
// slot 4, Version1 direct row, == uint at 0x78).

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

class BehaviorModule
{
public:
	void xfer(Xfer *xfer);
};

class UpdateModule : public BehaviorModule
{
public:
	void xfer(Xfer *xfer);

private:
	char m_unreconstructed_00[0x14];
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
};

// ?xfer@UpdateModule@@QAEXPAVXfer@@@Z @0x0044DF9F
void UpdateModule::xfer(Xfer *xfer)
{
	xfer->Version1();

	BehaviorModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	*xfer == m_nextCallFrameAndPhase;

	if (xfer->IsLoading())
		m_indexInLogic |= -1;
}
