# AODCrushCollide destructor consolidation

2026-11-05; parent `af98c0bb19`; claim owner `yasinschroeder-codexb5`.
Continues [LINK-322](../../docs/linking_obstacles/link-322-aodcrushcollide-destructor-view-blocks-tu-merge.md).

## Change and routing

The supported consolidation planner surveyed 46 Collide sources in seven groups.
Its stale committed-map view approved no trial; `tu_skeleton.py` rebuilt routing
from current inputs before its successful guarded dry run and application.
It absorbed `AODCrushCollideDtor.cpp` into the approved, provisional
`Code/GameEngine/Source/GameLogic/Object/Collide/AODCrushCollide.cpp` TU.
The two moved rows are the destructor at 0x004BBEDD (32 bytes) and scalar
deleting destructor at 0x004BC050 (28 bytes). Only their source columns changed
in functions.csv and tu_map.csv; the map was not regenerated on disk.
One Code source file is removed, with no newly recovered bytes claimed.

The prior external-vtable guard rejection no longer occurs against the local
official index dated 2026-11-05 05:17, revision `c95fcfcfcd`. Fetching the
published index confirmed the same revision. The merge guard reports all three
considered units census-linked and accepts the destructor donor.

## Verification and registers

- `./build.sh` on the resulting TU: all 13 rows exact (966 bytes); source,
  string, float and import checks pass. Its two renumbered funclet labels are
  verified through their parent EH data.
- `find_declared_unmatched.py`: all defined functions matched, before and after.
- `eh_verify.py`: both EH-bearing rows EXACT, no missing objects or baselines.
- `link_check.py` on current TU and retained family donor: both LINKS, 966 and
  56 bytes respectively. The TU's census figure was 906 bytes; the 60-byte
  difference is the absorbed donor, not a headline linking gain.
- `check_csv.py`, staged `tu_ownership.py`, and whitespace checks pass.
- Staged code identity (shadow) reports one divergent CollideModuleInterface
  constructor COMDAT. The link preview identifies its three-byte copy versus
  the majority nine-byte copy as unreferenced, diagnostic only; it is not a
  link blocker. No code-identity baseline is changed.
- No removed-donor keys occur in the header/MS-header queues, code-identity,
  data-check or hatch registers; no debt is retired. The merge tool refreshes
  destination header/MS-header reports, with no queue changes needed.
- Enforced converged data check: 11 addresses, zero second names or unjudged
  rows. Shadow data check reports three findings in the destination:
  duplicate-def/wrong-name `_DRAWABLE_FRAMES_PER_FLASH` at 0x00A0403C and
  wrong-name local static guard `$S3` at 0x00A04038. These findings remain
  unresolved; no data identity repair or baseline admission is claimed.

## Tooling compatibility audit

Audited the pending path changes over origin/master through parent `af98c0bb19`
plus this staged merge. The earlier pending commit has no source moves; this
batch removes only AODCrushCollideDtor.cpp. Searched old path/basename in tools,
hooks, workflows, source/include consumers, configuration, active ledgers and
registers, and documentation. No executable consumer or include names the
deleted file. Remaining mentions are source provenance comments, historical
attempt evidence and the census-owned link_status.csv snapshot. Preserve those
historical references. There are no donor data rows or fold-proof references
to repoint, and no aliases or hatches are removed. The merge's link guard and
current previews validate the affected provider/consumer composition; this is
not a new census or full-game link.

## Remaining prerequisite

`FamilyDeletingDtors_muse-95ab.cpp` remains intact with both rows and its
DominateEnemySpecialPowerModuleData header-queue debt. Its merge now stops at
C2511: the destination's AODCrushCollideModuleData view does not declare the
donor's synthetic `EmitVtableTag *` constructor. `tu_views.py` also reports a
novtable declaration conflict for that class. Reconcile this declaration and
emission contract in a separate byte-verified prerequisite commit before
retrying the family donor; do not discard its other row or retire its debt.
ModuleNameGetters3.cpp and CollideModuleDataBuildFieldParse.cpp remain mixed
and are not moved. Census confirmation is awaiting; no smoke run was started.
