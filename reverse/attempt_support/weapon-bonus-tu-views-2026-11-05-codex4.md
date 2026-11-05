# Weapon bonus views: consolidation prerequisite

Inspected `6e1212effe` on 2026-11-05. Scope:
`Code/GameEngine/Source/GameLogic/Object/Weapon.cpp` and its approved donors.
The consolidation picker claimed the 66 candidate files. The supported naming
planner ran under `build/consolidation/weapon-codex4`; the merge tool rebuilt its
stale TU map in memory. No TU map, ledger source path or debt key changed.

## Completed

`tu_views.py Weapon.cpp --class WeaponBonusSet --no-merge-check` applied one
identical declaration to `WeaponPrivateFireWeapon.cpp`, `WeaponBonusParse.cpp`
and `Rva002CA88BParse.cpp`: append/parse methods and 22 six-float bonus records
(size 0x210). The allocation parser now supplies the complete six-float
`WeaponBonus` declaration needed by this array. The retail allocation at
0x002CA88B and parser at 0x002C971E independently establish this record shape.

The two incomplete `WeaponBonus::Field` enums in the fire and clip-reload
sources now include the existing `PRE_ATTACK = 4` spelling. The sibling
`WeaponTemplatePreAttackDelay.cpp` documents the native field-name table at
VA 0x00DBC71C and uses this index. Existing enumerator values are unchanged.
No constructor, function body, pin, alias or compiler flag changed.

## Verification

- Before editing, `find_declared_unmatched.py` passed all 66 candidate files.
  It passed the four changed files again afterward. The bonus parser's existing
  absent-from-retail anchor remains unchanged.
- The view tool verified the three rewritten files' layouts, bytes and
  unmatched-body checks and reported `WeaponBonusSet: applied (3 files)`.
- `./build.sh` on all four changed files: **14/14 matched**; string, float and
  named-import checks passed. The allocation parser's compiler-renumbered EH
  label was verified against its parent's EH data at 0x00776FCD.
- `link_check.py` on these four files used current dependency-cache objects
  against census 2026-11-05 05:17 at `c95fcfcfcd`:

  | Source basename | Census bytes | Current preview bytes |
  | --- | ---: | ---: |
  | Rva002CA88BParse.cpp | 103 | 103 |
  | WeaponBonusParse.cpp | 90 | 90 |
  | WeaponPrivateFireWeapon.cpp | 3,452 | 3,452 |
  | WeaponTemplateClipReloadTime.cpp | 99 | 99 |

  All four preview LINKS; total 3,744 -> 3,744. This is preservation evidence,
  not a new census or a real-link measurement.
- `git diff --check` passed. No source removal, register retirement or hatch
  removal is part of this change; the link-wide load-ammo alias is untouched.

## Remaining boundary

The full `tu_skeleton.py --merge Weapon.cpp --dry-run` search was interrupted
after more than 25 minutes while still compiling combinations. It produced no
final merge verdict and applied no move; do not interpret it as proof that no
merge is possible. This exceeds the earlier recorded 900-second interrupted
search, so another broad retry should follow a concrete prerequisite change.

`tu_views.py --class WeaponBonus --dry-run` now gets past the enum conflict.
It next reports different inline constructor bodies: the fire source uses
literal six and `m_field`, the pre-attack source uses its six-valued
`FIELD_COUNT`, and the ammo loader uses `m_multiplier`. A temporary literal-six
change in the pre-attack source exposed the ammo-loader conflict and was
reverted. The retained changes do not claim shared `WeaponBonus` views.

The broader view plan also refuses `Object` (a raw field under inherited
storage) and `Rva002CD4A6` (a field under the vfptr). The seed still includes
the older `weapon_outofline` header, whose bonus record has five fields.
Reconcile these declarations against current layouts and adopt canonical
headers through their lane before another large merge search. No source-file
reduction or TU-approval increase is claimed here.
