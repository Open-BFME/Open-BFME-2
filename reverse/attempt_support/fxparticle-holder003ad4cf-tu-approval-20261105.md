# FXParticleSystem Holder003AD4CF approval prerequisite (2026-11-05)

Seat `yasinschroeder-codexb`, model `gpt-6.1-sol`, base `c756ff3c6b`.
The default picker proposed `Holder003AD4CF.cpp`, but the existing owner is
`Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva003AD4CFInit.cpp`.
Its three matched rows are the holder constructor at RVA 0x003AC48B (12 bytes),
the initializer at 0x003AD4CF (33 bytes), and cleanup at 0x007B806A (1 byte).
The source passes `find_declared_unmatched.py`; there is no missing body.

A fresh `name_lane.py consolidate --under
Code/GameEngine/Source/GameClient/System/FXParticleSystem/` packet left all
three rows unresolved with no alternative approved unit. `tu_skeleton.py
--plan Code/GameEngine/Source/GameClient/System/FXParticleSystem/Holder003AD4CF.cpp`
reported zero approved rows and zero donors. The private DefaultModuleTag<7>
and holder spellings do not establish a retail source path.

This is the existing initializer-scaffold prerequisite documented in
`docs/consolidation.md` (FXParticleSystem evidence, Initializers), not a new
regression. Do not promote the proposed path or merge this source without
new target file evidence or established original identities. No source or
TU-map edit was retained; the proposed scope claim was released.
