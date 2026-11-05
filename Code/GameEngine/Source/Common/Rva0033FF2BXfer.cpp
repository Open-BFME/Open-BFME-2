// cl: /MD
//
// ?xfer@AIInternalMoveToState@@MAEXPAVXfer@@@Z, retail 0x0033FF76, 180 bytes.
// Target C10DE8 slot2 name getter identifies AIInternalMoveToState; slot3
// points to this33FF76 body. WB E04E30 names DoXfer at AIStates.cpp2644;
// ZH protected xfer supplies the release method spelling. The existing
// dtor remains under its independent Rva0033FF2B name in Rva0033FF2BDtor.cpp.
// Version(1,3) via Xfer
// slot 0x28 then Coord at +0x20 via slot 0x60 plus PathfindLayer at +0x30
// via rowed XferPathfindLayerEnum 0x00305D0A plus bool at +0x49 via slot
// 0x90 plus Coord at +0x34 via slot 0x60 plus uint at +0x44 via slot 0x78
// plus version<3 dummy uint via slot 0x78 plus bool at +0x48 via slot 0x90
// plus TheAudio (data 0x009FE6E8) xferAudioHandle at AudioManager slot
// 0x160 for +0x40 plus version>=2 bool at +0x4B via slot 0x90 plus float
// at +0x2C via slot 0x70. Native ctor33F279 calls State4D73FC and
// establishes the20B state prefix. The audio handle at +0x40 matches the
// rowed dtor; derived
// classes add pointers at +0x4C/+0x68. Recipe is the FlammableUpdateXfer
// Version(1,3) plus audio-handle shape with Rva0045ADC1 add-edi tail.

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

#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferVersion.h"

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

typedef unsigned int AudioHandle;

#include "../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

Xfer *XferPathfindLayerEnum(Xfer *xfer, int *value);

#include "../../Include/Common/StateMachine.h"

#include "../../Include/GameLogic/AIInternalMoveToState.h"

void AIInternalMoveToState::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	*xfer == asBase(m_goalPosition);
	XferPathfindLayerEnum(xfer, &m_goalLayer);
	*xfer == m_waitingForPath;
	*xfer == asBase(m_pathGoalPosition);
	*xfer == m_pathTimestamp;
	if (version.m_minimum < 3) {
		unsigned int dummy;
		*xfer == dummy;
	}
	*xfer == m_adjustDestinations;
	if (TheAudio != 0) {
		TheAudio->xferAudioHandle(xfer, &m_ambientPlayingHandle);
	}
	if (version.m_minimum >= 2) {
		*xfer == m_4B;
		*xfer == m_2C;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?xfer@AIInternalMoveToState@@UAEXPAVXfer@@@Z=?xfer@AIInternalMoveToState@@MAEXPAVXfer@@@Z")
