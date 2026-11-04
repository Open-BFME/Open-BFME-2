# Consolidation seat 1 continuation probes — 2026-11-04

This continuation used only allocated, unheld shard 1 TUs. Each candidate passed
`consolidation_queue.py --check-tu`; the corresponding narrow consolidation
planner snapshot passed `--check` before its plan and merge dry run. No claims,
source edits, merges, splits, or ledger edits were applied.

| Destination | Dry-run result |
|---|---|
| `hcanim.cpp` | Neither donor accepted. Duplicate `AdaptiveDeltaMotionChannelClass::decompress` template; missing `BFME2MotionChannel::Pivot` and `Type`; class-view reconciliation required. Affected census-linked units were listed in the LinkGuard report. |
| `GiantBirdAIUpdate.cpp` | No donors accepted: missing/invalid `AICommandType`, undefined `Thing`, missing `Object` and `GiantBirdAIUpdate` members, plus `xfer` and path-method prerequisites. Reconcile target/class views; affected units census-linked. |
| `PlayerList.cpp` | No donors accepted: duplicate `SubsystemInterface`, missing `Player`/`PlayerList` members, `TeamsInfoRec::Int` syntax error, and target class-view reconciliation. Affected units census-linked. |
| `AITeamBuilder.cpp` | No donors accepted. `Rva0059A85CCtor.cpp` cannot convert `_STL::set` to `Rva002EE9B7*`; AITeamBuilder view reconciliation required. Both units census-linked. |
| `LANAPI.cpp` | No donors accepted. Seed fails bytes under all merged flag sets; a donor lacks `BfmeNetAddress::m_ip` and `m_port`; class-view reconciliation required. Affected units census-linked. |
| `StealthUpdate.cpp` | No donors accepted. Seed fails bytes under all merged flag sets. Donors fail on duplicate `Coord2D`/`Coord3D`, absent `m_ptr`/`m_24`, missing `Object::m_holder`, absent `Rva00373EC6` member, illegal `StealthUpdate::m_148` initializer, or donor byte mismatch. Reconcile views for `Object`, `Rva00331682Holder`, `Rva00373EC6`, `Rva003743CF`, and `StealthUpdateModuleData`. LinkGuard enumerated census-linked sources including the target and accepted-candidate donors. |

The `StealthUpdate.cpp` plan had 90 approved rows, 14 donors, seven mixed
sources, and no statically refused rows. Its final dry-run verdict was
`blocked: no verified merge of two or more donors; the seed itself fails under
every merged flag set: bytes`. No mixed-file split was applied because no merge
was unblocked. These are prerequisites for the code/view owners; this seat did
not repair declarations, layouts, signatures, flags, or bodies. No matched rows
were removed or newly preserved, and source-file reduction is zero.
