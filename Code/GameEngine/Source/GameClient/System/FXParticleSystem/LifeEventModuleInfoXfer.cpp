// cl: /MD /Ireference/shims/bfme2_ascii
// ?xfer@LifeEventModuleInfo@FXParticleSystem@@MAEXPAVXfer@@@Z, retail 0x00563E72, 54 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0081C188 (class of ??0LifeEventModuleInfo@FXParticleSystem@@QAE@ABV01@@Z)
// and slot 5 of 0x0081C2DC. IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, GameClientRandomVariable at +8 via rowed xferRandomVariable 0x00306183,
// AsciiString at +4 via Xfer slot 0x6C. No base call (Snapshot base is pure virtual).
// Layout from LifeEventModuleInfoDefaultCtor 0x00564001 and GetEventFX 0x0056410F
// (AsciiString m_eventName at +4, GameClientRandomVariable at +8, cache at +0x14).
// Precedent: RenderObjectUpdateModuleInfoXfer 0x00562182 (/O1 /MD, IsLightCRC+Version1
// plus xferRandomVariable). Caller 0x00563ED1 becomes ready.

#include "ascii_string.h"

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
class DamageInfo;

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

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT,
		UNIFORM,
		GAUSSIAN,
		TRIANGULAR,
		LOW_BIAS,
		HIGH_BIAS
	};

	DistributionType m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

namespace FXParticleSystem
{

class SnapshotBase
{
public:
	virtual ~SnapshotBase();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class LifeEventModuleInfo : public SnapshotBase
{
public:
	LifeEventModuleInfo();
	virtual ~LifeEventModuleInfo();

protected:
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_name;
	GameClientRandomVariable m_var;
	const void *m_cached;
};

}

void FXParticleSystem::LifeEventModuleInfo::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	xferRandomVariable(*xfer, m_var);
	*xfer == m_name;
}
