// cl: /MD /Ireference/shims/bfme2_ascii
// ?rva00563ED1@Rva00563ED1@@QAEXPAVXfer@@@Z, retail 0x00563ED1, 82 bytes.
// Chain of just-landed ?xfer@LifeEventModuleInfo@FXParticleSystem@@MAEXPAVXfer@@@Z
// at 0x00563E72. IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed
// 0x000053EE, LifeEventModuleInfo subobject at +0x20 via rowed 0x00563E72,
// flags at +0x1C +0x1D +0x3C via Xfer slot 0x90 (bool per LightningDrawModuleInfoXfer
// 0x005614D9 flag via 0x90). No base call. Layout: Pad20 (0x20, flags at end)
// then LifeEventModuleInfo (0x18) then cache dword at +0x38 then flag at +0x3C.
// Precedent: RenderObjectUpdateModuleInfoXfer 0x00562182 (/O1 /MD).

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

struct Pad20
{
	virtual ~Pad20();
	char m_pad[0x18];
	bool m_1c;
	bool m_1d;
	char m_padEnd[2];
};

class Rva00563ED1 : public Pad20, public FXParticleSystem::LifeEventModuleInfo
{
public:
	void rva00563ED1(Xfer *xfer);

private:
	const void *m_38;
	bool m_3c;
};

void Rva00563ED1::rva00563ED1(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	FXParticleSystem::LifeEventModuleInfo::xfer(xfer);
	*xfer == m_1c;
	*xfer == m_1d;
	*xfer == m_3c;
}
