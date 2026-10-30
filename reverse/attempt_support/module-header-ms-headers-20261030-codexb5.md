# Module-header writer Microsoft-header cleanup

Base: `c9c0fea9be`, 2026-10-30. Source:
`Code/GameEngine/Source/GameClient/Rva0055C9A0Write.cpp`.

Replace the local C `free` declaration with `<stdlib.h>`. The unit uses
`/D_CRTIMP=` to retain direct CRT declarations. Target disassembly proves that
the call at RVA `0x0055CA45` is `e8 e6 3d ad ff`, reaching the existing game
allocator wrapper `_free` at `0x00030830`, not the CRT import. A header-only
trial emitted an indirect `FF 15` call and failed the parent byte gate; the
final configuration restores the direct call without a private declaration.

Before and after `./build.sh` verify all four rows. Final EH verification is
EXACT for the parent. Frozen-file and CSV checks pass. Saved original and
final objects have identical 572 external COMDAT fingerprints, 589 external
symbol records and relocation-reference graphs. No source path, ledger
identity, pin or shared header changes. The Microsoft-header auditor reports
clean; its scoped `refresh_queue` API removes exactly this file's one-finding
queue entry and preserves unrelated entries.

Paired ordinary previews against `85f6b7f40c` (2026-10-29 15:08) retain
LINKS, 226 -> 226 authored bytes. Their unreferenced `basic_ios::setstate`
diagnostic is not a blocker. Strict current-provider preparation also passes
all four rows and writes reusable receipts without expanding its scope. This
is header cleanup, with no census or runtime gain claimed.

The staged-tree batch audit is INCONCLUSIVE: the index predates the outgoing
base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry this writer and its wider consumer scope into the next normal
census. No complete consumer closure is claimed.

Selection review at the same base and index: `Scripts.cpp` passes ten code
rows plus one data row and retains its protected OrCondition destructor and
vtable blockers (LINK-063). The existing placeholder destructor and unsupported
virtual pool slot still require coordinated identity/header reconciliation.
A possible empty `Script::loadPostProcess` alias at `0x000B3FD0` was not edited:
that address is held by another worker. `AptPlayerTooltipMap.cpp` passes all
nine rows and retains unresolved `Rva00224C95::~Rva00224C95`, the non-retail
hashtable constructor (COMDAT and selected-copy findings), and a conflicting
AptPlayer vtable. LINK-144's heterogeneous member, existing destructor-owner
and complete-table prerequisites remain. No unchanged naming trial was repeated;
both scope claims were released before this cleanup.

BFME 1 freshness remains overdue. Official upstream was fetched and compared:
`cbf0388859fe614622171543c509f33fdbdd7beb` versus verified reference
`efb2b2a27078c6e96538a8c587438b72b675d6df` (75 changed paths, no changed
headers or build settings). The earlier refresh's old-input full gate did not
finish; see `copyprotection-ms-headers-20261030-codexb5.md`. Neither the verified
gitlink nor its success timestamp was advanced. Completing the reference
refresh still requires both full-gate verdicts.

## Preparation recovery, 2026-10-30

The preparation record preserves all six original commits in
`refs/runner/preparation/1793344133562487918` and names no stash or resync
stash. The interrupted rebase finished at `09d68615fd` with five commits;
the writer cleanup from `8b407ef115` was absent from both that tree and its
upstream base `459d69de97`. Reapplying that saved patch restores the sixth
change without discarding any upstream work. The index and worktree had no
other saved edits or untracked files. Older, unrelated stashes remain intact.

Recovery uses upstream's verified reference `337e4b48e8f295f74bdd1155ad2b6dd848b63c32`,
published by `7745b48fcb`, rather than the historical pin discussed above.
The required official fetch found `26867900efa59274a3f0671a6b6cf48d0436178f`.
No reference update or successful freshness timestamp is claimed by recovery;
the historical refresh handoff remains preserved with the other saved work.

The recovery's five-source `./build.sh` check passes 21/21 code rows,
one data row, sixteen named imports and all three renumbered funclet bindings.
Dependency receipts are current for all five units. `check_csv.py` and the
writer's frozen-file check pass. The outgoing source paths are unchanged;
the clone's ABI-key replacement stays in its original tracked source.
