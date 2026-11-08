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
