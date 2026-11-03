### Group-merge and allocate-copy STLport 4.6 moves (2026-10-30)

`Common/Rva00283114GroupMerge.cpp` (f1f69f5166) and
`Common/Rva0008A1D0AllocateCopy.cpp` now select STLport 4.6. The group merge's
gen-alias allocate at 0x00068E15 takes the non-const QAE spelling shared by the
other 4.6 allocate rows there; the QBE key is tombstoned in
`reverse/deleted_rows.csv`. Its only other user,
`SkirmishAI/AIStatCollector/AIStatCollector.cpp` (still 4.5.3), defines its own
COMDAT of the QBE allocate in its object (checked in its `build/match` object's
symbol table), so no provider was lost. The allocate-copy unit keeps its private
vector/allocator views and only takes 4.6's `__false_type` (as
`Rva00568D68AllocateCopy.cpp` did). Both files byte-verify 9/9; no census gain
is claimed. Carry both units into the next scheduled census.

Follow-up moves the same day apply the same recipe to nine more units:
`HordeContain/Rva00474483ConfigureSlots.cpp`, `HordeContainModuleDataParse.cpp`,
`CreateAHeroRegistry.cpp`, `LivingWorldLogicDelayedEventXfer.cpp`,
`Rva002BA8F1AddPlayer.cpp`, `SiegeDockingBehaviorInitializeBones.cpp`,
`ScriptEngineDoXfer.cpp`, `AIWall.cpp` and `LivingWorldLogic.cpp` each rename
their typed allocate alias at 0x00068E15 from QBE to QAE (old keys
tombstoned). That rename was the missing step in the earlier recorded
ConfigureSlots, HordeContain, AIWall and LivingWorldLogic blocks. Two units also
needed small adaptations: `AIWall.cpp` drops `const` from its game-free
`deallocate` specialization and deletes its `_STLP_alloc_proxy::deallocate`
specialization, which is C2995 under 4.6 because the proxy only inherits it.
`LivingWorldLogic.cpp`'s `Rva002444BEAllocator` gains a `rebind` member. Every
file byte-verifies, 328 rows in all. Any 4.5.3 consumer of the renamed QBE
spellings was not checked one by one; read the pre-push batch audit and carry
these units into the next census. No census gain is claimed.

The two remaining owning-return clone units, `Rva00406CD3Clone.cpp` and
`Rva00567FBCClone.cpp`, follow `Rva004E74A0Clone.cpp`. Each clone and its
`__ehhandler$` take 4.6's class-key spelling `?AV?$auto_ptr@...`, and the old
`?AU` keys are tombstoned. The funclet rows keep their `$L` keys and their
`parent=` follows the new spelling; the gate verifies them past the renumbered
labels. 5/5 and 4/4 rows byte-verify. No unit outside the two files names the
clone symbols: the vtables in `Rva00406BB0Ctor.cpp` and `Rva00567847Copy.cpp`
declare neither clone nor any auto_ptr. Carry both units into the next census.
