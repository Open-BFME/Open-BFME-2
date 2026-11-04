# DeflectSpecialPower consolidation, 2026-11-04

Base: fe6f69426a. Selected by `next_work.py --claim`, owner
yasinschroeder-codex3. The consolidation planner surveyed SpecialPower;
its stale-map alternatives were hints only. `tu_skeleton.py` rebuilt routing
in memory and approved the constructor at 0x004C5671 for DeflectSpecialPower.cpp
through provisional N grouping. This does not prove the original file name
or intermediate module-data ancestry.

The guarded dry run and application accepted DeflectSpecialPowerModuleDataConstructor.cpp
alongside the existing TU. One source file disappears, one 18-byte constructor
row moves, and all 12 rows (499 bytes) remain exact. Only that row's source cell
in functions.csv and tu_map.csv changed; the committed map was not regenerated.
The composer joins the existing parse declaration with the constructor's
AIUpdateModuleData-derived lifetime view. No alias, pin or hatch was removed.

The other donor, DeflectSpecialPowerConstructorThunk.cpp, remains separate:
composition fails C2512 because the seed derives from Rva00589079 while the
constructor initializes WeaponModeSpecialPowerUpdateBase. `tu_views --dry-run`
confirms the base-clause conflict. The previous destructor-identity prerequisite
in the DeflectSpecialPower obstacle entry remains applicable; no new identity
or ancestry is inferred from this compile failure. ConstIntGetters4.cpp remains
mixed (255 other rows), so its getter cannot move as a whole donor.

## Verification

- Normal `./build.sh` verifies 12/12 rows, including the renumbered static-guard
  funclet through its parent's EH graph; declared-unmatched is clean.
- `eh_verify.py`: EXACT 1/1; data_check shadow: zero findings; converged
  enforced: 11 addresses, zero second names or unjudged rows.
- `check_csv.py`, case-collision check, staged TU ownership and diff whitespace
  checks pass. No protected debt key belongs to the removed donor. The seed's
  Coord3DBase/UpdateModule header rows and the remaining donor's BehaviorModule
  row remain on their existing owners; no header or Microsoft-header key moves
  or retires. Data-ledger local-static owners remain on the destination.
- The guarded composition preserves census-linked inputs. A current-object
  link preview reports DeflectSpecialPower.cpp 481 -> 499, remaining constructor
  78 -> 78, SiegeDeployHordeSpecialPower.cpp 133 -> 133 and AIUpdateModuleDataCtor.cpp
  68 -> 68 against census 2026-11-04 17:56 at 8c757ea0db. Four of four are clean.
  The 18 bytes moved between sources; this is no census coverage gain.
- Code identity remains in shadow mode and reports an identical two-object
  getter definition at 0x004C54B1. The extra copy is in the cached
  Disp8LeaNegSbbGetters object; its current source no longer defines this getter.
  The seed already defined the same macro invocation before this merge.
  This observation is stale-object evidence, not a proven current-source
  duplicate or a new regression; no baseline was changed.
- Scoped naming reviewed all 17 inventory entries, retained existing names and
  applied zero renames. The parent acknowledged the two branch-local `me`
  bindings collapsed into one key and the false-positive `Coord3D` type token
  in unnamed parameters. The inventory is not complete C++ binding coverage.

## Path-consumer audit

Audited origin/master through fe6f69426a plus this merge. The combined removal
set is W3DBridgeCtor.cpp -> W3DBridgeBuffer.cpp, Rva003ED9B1Merge.cpp -> BitRange.cpp,
and DeflectSpecialPowerModuleDataConstructor.cpp -> DeflectSpecialPower.cpp.
Searched the old basenames together under tools/, .githooks/, .github/, Code/,
docs/, reverse/ and build.sh. No active tool, source include, workflow, build
configuration or doxygen input names a removed path. Remaining mentions are
source-provenance comments, historical obstacle/attempt evidence and the
measurement-owned link_status.csv snapshot. The bridge and BitRange audits
remain in their earlier attempt-support files. No includes or compile flags
changed resolution; no internal static definition was removed. Active function
and TU-map source cells name the destination, with surviving debt kept intact.

No census, real-link run or smoke runner was started. Any outgoing link audit
that lacks current provider receipts remains for the next scheduled census;
these previews establish only their explicitly named four-unit scope.
