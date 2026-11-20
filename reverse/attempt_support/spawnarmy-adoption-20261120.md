# SpawnArmy consumer adoption

Base `579a7e91d2`, inspected 2026-11-20. Four queued consumers were tried
with `header_adopt_lane.py adopt --class SpawnArmy`.

LivingWorldArmy.cpp now uses the canonical record instead of a padded
nonvirtual caller view. Field references retain their native offsets.
The whole source passes 79/79 functions; acceptance retires its queue row.

LivingWorldLogic.cpp now uses the same canonical record. Its city predicate
remains an inline function to retain native AL evaluation. String assignment
retains its StringBase provider. The position is still copied as the existing
eight-byte coordinate aggregate over +0x20/+0x24: scalar float assignments
emit SSE moves instead, while memcpy emits an out-of-line call. Both failed
trials were replaced, not banked. All 213 functions and the data row pass;
acceptance retires this consumer's queue row.

Two consumers remain queued and unchanged:

- LivingWorldCampaignAct.cpp defines private `_STL::vector` and
  `_Vector_base` templates, including a specialized string vector with a
  BfmeE16 header constructor. The canonical header includes real STLport;
  the adoption probe reports C2953 redefinitions and C2955. Prerequisite:
  migrate those vector storage/lifetime views while preserving native
  constructor 0x00566BF6, cleanup and clear providers. Do not hide STLport's
  include guard to admit the header.
- WWLib/SpawnArmy.cpp includes Rva004E1B72.h before its private SpawnArmy
  view. That header selects capitalized, non-const-name, reference-transfer
  Snapshot slots; SpawnArmy requires the opposite native profile and rejects
  the combination explicitly. Prerequisite: reconcile the co-resident
  Snapshot-derived providers without changing slot names or adding bridges.
  Do not remove SpawnArmy.h's profile check.

The automatic WWLib probe also temporarily selected a replacement spanning
unrelated text and its compiler stalled; terminating that compiler allowed
the tool's normal restoration to finish. No probe edits remain in either
blocked consumer. A subsequent Wine path-conversion process stalled before
the Logic baseline; after terminating that child, path conversion recovered
and the normal whole-source build succeeded.

This is shared-layout cleanup only. No real-link, bridge-count, runtime or
CRC improvement is claimed.
