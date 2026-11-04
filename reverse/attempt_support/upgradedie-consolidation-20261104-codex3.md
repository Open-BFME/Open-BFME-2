# UpgradeDie consolidation audit, 2026-11-04

Scope: base `29dd15067d`, prerequisite `ac88cd6cd5`, and the accompanying
mechanical merge of `UpgradeDieOnDie.cpp` into
`Code/GameEngine/Source/GameLogic/Object/Die/UpgradeDie.cpp`.

The evidence planner surveyed `Code/GameEngine/Source/GameLogic/Object/Die/`
before both reconciliation and application. Its original-path and donor hints
do not themselves approve placement. `tu_skeleton.py` rebuilt the stale TU map
in memory and approved this move; the committed map changes only the moved
row's source column. Mixed `DieModuleDerived.cpp` stays untouched.

The first merge trial failed because the donor's private `UpgradeDie` view
lacked the seed's constructor and module-key declarations. `tu_views.py`
restored its symmetric rewrite because adding `onDie` to the standalone seed
introduced an external reference. Instead the prerequisite adds only the
seed's existing declarations to the donor. Its single body still byte-matches.
`header_adopt_lane.py accept --class Player` passed and retired the donor's
one header-queue row in that prerequisite commit.

Verification of the applied merge:

- `tu_skeleton.py --merge`: two files accepted, five rows, no rejected donor;
  census-linked guard passed for both original units. That guard compares
  provider/consumer bindings, selected COMDATs and outside-unit losses while
  replacing the two objects with their composition.
- `./build.sh UpgradeDie.cpp`: 5/5 matched, including both EH rows. The renamed
  compiler label `$L4039` was verified through the parent's EH data against the
  ledger's `$L441` at `0x0078C106`; one literal verified.
- `find_declared_unmatched.py`: all definitions matched.
- `link_check.py UpgradeDie.cpp --new-variants`: exit 0.
- Ordinary link preview: LINKS, file-local LINKED 120 -> 238 bytes, census
  index `8661f15284` dated 2026-11-03 20:03. This absorbs the donor, so these
  file-local numbers are not a gain in headline linked coverage.
- `check_csv.py` and staged whitespace check passed.

Debt and report ownership: neither file has code-identity, data-check, hatch
or flag-override baseline keys. The data ledger's two static-key globals
already belong to the destination. The donor's header debt was retired only
through acceptance. Merge report refresh found no remaining header or
Microsoft-header queue entries for either path. No aliases or pins changed.

Tooling compatibility audit covers this batch's only removed path,
`UpgradeDieOnDie.cpp`. Combined basename/path searches across tools, hooks,
workflows, Code, docs and reverse found no active hard-coded consumer to
update. `functions.csv` and the existing map source column were repointed by
the merge tool. Remaining mentions are the destination's donor-origin comment,
historical `reverse/link_status.csv`, LINK-166 and the historical module-base
obstacle entry; preserve them. Relative include resolution retains the same
directory. No fold proof or other path-keyed source owner names the donor.

Result: one fewer source file, all five matched rows retained. The next census
should measure the merged UpgradeDie TU; no new census, real link or runtime
smoke result is claimed.
