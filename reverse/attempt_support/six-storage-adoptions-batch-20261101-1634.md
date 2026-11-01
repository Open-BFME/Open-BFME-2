# Six BFME2 storage adoptions: bounded batch evidence

Initial outgoing base `640a2cfb086a67f392bd0cc366effafb09a5d214`. Six claimed source units adopt the existing
registered Matrix3D storage, removing six private copies. Normal gates preserve 7
existing native function/EH rows (2708 bytes of ledger extents) and 15
retained external code bodies and their resolved relocation targets.
No new native/authored-byte or matched-row gain is claimed.

- [Use canonical Matrix3D storage in maintain-position transforms](maintain-position-matrix3d-20261101-1634.md): 1 row(s), 491 bytes, 4 retained code bodies.
- [Use canonical Matrix3D storage in movement angle transforms](move-towards-angle-matrix3d-20261101-1634.md): 1 row(s), 475 bytes, 1 retained code bodies.
- [Use canonical Matrix3D storage in locomotor orientation](locomotor-orientation-matrix3d-20261101-1634.md): 1 row(s), 241 bytes, 3 retained code bodies.
- [Use canonical Matrix3D storage in drawable instance transforms](drawable-instance-matrix3d-20261101-1634.md): 1 row(s), 605 bytes, 1 retained code bodies.
- [Use canonical Matrix3D storage in tornado bone queries](tornado-bone-query-matrix3d-20261101-1634.md): 1 row(s), 480 bytes, 3 retained code bodies.
- [Use canonical Matrix3D storage in drawable transform cache](drawable-transform-cache-matrix3d-20261101-1634.md): 2 row(s), 416 bytes, 3 retained code bodies.

Normal/frozen/EH/strict and owning acceptance pass on each source; six Matrix3D
queue keys retire through their owning tool. The standalone native new-variants
check passes for all six objects. Removed helper components have no retained
runtime/data incoming edge; emitted array iterators have measured existing
34/48-byte compiler profiles and no retained runtime root in these objects.
Raw object comparisons remain available. Only defined compiler-local code
labels may be resolved by their identical external owner and section-relative
offset; external identities, bytes, relocation kinds and positions never change.
The native switch-table gate also validates maintain-position's nine entries.
The angle bit-copy retains its barrier after the fifth word; the orientation
cross products, tornado approximation and cache's explicit integer copy remain.

Final bounded preview (a prediction against an index, not a new census):

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/LocomotorMaintainCurrentPosition.cpp: LINKS  LINKED 491 -> 491 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 491)
Code/GameEngine/Source/GameLogic/Object/LocomotorMoveTowardsAngle.cpp: LINKS  LINKED 475 -> 475 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 475)
Code/GameEngine/Source/GameLogic/Object/LocomotorRva001E41FASetOrientation.cpp: LINKS  LINKED 241 -> 241 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 241)
Code/GameEngine/Source/GameClient/DrawableSetInstanceMatrix.cpp: LINKS  LINKED 601 -> 601 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 601)
Code/GameEngine/Source/GameClient/Rva00276952.cpp: LINKS  LINKED 480 -> 480 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 480)
Code/GameEngine/Source/Common/Rva000E459F.cpp: LINKS  LINKED 416 -> 416 bytes (census 2026-11-01 14:31 at 86db074988; file's own bytes 416)
link_check: 6 of 6 link cleanly; LINKED 2,704 -> 2,704 bytes (2.9s)
```

Immutable outgoing audit at `640a2cfb086a67f392bd0cc366effafb09a5d214` -> `c01b79411c903657226d8195b9c5b4b96b1a66d1` (before this documentation-only amendment), exit 2:

```text
link batch audit: INCONCLUSIVE baseline: index at 86db074988, outgoing base 640a2cfb086a67f392bd0cc366effafb09a5d214; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

Complete current provider/consumer selection remains unproven where the
available index or receipts are incomplete. No complete-image link, gameplay,
RAM/leak/crash/FPS gain is claimed. No shared header, compiler option, native
address pin, alias, new identity or baseline was changed.

Controls: ignored build/six-each-half-resources-20261101-1634 and the matching
diagnostic package. Two independent repository processes use BUILD_POOL=7 each
(aggregate ceiling14 of28 logical CPUs); memory budget about48GiB of95.7GiB.
No local model was needed. Claims are released after ordinary publication.
