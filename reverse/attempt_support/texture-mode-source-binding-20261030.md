# Texture-recording mode: static ownership affects scheduling

Control: 7906295d3f8e99862e1b7b005566c1fd7a6b4984.
DebugStatisticsRecordTextureEnd.cpp has duplicate-def and wrong-name debt
for file-static recordTextureMode at RVA 009EE8F4. The existing provider in
statistics.cpp is Debug_Statistics::RecordTextureMode record_texture_mode;
its enum lives in the Debug_Statistics namespace, rather than a class.
Before the trial all eight rows and the complete parent EH graph are exact,
and the ordinary paired preview retains 1,006 + 1,019 authored linked bytes
against ccafe54d1d (2026-10-30 15:43).

A direct extern adoption with the provider's scope and enum does not preserve
the parent. Retail compares the mode before the final empty-string character
store inside bfmeAssignInline; the extern version schedules that comparison
after the store. The independent static object lets the compiler prove the
two stores do not alias. A second trial snapshots the mode comparison into
a bool immediately before the string assignment; it also fails the parent
byte gate. The scoped EH-location refusal follows the mismatched parent and
is not evidence that the EH verifier needs bypassing.

The adjacent diagnostic patch preserves the second trial. A coherent native
statistics TU/global-ownership repair is needed; a new alias, import,
restrict assumption or hand-written assembly is not an ownership repair.
Both trials are fully restored; no data key or class/hatch register changes
are retained. Do not repeat these two source forms unchanged.
