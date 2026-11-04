# AudioLoopUpgrade declaration prerequisites, 2026-11-04

Inspected base: `ebfad6d325`; scope: the approved
`Code/GameEngine/Source/GameLogic/Object/Upgrade/AudioLoopUpgrade.cpp` TU and
its four clean donors. The picker claimed all five files. No row or path moved.

## Completed source repair

Replaced the TU-local `SoundHolder` at module-data +8 with the existing
`OpaqueRefElement4` header. Both initialize the four-byte pointer to null and
release a non-null `OpaqueRefCounted` in their inline destructor. The upgrade
implementation donor already uses `OpaqueRefElement4` for that field. Made the
+0xC delay unsigned, matching that donor and the rowed field table's
`INI::parseDurationUnsignedInt` callback. This does not establish a new donor
name or an original BFME source path.

Verification after both changes:

* `./build.sh .../AudioLoopUpgrade.cpp`: 17/17 matched, 1 data row verified;
  the two renumbered funclet labels resolve through their parents' EH data.
* `find_declared_unmatched.py`: all defined functions already matched.
* `link_check.py .../AudioLoopUpgrade.cpp`: LINKS, 680 -> 680 census-linked
  bytes against the 2026-11-04 02:25 index at `5a13f2cd61`.
* No protected-register key retired, no hatch added and no alias removed.

## Remaining consolidation prerequisites

The initial `tu_skeleton.py --merge ... --dry-run` accepted no donor. The
current `tu_views.py --dry-run` no longer reports the module-data +8 field-type
conflict. Its `--class AudioLoopUpgradeModuleData --no-merge-check` application
trial was restored automatically: the full declaration needs `DieMuxData`'s
definition in the upgrade-implementation donor (C2079). The original prefix
declaration remains there; no nonmatching source was retained.

The canonical `DieMuxData` has a default constructor. The seed's existing
private declaration has none and calls `m_die124.init()` explicitly after
`m_member14.construct()`. Merely including the canonical header in the seed
would add an earlier constructor call. Reconcile this initialization sequence
before adopting that header or retrying a complete module-data view.

`AudioLoopUpgrade` itself still has incompatible base clauses: the seed uses
`UpdateModule, UpgradeMux, ALU_Iface4`; the implementation donor spells a
different interface; the xfer and load-post-process donors use members in
place of bases; the update donor uses adjusted-this prefix views. Canonical
`UpgradeMux` adoption and these method/subobject views remain prerequisites.
No new census or source-file reduction is claimed.

## Header acceptance false reject

`header_adopt_lane.py accept --class UpdateModule .../AudioLoopUpgrade.cpp`
refuses `does not #include Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`.
The first directive is `#include "GameLogic/Module/UpdateModule.h"`; the source's
`// cl:` includes `/ICode/GameEngine/Include`. The current byte-verifier's
dependency receipt records the canonical header with digest
`764cb1af7a436e80b850ce6501f75f48`.

`includes_header()` accepts a suffix only when no other tracked header shares
it, ignoring the actual include roots. Six unrelated shim headers share that
suffix. The already-passing compile and receipt resolve this unit's directive
to the canonical header. No include respelling, gate change or queue deletion
was used to bypass the rejection. Next tooling check: resolve includes in the
unit's actual compiler search order, with shadow-header regression coverage,
before retrying the two stale UpdateModule queue rows.
