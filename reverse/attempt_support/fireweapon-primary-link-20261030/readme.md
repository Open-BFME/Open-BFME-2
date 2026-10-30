# FireWeaponWhenDeadBehavior primary contract

Base 190db05cc6c213ba433cbfd180b5616fcf00a763; model GPT-6; lane=R;
budget=30m. Both source file claims were origin-confirmed before edits.

The twelve original rows pass in both the original and proposed source pair.
The proposed pair compiles identical thirteen-slot primary tables, checked
slot by slot against native 0x008497B4. Slots 0/1/3/4/12 retain existing
ledger owners; slot 0 uses the compiler's weak E-to-G fallback to the rowed
scalar deleting destructor. Slots 5-11 have complete inline leaf bodies equal
to native, including the two-argument RET8 and the two null getters. Slot 2
is the exact six-byte const member getter at 0x00482E4B. No new pins or aliases
are required. The ObjectModule base header is unchanged.

A stale, unused BuffManager header in the constructor unit selected capitalized
Snapshot slots before its actual base was read. That made loadPostProcess and
xfer extra virtual slots. Removing the unused include permits the existing
name-slot contract; both views then add the known Behavior primary slots 10/11
and existing UpdateModule getUpdatePhase slot 12. The destructor view adopts
the registered ObjectModule header. Its qualified base transfer needs the
existing nonvirtual BehaviorModule xfer spelling at 0x004C9C7D, while the new
base now makes the C++ declaration virtual. A local member-address view uses
that existing symbol with ObjectModule at offset zero. The target compiler
proves both pointer representations four bytes; its emitted call remains
byte- and relocation-identical. No inline assembler or fallback is added.

The existing free-function placeholder Rva00482E4BGet is the same native
slot-2 getter, not a second ICF function. Per add_match's real-claim rule it
must be retracted in its own reviewable commit before readmission with the
actual member signature. The first commit therefore removes that one six-byte
row/body, records its tombstone and removes the old s02 alternatename. The
matching member body and full interface repair are retained in scratch for
the following readmission commit. This intermediate retraction is not published
on its own. No original-source naming claim is derived from a trivial byte
match alone: the module constructor's primary vptr and native Snapshot slot
contract establish the containing class and callable interface.

The tested three-source preview is 3/3 LINKS, retaining the other two units
and changing the constructor from 0 to 209 authored preview bytes against
85f6b7f40c. This is a bounded prediction, not measured census credit. Other
secondary interfaces and the wider affected-consumer scope still require
normal audit and scheduled census confirmation. The other destructor families
must retain all existing row bytes and bindings.
