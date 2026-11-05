# BoneFXDamage canonical INIException adoption

Inspected revision: `30e44e64fb`, 2026-11-05. Scope:
`Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp`.

The unit's private INIException declaration duplicated the registered header
`Code/GameEngine/Include/Common/INI/FieldParse.h`. Replace it with that header;
no shared header or function body changes. The header's existing target evidence
records the same eight-byte exception layout, constructors and destructor.

Validation:
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `./build.sh Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp`:
  9/9 exact, both renumbered funclets verified through parent EH data; all three
  string literals verified.
- `header_adopt_lane.py accept --class INIException` for this source: PASS,
  retired exactly its one header-queue row through the supported path.
- Grouped `link_check.py` with this source, `Damage/DamageModule.cpp` and
  `Source/Common/Rva004B96CCDerived.cpp`: all three LINKS, respectively
  0 -> 322, 6 -> 38 and 159 -> 159 bytes against the 2026-11-05 05:17 census
  at `c95fcfcfcd`. These are predictions, not new census measurements.
- `git diff --check`: clean.

An ordinary single-source preview against that index still reports unresolved
BoneFXDamage destructor and DamageModule loadPostProcess/xfer: its provider
facts predate today's landed repairs. The grouped preview above includes those
current providers and resolves them. This header adoption does not claim the
prior repairs' link gains. The original LINK-113 Snapshot-contract obstacle was
repaired in `a0e226ee89` and its prerequisite commits; this pass verifies that
scope and removes a remaining private exception view.

Remaining work from the earlier handoff: the pool-name getter at 0x004B9757
still has a static placeholder owner in BoneFXDamagePoolKey.cpp. Its identity
and TU recovery are separate cleanup, unchanged by this adoption. No menu,
skirmish, save/load or CRC result is claimed.
