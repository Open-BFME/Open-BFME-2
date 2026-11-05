# RvaSmartPtr12 canonical declarations, 2026-11-05

Base: `1abed13152`. Seven queued consumers now include
`Code/GameEngine/Include/Common/RvaSmartPtr12.h` instead of declaring private
class bodies. Each keeps the guarded unlink destructor inline in its own TU.
The shared header and `DestroyInstances.cpp` remain unchanged.

| Consumer | Byte-verified rows | Link preview bytes preserved |
| --- | ---: | ---: |
| Common/Rva00098690Destructor.cpp | 6 | 113 |
| Common/Rva001F5BBE.cpp | 3 | 133 |
| Common/Rva003FDC46.cpp | 3 | 165 |
| GameClient/System/FXParticleSystem/DefaultModuleHeadBase.cpp | 3 | 82 |
| GameClient/System/FXParticleSystem/Rva003A5A58WindUpdate.cpp | 3 | 717 |
| GameClient/System/FXParticleSystem/Rva0055F840Ctor.cpp | 11 | 440 |
| GameClient/System/FXParticleSystem/Rva0056224FCtor.cpp | 8 | 481 |

Paths above are relative to `Code/GameEngine/Source/`. The total is 37 rows
and 2,131 preview bytes. `header_adopt_lane.py accept --class RvaSmartPtr12`
accepted all seven together and retired their seven header-queue rows.
`find_declared_unmatched.py` passes for every changed source.

The destructor tests canonical `field00` before calling `rva0004CBC0`.
Typed uses of the former private pointer fields cast canonical `void *`
storage to `ParticleSystem *`; no second class layout is introduced.
DefaultModuleHeadBase's explicit cleanup is replaced by automatic member
destruction, retaining its 20-byte destructor and avoiding double unlink.

## Shared-header experiment and remaining work

Putting the same inline destructor in the shared header, either inside or
outside the class body, changes STLport `_Destroy<RvaSmartPtr12>` at
`0x00211F9A`. Its retail 9-byte body loads ECX and tail-jumps to the ordinary
destructor. MSVC 7.1 instead emits `8b4c2404 6a00 e8........ c3` (12 bytes),
calling the scalar deleting destructor with flags zero. The byte verifier
correctly refuses the relocation extending beyond the retail row. A scoped
87-dependent header gate exposed this failure; no extent, verifier or baseline
was changed to admit it. A noinline member redeclaration experiment also
fails compilation (C2761); it was removed.

TU-local inline definitions preserve both the seven consumers and the
existing STL cleanup: `./build.sh` passed 67/67 rows for the first two
consumers plus unchanged DestroyInstances, then 28/28 for the other five.
Shared inline lifetime and the missing default constructor remain prerequisites
for broader RvaSmartPtr12/BfmeParticleSystemHandle adoption. An automatic
SmartPtrRvoGetter swap still mismatches and was restored.

## Provider and link checks

`link_check.py` reports seven LINKS previews, 2,131 -> 2,131 bytes, against
the census index at `f44cbcf5b0` (2026-11-05 15:19). These are predictions,
not a new census or real-link measurement.

Comparing external definitions in all seven current objects with that index
retains every indexed RvaSmartPtr12 provider, including the ordinary
destructor; DefaultModuleHeadBase adds a destructor COMDAT. The full external
definition comparison shows five absent ParticleSystem accessor names in the
wind unit. `git diff f44cbcf5b0 HEAD -- <wind source>` proves those were already
removed by its earlier ParticleSystem header adoption, before this batch;
the index records no other object touching those five names. This batch
removes no alias or shared handle provider. The outgoing hook's batch audit
still decides affected-consumer losses and records any baseline uncertainty.

LINK-155 remains open for the remaining handle consumers and ParticleSys.cpp
consolidation.
