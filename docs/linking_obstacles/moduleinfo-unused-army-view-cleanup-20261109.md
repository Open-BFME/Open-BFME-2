# Unused ModuleInfo copy in the companion army source

Status: cleared for ModuleInfo in Common/ArmySummaryEntry.cpp (2026-11-09).

The unused private ModuleInfo/record declarations are removed and the source
includes the canonical header. All eight rows verify; all 557 COMDATs and
external binding/policy facts are identical. Three renumbered funclets are
placed by their verified parent EH graph. The source's own LINKS verdict
preserves 363 bytes against census 5b5011469d.

Owning acceptance retires one ModuleInfo queue entry, leaving 18 locally.
The source's ArmySummary, ArmySummaryEntry and CarryoverUnit entries remain
open. Evidence: reverse/attempt_support/moduleinfo-unused-army-view-cleanup-20261109.md.
