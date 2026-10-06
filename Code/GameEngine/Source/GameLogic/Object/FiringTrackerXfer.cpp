// cl: /DNDEBUG /MD /EHsc
//
// ?xfer@FiringTracker@@MAEXPAVXfer@@@Z retail 0x004DEBC1 199 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00861530 (class of rowed dtor
// ??1FiringTracker@@UAE@XZ in FiringTrackerDtor.cpp, same primary as rowed
// deleting dtor 0x004DEBA5 and pool key 0x004DEACB with FiringTracker string).
// Base UpdateModule xfer via rowed 0x0044DF9F then IsLightCRC early-out via
// Xfer slot 0x10 then Version(1,2) via Xfer slot 0x28 then int at +0x20 via
// Xfer slot 0x7C plus ObjectIDs at +0x24/+0x38 via rowed XferObjectID
// 0x003060B2 plus uints at +0x3C/+0x40/+0x44 via Xfer slot 0x78 plus Coord at
// +0x48 via Xfer slot 0x60 plus bool at +0x34 via Xfer slot 0x90 plus Coord
// at +0x28 via Xfer slot 0x60 plus version-gated uint at +0x54 via Xfer slot
// 0x78 plus TheAudio (data 0x00DFE6E8) xferAudioHandle at AudioManager slot
// 0x160 for +0x58. Layout is donor BFME1 FiringTrackerBFMEXfer (UpdateModule
// base 0x20 plus consecutiveShots plus victimID plus victimPosition plus
// victimIsPosition plus auxID plus three frames plus lastShotPosition plus
// stopLoopingSound plus audioHandle). Recipe follows FlammableUpdateXfer
// (Version plus audio-handle shape) plus GateOpenAndCloseBehaviorXfer.

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

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	virtual void _pad52() = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual void _pad77() = 0;
	virtual void _pad78() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle) = 0;
};

extern AudioManager *TheAudio;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	const void *m_moduleData;
	void *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class FiringTracker : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_consecutiveShots;
	ObjectID m_victimID;
	Coord3DBase m_victimPosition;
	bool m_victimIsPosition;
	unsigned char m_pad35[3];
	ObjectID m_auxiliaryObjectID;
	unsigned int m_frameToStartCooldown;
	unsigned int m_frameToForceReload;
	unsigned int m_lastShotFrame;
	Coord3DBase m_lastShotPosition;
	unsigned int m_frameToStopLoopingSound;
	AudioHandle m_audioHandle;
};

void FiringTracker::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_consecutiveShots;
	XferObjectID(xfer, &m_victimID);
	XferObjectID(xfer, &m_auxiliaryObjectID);
	*xfer == m_frameToStartCooldown;
	*xfer == m_frameToForceReload;
	*xfer == m_lastShotFrame;
	*xfer == m_lastShotPosition;
	*xfer == m_victimIsPosition;
	*xfer == m_victimPosition;
	if (version.m_minimum >= 2) {
		*xfer == m_frameToStopLoopingSound;
	}
	if (TheAudio != 0) {
		TheAudio->xferAudioHandle(xfer, &m_audioHandle);
	}
}
