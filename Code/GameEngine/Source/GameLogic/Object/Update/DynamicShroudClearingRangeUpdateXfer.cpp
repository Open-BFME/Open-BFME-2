// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ?xfer@DynamicShroudClearingRangeUpdate@@QAEXPAVXfer@@@Z retail 0x0048B505
// ~165 bytes. Behavior-side xfer completing the DynamicShroudClearingRangeUpdate
// file-unit (behavior ctor/dtor/??_G, ModuleData proc/ctor/factory, poolkey,
// instance factory and killGridDecals all rowed).
//
// Transcribed from the Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Update/
// DynamicShroudClearingRangeUpdate.cpp): base xfer, light-CRC early-out,
// Version1, two int runs, five unsigned runs, one bool run, three real runs.
// The Xfer declaration is the SkirmishGameInfoXfer proven spelling (slot 4
// IsLightCRC guard, Version1 direct row, == overloads in reverse slots:
// int 0x7C, uint 0x78, bool 0x90, float 0x70). UpdateModule::xfer rides the
// pinned 0x44DF9F base xfer.

class Thing;
class ModuleData;
class Player;
class Object;
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
typedef int Int;
typedef unsigned char Bool;

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

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();
	void xfer(Xfer *xfer);
};

class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	void xfer(Xfer *xfer);

private:
	const void *m_vtable;				// +0x00
	const ModuleData *m_moduleData;		// +0x04
	Object *m_object;					// +0x08
	const void *m_secondary0C;			// +0x0C
	const void *m_secondary10;			// +0x10
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
	int m_reserved1C;					// +0x1C
	int m_state;						// +0x20
	int m_stateCountDown;				// +0x24
	int m_totalFrames;					// +0x28
	unsigned int m_growStartDeadline;	// +0x2C
	unsigned int m_sustainDeadline;		// +0x30
	unsigned int m_shrinkStartDeadline;	// +0x34
	unsigned int m_doneForeverFrame;	// +0x38
	unsigned int m_changeIntervalCountdown;	// +0x3C
	bool m_decalsCreated;				// +0x40
	unsigned char m_pad_41[3];
	float m_visionChangePerInterval;	// +0x44
	float m_nativeClearingRange;		// +0x48
	float m_currentClearingRange;		// +0x4C
};

// ?xfer@DynamicShroudClearingRangeUpdate@@QAEXPAVXfer@@@Z @0x0048B505
void DynamicShroudClearingRangeUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	xfer->Version1();

	*xfer == m_stateCountDown;
	*xfer == m_totalFrames;
	*xfer == m_growStartDeadline;
	*xfer == m_sustainDeadline;
	*xfer == m_shrinkStartDeadline;
	*xfer == m_doneForeverFrame;
	*xfer == m_changeIntervalCountdown;
	*xfer == m_decalsCreated;
	*xfer == m_visionChangePerInterval;
	*xfer == m_nativeClearingRange;
	*xfer == m_currentClearingRange;
}
