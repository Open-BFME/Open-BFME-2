// cl: /O1 /G7 /MD /EHs /arch:SSE /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// Semantic source lead: BF1 2f243e26d PathfinderDestructor.cpp, with target
// offsets from172B2F213F..2F21EB and the native unwind table. Snapshot +4,
// sixteen40B layers +60, zone-manager accessed prefix +460,64 AsciiStrings
// +1BFBC, tree +1C1C0 and two owned allocation pointers are target evidence.
// Zone-manager full size is unresolved; an explicit gap preserves that fact.
// Native Snapshot name getter2F21EB returns the literal "Pathfinder".
// The target primary tableC05408 has seven entries (BF1/ZH has five); their
// opaque declarations describe slot count only, not recovered signatures.
#define BFME_SNAPSHOT_NAME_SLOT
// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "Common/Snapshot.h"
#include "ascii_string.h"
#include "../../../Include/GameLogic/PathfindLayer.h"
class PathfindZoneManager {public: ~PathfindZoneManager(); private:char storage[0x1BA54];};
class Rva002EE9B7 {public: ~Rva002EE9B7(); private:char storage[8];};
struct PathfinderAllocation { void *pointer; ~PathfinderAllocation(){if(pointer)free(pointer);} };
class PathfindServicesInterface {public: virtual void slot0()=0;virtual void slot1()=0;virtual void slot2()=0;virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;};
class Pathfinder : public PathfindServicesInterface, public Snapshot {
public: ~Pathfinder();
private:
 virtual void slot0() = 0; virtual void slot1() = 0; virtual void slot2() = 0; virtual void slot3() = 0; virtual void slot4() = 0; virtual void slot5() = 0; virtual void slot6() = 0;
public:
 virtual void loadPostProcess() = 0; virtual const char *GetSnapshotName()const = 0; virtual void xfer(Xfer*);
private:
 char unknown08[0x60-8];
 PathfindLayer layers[16];
 PathfindZoneManager zones;
 char unknown1BEB4[0x1BFBC-0x1BEB4];
 AsciiString strings[64];
 char unknown1C0BC[0x1C1C0-0x1C0BC];
 Rva002EE9B7 tree;
 char unknown1C1C8[4];
 PathfinderAllocation allocation1;
 char unknown1C1D0[0x1D1F0-0x1C1D0];
 PathfinderAllocation allocation2;
};
Pathfinder::~Pathfinder(){}
