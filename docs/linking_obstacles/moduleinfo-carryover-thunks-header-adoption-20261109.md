### Carryover traversal and existing thunks need canonical ModuleInfo

Status: both consumer adoptions verified; wider class recovery open.
Updated: 2026-11-09; inspected revision: 3a7b59cb3d.

Rva0037DF8DIterate.cpp and GapThunksSeat8.cpp adopt the unchanged canonical
header, preserving the byte-difference count and existing destructor/thunk
bindings. Nineteen rows pass normal verification; the two current-input previews
against index5b5011469d retain443/443 linked bytes. All36 COMDAT payloads,
public definitions and selection policies remain unchanged. Owning acceptance
retires two ModuleInfo header rows;22 remain locally, with no header key in
either file. Both sources have strict receipts.

[Scope, native facts and provider audit](../../reverse/attempt_support/moduleinfo-carryover-thunks-header-adoption-20261109.md).
Only GapThunksSeat8.cpp's current receipt is established here; historical wider
GameLogic/query consumer gaps and the preceding AICowerState_onEnter.cpp audit
gap remain open. Census/image confirmation is pending; no runtime outcome or
new global linking coverage is claimed.
