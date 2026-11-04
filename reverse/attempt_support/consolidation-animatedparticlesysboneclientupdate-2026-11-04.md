# AnimatedParticleSysBoneClientUpdate consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdate.cpp`; `consolidation_queue.py --check-tu` passed. A fresh Drawable/Update-scoped planner and its `--check` passed. The plan had six approved rows, one pull donor and one mixed donor.

The merge dry run accepted no donors. `FirestormDynamicGeometryInfoUpdateCtor.cpp` failed because the `AnimatedParticleSysBoneClientUpdate(Thing *, const ModuleData *)` constructor is absent from the class view. The mixed `ConstIntGetters4.cpp` row `0x004C9008` matched by itself, but LinkGuard refused the split because selected COMDAT `??_C@_0CE@MMFOENO@AnimatedParticleSysBoneClientUpd@` lacks matching private/weak-free context. No changes or claims were made. No source reduction or identity/link progress is claimed.
