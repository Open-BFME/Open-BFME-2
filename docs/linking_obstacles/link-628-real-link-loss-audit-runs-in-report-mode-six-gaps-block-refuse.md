### LINK-628: real-link loss audit runs in report mode; six gaps block refuse
Status: Open (report mode landed; refuse mode blocked). Updated: 2026-11-08; inspected revision: the
landing batch on 6186dccaff; the INCONCLUSIVE section below re-checked against 3b141964e7.

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

Why most pushes print INCONCLUSIVE (measured 2026-11-07 on srv1, master 46c764cbb8): the audit proves an
object current only through `link_census.object_current`, i.e. `build.compile_is_current(strict=True)`: a
version-2 receipt whose include search inventory still matches, or a header-free version-1 one. Only
`link_census.py --build`, `link_check.py --prepare-current` and `link_cycle.py` (`compile_rows(strict=True)`)
compile with `inventory=True`. The pre-push
hook's scoped gate, `./build.sh` and every worker compile call `try_compile_source(inventory=False)`, which
writes version 1, so a source the hook has just byte-verified fails the audit ("N source object(s) lack
current receipts", exit 2), and so does any consumer compiled the same way ("affected consumer lacks current
receipt"). Target facts:
- Receipts in caches: worker seat5 `build/match` 337 version-2 of 18,431 (1.8%), 5,004 header-free version-1
  (these pass), 13,090 (71%) fail strict. The census runner's cache: 16,400 version-2 of 22,802. An ops seat
  restored from the object store after 3,443 commits: 6,419 version-2 of 18,578 (the store returns the
  newest variant, a census-compiled one when the census compiled last). The runner's follower cycles write
  that cache too: on 2026-11-08 one restored 6,746 TUs from the store, nearly all as version 1 with headers,
  leaving 9,645 version-2 of 22,804 and 6,991 version-1 with headers. A strict compile on master at 3b141964e7
  still writes version 2 (two TUs, 110 and 118 headers), so this is the store's choice of variant, not a
  change in what the census writes.
- Inventory durability, once written: for 400 sampled ledger TUs, the in-repo search roots' inventories
  (tracked files, rebuilt from `git ls-tree`) were unchanged after 6 h, changed for 2% after 12 h and 5%
  after 24 h (1,353 master commits in 48 h). So receipts are missing, not going stale.
- Cost of writing them everywhere: `search_inventory` takes 0.07 s per TU uncached (50 TUs; 300 TUs share a
  cache in 7.1 s), run before and again after each compile (`_inventory_problems`): about 0.14 s on a Wine
  `cl` of 1-3 s, so +5-10% on TUs actually compiled and nothing on current ones.
Remaining prerequisites (structural inference, not yet tried): (1) make ordinary compiles record the
inventory (`compile_rows`/`try_compile_source` default), keeping `input_proof` census-only; (2) do not lose
the object store: `try_compile_source` skips `_restore_object` whenever `inventory` is set, so (1) alone turns
every restore into a compile; restore must instead prefer a stored version-2 variant and accept it only when
its inventory matches now (one inventory per restored TU, cacheable per `compile_rows` call); (3) the TUs
whose search cannot be inventoried (macro or `..` includes, headers outside the search roots) stay
unprovable outside a census and keep the audit inconclusive when touched. Their count is not settled: 226
and later 265 version-1 receipts with headers in the runner's cache on 2026-11-07, both upper bounds because
follower cycles write the same kind of receipt. Separately, `compiler_command` re-verifies the STLport overlay
(`stlport_overlay.materialize` -> `verify_tree`) twice on every call: 210 s of a 330 s single-core currency
check over 17,961 objects, so a per-process memo would cut every currency check, including this audit's
([proposal, not scheduled](../stlport_overlay_memo_proposal.md)).

Design: [strict receipts](../strict_receipts_design.md). Only its step 0 has landed: each audit run appends a
line to `<git common dir>/link_audit_verdicts.jsonl` (e2b22f90d4, 104cd6d6a8; readers drop `"base": "a"`,
`"tip": "b"` fixture lines). The rest is not scheduled; the owner will revisit it once the log has a real sample
of INCONCLUSIVE rates (2026-11-08: 9 real lines, 3 inconclusive, all for missing receipts).

Clearance: pending (refuse mode). Census confirmation: not claimed; this check reads object files and the
census index, it does not change census figures.
