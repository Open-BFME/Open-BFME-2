# W3DFloorBuffer consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DFloorBuffer.cpp`; `consolidation_queue.py --check-tu` passed. A fresh scoped planner and `--check build/consolidation` passed. Its plan had 76 approved rows, four pull donors and one mixed file.

The fresh merge dry run accepted no donors. `Rva000E48BC.cpp` needs missing Matrix3D declarations; `W3DFloorElementDestructor.cpp` needs `TextureClass` and has a specialization conflict; `Rva000E59D3Dtor.cpp` collides on `_STL::allocator` definitions. Class-view reconciliation is reported for these donors. The sole mixed source, `OpaqueScalarDeletingDtorsB01.cpp`, has no definition spelling the approved row `0x000E583E`, so its guarded split cannot carve it. No changes or claims were made. Revisit after the class/view prerequisites change; no source reduction or identity/link progress is claimed.
