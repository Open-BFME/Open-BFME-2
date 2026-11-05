# BfmeThingRE consolidation

Inspected base: `1c8e3b235a`, 2026-11-05; owner yasinschroeder-codex3.

## Prerequisite

The current TU map rebuilt by tu_skeleton approves the 36-byte scalar deleting
destructor at 0x006562B0 in BfmeThingRE.cpp. Its donor is
Code/Libraries/Source/DirtySock/Rva006560E0Deleter.cpp. The TU name is provisional;
this is grouping evidence, not recovery of the original filename or class name.
The other 16 mixed sources remain outside this merge.

Initial dry-run rejected the donor for bytes. In a scratch composition verified
through tu_skeleton.Verifier, the destination's /GS flags produced an out-of-line
call to ??1Rva006560E0 instead of retail's inline derived-vptr store and call to
BfmeDirtyBase::~BfmeDirtyBase. An explicit __forceinline on the destructor did not
change that result and was reverted. /GS /EHs-c- matches all 40 combined rows;
adding the donor's /MD would change three existing direct CRT calls to IAT calls.
Only /EHs-c- is added to the destination. No inline hint or /MD is retained.

Verification before the prerequisite commit:

- ./build.sh BfmeThingRE.cpp: 39/39 exact; 36 string literals and two imports checked.
- find_declared_unmatched.py: passes for both original files.
- link_check.py: both LINKS, 2,830 -> 2,830 bytes, index c95fcfcfcd (2026-11-05 05:17).
- tu_skeleton --merge --dry-run: accepts both files, 40 rows, no rejected donors;
  link guard preserves both previously linked units.
- No matches in header_queue, ms_header_queue, gate_baseline, data-check or
  code-identity registers for either source. The donor has two present-unmatched
  hatch keys; these must transfer through the merge tool, without retirement.

No real link, census, nightly or smoke measurement was run.

## Applied merge and tooling audit

After prerequisite da09453b6d, regenerated the supported consolidation planner
and applied tu_skeleton --merge (same 40-row composition; no rejected donor).
The tool removed one source, moved its only function row and its tu_map source
cell, and transferred both present-unmatched keys to BfmeThingRE.cpp. The map
was not regenerated on disk; only the moved row's source column changed.
No debt was retired. The existing alternatename and address-global hatches stay.

Final checks:

- ./build.sh BfmeThingRE.cpp: 40/40 exact, 36 literals and two imports verified.
- find_declared_unmatched.py: passes (all defined functions already matched).
- check_csv.py and git diff --cached --check pass.
- Merge link guard: both previously linked units retained through one object;
  selected COMDAT/provider-consumer checks passed. Final link_check: destination
  LINKS with 2,830 authored bytes; total equals the former 2,794 + 36 bytes.
  The preview's per-destination increase is a move, not a census gain.
- No donor/destination keys in header_queue, ms_header_queue, code-identity,
  data-check or gate-debt registers. Existing destination data-ledger owners,
  flag override and symbol pins stay in place. No new data binding is introduced.
- Path audit covers the complete outgoing batch from origin/master at
  1c8e3b235a plus the staged merge: searched old full path, basename and directory
  assumptions across tools, hooks, workflows, code/includes, root build/config
  files, ledgers/registers and docs. No active tooling or include references
  require updates. The only remaining old basename hits are the historical
  link_status.csv census row, two recipe comments, the generated provenance
  comment in the merged TU and this evidence file. Historical re_attempts.log
  entries remain untouched. Active function/map/hatch ownership is repointed;
  no body-owner, data-row, doxygen input or fold-proof entry names the donor.

The 16 mixed sources remain prerequisites for further consolidation; none were
split or moved here. The final file retains the donor's ordinary inline empty
destructor and emission-only constructor. Game/menu, real-link and census
confirmation remain with their scheduled maintainers.
