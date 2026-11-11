// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs
// Native 0x000532B7..0x0005333F, 136 bytes, RET4: Xfer flag virtual 0x90 then BfmeAudioEventPrefix136(ref 0) release xfer rva002D9FD9 return m_int0C else 1. Evidence: rowed EH_prolog 0x629188 BfmeAudioEventPrefix136 ctor 0x2D97D6 Release 0x50ED3 dtor 0x2D9A43 pin rva002D9FD9 0x2D9FD9; callers 0x5983F 0x59859; ret 0x4 (thiscall; ECX unused).
#include "Common/BfmeAudioEventPrefix136.h"
// The prefix xfer at 0x002D9FD9 is the rowed Rva002D9FD9Owner::rva002D9FD9
// (Rva002D9FD9Seq.cpp).
class Rva002D9FD9Arg;
#include "../../Include/Rva002D9FD9Owner.h"

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;

#include "../../../GameEngine/Include/Common/BfmeXfer.h"

// The native state transitions and temporary Release_Ref call prove that
// the null reference argument owns its temporary lifetime through the call.
struct Rva000532B7TemporaryRef : OpaqueRefElement4 {
};
// A MilesAudioManager member: its xfer caller 0x000596E9 passes the manager
// in ECX (the body never reads it), RET 4 either way.
#include "../../Include/MilesAudioDevice/MilesAudioManager.h"
int MilesAudioManager::rva000532B7(Xfer *xfer)
{
	bool flag;
	*xfer == flag;
	if (flag != 0) {
		BfmeAudioEventPrefix136 prefix(Rva000532B7TemporaryRef(), 0);
		((Rva002D9FD9Owner *)&prefix)->rva002D9FD9((Rva002D9FD9Arg *)xfer);
		int result = prefix.m_int0C;
		return result;
	}
	return 1;
}

// Native [0x5333F,0x5335x),19B: releases the refcounted object at +0x88 of the
// holder's +4 target when that pointer is set; the final release is a tail jump.
// Address-derived names: the holder and its target layouts are not proven.
struct Rva0005333FTarget
{
	unsigned char pad00[0x88];
	OpaqueRefCounted m_ref88;
};
struct Rva0005333FHolder
{
	int m_00;
	Rva0005333FTarget *m_target04;
	void rva0005333F();
};
void Rva0005333FHolder::rva0005333F()
{
	if (m_target04)
		m_target04->m_ref88.Release_Ref();
}
