### LINK-161: delayed spline event constructor retains a partial hierarchy (2026-10-30, seat codexb4)

Status: map dependency repaired; destructor placeholder folded; virtual
destructor blocked on a one-unit shape (below); census confirmation open.

**2026-11-04, halilkkaya-lk24:** `rename.py class --fold` gained a
destructor-only route ("fold a destructor-only placeholder by its slot"). `Rva002BAEAB` (dtor 0x002BAEAB and
deleting dtor 0x002BAE8F, no vptr store) now folds into `Rva003C2F40Owner`
("Fold class Rva002BAEAB into Rva003C2F40Owner") because its `??_G` is slot 0 of 0x00BFE408, the ctor 0x002BAE57's
own table. `BfmeRectVNI` (ctor 0x003FD64D) also installs that table and stays
unfolded: two ctor placeholders are overloads or ICF, which the narrow mode
does not merge. The anchor in `Rva002BAEAB.cpp` now deletes only. Its
`new` emitted an implicit `??0Rva003C2F40Owner@@QAE@XZ` COMDAT that link_check
flagged as a duplicate, non-retail body. link_check over Rva002BAEAB,
TreeCtor and BfmeRectVNI: 163 -> 163 B.

The QAE -> UAE respell (`function --virtual`, now with `--prepared`) is
still blocked:
- A Snapshot-based view with `virtual ~Rva003C2F40Owner() {}` compiles a
  `mov [esi],vftable` that retail's 0x002BAEAB lacks.
- With `__declspec(novtable)` on that view (the `Rva003ABA36Dtor.cpp`
  precedent), `??1...UAE@XZ` and its EH funclet match exactly. However, the
  unit then emits no vftable, so `??_GRva003C2F40Owner@@UAEPAXI@Z` is missing.

Retail lays out ctor 0x002BAE57, name slot 0x002BAE89, `??_G` 0x002BAE8F and
dtor 0x002BAEAB contiguously. That reads as one TU whose class declares no
destructor: the implicit virtual destructor, which has no vptr store, is
generated beside `??_G` from the ctor's vftable.

Prerequisite: put both units in one source (approved TU
`GameLogic/System/LivingWorld/LivingWorldLogic.cpp`, through `tu_skeleton.py`)
with no user-declared destructor and a +0xC member whose destructor binds
0x002B80CE. Then run `rename.py function --rva 0x002BAEAB --virtual
--prepared <unit>=<file>`. Never move the rows into `Rva003C2F40TreeCtor.cpp`:
it is not the approved unit.

**2026-11-04, halilkkaya-codex:** the constructor now uses the canonical
constructor-only Snapshot base, whose existing 0x0049B47C destructor is the
native unwind target. This removes the false `Rva003C2F40Base` destructor
reference. Thirteen family rows and EH remain exact; all nine LINKS peers
survive an 11-unit true base/tip preview, and scoped DIR32 passes 13+8.
The owner destructor and complete seven-slot event table remain open as
described below; no full-image/census closure is claimed. LINK-182 records
the bounded repair and local receipts.
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
