# VectorClass<int> scalar deleting destructor selection

The real link at fb27075119 reports the table at RVA 0x007BB5AC
with slot zero blocked on the first provider of
`??_G?$VectorClass@H@@UAEPAXI@Z`. The 34-byte retail body at
0x0000232B is rowed in `vector_class_resize.cpp`. The first
definition, from `Render2DSentenceAllocateSurfaceBFME2.cpp`, has
71 bytes. It inlines the VectorClass<int> cleanup and includes a
vector-delete call the 34-byte body lacks.

- Repeating the complete-destructor declaration after
  `NativeIntVectorSlots.h` leaves all 11 rows exact but still emits
  the same 71-byte scalar deleting destructor.
- A TU-local imported inline specialization at that location is
  rejected as a redefinition (C2995). The shared header already owns
  the forced-inline complete destructor.
- A declaration-only `Clear` specialization after the header is
  too late (C2908). Placing it before the header compiles and
  produces a 36-byte scalar deleting destructor. The parent at
  0x00158C60 and both verified funclets at 0x00767178/0x00767180
  change, so this variant does not preserve the retail parent.

The two unedited provider units passed 19/19 rows and their
per-file link preview. The retained inline cleanup in the allocation
parent and the exported scalar deleting destructor require separate
treatment. No candidate source or table change was retained.
