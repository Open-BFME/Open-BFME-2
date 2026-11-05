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
