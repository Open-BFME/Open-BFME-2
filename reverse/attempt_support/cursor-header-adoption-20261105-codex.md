# Rva000411084 header adoption, 2026-11-05

Inspected base: `bd3dc33fb4`. Scope: the eleven remaining header-queue consumers
of `Code/GameEngine/Include/GameClient/Rva000411084.h`; class claim held by
`yasinschroeder-codex`. No original class or template-specialization name is
recovered by this change.

All eleven consumers adopt the existing header and its established two-pointer layout:

- Common/RTS/PlayerInitFromDict.cpp
- Common/RTS/PlayerUpdate.cpp
- Common/RTS/PlayerXferStringMaps.cpp
- Common/Rva003EF36EDtor.cpp
- GameClient/LivingWorld/LivingWorld.cpp
- GameClient/LivingWorld/LivingWorldManagerXferObjects.cpp
- GameClient/Rva00213A85.cpp
- GameClient/System/FXParticleSystem/ParticleSystemManagerDtor.cpp
- GameLogic/ScriptEngine/ScriptEngine.cpp
- GameEngineDevice/Source/MilesAudioDevice/MilesAudioIsMusicAlreadyLoaded.cpp
- GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp

The Common/GameClient/GameLogic paths above are under Code/GameEngine/Source;
the last two paths are under Code/. Member references use the header's
`m_current` and `m_owner`. ParticleSystemManagerDtor explicitly casts the current
node to its existing node type before accessing its value.

`next` and `advance` remain inline member definitions outside the class in
PlayerUpdate, PlayerXferStringMaps, Rva003EF36EDtor and
LivingWorldManagerXferObjects. A declaration-only
trial changed code generation; retaining the existing bodies preserves the
compiler's alias analysis and external providers without another private class.
The owned implementations remain EvaMessageName.cpp (0x00411084, 22 bytes) and
EvaBucketAdvance.cpp (0x003F7925, 47 bytes).

PlayerXferStringMaps copies the typed WVIter's two fields into the canonical
cursor within a short scope. This replaces its private converting constructor
and unused assignment overload while preserving the original iterator lifetime
and code generation. Both xfer loops remain byte-exact.

Verification:

- Normal scoped `./build.sh` on original sources passed, then the final
  eleven-source build passed 645/645 code rows, 5 data rows, 226 funclet pins,
  5 STLport folds, 47 string literals plus 3 empty-string references, 40 float
  literals and 109 import references. No row identities, paths or pins changed.
- `find_declared_unmatched.py` passes on all eleven final sources.
- Compared all external definitions in original and final compiled objects.
  Only the empty default constructor from MilesAudioIsMusicAlreadyLoaded.cpp
  (`??0Rva000411084@@QAE@XZ`) and the WVIter converting constructor from
  PlayerXferStringMaps.cpp disappear. Scanned all 39,131 `.obj` files under
  build/ (including scratch objects) with the census COFF symbol/directive
  reader: no undefined, weak-external or /INCLUDE reference names either
  constructor. No other external definition or alias is removed.

This is header cleanup of an existing placeholder, not a missing-row regression.
Acceptance: one `header_adopt_lane.py accept --class Rva000411084` over all
eleven sources passed and retired all eleven header-queue rows. Its scoped
link preview gave a usable no-loss verdict for every source, using the index
dated 2026-11-05 15:19 at f44cbcf5b0 and the fetched object store. This is a
retirement guard, not a new census or a real-link improvement measurement.
