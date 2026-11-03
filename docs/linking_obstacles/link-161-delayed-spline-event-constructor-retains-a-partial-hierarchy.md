### LINK-161: delayed spline event constructor retains a partial hierarchy (2026-10-30, seat codexb4)

Status: map dependency repaired; native hierarchy and census confirmation open.
`Common/Rva003C2F40TreeCtor.cpp` (0x002BAE57, 50 B) previously had three
unresolved names. Its map call at 0x002BAE75 reaches the existing 25-byte
provider at 0x005011C1 in `StlportIntMapDefaultCtor.cpp`. Using that provider's
constructor spelling retires the unused `Rva003C2F40Tree` pin and reduces the
current preview to two unresolved virtual destructors: `Rva003C2F40Base` and
`Rva003C2F40Owner`. The map provider stays LINKS (25 B); the constructor stays
at zero. No census gain is claimed. Strict two-source preparation passes 2/2
rows, the constructor's EH graph is EXACT, and only its map-call relocation
changes among six otherwise identical external COMDAT bodies.

Retail installs the seven-slot table at 0x007FE408; its name slot returns
`DelayedSplineCameraEventModule`. The current source's one-slot placeholder
base cannot describe that table. The real destructor and deleting destructor
already have rows at 0x002BAEAB/0x002BAE8F, but `Rva002BAEAB.cpp` models them as
composition with a nonvirtual deleting-destructor name. Reconcile the native
hierarchy, the slot-owner signatures and the existing kind-8 consumer in
`LivingWorldLogicDelayedEventXfer.cpp` together; do not add destructor pins or
discard the native table. The shared return-8 slot's CameraClass ledger owner
does not establish the event's source identity. The old VNI comment was not
supported by target evidence and is corrected.

[Native addresses, provider evidence and remaining prerequisites](../../reverse/attempt_support/delayed-spline-tree-provider-20261030-codexb4.md).
The staged batch audit is INCONCLUSIVE: its index is at `12b9e7a7c0`, behind
the outgoing base `0b2b06a5e4`, and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry this
provider/caller scope and broader affected consumers into the next scheduled
census; the bounded preview does not establish full-image selected-provider
or loss clearance.

The separate consolidation now absorbs the two-argument resize donor and removes
one source file. All seven rows and the 19 code definitions/reference graph
survive composition; the destination's strict receipts and four-unit caller
preview pass (3,272 bytes including the moved 73 bytes, no coverage gain).
The broader outgoing batch audit remains INCONCLUSIVE on the older index and
missing current `Common/0CreateAHeroManager21FE49.cpp` affected-consumer receipt.
Carry the source moves and broader selected-provider/consumer scope into the
next scheduled census; this does not clear the other quadruped prerequisites.
