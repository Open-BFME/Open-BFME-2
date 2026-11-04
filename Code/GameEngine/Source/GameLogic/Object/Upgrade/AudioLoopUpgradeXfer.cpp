// cl: /MD
//
// ?xfer@AudioLoopUpgrade@@MAEXPAVXfer@@@Z, retail 0x004B7E75, 72 bytes.
// Virtual slot 3 (offset 0x0C) of vtable RVA 0x00858CC4 (VA 0x00C58CC4,
// class of rowed dtor ??1AudioLoopUpgrade@@MAE@XZ at 0x004B7B20 in
// AudioLoopUpgradeDtor.cpp): Version(1,1) via Xfer slot 0x28 then TheAudio
// (data 0x009FE6E8) xferAudioHandle at AudioManager slot 0x160 for +0x2C
// then base UpdateModule xfer via rowed 0x44DF9F then UpgradeMux base at
// +0x20 via rowed 0x004CE397. Layout is UpdateModule base 0x20 plus
// UpgradeMux base plus iface vptr at +0x28 plus int m_2C (size 0x30 per
// rowed factory news 0x30 and rowed ctor 0x4B7CBC). Recipe is the
// FoundationAIUpdateXfer audio-handle shape plus the RadiateFearUpdateXfer
// Update-plus-mux tail.

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

typedef unsigned int AudioHandle;

struct BfmeAudioEventPrefix136;
class Xfer;

#include "../../../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class AudioLoopUpgrade;

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

// The constructor and destructor in AudioLoopUpgrade.cpp establish these
// secondary bases at +0x20 and +0x28; the audio handle follows at +0x2C.
class ALU_Iface4 { public: virtual void rva004B7E3C(int) = 0; };

class AudioLoopUpgrade : public UpdateModule, public UpgradeMux, public ALU_Iface4
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	AudioHandle m_2C;
};

void AudioLoopUpgrade::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	TheAudio->xferAudioHandle(xfer, &m_2C);
	UpdateModule::xfer(xfer);
	UpgradeMux::upgradeMuxXfer(xfer);
}
