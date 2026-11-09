# Companion army source: unused ModuleInfo view cleanup

2026-11-09: ArmySummaryEntry.cpp retains no ModuleInfo object or accessor use.
Remove its unused private ModuleInfo and WorldMapModuleRecordView declarations,
and include the canonical Common/ModuleInfoClass.h as required by the owning
header lane. The source's constructors and other function bodies are unchanged.

Before, private candidate and normal builds verify all eight rows. All 557
COMDAT payloads, definitions, undefined symbols, weak defaults, aliases,
includes and selection policies are unchanged. Three compiler funclet labels
renumber; verified parent EH placement still maps them to 0x007857FC,
0x00785804 and 0x0078580F without pin/ledger edits. Own link verdict is LINKS,
363 bytes unchanged against census 5b5011469d (2026-11-09 19:12).

The first deletion-only probe had the same exact object, but did not satisfy
the lane's canonical-include requirement. The final candidate includes the
header and passes owning acceptance, retiring one ModuleInfo row: 19 to 18.
ArmySummary, ArmySummaryEntry and CarryoverUnit still have separate header
entries in this source. Their lifetime/layout adoption is not claimed here.

Scratch receipts use moduleinfo-army-unused under
build/thingtemplate-header-cohort-20261109; candidate-v2 is the final source.
This is source/debt cleanup, not a new image or runtime result.
