# SplitUpgrades CRT header cleanup

Base: `7032de9ba0`, 2026-10-30. Source:
`Code/GameEngine/Source/Common/System/SplitUpgrades.cpp`.

The Microsoft-header picker served the file's local `_mbscpy` and `strtok`
declarations. The source now includes the toolchain's `<string.h>` and
`<mbstring.h>`, passing unsigned-character pointers to the latter's real
prototype. A saved/restored `_CRTIMP` configuration around only mbstring.h
preserves the existing direct `_mbscpy` thunk call while string.h retains
the imported strtok declaration. Compilation flags, game interfaces, ledger
rows, pins and source paths are unchanged.

Verification:

- Normal builds before and after preserve the complete 199-byte row, its
  delimiter literal, empty-string reference and named strtok import.
- Frozen-source checks pass before and after. The Microsoft-header auditor
  reports clean; its `refresh_queue` API removes exactly this file's queue
  entry (two local declarations), preserving unrelated records. The auditor's
  existing unresolved STLport include-closure diagnostics remain unchecked;
  this is clearance of the two local CRT declarations only.
- All 15 external COMDAT name/digest/size records, one strong definition,
  12 undefined names and zero weak bindings are identical before and after.
  The CRT references remain `__mbscpy` and `__imp__strtok`. The supported
  strict rebuild preserves the same facts. [Comparison](splitupgrades-msheaders-20261030-codex3.json).
- `link_check.py --prepare-current` passes for the explicit source with a
  strict reusable receipt. Ordinary preview retains LINKS for 199 bytes
  against index `85f6b7f40c` (2026-10-29 15:08). This is unchanged preview
  coverage, not a measured census gain.
- CSV validation and `git diff --check` pass.

The staged-tree batch audit is INCONCLUSIVE (exit 2): its index predates
the base and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry this provider and its affected consumers into the next
scheduled census. The unchanged external object facts establish the scoped
preservation above; full consumer closure and census confirmation remain
unverified. No census gain is claimed.

The initial default pick was the remaining Xfer header adoption package.
Inspection of its current source and prior handoffs confirms unchanged
constructor-emission, concrete-reader identity and stream identity
prerequisites. No Xfer source trial was repeated, no Xfer queue row changed,
and the class claim was released before selecting this cleanup.

Raw objects and local diagnostics are under
`build/splitupgrades-msheaders-20261030/`; the checked-in comparison records
the bounded object evidence independently of those scratch files.
