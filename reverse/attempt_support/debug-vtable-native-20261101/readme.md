# Debug native-table correction and operator-tool prerequisite

2026-11-01, base 7ae766037536997b57534c1efb5eeef141d47943; model GPT-6.
Native-table investigation: 12 minutes, lane R, 30-minute body budget.
Production source, ledger function rows, pins and headers are unchanged.
No newly matched bytes or census gain. Prior source/alias trials were not repeated.

## Correction to the old handoff

The native Debug table is **46 entries**, not the previously stated 37.
Debug constructor 0x00038440 and complete destructor 0x00038710 both store
VA0x00BBE810. The next distinct table starts at RVA0x007BE8C8, installed by
DebugCmdInterfaceDebug constructor 0x00038670; its first target is that class's
scalar delete at 0x00039950. The 184-byte Debug data-ledger extent agrees with
this independently installed boundary. prove_table.py checks these stores and
all table pointers against the retail image; native-table.log maps all known
owners by filtering the current ledger. Slot46 belongs to the next table.

Slots0..15 are the reverse-ordered stream overload group, with RepeatChar at15
and const-char at14. The helper format-manipulator overloads in the current
35-slot shim are not extra native entries of that group. Slot16 is scalar delete,
slot28 is isLogEnabled, slot35 Command, slot36 ExecuteFrameCommands, slot37
Update, slot38 GetInput, slot39 SetBuildInfo, slots40..42 the three version/date
buffer addresses, slots43/44 windowed query/update and slot45 AddLogGroup.
These placements establish dispatch facts, not original names for placeholder
owners. Several current providers are still separate neutral class views.

## Current normal preview

Against index12902e9e1b, the original destructor unit still loses its one-slot
Debug table; its code bytes are99 (the ranking's113 also includes14 EH bytes).
The constructor418 and debug_debug2295 remain LINKS; cohort2713->2713.
The preview does not validate their existing35-slot table against native46
(no retail-address binding for the COMDAT). Do not call it a recovered interface.
The original frozen-file checks passed before planning any production edit.

## First bounded identity prerequisites

The bool stream30B at38890 and both int64 streams83B at3B510/3B570 occur in
native slots9/4/3 but their rows are nonvirtual QAE. Current ordinary C++ stream
views must preserve the entire overload group: just adding virtual bool can
move const-char dispatch away from slot14. A correct recovery must also account
for the whole class prefix and existing field offsets; adding the first vptr to
AddLogGroup's view would shift its9C80 list head by four without a pad adjustment.
No such source trial was applied.

The official rename.py function --virtual dry-run for bool refuses operators at
member_function_header before considering the native evidence. operator-refusal.log
is the exact refusal. This is a tooling prerequisite, not a byte mismatch or
permission denial. Any operator support must select the exact overload and keep
constructor/template/static/folded-body refusals, native installation proof,
protection checks, transactional restoration and normal byte verification. Record
this false reject separately before changing tooling; do not hand-respell rows
around the control. Current overload sets are deliberately refused by the generic
virtual_declarations path.

An ordinary AddLogGroup virtual dry-run reaches the shared shim and exceeds the
25-file safety limit. This is a scope limit, not proof the rewrite byte-matches;
a larger explicit limit is supported, but does not fix the46-slot contract.
No aliases, new pins, partial tables or shared-header patches were introduced.

## Subsequent tooling result

The separate debug-stream-virtual-tooling-20261101 handoff records the precise
operator selector and its regression coverage. All three actual stream dry-runs
now pass planning with native slot evidence. The investigation-time refusal above
is preserved as history; Code and function rows remain unchanged.
