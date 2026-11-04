# RespawnBody canonical DamageInfo and consolidation boundary

2026-11-04; inspected revision `10b67cc307d6`.

Applied: replace the private eight-byte-prefix DamageInfo view in
`Code/GameEngine/Source/GameLogic/Object/Update/RespawnBody.cpp` with the
registered `GameLogic/Damage.h` declaration. The existing source-ID read now
uses its canonical `m_sourceID` field, still at complete-record offset +8.
No inheritance, virtual slot, pin, alias, ledger row or source path changes.

Verification:

- Normal `./build.sh` passes 6/6 rows (424 bytes), including literal and
  relocation checks, before and after the change.
- `tools/class_cleanup.py`'s runtime-graph comparison reports identical
  non-debug section bytes, symbolic relocations, external definitions, weak
  routes and COMDAT policies. Both source versions were compiled exclusively
  through `./build.sh`; the final modified version was rebuilt afterward.
  Full graphs: [runtime comparison](respawn-body-damageinfo-20261104-codex5.json).
- `find_declared_unmatched.py`: all defined functions already matched.
- `eh_verify.py`: both parents EXACT; no baseline or missing object.

Header retirement was attempted through `header_adopt_lane.py accept --class
DamageInfo`, which refused because `link_check.py` produced no per-unit verdict.
The unit is absent from the census index (initially census `171fb36062`; after
the supported `--fetch-index`, published index `a62ac1c10b`, dated 07:28 UTC,
census `5a13f2cd61`). Ordinary preview explicitly says "not in census ... so not
previewable". The DamageInfo queue row remains untouched. This is missing
measurement evidence, not a claim of a false rejection or a byte failure.
No census-linked, image-ownership, debt-retirement or runtime gain is claimed.

The original selected merge was not applied. Current-input planner
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/
--out build/consolidation/respawn` reports the existing destination as
mixed-or-incomplete with a path-keyed data-ledger prerequisite; its snapshot
passed `--check` before the runtime-comparison rebuild. The merge dry-run
approves 18 rows but rejects the only clean donor, `Body/RespawnBodyCtorThunk.cpp`,
with C2511: the kept RespawnBody view lacks its constructor. `tu_views.py
--dry-run` identifies the structural conflict: the seed models a secondary
interface with no base clause; the ctor donor derives from its private
ActiveBody. ActiveBody is already registered, so an additional private shared
view is not an acceptable remedy. Four mixed files remain untouched.

Next work: reconcile complete-object/secondary-interface declarations through
canonical ActiveBody and its existing BodyModule hierarchy in a separately
verified change. Then rerun the merge planner and dry-run. After a scheduled
census includes RespawnBody.cpp, rerun ordinary link preview and the exact
DamageInfo acceptance command above; retire the header queue row only if that
owning verdict passes.
