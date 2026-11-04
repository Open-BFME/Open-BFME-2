// cl: /MD
//
// WindModuleInfo::DoXfer(Xfer&), retail 0x003A547E, 226 bytes.
// Target export and native Wind info vtable slot 3 establish the owner.
// Slot 7 (offset 0x1C) of vtable 0x0081BF84 (class of
// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
// in Code/GameEngine/Source/GameClient/FXParticleSystemModules.cpp).
// Ghidra labels DoXfer. Evidence: IsLightCRC early-out via Xfer slot 0x10,
// Version1 via rowed 0x000053EE, int at +0x04 via rowed XferWindMotion
// 0x0030606A, floats at +0x08-0x38 and +0x40-0x44 via Xfer slot 0x70, char at
// +0x3C via Xfer slot 0x8C. Layout is wind-motion plus float block.
// Recipe is PoisonedBehaviorXfer slot pattern with Xfer decl copied verbatim.

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

#include "../../../../Include/Common/BfmeXfer.h"

void XferWindMotion(Xfer *xfer, int *value);

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

#include "../../../../Include/GameClient/WindModuleInfo.h"

// Retail export names this owner; BE15A4 slot3 and the same field accesses
// independently establish WindModuleInfo and its reference-transfer ABI.
void FXParticleSystem::WindModuleInfo::DoXfer(Xfer &stream)
{
	Xfer *xfer = &stream;
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	XferWindMotion(xfer, &m_04);
	*xfer == m_08;
	*xfer == m_0C;
	*xfer == m_10;
	*xfer == m_14;
	*xfer == m_18;
	*xfer == m_1C;
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
	*xfer == m_2C;
	*xfer == m_30;
	*xfer == m_34;
	*xfer == m_38;
	*xfer == m_3C;
	*xfer == m_40;
	*xfer == m_44;
}

// ?rva003A5757@Rva003A5757@@UAEXPAVXfer@@@Z, retail 0x003A5757, 28 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0081C60C (class of ??0Rva003AED3E@@QAE@ABV0@@Z
// in ConcreteModuleTemplateCopyCtors.cpp). Chain from 0x003A547E: Version1 via
// rowed 0x000053EE, then inner wind-motion block at +0x1C via rowed 0x003A547E.

class Rva003A5757
{
public:
	virtual void anchor();
	virtual void rva003A5757(Xfer *xfer);
	char _pad04[0x18];
	FXParticleSystem::WindModuleInfo m_1c;
};

void Rva003A5757::rva003A5757(Xfer *xfer)
{
	xfer->Version1();
	m_1c.FXParticleSystem::WindModuleInfo::DoXfer(*xfer);
}

class INI;
#include "../../../../Include/Common/INI/FieldParse.h"
#include "../../../../Include/Common/INI/INI.h"
namespace FXParticleSystem {
// Export names the five-entry native enum table at C1B6C4; the null terminator
// and next datum bound its complete 20 bytes.
extern const char * const WindMotionNames[] = {
    "NONE", "Unused", "PingPong", "Circular", 0
};
// Descriptive table name inferred from the native 3A5560 parser reference.
// C1B420..C1B4F0: twelve 16-byte records followed by the null record.
extern const FieldParse WindFieldParse[] = {
    { "WindMotion", INI::parseIndexList, WindMotionNames, 0x0c },
    { "WindStrength", INI::parseReal, 0, 0x10 },
    { "WindFullStrengthDist", INI::parseReal, 0, 0x14 },
    { "WindZeroStrengthDist", INI::parseReal, 0, 0x18 },
    { "WindAngleChangeMin", INI::parseReal, 0, 0x24 },
    { "WindAngleChangeMax", INI::parseReal, 0, 0x28 },
    { "WindPingPongStartAngleMin", INI::parseReal, 0, 0x30 },
    { "WindPingPongStartAngleMax", INI::parseReal, 0, 0x34 },
    { "WindPingPongEndAngleMin", INI::parseReal, 0, 0x3c },
    { "WindPingPongEndAngleMax", INI::parseReal, 0, 0x40 },
    { "TurbulenceAmplitude", INI::parseReal, 0, 0x48 },
    { "TurbulenceFrequency", INI::parseReal, 0, 0x4c },
    { 0, 0, 0, 0 }
};
}
namespace FXParticleSystem {

template <int CATEGORY>
class DefaultModuleTemplate
{
public:
	void parse(INI *ini);
};

template <>
void DefaultModuleTemplate<7>::parse(INI *ini)
{
	ini->initFromINI(this, WindFieldParse);
}
}
