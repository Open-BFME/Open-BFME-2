// cl: /Ireference/shims/bfme2_ascii /MD
// ?xfer@RenderObjectDrawModuleInfo@FXParticleSystem@@MAEXPAVXfer@@@Z
// @0x00562871 194B: slot 3 xfer over vtable 0x81C1B8; Version1 then bool
// +0xC, AsciiString/uint/float/int-enum triples at +0x10/+0x20/+0x30, header
// bool/float at +0x4/+0x8. Layout mirrors DefaultCtor; Xfer decl verbatim
// from PoisonedBehaviorXfer; enum via rowed XferParticleShaderType.

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

void XferParticleShaderType(Xfer *xfer, int *value);

#include "ascii_string.h"

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoBase
{
};

class RenderObjectDrawModuleInfo : public RenderObjectDrawModuleInfoBase
{
public:
	RenderObjectDrawModuleInfo();
	virtual ~RenderObjectDrawModuleInfo();

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_enabled;
	float m_type;
	bool m_flag;
	AsciiString m_name0;
	int m_value00;
	float m_value01;
	int m_value02;
	AsciiString m_name1;
	int m_value10;
	float m_value11;
	int m_value12;
	AsciiString m_name2;
	int m_value20;
	float m_value21;
	int m_value22;
};

}

void FXParticleSystem::RenderObjectDrawModuleInfo::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_flag;
	*xfer == m_name0;
	*xfer == m_value00;
	*xfer == m_value01;
	XferParticleShaderType(xfer, &m_value02);
	*xfer == m_name1;
	*xfer == m_value10;
	*xfer == m_value11;
	XferParticleShaderType(xfer, &m_value12);
	*xfer == m_name2;
	*xfer == m_value20;
	*xfer == m_value21;
	XferParticleShaderType(xfer, &m_value22);
	*xfer == m_enabled;
	*xfer == m_type;
}
