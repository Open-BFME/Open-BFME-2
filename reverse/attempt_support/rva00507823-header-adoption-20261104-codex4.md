# Rva00507823 header adoption

Inspected revision: `fdd1fea7722f67fdfb6dcdb7f5187028a977af85` (2026-11-04).
Scope: the nine Rva00507823 units served by `next_work.py --claim`.

## Landed subset

Replace the private base declaration with the existing canonical
`Code/GameEngine/Include/GameLogic/Module/Rva00507823.h` in three units.
The header already supplies the 0x128-byte base, so derived padding must
start at +0x128 rather than +4 (or +0 for the formerly empty base).
No canonical header, method identity, pin or alias changes are needed.

| Unit | Layout correction | Current-object link preview |
| --- | --- | --- |
| Common/VslotSmallBodiesAD.cpp | Remove both redundant 0x128-byte derived padding arrays | LINKS, 308 -> 308 bytes |
| GameLogic/Object/Made002CC5E1Rva005084FC.cpp | Remaining padding covers +0x128..+0x178 | LINKS, 532 -> 532 bytes |
| GameLogic/Object/Made002CCA37Dot.cpp | Remaining padding covers +0x128..+0x1A4 | LINKS, 141 -> 141 bytes |

Paths in the table are relative to `Code/GameEngine/Source/`.
Target offsets and base extent come from the canonical header's existing
retail constructor/access evidence, not a donor layout or naming inference.

Verification:

- `find_declared_unmatched.py` before and after: all defined functions matched.
- `./build.sh` on the three units: 13/13 functions matched; string, float and
  import reference checks passed (four compiler float literals verified).
- `header_adopt_lane.py accept --class Rva00507823` on these units: three PASS
  verdicts; the tool retired exactly their three header queue rows.
- `link_check.py` on the same fresh objects: all three link cleanly,
  981 -> 981 bytes, against the published 2026-11-04 22:40 index at
  `3a95b274a2`. This is a preview, not a new census or real-link measurement.

## Remaining six units

The initial ordinary `header_adopt_lane.py adopt --apply` trial on all nine
units passed none and restored every failed source. The following six remain
unchanged with their header queue debt intact:

- `Common/Rva00507823Ctor.cpp`: field mapping refuses `m_bits04`
  (`Rva001EAE6FHelper`) against canonical `m_mask04` (word array). Its vector
  and filter members also require construction and EH semantics that raw
  canonical storage does not supply. Next: reconcile actual member types and
  initialization/destruction in the canonical contract before another trial.
- `Common/Rva00507823Dtor.cpp`: mapping refuses `m_vec108` (`RvaVecAscii`)
  against canonical `m_storage108` (byte array). Same member-lifetime prerequisite.
- `GameLogic/Object/Made002CC5E1Rva00507991.cpp`: byte verification fails
  `?rva00507991@DamageNugget@@UAEXPAX0@Z`. Its private derived vslots follow a
  destructor-only base; appending them after the canonical base slots changes
  dispatch offsets. Next: reconcile inherited slot declarations and provider
  identities with retail tables, preserving ledger method bindings.
- `GameLogic/Object/Made002CC711.cpp`: C3861, `accepts` not found.
- `GameLogic/Object/Made002CCAA1.cpp`: C3861, `accepts` not found.
- `GameLogic/Object/WeaponEffects/Made002CC64B.cpp`: C3861, `accepts` not found.

For the last three units, the private base names slot 1 `accepts`; the canonical
base calls it `vslot01` with a byte result and const descriptor pointer. Next:
reconcile dispatch declarations and derived vtable providers before acceptance;
do not add an alias or assume a renamed call alone preserves emitted vtables.
The six failures are bounded adoption trials, not new unmatched retail bodies.
