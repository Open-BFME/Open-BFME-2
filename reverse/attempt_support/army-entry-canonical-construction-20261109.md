# Army entry: real base construction and shared headers

2026-11-09, Common/ArmySummaryEntry.cpp. Adopt the canonical CarryoverUnit,
Rva0007DF07 and ArmySummaryEntry declarations. Remove the private CarryoverUnit,
MemberAC and ArmySummaryEntry views and their explicit vtable declarations.
Both entry constructors now use the real bases and ordinary field initialization;
the compiler supplies their primary/secondary vptr stores in retail's order.
The retained opaque ArmySummary cleanup view invokes Snapshot's qualified
destructor instead of naming its vtable as an external array.

Verification:

- All eight existing rows remain exact. The three funclets are placed from
  their parent EH data; no row, pin, extent, source path or compiler flag changes.
- The compiler's primary table is 16 bytes and its secondary table four bytes.
  All five relocations resolve to the actual retail slots at 0x0083944C/5C.
- Seven emitted helpers independently verify against their current native
  boundaries, including the 11-byte secondary adjustor, 28-byte deleting
  destructor, Snapshot and secondary-base lifetime helpers. Their payloads
  equal those emitted under the source's own flags.
- All 556 retained COMDAT payloads and policies are unchanged. Eleven added
  selection-2 copies match existing indexed providers; no new variant is added.
  The only removed definition is the unused MemberAC constructor, a 13-byte
  twin of the canonical secondary-base constructor. Its sole indexed provider
  was this source; the equality source's MemberAC is a plain struct with no
  constructor use. Aliases are unchanged; three ordinary compiler weak
  deleting-destructor defaults are inherited from the shared class definitions.
- The isolated LinkGuard reports no losses. The normal source's own verdict
  is LINKS, 363 bytes unchanged against census 5b5011469d (2026-11-09 19:12).
  Its final normal object equals the private candidate's payload/binding facts.

Owning acceptance retires two header rows. Five ArmySummaryEntry and five
CarryoverUnit units remain locally. The source's sole remaining header entry
is ArmySummary, with 14 units remaining for that class.

Remaining ArmySummary scope: the read-only supported adoption preflight still
stops on C2373 for its manual external vtable. A complete recovery must remove
that binding together with its constructor's manual layout model. Native
construction calls the measured no-throw 0x00330757 initializer on +4; its shared
Rva00330757Member view is 16 bytes. The canonical ArmySummary header instead
names a 16-byte listener base with no constructor declaration and keeps its
two vector headers opaque. Equal size alone does not prove those placeholder
identities equivalent. Reconcile the base-constructor owner and storage
lifetimes before claiming that adoption. No ArmySummary constructor trial was
left in Code; its current 165-byte row and cleanup rows still verify.

Scratch before/final candidates, per-body helper/table proofs, provider
comparison, read-only preflight and normal receipts are under
build/army-native-class-adoption-20261109/. This package is source/structure
and header-debt recovery, not a newly linked game-image claim.

Carry forward the previous d20964076c push's broader INCONCLUSIVE audit:
unchanged AICowerState_onEnter.cpp lacks a current receipt against index
5b5011469d and outgoing base 8541635d74. Its directly changed source retained
LINKS and passed all eight rows plus its one EH graph; that does not clear the
unrelated consumer evidence gap.
