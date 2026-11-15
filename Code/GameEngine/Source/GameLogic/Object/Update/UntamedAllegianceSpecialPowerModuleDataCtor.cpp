// cl: /O1 /MD /DNDEBUG
// ??0UntamedAllegianceSpecialPowerModuleData@@QAE@XZ at retail 0x004C72D3.
// Default ctor over opaque intermediate base 0x004930A0 (pinned); vtable
// 0x00C5E7A8 only, no trailing members. Target identity: ModuleFactory
// registers the data factories 0x2524B2 (UntamedAllegianceSpecialPower),
// 0x2526DF (ManTheWalls/SplitHorde), 0x252768 (Repair) and 0x25287D
// (HordeDispatch); all four new 0x7C with this one folded ctor. Named after
// the lowest-address registration; the other three classes fold here.
#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

class UntamedAllegianceSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	UntamedAllegianceSpecialPowerModuleData();
};

UntamedAllegianceSpecialPowerModuleData::UntamedAllegianceSpecialPowerModuleData()
	: SpecialPowerModuleData()
{
}

// The destructor is implicit: retail's deleting destructor 0x004C2A84 (slot 0
// of the table 0x00C5E7A8) calls 0x004C8AB0, a bare tail jump to
// ??1SpecialPowerModuleData with no store of this class's table.
