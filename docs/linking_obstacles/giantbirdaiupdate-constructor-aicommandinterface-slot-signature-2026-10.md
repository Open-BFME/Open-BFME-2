### GiantBirdAIUpdate constructor: AICommandInterface slot signature (2026-10-29)

Cleared for `GiantBirdAIUpdateCtor_GiantBirdAIUpdate.cpp` (518 B). Its local
`AICommandInterface` view declared `virtual void aiDoCommand()`, so the
GiantBirdAIUpdate vtable named the nonexistent
`?aiDoCommand@AICommandInterface@@UAEXXZ`. Retail's secondary slot 0 is
`AIUpdateInterface::aiDoCommand(const AICommandParms *)` (0x002673F6, no adjustor
thunk), as in `gamelogic/ai.h` and `module/aiupdate.h`. The view now declares the
pure `AICommandInterface` slot and the `AIUpdateInterface` override. Evidence:
`./build.sh` 6/6 matched; `link_check.py` on the file: LINKS, 0 -> 518 B
(prediction against the 2026-10-28 20:44 census, 840db2d676). Three other
files keep the parameterless view (`GiantBirdAIUpdateOnCollide.cpp`,
`GiantBirdAIUpdateCtor.cpp`, `DozerAIUpdateConstruct.cpp`); they emit no vtable
and already link, so they were left alone.

2026-11-04: `GiantBirdAIUpdateOnCollide.cpp` now adopts canonical AI interfaces; both header-queue rows retired, 238/238 bytes still match and link prediction remains LINKS. [Evidence](../../reverse/attempt_support/giantbird-oncollide-header-20261104-codex.md).

2026-11-04: the main `GiantBirdAIUpdate.cpp` now adopts canonical AI/module bases and state-machine headers; seven queue rows retired with 18/18 byte matches and unchanged 2,249 linked-byte prediction. Remaining merge prerequisites: [evidence](../../reverse/attempt_support/giantbird-main-headers-20261104-codex.md).

2026-11-05: factory/append donors now adopt canonical AIStateMachine, with the append donor using the canonical AI base and slot-30 declaration; four header-queue entries retired, all four checked units still predict LINKS (1,351 bytes unchanged). Remaining merge prerequisites and verification: [evidence](../../reverse/attempt_support/giantbird-state-headers-20261105-codex.md).

2026-11-05: seed/collision declarations now agree; 19/19 rows match and both units still predict LINKS (2,487 bytes unchanged). Next run the guarded composition: [evidence](../../reverse/attempt_support/giantbird-collision-prep-20261105-codex.md).

2026-11-05: guarded merge absorbed the collision donor into the approved GiantBird TU, removing one source file with 19/19 rows preserved and unchanged combined 2,487-byte link prediction. Remaining donor prerequisites and path/register audit: [evidence](../../reverse/attempt_support/giantbird-collision-merge-20261105-codex.md).

2026-11-12: the main caller adopts canonical Rva00368C7A declarations;
the owning accept tool retires its one queue row. Normal build passes20/20
and16 float references, and own preview preserves LINKS2503->2503 against
the published b974574bd6 index. The two implementing TUs remain queued:
their shared4C8 path member still has the distinct Rva00312C95 and
Rva00375A73Context parameter identities in AerialPathfinder. The observed
550-byte prefix does not prove complete class size, and the opaque header
cannot yet replace those field views. Both deferrals and the native offset
map are retained; broader GiantBird/census clearance remains pending.
[Accepted caller and context prerequisites](../../reverse/attempt_support/rva00368c7a-header-20261112.md).
