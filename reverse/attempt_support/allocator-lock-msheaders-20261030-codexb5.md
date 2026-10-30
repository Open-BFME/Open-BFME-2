# Allocator lock wrapper: SDK declarations

2026-10-30, base `335b60649d17`, owner `yasinschroeder-codexb5`.
Scope: `Code/GameEngine/Source/Common/System/Rva00035080Finish.cpp`,
claimed through the Microsoft-header picker.

The unit used private `dllimport` declarations of EnterCriticalSection and
LeaveCriticalSection with `void *` parameters and `throw()`. It now includes
the VS2003 Platform SDK's windows.h and converts the existing opaque lock
pointer to CRITICAL_SECTION at each call. `/EHsc` preserves the nonthrowing
C API contract. This follows the already verified sibling
Rva00034D10Snapshot.cpp and its snapshot-msheaders-20261029-codexb4 evidence;
it does not establish a new allocator type identity or layout.

Verification:

- `find_declared_unmatched.py` passes before and after the source change.
- The baseline and final `./build.sh` checks pass the one 120-byte row at
  0x00035080 and both named imports. The ordinary source build populates the
  shared cache; no manual compiler invocation was used.
- `eh_verify.py` reports EXACT for the wrapper.
- The current Microsoft-header auditor reports clean with no analysis error.
  Its scoped `refresh_queue` API removes only this unit's queue row (two
  local definitions), reducing the register from 937 units to 936. Unrelated
  entries are preserved byte-for-byte.
- Before/after object comparison using link_census readers preserves all
  three COMDAT fingerprints (35-byte guard constructor, 23-byte destructor,
  120-byte wrapper), all eight external symbol records, the empty weak-external
  set and the complete object-reference graph.
- `link_check.py --prepare-current` verifies the explicit provider with a
  strict reusable receipt. Ordinary preview retains LINKS 119 -> 119 authored
  bytes against the 2026-10-29 15:08 index at `85f6b7f40c`. That count excludes
  the row's final padding byte; it is not a census gain.
- The staged-tree `link_batch_audit.py` exits 2: the index predates the base,
  and the affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Carry that consumer and the wrapper into the next scheduled census;
  full consumer closure remains unverified.

Scratch logs and object comparison are under
`build/allocator-lock-msheaders-codexb5/`.

Selection checks: the default picker first served stlport_list_int.cpp and
AttributeModifierAuraUpdateCtor.cpp. Current previews already retain LINKS
for 67 and 128 authored bytes respectively. Their claims were released
without source edits; no new linking repair is claimed for those stale picks.

Reference freshness: official BFME 1 upstream was fetched at
`cbf0388859fe614622171543c509f33fdbdd7beb`. The previously verified gitlink
`efb2b2a27078c6e96538a8c587438b72b675d6df` is retained. Earlier old-input full
gates remained incomplete (see the existing blocked BFME 1 refresh handoffs).
This scoped SDK cleanup neither advances the reference nor records freshness
success; old/new full-gate verification remains pending.
