// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0056ABD6@Rva0056ABD6@@QAE_NPAULivingWorldArmy@@PAVRva00318C32Ret@@@Z,
// retail 0x0056ABD6 (80 bytes, RET 8): slot 4 of the Rva0056ACFF_B1 table
// 0x0086D160, after the slot-1 forwarder 0x0056ABCB (Rva0056AC26Derived.cpp).
// The receiver is unused. The living-world logic singleton must first accept
// the army (rowed 0x002B4BC9); then its region manager (+0xB0) validates the
// army's entry from its current region (pinned getter 0x00318C32) into the
// target region (0x0020EC99, LivingWorldRegionManager::ValidateArmyRegionEntry
// per WorldBuilder), accepting results 0 and 1, the same test as the rowed
// LivingWorldLogic::rva002B27B5. Address-named storage views.
typedef int Int;

struct LivingWorldArmy;
struct Rva002B4BC9Arg;
class Rva00318C32Ret;

#include "../../Include/GameLogic/Rva00318C79Owner.h"

#include "../../Include/GameLogic/LivingWorldRegionManager.h"

class Rva002B4BC9
{
public:
	bool rva002B4BC9(Rva002B4BC9Arg *arg);
};

struct Rva0056ABD6Logic
{
	unsigned char m_pad00[0xB0];
	LivingWorldRegionManager *m_regionManager;	// +0xB0
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva0056ABD6
{
public:
	bool rva0056ABD6(LivingWorldArmy *army, Rva00318C32Ret *target);
};

bool Rva0056ABD6::rva0056ABD6(LivingWorldArmy *army, Rva00318C32Ret *target)
{
	if (!((Rva002B4BC9 *)TheLivingWorldLogic)->rva002B4BC9((Rva002B4BC9Arg *)army))
		return false;
	LivingWorldRegionManager *manager = ((Rva0056ABD6Logic *)TheLivingWorldLogic)->m_regionManager;
	Int result = manager->ValidateArmyRegionEntry(army, ((Rva00318C79Owner *)army)->rva00318C32(), target, 0, 0);
	return result >= 0 && result <= 1;
}
