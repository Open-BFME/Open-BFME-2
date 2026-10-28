# HordeTransportContain consolidation, 2026-10-28 (claudeb)

Destination: Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/
HordeTransportContain.cpp, the approved TU in reverse/tu_map.csv (46 approved
rows). This session's four guarded merges absorbed 9 whole-file donors (RadarUpgrade
was a separate TU). Each view change landed in its own verified commit before
its merge; the merges themselves lost no matched row.

Shared view now in the seed (single inheritance, the only shape every merged
body agrees on): OpenContain { exitObjectViaDoor; protected xfer },
TransportContain { ~TransportContain; update; protected xfer },
__declspec(novtable) HordeTransportContain { dtor, getModuleNameKey, onDie,
exitObjectViaDoor; protected xfer; prefix04[4]; m_object at +0x08 }. Object is
method-only; field reads go through inline accessor views
(Rva00477305ObjectView, ExitTemplateView, HordeTransportContainXferView), so
a donor never needs data members on the shared classes. The composer moves
`#define`/`#undef` lines apart from the classes that use them: macros the
shared views use stay defined (PURE_SLOT).

Remaining whole-file donors, all rejected by `--merge --dry-run`:

- HordeTransportContainCtor.cpp (/GX): models the ctor through a pack(1)
  non-polymorphic TransportContain with explicit vtable stores at +0x00..+0xFC,
  three address-named char globals (g_00C45CFC, g_00C45D30, g_00C45EB8) and a
  Coord2D member at +0x11D. Joining needs the real multiple-inheritance model
  of TransportContain/OpenContain (its secondary vptrs at +0x0C, +0x10,
  +0x20..+0x34, +0xFC), which the seed's single-inheritance view cannot carry.
- HordeTransportContainIface20.cpp and HordeTransportContainIsValidContainerFor.cpp:
  overrides in the +0x20 interface vftable 0x00C45D30, so `this` is the +0x20
  subobject and slot positions (38, 51, 69) are layout. Same prerequisite: a
  shared MI declaration of HordeTransportContain's bases; IsValidContainerFor
  also declares HordeTransportContainModuleData as a struct with data
  (the seed has a class) and Object with a data member at +0x250.
- HordeContain/HordeTransportContainNestedRiders.cpp (/O1): needs the body of
  Rva0046247D::rva0046247D visible (inline, noinline) while the seed's
  rva004779F9 and redeployOccupants need it opaque; and it calls slot 15 (x3C)
  on a pure-virtual HordeTransportContain view.
- HordeContain/HordeTransportContainRva00477BA2.cpp (/O1 /G7 /arch:SSE): its own
  Matrix3D/Vector4 view clashes with the seed's matrix3d.h (Get_X_Vector return
  type), Object carries data members, and its flags differ from the seed's.

Mixed sources outside the merge: Common/ConstIntGetters4.cpp,
Contain/ContainModuleDeletingDtors.cpp,
Contain/HordeSiegeEngineContainModuleDataDtor.cpp; the funclet rows in
Code/gen_small/uw_gen_012.cpp follow their parents.

Debug aid that proved faster than repeated dry runs: compose the seed plus one
donor with tu_skeleton.compose (relocate_includes with repo-relative
directories) and compile that text through build.try_compile_source to see the
full error list; the dry-run log keeps only the first error per donor.
