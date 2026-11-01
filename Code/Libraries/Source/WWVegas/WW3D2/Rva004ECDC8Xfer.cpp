// cl: /MD
// ?rva004ECDC8@Rva004ECDC8@@QAEXPAVXfer@@@Z @ 0x004ECDC8, 66 bytes.
// Xfer helper for a 0x14-byte element (uint at +0, Coord3DBase at +4, int at
// +0x10) with Version(1,1) via slot 0x28 then uint/Coord/int via
// 0x78/0x60/0x7C. Evidence: callers at 0x004EDB95 and 0x004EDBC7 in 0x004EDA8C
// (Xfer with IsLoading at +0x4 IsStoring at +0x8 Version 0,2 via +0x28 bool via
// +0x90 uint via +0x78 int via +0x7C Coord via +0x60 Ascii via +0x6C); Xfer
// vtable with reversed operator== group copied verbatim from
// Code/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehaviorXfer.cpp;
// Coord3DBase 12B from game/Libraries/Source/WWVegas/WWMath/coord3d.h;
// Xfer::Version 2B from game/GameEngine/Source/Common/System/xfer.h;
// Rva honest-address name since caller class is UNCLAIMED.
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

#include "../../../../GameEngine/Include/Common/BfmeXfer.h"

#include "../../../Include/Lib/Coord3DBase.h"

class Xfer::Version
{
public:
	unsigned char data[2];
};

class Rva004ECDC8
{
public:
	unsigned int m_unk0;
	Coord3DBase m_unk4;
	int m_unk10;
	void rva004ECDC8(Xfer *xfer);
};

void Rva004ECDC8::rva004ECDC8(Xfer *xfer)
{
	Xfer::Version v;
	v.data[0] = 1;
	v.data[1] = 1;
	*xfer == v;
	*xfer == m_unk0;
	*xfer == m_unk4;
	*xfer == m_unk10;
}
