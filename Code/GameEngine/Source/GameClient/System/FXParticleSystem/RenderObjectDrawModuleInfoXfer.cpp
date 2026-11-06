// cl: /Ireference/shims/bfme2_ascii /MD
// ?DoXfer@RenderObjectDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
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

#include "../../../../Include/Common/BfmeXfer.h"

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
	virtual void DoXfer(Xfer &xfer);

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

void FXParticleSystem::RenderObjectDrawModuleInfo::DoXfer(Xfer &xfer)
{
	xfer.Version1();
	xfer == m_flag;
	xfer == m_name0;
	xfer == m_value00;
	xfer == m_value01;
	XferParticleShaderType(&xfer, &m_value02);
	xfer == m_name1;
	xfer == m_value10;
	xfer == m_value11;
	XferParticleShaderType(&xfer, &m_value12);
	xfer == m_name2;
	xfer == m_value20;
	xfer == m_value21;
	XferParticleShaderType(&xfer, &m_value22);
	xfer == m_enabled;
	xfer == m_type;
}
