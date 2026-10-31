# WeaponSet TU reconciliation (2026-11-01)

Base inspected: e78b61f1b2d2. Seat: halilkkaya-codex. No merge applied.

Target evidence and change:
- The 60-byte constructor at 0x002C72D5 installs WeaponSet's table at +0.
  The destructor at 0x002C7311 and deleting destructor at 0x002C75B5 already
  use canonical Snapshot. The constructor now uses that base and its automatic
  vfptr store, instead of modelling the same address as an ordinary field.
- Seven donor files now have the same 0x40-byte WeaponSet view, produced and
  layout/byte-checked by tu_views. Fields retain the constructor's proven
  +4/+8/+20/+24/+28/+2C/+30/+34/+35/+36/+3C offsets. The destructor casts
  the weapon pointer to its existing slot-0 call view; no Weapon class is added.
- Native parsers index six 0x1C-byte masks at +0x44/+0xEC and six 0x4C-byte
  masks at +0x194. Three WeaponTemplateSet views now use the attack donor's
  BitFlags<218>/ModelConditionFlags storage and one declaration spelling.
  Existing address-owned parser call views remain explicit casts at call sites.
- Local field spellings follow the existing attack donor to avoid the tool's
  rejected token-wide rename of WeaponTemplate::m_anti or Weapon::m_template.
  Two owner lookups explicitly cast the common integer field to ObjectID.

Validation:
- ./build.sh over all eight touched sources: 23/23 code rows and one data row
  exact; literal, float and import checks pass. find_declared_unmatched clean.
- link_check over the seed and all 16 whole-file donors: 16/17 LINKS,
  6,041 -> 6,041 authored bytes. The unchanged seed remains nonlinking.
  --new-variants over the same 17-file cohort passes with no findings.
- tu_views applied both shared classes and verified their compiler layouts.
  Failed intermediate trials were restored before dependencies/casts were fixed.
- tu_skeleton --merge --dry-run before and after: zero accepted donors.
  Logs: build/weaponset-merge-before.txt and build/weaponset-merge-after.txt.

Remaining prerequisites:
- The seed includes the old Zero Hour WeaponSet declaration (three slots,
  old signatures), outside tu_views' private-block scope. It retains an old
  destructor body that collides with the native donor, old table-name
  declarations, and incompatible included canonical Weapon/Coord3D/GameLogic
  surfaces. Its inline clients reference unresolved Object attack-selection,
  Weapon attack-range and INI static scanIndexList signatures.
- The merged flag environment additionally exposes AsciiString providers and
  include redefinitions. StringBase/AsciiString and Weapon.cpp are excluded
  from this seat's assignment; no trial changes them or thing.h.
- Reconcile the seed's own declaration/include surface and retire the obsolete
  destructor through its owning debt workflow before retrying a merge. Preserve
  existing BitFlags/StealthUpdate repairs and all linked donors.
- The supported planner was run and its original-path alternatives/blockers
  reviewed. tu_skeleton rebuilds the stale committed TU map in memory; no map
  is regenerated or staged. No paths moved, hatches added, pins changed or
  census-linked gain claimed.
- docs/linking_obstacles.md is actively held by hdr-player-2; this seat leaves
  that claimed file unchanged. This handoff supplies the current bounded result
  and the exact remaining prerequisite for the shared-register maintainer.

Setup control: the initial full build verified 99,264/99,264 code rows, but its
final source-presence scan raced this seat's dry-run temporary .cpp. The full
check will be repeated without any dry-run active before the session ends.
