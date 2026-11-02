# Six BFME2 canonical-storage adoptions: bounded batch evidence

Initial outgoing base `bcd82c82acff2ec8020dda7d12604d8ce21a074b`. Six separately claimed source units remove six
private Matrix3D definitions and use the existing canonical storage header.
The normal gates preserve 68 existing function/EH rows (9880 bytes of
ledger extents), 174 retained external code bodies and their resolved
relocation targets. Independent named-static checking preserves 9
local C++ code definitions. Compiler-generated EH labels are covered by complete
BFME1 runtime-section comparison or BFME2 native parent EH verification.
Added/removed code components are checked for runtime incoming references;
new emitted constructors/iterators are checked against measured exact profiles.
No new matched-row or native/authored-byte progress is claimed.

- [Use canonical Matrix3D storage in sun-ray setup transforms](sun-rays-matrix3d-20261102-1509.md): 6 rows, 2028 bytes, 9 retained external code definitions.
- [Use canonical Matrix3D storage in matrix inverse widening](inverse-widening-matrix3d-20261102-1509.md): 1 rows, 332 bytes, 4 retained external code definitions.
- [Use canonical Matrix3D storage in transport rider updates](transport-rider-update-matrix3d-20261102-1509.md): 6 rows, 818 bytes, 25 retained external code definitions.
- [Use canonical Matrix3D storage in farm model-state transforms](farm-model-state-matrix3d-20261102-1509.md): 27 rows, 3780 bytes, 72 retained external code definitions.
- [Use canonical Matrix3D storage in horde model-state transforms](horde-model-state-matrix3d-20261102-1509.md): 26 rows, 2791 bytes, 62 retained external code definitions.
- [Use canonical Matrix3D storage in matrix comparisons](matrix-comparison-matrix3d-20261102-1509.md): 2 rows, 131 bytes, 2 retained external code definitions.

Owning acceptance retires 6 Matrix3D queue rows. Normal/frozen/native EH
verification, strict current receipts and new-variant checks pass. The existing
committed BFME1 reference remains131fb8ff0a515c504313ac10ec87c929d71cf214;
no dependency pointer is authored. The published index was fetched by the native
tool; its date/commit are included in every bounded prediction below.

Final bounded preview (not a new census, complete current selection or runtime):

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva0009CD9BSunRaysSetup.cpp: LINKS  LINKED 1,978 -> 1,978 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,978)
  diagnostic  ??0ShaderClass@@QAE@ABV0@@Z  (register allocation differs from the majority copy, same instructions and offsets; unreferenced, not a blocker)
Code/Libraries/Source/WWVegas/WWMath/Rva007133F0MatrixInverse.cpp: LINKS  LINKED 332 -> 332 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 332)
Code/GameEngine/Source/GameLogic/Object/Contain/TransportContainRiders.cpp: LINKS  LINKED 809 -> 809 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 809)
Code/Libraries/Source/WWVegas/WWLib/setModelStateRva000C4E23Farm.cpp: LINKS  LINKED 3,581 -> 3,581 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,581)
  diagnostic  ??$__destroy_aux@PAVAsciiString@@@_STL@@YAXPAVAsciiString@@0ABU__false_type@0@@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ??$__destroy@PAVAsciiString@@V1@@_STL@@YAXPAVAsciiString@@00@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DHordeModelDrawSetModelState.cpp: LINKS  LINKED 2,579 -> 2,579 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,579)
Code/Libraries/Source/WWVegas/WWMath/matrix3d_equal.cpp: LINKS  LINKED 131 -> 131 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 131)
link_check: 6 of 6 link cleanly; LINKED 9,410 -> 9,410 bytes (3.0s)
```

Immutable audit before this documentation-only amendment, `bcd82c82acff2ec8020dda7d12604d8ce21a074b` -> `59ace4d0d655d693aaae4042e61ce427bc205aa3`, exit 2:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base bcd82c82acff2ec8020dda7d12604d8ce21a074b; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

Missing receipts, differing indexes or other unverified provider/consumer
selection remain UNKNOWN/INCONCLUSIVE. A full engine link, gameplay and any
RAM/leak/crash/FPS gain are unproved. No shared header, compiler flag, native pin,
alias, new identity, gate or baseline is changed. Scratch controls live under
build/six-each-full-resources-20261102-1509. BUILD_POOL=14 per independent
repository process, aggregate28 workers on28 logical CPUs; all system resources
were authorized, without a local inference or GPU workload. Claims are released
after ordinary publication.
