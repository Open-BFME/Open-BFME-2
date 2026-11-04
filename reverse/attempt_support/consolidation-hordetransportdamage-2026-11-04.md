# HordeTransportContainDamage consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Damage/HordeTransportContainDamage.cpp`; `consolidation_queue.py --check-tu` passed. A fresh Damage-scoped planner and its `--check` passed. The plan had 11 approved rows, three pull donors and one mixed donor.

The merge dry run accepted no donors. `HordeTransportContainDamageCtor.cpp` failed because the constructor is absent from the `HordeTransportContainDamage` class view. `HordeTransportContainDamageCallback.cpp` failed because `rva004BB176` is absent from that view. The mixed `Rva004B96CCDerived.cpp` split matched rows `0x004BB0CC` and `0x004BB15A` alone, but LinkGuard refused the split because the moved destructor and both vtable COMDATs lacked matching private/weak-free context. No changes or claims were made. Class-view and link-context prerequisites are outside this mechanical lane; no source reduction or identity/link progress is claimed.
