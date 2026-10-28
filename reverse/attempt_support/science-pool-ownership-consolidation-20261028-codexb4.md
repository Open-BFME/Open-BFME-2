# Science consolidation: pool ownership prerequisite (2026-10-28)

Target: `Code/GameEngine/Source/Common/RTS/Science.cpp`, at `5c1449577d`.
No source, code-row, data-row or census change is retained by this investigation.

The current in-memory TU map approves ten clean sources (26 code rows) and
leaves eleven mixed sources. The supported `tu_skeleton.py --merge ...
--dry-run` cannot form a verified pair: its seed and list-cleanup donor fail
the provider guard on `?g_Va00DB9440@@3VRva002E8548@@A`. Declaration/STL/byte
prerequisites also remain in other donors. This is a current ownership
prerequisite, not evidence of a lost function row.

## Target facts

* `Science.cpp` and `Rva001FF6D7List.cpp` verify 17/17 existing code rows.
* The pool definition moved into approved `AIPathfind.cpp` in `48bda983ba`.
  It is the existing six-field, 24-byte initializer with 128 nodes, null
  lists/context, and callbacks at retail VA `0042FFC0` and `0042FFE0`.
* `reverse/data_ledger.csv` records the global at RVA `009B9440`, but
  `reverse/data_rows.csv` has no matched row for that complete symbol.
  `link_census.ledger_owners` uses matched code and data rows, rather than the
  inventory ledger, to establish replacement providers.
* Published index `d92e7e6635` (2026-10-28 15:58) predates the AIPathfind merge.
  `link_check.py --fetch-index` fetched the current available index; it did
  not resolve this prerequisite.
* A temporary complete data row passed the source byte verification:
  `./build.sh AIPathfind.cpp` verified 72/72 code rows and both 24-byte data
  rows, including the pool initializer and its two relocations.
* Global data-row integrity refused that temporary row: existing
  `?g_00DB9448@@3PAXA` in `GapBodiesGE53.cpp` owns RVA `009B9448`, four bytes
  inside the pool. That source defines a separate zero-initialized pointer
  and uses it in `Rva001FF547::deallocate` at RVA `001FF547`. The same source
  already references the complete pool for allocation.
* `GapBodiesGE53.cpp` was claimed by another worker. No edit to it was made.
  The temporary pool row was removed; the data ledger is unchanged.

## Remaining work

When that source is available, reconcile the interior pointer with the
existing pool's `m_head` at offset 8, prove the deallocator's bytes and
relocation target, and replace the interior data row with the verified
complete pool ownership row. Check data ownership, external consumers and
link admission together. Preserve the existing pool symbol: its original
identifier remains unknown, and this evidence establishes no recovered name.
Then retry the supported Science merge against current inputs; the other
compiler/STL prerequisites still require their own verification.

The local logs are scratch evidence only:
`build/science-dry-run-20261028.log`,
`build/science-baseline-build-20261028.log`, and
`build/science-pool-data-build-20261028.log`. No linked coverage, ownership,
source-file reduction or debt retirement is claimed for this investigation.
