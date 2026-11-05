# AttachUpdate constructor consolidation

Applied after `2ad47b0e1e`, the [canonical-header prerequisite](attachupdate-constructor-header-20261105.md).
The supported Object/Update consolidation survey was regenerated. Its original-path
evidence remains unresolved, with no alternative donor paths; this survey does
not approve placement. The merge engine's fresh in-memory TU map approves the
constructor and its EH handler for AttachUpdate.cpp.

`tu_skeleton.py --merge` absorbs AttachUpdateCtor.cpp into AttachUpdate.cpp,
removes one source file, and repoints two function rows, one data row and two
TU-map source cells. No assignment, evidence or confidence changes in the map.
The module-data constructor is still rejected by the existing STLport
`_Base_bitset` declaration conflict; the earlier vptr prerequisite remains.
Mixed donors and the generated constructor funclet are untouched.

Verification:

- `./build.sh AttachUpdate.cpp`: all 16 code rows and the one 52-byte data row
  match; literal/import checks pass. Renumbered funclet labels verify against
  parent EH data. `eh_verify.py`: EXACT 4/4.
- `find_declared_unmatched.py`: all definitions matched. `check_csv.py`: PASS.
- The merged object's external-definition set equals the pre-merge union:
  39 definitions, none added or removed. Undefined references, weak externals,
  alternatename directives and forced includes equal the pre-merge unions.
  Native tables retain their names; no new derived vtable is emitted. Existing
  shared inline COMDAT providers retain their declarations and bodies.
- `link_check.py`: LINKS at 1,117 authored bytes, equal to 1,018 + 99 before
  composition, using census c95fcfcfcd (2026-11-05 05:17). Its 1,018 -> 1,117
  display is absorption, not new census-linked coverage or a whole-game link.
- Narrow debt-register searches find no ctor/destination gate, code-identity,
  data-identity, hatch, header or MS-header keys. The prerequisite already
  retired the ctor's UpdateModule header key through acceptance. The merge's
  header transfer and MS-header rescan produce no queue diff. Existing data
  ledger globals remain owned by the destination; the table's data row moves
  with its definition. Converged data check passes 11 addresses, zero second
  names or unjudged rows. No debt key or alias is removed by this merge.

Audited all pending source moves after fetching origin/master: this constructor,
the three narrow-streambuf fragments into StdioStreambufBase.cpp, and
StlSweepR3Rva0028681A.cpp into FireLogicSystem.cpp. Upstream advanced during
the session; outgoing-commit and merge-base comparisons distinguish its newer
edits from this batch. Combined old-path/basename searches include tools, hooks,
workflows, source/header includes, root build/config files, registries and docs.
No active filename consumer needs a change. Remaining mentions are provenance
comments, historical obstacle/attempt evidence, link_status.csv and
stlport_trial.csv; the prior streambuf audit covers their historical-to-live
queue mapping. No active ledger still names AttachUpdateCtor.cpp.

The module-data constructor's bitset/vptr repair is the remaining prerequisite;
no new trial of its source was made. No real-link, census, nightly or smoke run
was started. Normal commit and outgoing publication hooks remain authoritative.
