# PathNode debug consumer: Coord3D class-key prerequisite

Inspected revision: `133835fe3e` (2026-11-04).
Scope: `Code/GameEngine/Source/GameLogic/AI/PathDebugOutput.cpp`,
`??6@YAAAVDebug@@AAV0@ABVPath@@@Z`, RVA `0x002E7CCB`, 93 bytes.

The header queue reports an incompatible `Coord3DView` position member.
Replacing the private PathNode/coordinate views with `PathNode.h`, using
`m_nextOpti`, and streaming `node->m_pos` directly compiles. The complete
93-byte function matches except its unresolved call relocation: the included
canonical `struct Coord3D` makes MSVC emit
`??6@YAAAVDebug@@AAV0@ABUCoord3D@@@Z`. The existing 103-byte provider at
`0x000050BA` in `Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp` is
`??6@YAAAVDebug@@AAV0@ABVCoord3D@@@Z` and declares Coord3D as a class.
This is the already documented Region3D class-key prerequisite, now observed
in the remaining queued PathNode consumer too.

Retaining the original class forward declaration and stream declaration before
including PathNode.h still produces the U-keyed reference. The second trial is
saved in [trial.patch](trial.patch). Neither trial passed byte verification;
no header acceptance was requested and the queue entry remains.

Both trials were reverted. Restored `./build.sh` verification passes the one
93-byte row and all four string references. No source, ledger, pin, alias or
shared header change remains. Resume this adoption after coordinated Coord3D
class-key reconciliation; changing the exported provider or adding a second
name is not this consumer's repair.
