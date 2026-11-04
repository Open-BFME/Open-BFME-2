# PortNegotiationSchema placement-new cleanup and consolidation boundary

Inspected revision: `0d2659fd79`. Scope:
`Code/GameEngine/Source/Common/PortNegotiationSchema.cpp` and the seven
single-TU donors served by `next_work.py --claim`. No source paths or ledger
rows move in this change.

## Retained cleanup

Replace the seed's local placement `operator new` definition with the VS2003
`<new>` header. The native copy constructor at 0x005DBCD1 is already rowed in
`V3PolyCopyCtors.cpp`; its body installs the vptr and copies shorts at +4/+6,
without calls. Declare that constructor `throw()` in the seed. This prevents
the standard placement-delete declaration from adding exception cleanup to
the seed's uninitialized-copy and fill helpers. The constructor implementation
and its owning source are unchanged.

Header-only trial: uninitialized-copy/fill no longer match. Header plus the
nonthrowing constructor declaration: all 13 seed rows match. This is a
target-body observation, not evidence for a recovered application type name.

Verification:

- `./build.sh Code/GameEngine/Source/Common/PortNegotiationSchema.cpp`:
  13/13, string/float/import checks pass; existing funclet is verified through
  its parent's EH data after compiler-label renumbering.
- `find_declared_unmatched.py` passes; `eh_verify.py` reports EXACT 1/1.
- `allowed_symbols.py --source`: ten references, zero wrong bindings.
- `ms_header_audit.py show/check`: clean. Its targeted
  `scan <source> --write-queue` removes only this source's one local
  Microsoft-definition queue row.
- Ordinary `link_check.py <source>`: LINKS, 649 -> 649 authored bytes,
  against census/index revision `8661f15284` (2026-11-03 20:03 UTC).
  This is a prediction using the indexed providers, not a new census or
  real-link measurement.

## Consolidation remains blocked

The supported `name_lane.py consolidate --under Code/GameEngine/Source/Common/`
report was fresh before edits. Its alternative GameNetwork path was a lead,
not merge approval. `tu_skeleton.py --plan` rebuilt its map in memory and
approved 43 rows for the existing Common seed, with nine mixed-source files
excluded. No regenerated map is committed. The report is now stale after
this source edit; regenerate it before resuming a merge.

Both `tu_skeleton.py --merge <seed> --dry-run` trials accept no donors. Before
the header change, the vector donors collide with the local placement-new
definition. With the retained cleanup, the vector donors compile but lose
byte matches. No merge is applied. The rejected donors are:

- `PAVectorEraseRange003AF7A0.cpp` and
  `WWVegas/WWLib/StlportVectorRva005DBCD1Overflow.cpp`: byte verification.
- `PortNegotiationSchema_getTimeToSendPing.cpp`, `Rva005DBCA6Get.cpp`,
  `Rva005DBEEB.cpp`, `PortNegotiationSchema_sentAPingPacket.cpp`, and
  `PortNegotiationSchema_handleNegotiationResult.cpp`: incompatible private
  class declarations, missing members or declaration ordering.

`tu_views.py <seed> --dry-run` identifies the concrete layout conflicts:
`Elem005DB98E::m_data[20]` overlaps the timing float fields; the seed's
`PortNegotiationSchema::m_arr2[81]` at +0x18 overlaps a donor's
`m_state[64]` at +0x18. Array bounds must be recovered from all native
accesses before replacing those views. Other listener/record views have
mechanical union plans, but none were applied in this pass.

Next: independently reconcile the verified private views and vector
exception/codegen contracts, preserving every donor's row and emitted
binding, then retry the supported merger. Do not shorten the seed arrays
merely to make the layout planner accept them. No source-file reduction or
census gain is claimed here.
