// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Rva0040D43FRun@@YAXPAVLivingWorldBattle@@@Z, retail 0x0040D43F, 46 bytes.
//
// Evidence: the stack callback temp at [ebp-0x10] stores vtable 0x00C394C8
// (the rowed 9-byte ctor ??0Rva0040CFFF@@QAE@XZ 0x0040CFFF), then the rowed
// LivingWorldBattle::rva003F498A (0x003F498A) is called with the temp. The
// EH prolog and state 0 need a destructible temp; an inline-empty
// destructor supplies it without emitting a call on the normal path.

struct Rva0040E0C5Arg;

// The callback root: ??1Rva0040CFFF is the shared 0x005FED52, which stores
// table 0x00C1C780, so the temp derives from it as LivingWorldBattle's
// other callbacks do. Same single slot as Rva0040CFFF's override.
class Rva003F498ACallback
{
public:
	virtual bool rva0040E0C5(Rva0040E0C5Arg *arg) = 0;
	~Rva003F498ACallback() {}
};

class Rva0040CFFF : public Rva003F498ACallback
{
public:
	virtual bool rva0040E0C5(Rva0040E0C5Arg *arg);
	~Rva0040CFFF() {}
};

#include "../../Include/GameLogic/LivingWorldBattle.h"

class Rva003F468D;

#include "../../Include/Common/ArmySummarySystem.h"

void ArmySummarySystem::rva0040D43F(Rva003F468D *arg)
{
	Rva0040CFFF callback;
	((LivingWorldBattle *)arg)->rva003F498A((Rva003F498ACallback *)&callback);
}
