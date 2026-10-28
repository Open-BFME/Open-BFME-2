# GameResultsThread cleanup and composition handoff

Inspected revision: `8416feb308`, 2026-10-28. The default picker claimed
GameResultsThread.cpp and its four complete donors. The Thread/ name-lane
planner was generated; its stale committed TU map was rebuilt in memory by
tu_skeleton. No TU-map or source-path change is proposed.

The applied cleanup removes the redundant local `free` declaration from
GameResultsThread.cpp. The existing CRT header already supplies the declaration;
the call binding is unchanged. A scoped `ms_header_audit.scan_text` and
`refresh_queue` removes this source's one local-definition queue entry, leaving
all unrelated entries untouched. This is not a migration of the donor include
closure: its Windows/Winsock shim declarations remain.

Verification of the final source:

- `./build.sh`: 14/14 matched rows, eight named import references verified.
- `find_declared_unmatched.py`: all defined functions already matched.
- `eh_verify.py`: no EH rows and no missing objects in this seed.
- `data_check.py`: zero findings.
- Staged code-identity shadow check reports the existing divergent
  `_STL::allocator<BfmePod16>::deallocate` definition. The saved baseline and
  final object have identical external providers, including this definition;
  this cleanup does not repair that separate emission issue.
- `link_check.py --prepare-current`: strict reusable receipt, all 14 rows exact.
- All 620 external code/data providers and 11 undefined reference names equal
  the saved baseline object. Comparison includes bytes, sizes, relocation
  referents, section flags and COMDAT selections.
- Ordinary link preview retains LINKS for 902 authored bytes, using index
  `d92e7e6635` (2026-10-28 15:58). No linked-byte increase is claimed.
- Outgoing staged-tree audit is INCONCLUSIVE: that index predates the inspected
  base and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Carry this provider/consumer scope into the next census.

Composition investigation: `tu_views.py` verified one shared Rva0041A3C4 view
in the seed and startup donor, but ordinary before/after merge searches both
accepted zero additional donors. Startup does not use that view. The rewrite
was reverted; no unused declaration-only prerequisite is landed. Worker
Thread_Function and both narrow-record/deque teardown donors still fail byte
composition. Startup fails with an AsciiString redefinition in the bfme2_ascii
include closure. GameResultsThreadBase and GameResultsThreadClass already
agree; Rva00641F2EQueueSlots lacks a compiler-emitted layout in either file.
Allocator macro order and /EHs versus /EHsc remain investigation leads, not
proven causes or fixes. Prior guard evidence is in
`consolidation-sol-results-guard-20261026.md`.

A trial placing the real Platform SDK before the sweep include path failed
compilation: nested donor headers still include sweep/windows.h, redefining
_ULARGE_INTEGER, GUID, SYSTEMTIME and other SDK types. That trial was reverted.
The next SDK migration must replace the relevant include closure coherently;
do not repeat the include-order-only trial.

Local receipts: `build/gameresults-views.log`, `build/gameresults-planner.log`
and `build/gameresults-headers-codexb/`. No source moves, pins, ledger rows,
shared headers, protected debt keys, census or ownership figures change.
No maintainer-only measurement or runtime runner was invoked.
