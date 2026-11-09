# Statistics source consolidation: routing and provider prerequisites

Status: open (2026-11-09). Scope: Common/INIStatsRecord.cpp and
Common/Rva0050CBA2StatsDump.cpp. This is source cleanup, not a runtime blocker
established on an image.

Both sources' ModuleInfo header adoption is verified and published. A fresh
`tu_skeleton.py` plan still leaves 22 of the diagnostic fragment's 23 rows
without an approved TU. Its remaining row, the 21-byte INIStatsRecord destructor
at 0x0050C688, is approved for INIStatsRecord.cpp, whose current object does not
emit it. It cannot be rehomed without preserving its compiled provider.

The destination's 11 approved rows include two mixed providers: the diagnostic
fragment (22 other rows) and stlport_pod_vector_bodies.cpp (64 other rows). The
supported merge dry run accepted no donors and stopped at `fewer than two
donors`; no compiled merge was attempted, no source was removed, and no rows
moved. The consolidation planner's ThingFactoryIniStatsHelper grouping is not
TU approval.

Remaining prerequisites: approved routing/TU evidence for the diagnostic rows,
then separately verified supported splits or destructor emission reconciliation
before a whole-file merge. The future move also needs the ordinary debt,
header, provider/consumer and active-tooling compatibility audit. Full evidence:
`reverse/attempt_support/stats-tu-routing-blocker-20261109.md`.
