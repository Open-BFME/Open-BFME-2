# AODHordeContain callback GeometryInfo adoption

2026-11-04; inspected base `a1ad5f0db7`.

The default picker selected consolidation into
`Code/GameEngine/Source/GameLogic/Object/Contain/AODHordeContain.cpp`.
The supported planner ran under `Code/GameEngine/Source/GameLogic/Object/Contain/`.
Its original-path witness at 0x0047B6DB names the nested
`Contain/HordeContain/AODHordeContain.cpp`; the parent-path destination remains
the TU skeleton tool's freshly rebuilt approved assignment. The planner's
WorldBuilder alternatives are hints, not approval for a manual path move.

## Applied change

`AODHordeContainOnContaining.cpp` includes canonical `Common/Geometry.h`
before `GameClient/Drawable.h`, so GeometryInfo establishes its required
Snapshot variant. Remove the private one-byte GeometryInfo view. Its field
still starts at Object+0xA8, now ends at +0x104 (canonical sizeof 0x5C), and
the following gap ends at +0x258. The AI pointer remains +0x258 and the
experience pointer +0x264. Target instruction RVA 0x0047A3F5 loads
`[esi+0x264]`; no donor layout is asserted. No class, virtual slot, pin,
alternate name, source path or ledger ownership was changed.

Verification:
- `./build.sh Code/GameEngine/Source/GameLogic/Object/Contain/AODHordeContainOnContaining.cpp`:
  1/1 function rows exact; string, float and import checks pass.
- `find_declared_unmatched.py` passes before and after the edit.
- `header_adopt_lane.py accept --class GeometryInfo` on this source: PASS,
  retired exactly its one header-queue row through the owning workflow.
- `link_check.py` on the source: LINKS, LINKED 72 -> 72 bytes; index census
  2026-11-04 02:25 at `5a13f2cd61`.
- `check_csv.py`: OK, functions 99434, symbols 9338, data rows 2269.

This removes one header debt item; no new census-linked bytes are claimed.

## Consolidation boundary

Before the edit, `tu_skeleton.py --merge` dry-run rebuilt the stale map in
memory, found 33 approved rows across eight files, and accepted no donor.
Four mixed sources stayed in place. Rejections:
- onContaining: missing declarations in the kept AODHordeContain/HordeContain views.
- Rva0047AC8F: LocomotorSet requires a different Snapshot variant.
- xfer and pool key: missing methods in the kept class view.
- destructor and both STLport helpers: byte mismatches under shared flags.

`tu_views.py --dry-run` confirms incompatible HordeContain base clauses,
AODHordeContain's base missing in the pool-key view, and the pre-edit Object
GeometryInfo extent conflict. The applied adoption fixes only the callback's
canonical GeometryInfo prerequisite. Reconcile the native base/virtual
contracts and compiler configurations before retrying the full merge; do not
combine views by adding arbitrary virtuals. No merge or source-file reduction
was applied. Existing alternate-name routes and their hatch lines are retained.
No active data/code-identity or MS-header key names this callback; its one
GeometryInfo header key is retired solely by the acceptance command above.

## Other picker lead

Before selecting this TU, the picker served W3DGameClient.cpp's already repaired
factory blocker (LINK-179). Current `link_check.py` reports LINKS 0 -> 351 bytes
against `5a13f2cd61`, confirming the later repair's preview. Its obstacle already
requests the next census; no changed prerequisite or new obstacle was found.
That claim was released without source changes.
