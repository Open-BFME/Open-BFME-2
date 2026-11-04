# CitadelSlaughterHordeContain constructor consolidation

Inspected revision: `e09de4ce5a`, 2026-11-04. Scope:
`Code/GameEngine/Source/GameLogic/Object/Contain/CitadelSlaughterHordeContain.cpp`
and its five separately compiled fragments. The supported planner was refreshed
before composition; its path hints alone were not used as TU approval.
`tu_skeleton.py --merge` rebuilt the current TU map in memory and accepted the
constructor at RVA `0x0048059F` (91 bytes) into its provisionally approved TU.
The committed map is left unchanged, per the consolidation-lane rule.

## Completed and verified

- Reconciled the constructor's base and derived class views with the seed in
  separate verified commits. The explicit primary-vptr store preserves retail's
  store order under the shared `novtable` declaration.
- Kept `_ReadWriteBarrier`'s declaration and intrinsic pragma together in an
  `extern "C"` block. The composer otherwise hoisted the pragma before the
  declaration and emitted a five-byte external call in place of the intrinsic.
- The supported merge absorbed only `CitadelSlaughterHordeContainCtor.cpp`;
  source count falls by one. All 16 destination rows byte-match, including the
  complete 91-byte constructor. `find_declared_unmatched.py` reports no unrowed
  definitions. `check_csv.py` passes (99,442 function rows).
- `eh_verify.py` reports EXACT 3/3 EH graphs, no missing objects or baseline
  exceptions. The normal build verifies six emitted funclet placements despite
  compiler-label renumbering. Microsoft-header check and diff checks pass.
- `link_check.py` previews LINKS for the merged TU, 638 own bytes, against the
  census of 2026-11-04 12:23 at `40fe1783d7`. Before composition the seed and
  constructor both previewed LINKS, 547 + 91 bytes. This is preservation of
  scoped preview results, not a measured LINKED or ownership gain. The merger's
  census-linked donor guard also passed.

## Debt, bindings and path-consumer audit

Audited `origin/master..e09de4ce5a` plus the staged merge: the earlier outgoing
commits contain no source-path moves. The only absorbed path in this batch is
`CitadelSlaughterHordeContainCtor.cpp` to `CitadelSlaughterHordeContain.cpp` in
the same directory. Search covered its full path and basename in `tools/`,
`.githooks/`, `.github/`, `Code/`, `docs/` and `reverse/`; directory placement
does not change. No active tool, include or configuration consumes the old path.
The remaining old-path mentions are the historical census receipt in
`reverse/link_status.csv` and the composer's donor-provenance comment.

The constructor row moved once, with its status, size and notes preserved.
The merge transferred all nine data-ledger records (three source fields and
six path-qualified local symbols); their addresses, identities and counts did
not change. The existing secondary-table bindings and primary table binding
remain those of the constructor's standalone object. No pin, alias, hatch,
flag override, class registration or fold proof was added or removed.

Narrow register searches found no constructor key in the identity, data-check,
header, Microsoft-header, hatch or override registers. The merger refreshed
header-source ownership and rescanned the destination's Microsoft-header queue;
neither queue needed a diff. The destination's MultiIniFieldParse header debt
and the residual donors' AI/AIUpdateInterface/AICommandInterface/Rva000421C8
header debt remain at their existing owners. No debt is claimed retired.

## Remaining composition prerequisites

The four rejected fragments remain unchanged and retain their standalone rows.
The three behavior fragments fail composition on the existing header/declaration
order (notably ObjectID), missing private-view members, and a template
specialization conflict in `CitadelSlaughterHordeContainRva00480E9A.cpp`.
Reconcile those views in independently verified commits before another merge.

`CitadelSlaughterHordeContainModuleDataDtor.cpp` still needs a compatible
ModuleData class contract: the seed's non-novtable view causes a vptr store in
the composed destructor. A trial removing `novtable` from the standalone donor
added six bytes at compiled offset 17 (retail has no such store), so that trial
was reverted. Its 74-byte row at `0x004811E6` remains matched in the original
source. Check how to retain constructor vptr initialization and suppress the
destructor's store together; do not repeat merely dropping `novtable`.
