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
SphericalEmissionVelocity, OutwardEmissionVelocity, TerrainFireEmission, QuadDraw, StreakDraw.
Butterfly's copy constructor now names `DefaultModuleTemplate<6>`'s real +0 table through its
existing alternatename.
Remaining / next check:
- ButterflyDraw: its default-constructor unit was held by another worker on 2026-11-08 (it views
  the info through `SecondaryModuleBase`/`ModuleInfo`).
- RenderObjectUpdate: `RenderObjectUpdateModuleInfo.h` spells the Zero Hour slots
  (`loadPostProcess`, protected `xfer(Xfer *)`); it needs the capitalized BFME 2 slots first.
- Box, Point and Sphere EmissionVolume: their default constructors live in
  `FXParticleSystem.cpp`'s own views (59, 41 and 49 bytes), so only the copy constructors can adopt
  a header until that unit is reconciled.
- HemisphericalEmissionVelocity, `DefaultModuleTemplate<7>` (three stores, no info copy) and
  `DefaultModuleTemplate01InlineCopyCtors.cpp` keep their stand-ins.
- Confirm in the next published real link that the converted tables leave
  `reverse/vtable_bridge_queue.tsv`.
