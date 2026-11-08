### LINK-636: FX module template copy constructors stored hand-written char stand-ins for their class tables
Status: Partly cleared. Updated: 2026-11-08; inspected revision: 273aaff9b5.
Evidence / affected units: the `*ModuleTemplateCopyCtorThunk.cpp` units under
`Code/GameEngine/Source/GameClient/System/FXParticleSystem/` defined one-byte
`extern "C" char <Class>_cvtbl0` / `_csub_vtbl` globals at each retail table's address and stored
their addresses. The real link refused them (`strong-definition`), and the default-constructor units'
real tables were bridged because they carried only the deleting-destructor slot.
- Retail (target facts): each template's +0 table is deleting destructor, two pure calls and
  `writeINI`; +4 is the folded single-pure `CategoryModuleInfo` table VA 0x00C1C780; +8 is the -8
  deleting-destructor thunk, then its info's `LoadPostProcess`, `GetSnapshotName` and `DoXfer`.
  `CategoryModuleTemplate<6>`'s own table (deleting destructor 0x00001EAE, three pure calls) shows
  that the category template introduces the three slots.
Recipe (landed): `Code/GameEngine/Include/GameClient/FXModuleTemplateBase.h` declares the bases with
the three slots; a per-template header declares the class on `CategoryModuleTemplate<N>` and its
info class (an info header with the capitalized Snapshot slots); both constructors include it and the
copy constructor is a plain member-wise copy. The class is abstract, so the deleting destructor is
emitted by the `VectorDeletingDtorsV0x_Unresolved.cpp` anchor unit through a `novtable`
size-and-base view under the real class name, and rowed with its -8 thunk as ICF folds of the
opaque `Rva...Vec` owners. Every constructor still matches; emitted slots were checked against
the bridge queue's retail targets.
Completed (commits 3db87a43ad..273aaff9b5): LightningDraw, LightningEmission,
DefaultModuleTemplate<0>, <1>, <2>, <3>, <6>, CylindricalEmissionVelocity, OrthoEmissionVelocity,
SphericalEmissionVelocity, OutwardEmissionVelocity, TerrainFireEmission, QuadDraw, StreakDraw;
RenderObjectUpdate in c1611d4466 (its template header selects the capitalized Snapshot slots before
including `RenderObjectUpdateModuleInfo.h`).
Butterfly's copy constructor now names `DefaultModuleTemplate<6>`'s real +0 table through its
existing alternatename.
Regression found and repaired (2026-11-08, link_check over the 34 touched units: 16 -> 34 link,
census bytes 4,336 -> 4,455):
- The default-constructor units inline `CategoryModuleTemplate<N>`'s constructor, so they emit its
  table. With the three slots declared there it had retail's four slots, but `FXParticleSystem.cpp`
  (held by another seat) emits a one-slot copy first in link order. The slots now come from
  `FX_MODULE_TEMPLATE_SLOTS` in each template class (identical derived tables), until that unit's
  category view carries them.
- `new X[2]` in the anchor units' views generated an implicit default constructor under the real
  constructor's name (a duplicate strong definition). The views now declare the constructor.
Lesson: run `tools/link_check.py` over every touched unit before pushing; byte matching alone does
not show either failure.

Remaining / next check:
- ButterflyDraw: its default-constructor unit was held by another worker on 2026-11-08 (it views
  the info through `SecondaryModuleBase`/`ModuleInfo`).
- Box, Point and Sphere EmissionVolume: their default constructors live in
  `FXParticleSystem.cpp`'s own views (59, 41 and 49 bytes), so only the copy constructors can adopt
  a header until that unit is reconciled.
- HemisphericalEmissionVelocity and `DefaultModuleTemplate<7>` (three stores, no info copy)
  keep their stand-ins.
- 2026-11-08 DefaultModuleTemplate01InlineCopyCtors.cpp removes its two unowned char
  stand-ins at 0x0081BA60/0x0081D5E8 and binds existing compiler tables, whose addresses
  are independently proved by native constructor DIR32 operands. Its 97-byte copy and
  two unrelated registered data rows remain exact; the private alpha-info copy view and
  unused helper disappear. Bounded cached replay removes two strong-definition refusals,
  with the existing five-slot head bridge unchanged. Registered v0b/vsub chars remain for
  complete class recovery; real-link confirmation is pending.
  [Evidence](../../reverse/attempt_support/default-alpha-table-bindings-20261108/README.md).
- Confirm in the next published real link that the converted tables leave
  `reverse/vtable_bridge_queue.tsv`.

2026-11-08 particle clone prerequisite: Rva003AF27BClone.cpp removes its own
two one-byte stand-ins for0x0081CFB0/0x0081C030 and binds the existing compiler
tables, with native constructor operands proving each address. Its81-byte row
and parent EH graph remain exact; preview conserves LINKS/81. Bounded replay
removes two strong-definition refusals, retaining the same two bridges/six
slots. The shared +0x18 char belongs to ParticleModuleTemplateCopyCtors.cpp
and remains for that nine-row cohort's recovery. Full concrete class/template
recovery and real-image confirmation remain open.
[Evidence](../../reverse/attempt_support/particle-clone-table-bindings-20261108/README.md).

**2026-11-08 particle copy-constructor cohort:** ParticleModuleTemplateCopyCtors.cpp
retires its 21 unowned one-byte table stand-ins and nine old linker aliases.
Existing compiler symbols have independent native constructor operand proofs;
distinct construction-stage symbols preserve stores at the folded pure table.
The sole live outside char consumer, Rva003AF27BClone.cpp, changes in the same
batch. All 10 rows (579 bytes of extents), EH 1, strict preparation and paired
consumer checks pass; code COMDAT facts and flags remain equal after only
proved table-referent normalization. Bounded cached replay removes 21 strong
definition refusals, with the same 29 bridges/115 slots remaining. The previous
clone packet's shared-char prerequisite is resolved; full class recovery and
real-image confirmation remain open. No bridge-retirement or runtime claim.
[Native proofs and stage-coalescing boundary](../../reverse/attempt_support/particle-copy-table-bindings-20261108/README.md).

