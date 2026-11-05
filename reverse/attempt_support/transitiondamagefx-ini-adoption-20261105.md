# TransitionDamageFX INI adoption

Inspected `bdbf2ed06c`, 2026-11-05. The approved seed TU now includes
`Common/INI/INI.h` instead of its private INI declaration. The seven parser
accesses use the canonical public `m_sepsColon` field: the header documents
the native pointer at +0x420. This preserves the previous direct loads;
calling the canonical out-of-line accessor would add calls absent from retail.

`./build.sh Code/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp`
passes 58/58 rows, 13 unwind pins, 28 literals plus two empty-string references,
and five named imports. The frozen-file check passes. The registered
`header_adopt_lane.py accept --class INI` byte/link guard passes and retires
exactly this source's one INI queue row. No header, row, source path or other
debt register changes.

The consolidation pass remains blocked; this adoption does not claim a merge
or census coverage gain. LINK-002 tracks the separate record/vector and
destructor contracts.
