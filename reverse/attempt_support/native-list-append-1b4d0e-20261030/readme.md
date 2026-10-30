# Native list append binding, 2026-10-30

Base `505b71888c`, reference `1d5131d3f193cdf01a99da66ccd6828639585650`,
published index `12b9e7a7c0` (10:11).

The complete eight-byte wrapper at 0x001B4D0E adjusts its receiver by 12 and
tail-calls the existing list push_back at 0x001B4CEF. The wrapper's unnecessary
local instantiation emitted a plain-POD `_Construct<BfmePod72>` copy that is
not retail's selected construction operation. The provider's actual node
construction at 0x001B4C58 uses the existing nontrivial record construction;
the wrapper must not substitute its size-only view's copying machinery.

A declaration-only push_back specialization leaves the exact wrapper and
its native target unchanged, while removing all 11 local helper copies. The
one retained COMDAT is identical and nothing is added. All 71 rows across
the wrapper, StlportListInsertFootprints and stlport_pod_list_bodies pass
normal strict preparation; all four EH graphs are EXACT. The frozen check
passes. The paired bounded preview improves 2/3 to 3/3 LINKS, 2,361 to 2,369
authored bytes, with both support units preserved. No new pins, rows or
hatches are introduced. This is an eight-byte preview gain, not a census gain.

The staged outgoing audit is INCONCLUSIVE on the older index and affected
consumer Common/0CreateAHeroManager21FE49.cpp without a current strict receipt.
Carry the wrapper, removed construction chain, existing providers and affected
consumers into the next scheduled census. Full consumer closure is unmeasured.

The original enclosing class and element identity remain unproven. No row or
source moves: its existing provisional SubsystemLegend routing and semantic
naming handoff remain separate work. Local logs and source trials are in
`build/append-1b4d0e-20261030/`; [proof.json](proof.json) preserves the byte,
object and receipt evidence. No link cycle, nightly or smoke runner was started.