Published as 7efac5f6d8; first attempt landed in 29.4 seconds. Required
row/EH/scoped-DIR32 checks pass after rebase. Broader link audit remains
INCONCLUSIVE: index d171e84869 versus outgoing base
0292da473397a175f09d211b8414f863e409d73a; Common/AIBaseBuilder.cpp lacks a
current receipt. Carry that consumer into the next census/image check;
this publication does not establish full link closure or runtime progress.

**2026-11-08, seat LeonardBuhl: Rva003AE1A7CopyCtor.cpp's two stand-ins replaced (`898bd40bda`).** The copy
constructor 0x003AE1A7 now stores `??_7Rva003ACA93Object@@6BRva003AC8D7Slot0@@@` (VA 0x00C1CA40) and `...Slot2@@@`
(0x00C1CA2C), the SELECT_ANY tables ModuleTemplateCloneSlots.cpp emits and the data ledger binds there, instead of the
strong one-byte `Rva003AE1A7_v0`/`_v0C`. 1/1 row exact; link_check LINKS 38 -> 38. Expected next real link: the two
strong-definition refusals at 0x0081CA40/0x0081CA2C go and those tables are bridged (short one-slot copies), like the
`7efac5f6d8` cohort. Clearance: none claimed. The concrete class (ConcreteModuleTemplate over
RenderObjectParticleUpdateModule, opaque here as Rva003ACA93Object) and its full tables remain.

Same seat, its base 0x003AE1CD (Rva003AE1CDCopyCtor.cpp): `Rva003AE1CD_v0`/`_v0C` give way to
`??_7Rva00562366@@6BRva003ADFDBPrimary@@@` (VA 0x00C1D31C) and `??_7Rva00562366@@6B@` (0x00C1D348), the SELECT_ANY
tables Rva0056224FCtor.cpp emits there. 1/1 row exact; link_check LINKS 64 -> 64. Clearance: none claimed.

**2026-11-08 Rva003AE2A9 copy/clone:** the two-row unit replaces its three
unowned one-byte stand-ins at 81CAA4/81CAA0/81CA90 with the existing compiler
tables for Rva003ACB08Object's three bases. Fresh factory operands at
3ACB3D/44/4B prove the bindings; all seven source/emitter rows and five EH
graphs pass. No provider is introduced, and the two code bodies differ only
in proved table referents. Bounded replay removes three strong-definition
refusals while retaining the same three bridges/nine slots. The current
providers are still only one slot each. ConstIntGetters4.cpp is held by
another worker: its cached getter bytes/literal pass read-only checks, but
its full strict receipt remains absent. Full classes/tables, that receipt
and next-image confirmation remain open; no image/runtime gain is claimed.
[Operand, provider and scope evidence](../../reverse/attempt_support/particle-terrain-copy-bindings-20261108/README.md).

Published as 93b020e848 on attempt two (39.7 seconds for that attempt).
Required checks pass. The broader audit is INCONCLUSIVE: index c885072a48
versus outgoing base 7f2a947b2b3921105c072485964426740fef0357, with the three
removed char names reported as provisional loss candidates through an
unread object and zero proven newly unresolved names. The scoped consumer
proof found no outside live consumer. Carry those names and the held
getter receipt into the next census/image; no full-link clearance is claimed.

2026-11-08 root alpha Snapshot follow-up: Rva003AEA15CopyCtor.cpp removes
three byte stand-ins, uses the existing primary/factory arrays and full
Rva003ABC6E Snapshot table, and fixes its stale C1C900 compiler qualifier
from the exact 3ACEFC store. The C1CDBC data owner transfers from the
one-byte char to the existing 16-byte compiler table; all four native
targets/relocations and its independent next-datum boundary pass. Normal
37 code/16 data rows pass. Bounded replay removes strong/unbounded
refusals 2 -> 0 with no bridge required for this table. The full generated
index retains every verified owner; its raw extent must be refreshed for
the real link. Primary/factory array recovery and next-image confirmation
remain; this is not full enclosing-class or runtime clearance.
[Native owner and index scope](../../reverse/attempt_support/alpha-snapshot-owner-20261108/README.md).

Published as cfeb0c1829 with index ee6718dbac (first attempt, 34.8 seconds).
Required checks and post-publication table proof pass. Broader audit stays
INCONCLUSIVE for unchanged ConstIntGetters4.cpp's missing current receipt
at indexc885072a48/base15b108ac97; two unchanged emitter destructor-alias
identity shadow findings remain. Carry those scopes into the next census
and image check; no complete game/link clearance is claimed.

2026-11-09, LightningDraw runtime wrapper: Rva00561527.cpp removes its two
strong V3Slot0/V3Slot2 arrays and an unused private class declaration. The
three live constructor stores now use existing Rva005EBCC0Object compiler
tables, independently placed at CD54/CD40 by the exact 3AE792 copy. Normal
23/23 code and two data rows pass; whole code/flags/policies and other data
are equal after the two referent substitutions. Cached replay removes two
strong refusals with the same two bridges/fifteen slots. The 4-byte views
still need complete 44/16-byte class recovery. Thirteen cached support
objects lack strict receipts, including held getters/animobj; no global or
image clearance is claimed. Next: maintained census/image queue confirmation.
[Native operands, retained bridges and support gaps](../../reverse/attempt_support/lightning-stored-tables-20261109/README.md).
