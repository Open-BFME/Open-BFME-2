### LINK-161: delayed spline event constructor retains a partial hierarchy (2026-10-30, seat codexb4)

Status: map dependency repaired; destructor placeholder folded; the
constructor unit's unresolved `??1Rva003C2F40Owner@@UAE@XZ` repaired in
preview (below); the row respell and TU merge stay blocked; census
confirmation open.

**2026-11-04, halilkkaya-lk25:** `Rva003C2F40TreeCtor.cpp` now declares no
destructor, so its vftable's `??_G` reaches the implicit virtual destructor
the unit emits itself. Its +0x0C map view holds the
`_Rb_tree<int, pair<const int, AsciiString>>` storage whose destructor is the
existing 0x002B80CE row. The emitted `??1...UAE@XZ` and `??_G...UAE` equal
retail 0x002BAEAB and 0x002BAE8F with relocations masked, and their call
targets are the 0x002B80CE and 0x0049B47C rows. The map view's destructor is
`dllimport __forceinline`, so no stray `??1?$map@HUBfmePod24...` COMDAT is
emitted. That copy would jump to the AsciiString tree, and this unit precedes
the majority copies in link order. The unit's flags go from `/Os` to `/O1`,
the approved TU's level. The constructor is still 1/1 exact.
link_check over 11 units (the two units, both tree/map providers, Snapshot,
the kind-8 consumer, BfmeRectVNI, the name getters, SpawnArmy and the two
other int-map users): TreeCtor 0 -> 50 B LINKS, the other 10 unchanged LINKS,
5,396 -> 5,446 B. Scoped DIR32 OK; 0 orphans.
The ledger still rows 0x002BAEAB/0x002BAE8F as the QAE copies in
`Rva002BAEAB.cpp`. The linked image takes the UAE copies, which are unrowed.

The planned merge and respell are blocked on three counts:
- `tu_skeleton.py --merge LivingWorldLogic.cpp --dry-run` refuses: "TU path
  exists and holds rows of another TU (split it first)". The foreign row is
  0x002B3A9C `AttackOrders::GetMaxHeroLeaderRank`, which the map proposes
  for `AttackOrders.cpp` by name. A TU-approval decision must come first.
- The dry run lists `adopt_first`: `Rva002BAEAB.cpp` needs `WindModuleInfo`. That queue row
  (`header_queue.tsv`, still naming the pre-fold `??1Rva002BAEAB`) pairs the unit with the wrong
  class:
  - the unit's 12-byte `FXParticleSystem::WindModuleInfo` member only stands in for the Snapshot
    base;
  - it is there to bind the ICF-shared destructor 0x0049B47C;
  - canonical `WindModuleInfo.h` is 0x48 bytes, so adopting it would move `m_0C`.
  
  `header_adopt_lane.py adopt` also fails at compile: it writes the include inside
  `namespace FXParticleSystem`, so `::Snapshot` is not found. The row leaves with the unit once the
  merge and respell absorb it.
- No tool can move the rows and respell them in one step. One TU cannot hold
  both donors' views: the constructor needs the Snapshot base, and the QAE
  rows need the composition view with a non-virtual destructor. `??_G` is
  emitted only beside a vftable, and the vftable only beside the constructor.
  So `rename.py function --virtual --prepared` would still verify the rows at
  `Rva002BAEAB.cpp`, where the UAE pair cannot be emitted.
- Next step: once the TU is unblocked, merge `TreeCtor.cpp`. LWL then emits
  exact UAE copies, so the remaining step is a rehome with a respell:
  `rehome_rows.py` / `add_match --replace-existing` extended to a virtual
  respell, or `rename.py --virtual` repointing rows to a prepared approved TU.

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


2026-11-13 (merge-climb retry after class_gate fixes 4783bc7256e, 62293cb43e1,
and 0d695d658a1; base `a518c2c963fd`): the official composer absorbs
28 approved donors into `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp`.
`./build.sh` verifies 212/212 matched rows with zero row identities lost;
CSV and frozen-source checks pass. LinkGuard and ProviderGuard admit the
composition using freshly fetched index SHA-256 `d1d043b3a395600da212d61d693c571e8fa570dddb3c1f42741984890ef3c324`
(meta `50ce6f90bb`, census `50ce6f90bb`).
This is partial source consolidation, not a new census or full-image/runtime
result; historical evidence and unrelated prerequisites remain in force.
The absorbed Common/Rva002BAEAB.cpp bodies now reside at the TU path above.
Common/Rva003C2F40TreeCtor.cpp remains separate; the native hierarchy, slot
identities and kind-8 consumer reconciliation remain their own work.
