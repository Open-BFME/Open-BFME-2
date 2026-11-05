### Connection ack alias cleanup and composition prerequisites (2026-10-29, codexb4)

At base `01bdf8d618`, the stage-1 ack branch now calls its existing
rva0058BD4F owner directly, removing one linker alias and its unused pin.
All 19 rows across the eight-file scope verify; both dispatcher/provider
strict receipts pass and ordinary preview retains LINKS, 81 -> 81 authored
bytes against index `85f6b7f40c`. Normalized COFF bytes and call targets are
unchanged. Both direct branches coalesce retail's two call sites, so the
both-stage alias remains. No census gain is claimed.

The supported merge still stops before composition: the carried
`-O2 -arch:SSE` override loses two seed rows. tu_views also reports the
NetCommandList vfptr, Connection address fields, NetCommandMsg return type,
NetCommandRef retry/relay and NetPacket extent conflicts. No paths moved.
Resolve these prerequisites before retrying; retain the mixed donor.
The staged-tree batch audit is INCONCLUSIVE: the index predates the base and
affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt.
Carry this consumer and the two-unit cleanup scope into the next scheduled census.
[Evidence and verification scope](../../reverse/attempt_support/connection-ack-cleanup-20261029-codexb4.md).

2026-11-04: The two-file Connection.cpp/ack composition is cleared (22/22 rows); broader class/header work and the next-census consumer audit remain. [Evidence](../../reverse/attempt_support/connection-ack-consolidation-20261104.md).

2026-11-05: NetCommandList's private-vfptr prerequisite is cleared in Connection.cpp and two ConnectionManager consumers: 25/25 rows and all 58 external COMDATs/bindings are retained; owning acceptance retires three header rows, ordinary previews preserve 2,057 bytes. The unchanged relay consumer still needs node traversal and destruction-access reconciliation. [Evidence](../../reverse/attempt_support/netcommandlist-header-20261105-codex4.md).
