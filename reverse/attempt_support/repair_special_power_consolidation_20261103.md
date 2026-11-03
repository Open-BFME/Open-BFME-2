# RepairSpecialPower consolidation, 2026-11-03

Scope: `Code/GameEngine/Source/GameLogic/Object/SpecialPower/RepairSpecialPower.cpp`
and its `RepairSpecialPowerAtObject.cpp` donor. Prerequisite commits were
`ff4503fb32` (canonical base) and `0a8cf24ddb` (declaration reconciliation),
as rebased by runner publication. The merge was applied at `0a8cf24ddb`.

## Evidence and change

The initial `tu_views.py` trial accepted no donor: the seed used a private
12-byte BehaviorModule plus two secondary interfaces, while the donor used
ModuleBase plus BehaviorModuleInterface and SpecialPowerModuleInterface. The
views also disagreed about the declared virtual methods. This reproduced the
prior consolidation deferral in `reverse/re_attempts.log`.

The canonical BehaviorModule already contains the interface at +0x0c. Including
its header and removing the seed's extra ModuleInterface preserves the
SpecialPowerModuleInterface at +0x10. Both files now declare the same relevant
methods. `header_adopt_lane.py accept --class BehaviorModule` passed and retired
one queue entry in the first prerequisite commit. No shared header changed.

`tu_skeleton.py --merge` then accepted both files (six rows), removed the donor
and repointed its one function row. It transferred the three remaining header
queue entries and refreshed the Microsoft-header queue through its owning tools.
The only tu_map change is the moved row's source column, not regenerated routing.
The map's approval is provisional grouping evidence, not proof of an original
retail filename; the evidence planner reported no independent path route.

## Verification

- Before merging: normal scoped build, six of six rows exact; both current
  objects predict LINKS (148 and 75 census bytes).
- Applied merge: normal scoped build, six of six rows exact; string, float and
  import reference checks pass. Declared-unmatched check passes with the one
  existing destructor hatch retained. EH label renumbering is verified against
  the parent graph; no new function row or hatch was admitted.
- Merge link guard: both inputs census-linked. Current merged-object preview:
  LINKS, 223 census bytes. The 148-to-223 per-file change is transferred ownership,
  not an increase in total linked coverage. Index: 2026-11-03 20:03, `8661f15284`.
- `check_csv.py`, staged `tu_ownership.py`, `check_case_collisions.py` and
  `git diff --cached --check` pass. The refreshed consolidation snapshot passes
  `name_lane.py consolidate --check build/consolidation` after composition.

## Path and register audit

Audited the outgoing RepairSpecialPower changes through the staged merge, with
the sole deletion `RepairSpecialPowerAtObject.cpp` mapped to `RepairSpecialPower.cpp`.
Searched the old basename/path across tools, hooks, workflows, source/includes,
configuration, docs and reverse metadata. No active tooling or include depends on
the removed file. Remaining references are the source-provenance comment and
historical census/attempt records. The function ledger, source-only TU-map row
and header queue point to the surviving unit. No affected data/code-identity,
gate-baseline or Microsoft-header debt key names the deleted file. The existing
present-unmatched destructor hatch and local-static data owners stay on the seed.
No alternatename was removed. Compiler flags are the seed's /DNDEBUG /MD /EHsc;
the merged relative includes retain the same directory and targets. The source
file count falls by one, with all six matched rows retained.

Remaining: ConstIntGetters4.cpp and Rva00493DEFDerived.cpp are mixed owners and
were not split or edited. Their three RepairSpecialPower rows remain outside
this TU. The existing destructor hatch remains. The three transferred canonical
header queue entries require their own accept verdicts. No new census or game
smoke result is claimed; publication still runs the ordinary batch link audit.
