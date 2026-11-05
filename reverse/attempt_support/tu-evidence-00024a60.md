# TU evidence: 0x00024A60..0x00024CC0

Inspected 2026-11-05 at `1d123cff0d`; owner `yasinschroeder-codex5`.

The picker served 16 rows in eight sources with no map signal. The neighbouring
rows propose different provisional TUs (`BfmeRangeAM.cpp` below and
`BfmeThingQB.cpp` above), so address proximity supplies no common bracket.

Checks:

- `python3 tools/tu_evidence.py --source Code/GameEngine/Source/Common/Rva0082BEC0Copy.cpp`
  emitted the CSV header and no evidence rows.
- `python3 tools/name_lane.py consolidate --under Code/Libraries/Source/STLport/`
  reported 15 source files, 15 unresolved files, zero groups, zero routed rows
  and no missing inputs.
- The claimed sources contain placeholder helpers, the standard exception
  destructors and `__Named_exception`'s constructor. The ledger and attempt log
  already document the BFME 1 byte twins and exception identities. These are
  existing matched owners, not missing coverage.
- `reverse/symbols.csv` already pins `_STL::__get_c_string` to 0x00024C20,
  whose body is rowed as `rva0082C160Deref`; `NamedException.cpp` emits the
  typed implementation. That is an identity-cleanup lead, not evidence for
  the original emitting TU. It does not authorize moving the row.

Target facts: current row ownership and absence of a re-derived placement.
Donor facts: BFME 1 byte twins and STLport declarations. Neither donor paths
nor helper semantics establish a BFME 2 TU. Header-inline COMDATs may be emitted
by different consuming objects (`docs/consolidation.md`, whole upstream files).

Blocked on a hard target path/name anchor or an independently anchored retail
layout bracket. Re-run the map/evidence tools after such evidence lands; do not
assert a TU or repoint these rows based on their library-like names alone.
No source, pin, coverage or TU-map changes were made. Claims released.
