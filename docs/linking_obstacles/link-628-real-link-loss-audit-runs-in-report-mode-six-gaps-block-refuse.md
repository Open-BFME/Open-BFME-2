### LINK-628: real-link loss audit runs in report mode; six gaps block refuse
Status: Open (report mode landed; refuse mode blocked). Updated: 2026-11-07; inspected revision: the
landing batch on 6186dccaff.

Evidence / affected units: `tools/link_batch_audit.py` (`real_link_losses`, `import_supplies`,
`import_request_reader`, `reference_reader`, `bridge_copy_reader`, `report_real_link_losses`),
`tools/vtable_bridge.py` (`copy_refusal`, `strong_names`, shared with the planner). Origin:
[LINK-626](link-626-pin-only-destructor-bindings-leave-13-names-undefined-in-the-real-link.md), where four
pushes removed wrong-but-present destructor bodies and the real link lost 13 names while the push audit,
which rejudges only census-`linked` units, passed them.

What the check does: for an outgoing batch it reports every name a kept real-link input references (symbol
table or `/INCLUDE`) that resolved before the batch and resolves no more after it, from object symbol tables
and directives alone (no census verdict, no `symbols.csv` pin). Resolution follows the real link: a
definition among `exit_link.py`'s inputs (placement objects omitted), msvcrt.lib/oldnames.lib, an import
member `exit_link.py` would generate (requests from `link_cycle.undefined_imports` /
`undefined_plain_imports` over the kept files, `link_cycle.import_def_entries`, CODE thunk unless a section
defines the symbol), an `/alternatename` chain (cycle-safe), or the referrer's own weak default. A loss is
`REAL-LINK LOSS`; a finding whose only referrers could not be read, or whose name the vtable bridge's own
copy rules (`vtable_bridge.copy_refusal`) would still let it emit, is `REAL-LINK LOSS CANDIDATE`.
`REAL_LINK_LOSS_MODE = "report"`: findings print and the exit code is unchanged, and the audit no longer
prints "no linking regression found" after real-link findings. In `refuse` mode a loss on an exact base
exits 1 and a candidate exits 2 (UNVERIFIED, not blocking).

Completed: landed in report mode after five Codex review rounds and three targeted re-checks; each
round's reproductions are tests in `tools/tests/test_link_batch_audit.py` (115 tests; each of 56 reverts of
the rules fails one). On the objects saved for LINK-626's four commits (99051e8efb, 0b28664ee5, 8e618085ec,
9e1df1c621) it reports all 13 names as losses, none as candidates. `vtable_bridge.copy_refusal` /
`strong_names` were factored out of `plan()` unchanged: `plan()` over srv1's full object set (17,957 inputs)
gives identical entries, refusals and already-correct tables (5,145 tables, 273 refusals).

Known gaps (each found by review or declared at landing):
- (a) Weak-only references as import requests. Where the audit cannot run `link_cycle`'s helpers on a file
  (a changed or removed object's before-state, whose earlier file is gone, or an unreadable file) it takes
  requests from the index's names less the object's own section definitions; those names include weak
  externals, which `undefined_imports` (storage class EXTERNAL only) never requests. Can pass a loss.
- (b) Runtime-library names reached only through an `/alternatename` target are taken as resolved; it is
  not verified that link.exe searches msvcrt.lib/oldnames.lib for an alternate target. Can pass a loss.
- (c) Vtable bridge slot rules are not judged (retail slot extents, slot target resolution, archive import
  members): a name whose neighbours pass `copy_refusal` is a candidate, not a pass.
- (d) The bridge also adds address bindings it discovers from matched code to its ambiguity check; the
  audit reads the data ledger's addresses only. A disagreement makes a candidate.
- (e) Indexed `strong` entries can be absolute symbols (section -1), but `link_cycle.defined_externals`
  requires section > 0; the audit's section-definition reads (plain-request filter, DATA entry, the
  before-state stand-in) count an absolute as defined (`tools/link_batch_audit.py` `in_section`,
  `own_definitions`). Can drop a real request.
- (f) Unindexed units (added by `--update-index`) are read through `link_census.object_symbols`, which
  classifies a COMMON record as defined and leaves out its import request, so an unindexed COMMON
  `__imp__socket@12` disagrees with the real request reader (`import_request_reader`). Can drop a real
  request.

Remaining / next check: (a), (b), (e) and (f) block switching `REAL_LINK_LOSS_MODE` to `refuse`; (c) and (d)
only make candidates (exit 2). Fix (e) and (f) by reading section numbers and storage classes from the files
(`import_request_reader` already does for kept files; an index storing per-object storage/section would let
the before-state use the same rule). Close (a) for the before-state by recording each object's import
requests in the census index. Settle (b) with a native link of a one-object alias to an msvcrt.lib name.
Then the switch to `refuse` is its own reviewed `Verifier-Change` commit; read the report-mode lines on
real pushes first.

Clearance: pending (refuse mode). Census confirmation: not claimed; this check reads object files and the
census index, it does not change census figures.
