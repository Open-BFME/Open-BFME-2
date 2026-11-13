// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DelayedLuaEventUpdateModuleData constructor lifted from retail.

#include "../../../Include/Common/DelayedLuaEventUpdateModuleData.h"

// ??0DelayedLuaEventUpdateModuleData@@QAE@XZ
DelayedLuaEventUpdateModuleData::DelayedLuaEventUpdateModuleData()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0DelayedWeaponSetUpgradeUpdateModuleData@@QAE@XZ=??0DelayedLuaEventUpdateModuleData@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0HordeTransportContainDamageModuleData@@QAE@XZ=??0DelayedLuaEventUpdateModuleData@@QAE@XZ")
