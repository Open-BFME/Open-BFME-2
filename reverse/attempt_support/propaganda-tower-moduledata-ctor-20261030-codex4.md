# PropagandaTowerBehavior module-data constructor composition trial

Boundary: `??0PropagandaTowerBehaviorModuleData@@QAE@XZ`,
RVA `0x0048197C`, 66 bytes. This is an existing matched body in
PropagandaTowerBehaviorModuleDataCtor2.cpp, not an unrowed regression.
The old 65-byte blocked-name attempt and subsequent landed verdict were read.
The file and RVA were claimed before the trial.

## Target facts and attempted change

The existing constructor uses a four-byte raw base, explicitly installs its
native table, and initializes the scalar/pointer fields. The seed destructor
uses Snapshot and owns an AsciiString at +0x18; the native field-parse table
identifies the members at +0x08 through +0x20. These support the field view,
but do not prove a constructor with the seed's header policies byte-matches.

The rejected trial replaces the raw base with that existing Snapshot/AsciiString
declaration and retains the constructor's native table installation and scalar
assignments. The explicit pointer-zero assignment becomes the string's default
initialization. No external donor implementation was consulted or imported.

Normal `./build.sh PropagandaTowerBehaviorModuleDataCtor2.cpp` fails 1/1.
Retail begins with a radius load, then `mov eax,ecx; xor ecx,ecx`, installs the
derived table, and clears the string field before the remaining scalar stores.
The trial begins with `mov eax,ecx`, additionally installs Snapshot's table,
and clears the string before entering the explicit constructor body. The
extra base initialization and resulting scheduling do not match the 66-byte
boundary. No row extent, flags, pin, baseline or gate was changed to admit it.

The source was restored. Subsequent strict preparation verifies its original
66-byte row with all 23 scoped rows. Initially this cleanup trial was recorded
as partial with a generated stash; check_csv correctly refused that redundant
stash because the address already has real matched C++. The generated stash
was deleted, its partial classification retracted through `re_log.py`, and
the result recorded as attempted. This handoff preserves the failure and
reproduction details; it is not an unmatched reconstruction or new progress.

## Remaining prerequisites

Reconcile construction and destruction policies together before combining this
donor with the seed. The Snapshot shim already offers a constructor-only
surface, but this trial did not select it; changing the policy for the composed
TU must also preserve the seed's matched destructor/EH graph and string lifetime.
Do not copy the failed body into Code or assume identical field offsets prove
identical construction. Constructor, Update and Xfer hierarchy/interface work
is separately unfinished.

The successful scan merge's hook also reports existing shadow ownership
findings for BfmeWideResult and PartitionManager at their new seed location
(registered header PartitionRangeQueryCallView.h). Their definitions and
COMDATs were transferred unchanged from the absorbed scan donor, not duplicated.
Canonical-header adoption remains follow-up work; no header debt was retired.

The publication rebase resolved only competing obstacle-register insertions,
preserving both the upstream ghost-manager entry and this pass's entries. No
incoming change touched the six Propaganda sources. The fleet publisher accepted
the merge handoff; no commit content was amended after publication.
