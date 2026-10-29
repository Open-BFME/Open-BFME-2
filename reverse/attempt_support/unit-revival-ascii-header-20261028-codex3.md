# UnitRevivalEntry canonical AsciiString adoption

Inspected base: `52967e295106572252a325ff2adc595ae7fece05`.
Source: `Code/GameEngine/Source/Common/UnitRevivalEntry.cpp`.
Claim: `class:AsciiString` (codex3).

## Target facts and retained reconstruction

The existing default-constructor row `??0UnitRevivalEntry@@QAE@XZ` at
`0x0037E352` covers 135 bytes. Its initialization sequence clears the
128-byte member through `clear80` at `0x001EAE6F`, constructs the 24-byte
record through the existing constructor at `0x004E04FD`, then initializes
the final words, including the AsciiString buffer at offset `0xD4`.
Those callees already have ledger owners; this is neither a missing body
nor a new identity claim.

The former private AsciiString view allowed a late raw null store. Simply
including the canonical header moved default construction before the old
constructor body. Expressing the entire initialization sequence in member
initializers instead preserves the late canonical default construction.
The record is now a typed 24-byte member, and a forced-inline member
constructor calls the existing clear worker. The existing compiler barrier
is retained before `m_D0` initialization to preserve the float-store order.
Numeric member and helper names remain placeholders; no donor identity or
original field names are claimed. Shared headers, pins and ledger rows are
unchanged.

## Verification

- `find_declared_unmatched.py` passes before and after the change.
- Normal `build.sh` verifies the sole row: all 135 bytes and the float
  literal match retail.
- `header_adopt_lane.py accept --class AsciiString` passes and retires the
  source's one header-queue entry through the owning tool.
- `link_check.py --prepare-current` produces a strict current receipt.
  Both the ordinary preview and `--census-only` preview retain LINKS and
  134 authored bytes against index `d92e7e6635` (2026-10-28 15:58).
- Scoped allowed-symbol, data and class checks pass: two references bind
  to their two owners, with zero wrong bindings or data findings.
- Object comparison retains both existing COMDAT fingerprints, including
  the constructor's bytes and relocations. It removes the unused placement
  new adapter and adds unreferenced AsciiString constructor/destructor and
  clear-member constructor copies. No root references, exclusive definitions
  or weak bindings change. The new clear-member adapter is compiler-emitted
  support, not a newly recovered retail body. See the companion JSON.

## Remaining audit scope

The staged `link_batch_audit.py` is INCONCLUSIVE: its index predates the
outgoing base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry this provider and consumer into the next scheduled census.
There is no proven link loss, but the wider consumer audit is unverified.
No census or image-ownership gain is claimed. The other AsciiString header
queue entries and LINK-100's remaining contracts stay open.

## Preparation recovery publication verdict

The local acceptance and byte checks above passed again during recovery,
including the actual dry-run push hook at base `13850b92b4`. The fresh fleet
publisher nevertheless refused the queue retirement because its own
`link_check` run produced no usable per-unit verdict. This is missing
retirement evidence, not a reported byte mismatch or proven link loss.
The recovery correction restores the exact upstream header-queue row while
retaining the canonical source and this proposal's evidence. Its original
FAIL text records the earlier private-view failure; the current prerequisite
is a usable preview in the publisher checkout. Header debt remains open and
may leave only through the owning adoption tool when publication can verify
the verdict. No census, ownership or debt gain is claimed for this adoption.

## 2026-10-29 retirement retry

Base: `46a3ff46d4`. The source already contains the verified canonical
adoption; this retry changes no source, shared header, pin or ledger row.
The restored queue diagnostic is historical, so a new source trial is not
needed. With the current published index fetched through
`link_check.py --fetch-index`, the owning acceptance tool now succeeds:

- `find_declared_unmatched.py Code/GameEngine/Source/Common/UnitRevivalEntry.cpp`:
  all defined functions are matched.
- `header_adopt_lane.py accept --class AsciiString Code/GameEngine/Source/Common/UnitRevivalEntry.cpp`:
  PASS; retired exactly one row from `reverse/header_queue.tsv`.
- `./build.sh Code/GameEngine/Source/Common/UnitRevivalEntry.cpp`:
  one of one functions matches, including the float literal; the existing
  dependencies and object are current.
- `link_check.py Code/GameEngine/Source/Common/UnitRevivalEntry.cpp`:
  explicit per-unit `LINKS`, `LINKED 134 -> 134 bytes`, using census index
  `85f6b7f40c` (2026-10-29 15:08).

The fleet publisher must repeat retirement validation in its own checkout;
the prior publisher failure remains recorded above. This is one header-debt
retirement, with no claimed census or image-ownership gain. The earlier
wider consumer-audit prerequisite is not cleared by the scoped preview.
