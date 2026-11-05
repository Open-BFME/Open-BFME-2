# TeamPrototype canonical header adoption

Inspected revision: `8b681de717`, 2026-11-05. Scope is nine TeamPrototype
consumers; no shared header, ledger identity, source path, pin or alias changes.

The canonical `Common/Team.h` already proves the 0x338-byte layout. Its opaque
string/template storage blocked automatic member mapping in the reset and
transfer units. The reset method now casts the same +0x10/+0x14 storage to
AsciiString and +0x12C storage to its existing TeamTemplateInfo view. Transfer
uses AsciiString at +0x318 and Snapshot at +0x12C; its coordinates, flags,
frame and list head use the canonical fields. These are target offsets already
recorded in Team.h, not newly inferred donor layouts. Transfer no longer needs
its separate TeamTemplateInfo declaration.

Seven other consumers had private TeamPrototype views containing just the
+0x334 list head and an inline iterator constructor. Automatic adoption removed
that inline implementation along with the class, leaving an external call to
the header's declaration and failing the byte check. Defining the same method
inline outside the canonical class preserves each TU's existing iterator ABI
and code generation. PlayerSetObjectsEnabled independently verified this
explanation before applying it to the other six consumers. The shared header
stays unchanged; no additional class view or linker escape hatch is introduced.

Verification:

- `./build.sh TeamPrototypeReset.cpp`, `TeamPrototypeXfer.cpp` and
  `PlayerSetObjectsEnabled.cpp`: each 1/1 function row exact.
- A combined build of PlayerAddScience, PlayerKillPlayer, PlayerRva002AD93A,
  PlayerTransferAssets, PlayerUpdate and TacticalAI_updateInterestZones:
  21/21 function rows exact, four renumbered funclets verified through parent
  EH data, 13 string literals and one float literal verified.
- `find_declared_unmatched.py`: all defined functions matched in all nine units.
- `header_adopt_lane.py accept --class TeamPrototype`: all nine PASS; exactly
  nine queue rows retired by the owning tool. Other classes' queue rows remain.
- Current-object `link_check.py` of all nine: 9/9 LINKS and 3,939 -> 3,939
  preview-linked bytes against the local 2026-11-05 15:52 index at `112a456a2c`.
  Per unit: PlayerAddScience 505, PlayerKillPlayer 499, PlayerRva002AD93A 393,
  PlayerSetObjectsEnabled 145, PlayerTransferAssets 1,045, PlayerUpdate 361,
  TeamPrototypeReset 152, TeamPrototypeXfer 473, TacticalAI_updateInterestZones 366.
- `link_check.py --fetch-index` kept that local index because the published
  index was older (15:19 at `f44cbcf5b0`). Published object import completed.
- `check_csv.py` and `git diff --check` pass.

No census gain, real-link clearance, ownership gain or runtime test is claimed.
The initial default pick was the already repaired BoneFXDamage blocker; its
prior evidence was read and the unchanged old-index failure was not reworked.
The remaining TeamPrototype queue includes constructor/destructor, typed
string-storage and other iterator consumers; this scoped adoption does not
clear the broader Team.cpp merge prerequisites.
