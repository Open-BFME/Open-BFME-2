# RainOfFireUpdate destructor merge audit

Base: `31039f1b5a`; fetched origin/master: `db634570ce`.

The supported `tu_skeleton.py --merge` absorbs RainOfFireUpdateDtor.cpp into
the address-approved RainOfFireUpdate.cpp. Four source columns move in each of
functions.csv and tu_map.csv; the map's approvals and evidence are unchanged.
There are 13 matched rows in the resulting TU, totaling 1,321 bytes. One C++
source is removed. The constructor and both mixed-source rows remain separate.

Verification:

- `./build.sh` verifies 13/13 rows, two string literals, 13 float literals and
  both renamed funclet labels through their parent EH graphs.
- `eh_verify.py`: two parent graphs, both EXACT, no missing objects or debt.
- `find_declared_unmatched.py`: all definitions matched.
- `check_csv.py`, case-collision checking and staged TU ownership pass.
- Strict `link_check.py --prepare-current` succeeds for the composed TU.
  The merge's census guard accepts the original TU, destructor and constructor.
  The final two-source preview reports LINKS: main TU 1,192 -> 1,321 bytes,
  constructor 135 -> 135, against census `2f0cb97f52` (2026-11-04 16:16).
  The 129-byte increase in the destination is the absorbed donor, not a census
  gain. The original three-source total and final two-source total are 1,456.

Debt, identities and bindings:

- No destructor-source keys occur in the data, code-identity, header or
  Microsoft-header debt registers. The merger ran their supported queue refresh;
  no queue change was needed. The destination's Display, TerrainLogic and View
  header obstacles remain.
- The existing Secondary20 alternatename moves verbatim. `hatch_counters
  --update`, called by the merger, transfers its source key with totals kept.
  It remains link-wide; no claim is made that other objects no longer need it.
- Enforced converged data checking reports 11 addresses, no second names or
  unjudged rows. Shadow data checking retains the compiler-local guard-name
  discrepancy at 0x00A03CF8 (`$S2` versus the ledger's `$S1`).
- Staged code identity reports the retained alias as unreferenced in the
  destination object. This is recorded, not retired. The merge link guard and
  final constructor preview cover the sibling constructor's table bindings;
  external consumer selection still awaits the normal census and outgoing
  batch audit.

Tooling compatibility audit:

The complete pending range from fetched origin/master through HEAD and the
staged merge has one path removal: RainOfFireUpdateDtor.cpp ->
RainOfFireUpdate.cpp. Searches for the old path and basename found no active
tool, hook, workflow, build/configuration or source-include consumer. Remaining
mentions are the destination's provenance comment, the deleting-destructor row's
historical notes, old attempt evidence, the historical LINK-168 repair record,
and the census-owned link_status.csv entry. The active source columns and hatch
key resolve to the destination. No historical record or census status is edited.

Remaining prerequisites: constructor Secondary20 explicit-table declaration
conflict; the mixed ConstIntGetters4.cpp and ModuleDataBuildFieldParse.cpp rows;
normal census confirmation for all external consumers. This closes only the
destructor composition obstacle.
