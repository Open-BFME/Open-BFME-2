# AutoHealBehavior canonical-base seed prerequisite

Scope: `Code/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior.cpp`.
Inspected base: `7f1b7d53ab`; census preview: `c95fcfcfcd` (2026-11-05).

The supported merge initially accepted no donor: PoolKey introduced the canonical
SubsystemInterface beside the seed's imported legacy definition. Other donors
also collided with Module/ObjectModule/UpdateModule, GameLogic and math views.

The seed now includes the canonical UpdateModule and UpgradeMux headers directly.
Its TU-local AutoHealBehavior declaration preserves the native base placement:
UpdateModule +0, UpgradeMux +0x20, DamageModuleInterface +0x28, state +0x2c.
Only the existing six rowed bodies are defined. The static PoolKey method is
also declared so its existing donor can be composed without a second class view.
No new row, pin, alias, emitted lifetime body or debt retirement is introduced.
The compiler-flag line is unchanged.

Retail byte verification establishes the module-data UpgradeMuxData subobject
at +8 in performUpgradeFX and the stopHealing sentinel 0x3fffffff. These are
BFME 2 target facts; the donor method spelling does not establish an original
BFME 2 source path or a complete module-data layout.

Checks:

- Frozen-file check passes before and after; `./build.sh` verifies 6/6 rows.
- Ordinary link preview preserves LINKS and 167/167 authored bytes. This is a
  preview, not a new census result or a real-link milestone.
- Compared with the published census object's COMDAT digests, 8 survive and all
  are identical; 541 disappear, with no additions. Of the removed definitions,
  540 retain another provider in that census. The sole unique removed getter,
  getAutoHealBehaviorModuleData, has no other census consumer. No weak aliases
  are emitted or removed. The broader outgoing batch audit remains necessary.
- Narrow searches find no seed keys in the header/ms-header queues, data/identity
  debt registers, hatch baseline or flag overrides.
- A fresh supported dry-run accepts seed + PoolKey: 9 code rows, two data-ledger
  keys carried, one source file removable. Other donors remain rejected on
  member/layout/vftable or math-header conflicts and retain their owners.

This commit is the independently verified declaration prerequisite. The source
move and its register transfer must be applied by tu_skeleton in a separate
commit, with its own post-composition checks and tooling audit.
