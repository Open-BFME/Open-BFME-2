# UpgradeMuxCtor.cpp canonical UpgradeMux.h trial (2026-11-04, base f50e1dba12)

Target facts: ??0UpgradeMux@@QAE@XZ 0x004CE2A3 (13 B) stores table 0x00C5FF10 and clears +4.
Table slots per UpgradeMux.h's own header comment: 2=0x004CE2B0, 3=0x004CE342, 4/7=0x0047A699,
9=0x00452354, 17=0x000B3FD0.

Trial (not left in Code/): replace the novtable view and `g_00C5FF10` with
`#include "../../../../Include/GameLogic/Module/UpgradeMux.h"` and an out-of-line
`UpgradeMux::UpgradeMux() : m_upgradeExecuted(false) {}`.

- `./build.sh` of the unit: exact (with UpgradeMuxAttemptUpgrade.cpp, 5/5).
- `header_adopt_lane.py accept --class UpgradeMux UpgradeMuxCtor.cpp`: FAIL, link_check predicts a loss.
- `link_check.py UpgradeMuxCtor.cpp`: does not link, LINKED 13 -> 0 (census 2026-11-03 20:03 at 8661f15284):

```
unresolved  ?isSubObjectsUpgrade@UpgradeMux@@UAE_NXZ                    slot 4  -> 0x0047A699 (rowed Xfer::IsCRC etc., fold)
unresolved  ?resetUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z      slot 3  -> 0x004CE342 (rowed ?rva004CE342@Rva004CE342@@...)
unresolved  ?setUpgradeExecuted@UpgradeMux@@UAEX_N@Z                    slot 9  -> 0x00452354 (rowed ?rva00452354@UpgradeMux@@QAEX_N@Z)
unresolved  ?upgradeMuxLoadPostProcess@UpgradeMux@@MAEXXZ               slot 17 -> 0x000B3FD0 (shared empty ret, fold)
unresolved  ?vslot07@UpgradeMux@@UBE_NXZ                                slot 7  -> 0x0047A699 (fold)
unresolved  ?wouldUpgrade@UpgradeMux@@UBE_NABV?$BitFlags@$0IA@@@@Z      slot 2  -> 0x004CE2B0 (rowed ?rva004CE2B0@Rva004CE2B0@@...)
```

Placeholder callers of 0x004CE2B0/0x004CE342 by name (rg, 2026-11-04): StatusBitsUpgradeIfEldestKindofSlot2.cpp,
LevelUpUpgradeMuxSlots.cpp, ReplaceSelfUpgrade.cpp, UpgradeModuleConditionState.cpp, and two link-wide
`/alternatename` pragmas in ReplenishUnitsBehaviorDtor.cpp (lines 72-73) that target the placeholder names.
