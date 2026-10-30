# Thai sentence allocator provider repair

Inspected parent `520c4d3ddd`; published index `ccafe54d1d` (2026-10-30
15:43). This repairs selected-copy linking, not missing byte coverage or a
recovered original translation-unit name.

## Target evidence and change

`Render2DSentenceBuildThaiBFME2.cpp` supplies the first selected const
`allocator<unsigned short>::deallocate` COMDAT. Its 18-byte body is not retail's
20-byte body at `0046264A`. The next existing provider,
`StlSweepR3Rva0022CCEF.cpp`, already supplies that complete native body through
the existing allocator pin. The Thai object's only incoming relocation to its
copy is `.debug$F`, with no executable or data caller. This is independent of
the earlier failed `BfmeWordVec::resize` declaration-only trials.

A TU-local imported forceinline specialization retains the existing BFME
allocator shim's operation and assertion, including its const signature and
free-call declaration context. It suppresses only the unused external copy.
No shared header, row, pin, alias, counted hatch, ABI or compiler flag changes.
The established inline-preserving suppression recipe is used; no donor source
or original filename is inferred from exact bytes.

## Verification

Private before/after objects reproduce all five Thai rows and all emitted
handler-parent EH graphs exactly. All 46 retained external code definitions
and their symbolic relocations are identical. Only the unwanted deallocator
definition disappears; no deallocator import symbol is introduced.
[Private comparison](private-comparison.json).

Literal `./build.sh`, frozen-definition and strict preparation pass. The actual
strict Thai object reproduces all 46 private definitions; the next provider's
complete 20-byte body resolves exactly to native `0046264A`, including its free
call. [Actual-object proof](actual-proof.json).

Strict six-source preparation passes 195/195 rows, two data rows, 117 literals,
27 empty-string references, three float references and 30 named imports. The
six-source ordinary preview retains 6/6 LINKS, 0 -> 21,683 authored bytes:

- Thai sentence builder: 2,191.
- PeerThread: 18,622.
- MultiByteToWideCharSingleLine: 204.
- Rva0038E4B9Finish: 545.
- StlSweepR3Rva0022CCEF: 59.
- stlport_money_get_wide: 62.

These are bounded predictions against the published index, not a new census,
an actual full-image link, or additional unique byte coverage. Full affected
consumer selection/loss checks and scheduled census confirmation remain
separate; read the outgoing audit qualification below when available.

## Outgoing audit qualification

The ready-batch audit is INCONCLUSIVE: index `ccafe54d1d` predates outgoing
base `520c4d3ddd`, and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. The six-source
proof does not clear broader selected-copy/loss behavior. Carry the removed
provider and its affected consumers into the next scheduled census; no
full-image link or official linked-coverage gain is claimed.
