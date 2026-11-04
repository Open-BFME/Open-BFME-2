# ExperienceLevelSystem hash-clear composition (2026-11-04)

Prerequisite: 6c98398c11 reconciles the three hash-table views and real STLport
pair. The separate qualified-type parser fix preserves `Outer::Node` rather
than discarding it as a duplicate of `Outer`. Its regression tests failed
before the fix; pytest passes 236 tests, skips one existing test, and passes
63 subtests across test_tu_skeleton.py and test_gate_exploits.py.

The supported consolidation planner snapshot passed its currency check before
application. `tu_skeleton.py --merge
Code/GameEngine/Source/GameLogic/System/ExperienceLevelSystem.cpp --dry-run`
accepted the seed and Common/Rva00289371HashClear.cpp; normal `--merge` then
reverified and applied that composition. One source file is removed. Only the
two source columns for 0x00289164 and 0x00289371 change in functions.csv and
tu_map.csv. No TU assignment or approval is changed; the map is not regenerated.

## Verification and bindings

- `./build.sh` on the merged TU passes 48/48 function rows and both data rows,
  including EH parent graphs, strings and imports. The five function rows in
  Common/ExperienceLevelSystem.cpp remain independently verified. The original
  three-source scope retains all 53 function rows and both data rows.
- `find_declared_unmatched.py`, check_csv.py and `git diff --check` pass.
- The merged object preserves every retained COMDAT digest and symbolic
  relocation: 257 original union COMDATs become 256, and 259 external
  definitions become 258. The only removed provider is the unrowed
  `_List_base<BfmePod264>` destructor; there are no added or changed COMDATs.
- That destructor's prior 23-byte body is identical to the rowed
  `_List_base<crateCreationEntry>` destructor except its clear-callee spelling.
  The existing BfmePod264 destructor pin names 0x002889A4; its clear pin names
  0x002887EA. The retained crateCreationEntry owners at those addresses are
  byte-verified in this TU. Thus the 74 external dependencies exchange the
  BfmePod264 clear for the already-pinned base destructor. No pin or alias is
  added or removed. The pair/list destructor copies retain their digests.
- The merge's own link guard passes. Ordinary `link_check.py` reports LINKS
  for the merged 2933 authored bytes and Common's 239: the original complete
  3172-byte scope is preserved. The apparent +101 in the per-file preview
  reflects the absorbed donor; it is no census or real-link gain. The known
  unreferenced `_Destroy<BfmePod264>` diagnostic remains.

## Registers and path-consumer audit

Audited the entire pending range from origin/master plus this staged merge.
The ledger's path changes are ToppleUpdate -> Rva004A8091Xfer (one row),
TransportAIUpdate -> TransportAIUpdatePrivateAttackPosition (three rows), and
this hash-clear -> ExperienceLevelSystem composition (two rows). The first
pair of old sources remain present; the only deleted source is this donor.
Searched their full basenames and new paths in tools, .githooks, .github,
Code, docs, reverse and root build/config files, including include consumers.
No active tooling or build consumer needs an update. The only tooling hits
are unrelated StructureToppleUpdate ledger-guard fixtures. Remaining mentions
of the deleted donor are the TU's provenance comment, historical attempt
evidence, and the historical link_status.csv census observation. These are
retained; the next scheduled census must measure the composed provider scope.

The donor has no code/data identity, data-ledger, flag-override, header or
Microsoft-header queue key. The merge's supported register refresh leaves the
destination's existing header keys intact and refreshes Microsoft-header
results. hatch_counters --update leaves the hatch register unchanged. No debt
is retired, no baseline line is removed, and no Debt-Retired trailer is used.
The existing wider TU blockers remain; this clears only the hash-clear donor
and its qualified nested-type composition prerequisite.
