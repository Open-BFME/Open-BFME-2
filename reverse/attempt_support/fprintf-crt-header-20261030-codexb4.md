# Format-and-append CRT header cleanup

Base: `a92f873f7e`. Scope:
`Code/GameEngine/Source/Common/FprintfAppendLine.cpp`.

The source already implements the game-side `_fprintf` helper with an object
containing a string vector. Its `_vsnprintf` call imports the CRT function.
Replace that copied declaration with the toolchain's `stdio.h` in
`NativeFormatCrt` and qualify the call. The namespace keeps the header's
FILE-based declaration separate from the existing game helper's signature.
No helper name, caller type, linkage, flags or ledger row changes.

Checks:

- Baseline and changed `./build.sh` pass all three rows and the named import.
- `find_declared_unmatched.py` passes before and after; `eh_verify.py` reports
  one EXACT graph, with no baseline exception. The renumbered unwind label
  remains verified through its parent graph.
- All seven non-debug COFF sections retain their names, sizes, raw bytes and
  relocation counts. All ten external symbol records (name, storage, value and
  definition status), three external COMDAT byte-and-relocation fingerprints
  and weak bindings remain identical.
- Strict current provider preparation passes all three rows. Ordinary preview
  retains LINKS and 118 authored bytes against index `12b9e7a7c0`
  (2026-10-30 10:11 UTC).
- The owning Microsoft-header scan is clean. Its scoped `refresh_queue`
  removes exactly this source's one `_vsnprintf:same` queue entry and
  preserves unrelated records. The header check and CSV validation pass.

The staged outgoing audit is INCONCLUSIVE on the older index and missing
current `Common/0CreateAHeroManager21FE49.cpp` consumer receipt. Full consumer
selection/loss verification remains pending; carry this provider and affected
consumers into the next scheduled census. No census gain is claimed. The
separate game logger identity prerequisite in other callers remains open.

Before selecting this cleanup, the default picker served
`GameWindowManager_registerTabList.cpp`. Its current preview still reports
the known registerTabList COMDAT/selection failure, 0 -> 0 bytes: the native
assignment target is `0x002C54EE`, while the declared GameWindow-pointer list
assignment row owns `0x0046F0C2`. Current rows and prior attempts corroborate
the existing identity prerequisite. No trial, pin or source edit was made;
the claims were released.
