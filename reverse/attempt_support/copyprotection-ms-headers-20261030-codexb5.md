# CopyProtection Microsoft-header migration

Inspected base: `3154df1e36`, 2026-10-30. Source:
`Code/GameEngine/Source/Common/System/CopyProtection.cpp`.

Replace the unit's local Windows types, message structure, constants and API
declarations with the VS2003 Platform SDK's windows.h and mmsystem.h. Use the
CRT's string.h for strcmp. The unit's `// platformsdk` setting selects the
Microsoft headers; dependency receipts confirm all three header paths and no
sweep-shim dependencies. No function bodies, compiler optimization flags,
source paths, ledger identities, pins or shared headers change.

Before and after `./build.sh` verify all six function rows and 14 named imports.
The saved original and migrated objects have identical external COMDAT digests
(six), external definition/reference entries (21), and relocation-reference
graphs. In particular, strcmp retains its existing direct external reference.
Frozen-file, ledger and scoped shadow data checks pass.

Strict preparation in the prepared worktree passes for this explicit provider.
The staged identity check reports six rows and zero new findings. Ordinary
preview retains LINKS, 397 -> 397 authored bytes, against index `85f6b7f40c`
(2026-10-29 15:08). This is cleanup, with census confirmation still pending.
The header auditor reports clean; its scoped `refresh_queue` API removes
exactly this source's 24-finding queue entry, preserving unrelated entries.
The final main-checkout build and object comparison pass too.

The staged-tree outgoing audit is INCONCLUSIVE: the index predates the base,
and affected consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
lacks a current receipt. Carry this provider and consumer into the next normal
census. No full consumer closure, measured linking gain or runtime result is
claimed.

The overdue BFME 1 check fetched official upstream `40e7327e50d776c21391bd712c50b3c8745fb7ea`
against verified input `efb2b2a27078c6e96538a8c587438b72b675d6df`. The 70 changed
paths include 28 game source paths and no changed headers or build settings.
The bounded affected-donor placement audit examined 600 rows / 419 native
bodies (14 unique placements); placements alone do not establish recovered
source identities. At the fixed BFME 2 base, the old-input full verification
was stopped with exit 143 after about 20 minutes while restoring cached
objects and materializing STLport inputs, before a function-verification
verdict. No new-input full gate ran. The verified reference pin and success
timestamp remain unchanged; the refresh still needs both full-gate verdicts.

Selection review: the default queue's peerPing data identity remains blocked by
the existing GameSpy static-name/TU prerequisite. The shader-vector fill-insert
unit at 0x001524F9 still requires the coordinated record identity reconciliation
already recorded under LINK-002. Neither source was changed, and both claims
were released before selecting this unit.
