# InvisibilitySpecialPower constructor composition

Inspected revision: `2690b78ff20528d4b544e1891b48c30032ae845f`.
Date: 2026-11-05. Both file scopes claimed before investigation.

## Current result

The previous attempt at this TU (re_attempts, `tu-merge:` key) stopped because
the census-linked sources were absent from its index. With the downloaded
index at `c95fcfcfcd` (2026-11-05 05:17), that is no longer the reported blocker:
the supported merge reaches compilation and rejects its sole clean donor,
`InvisibilitySpecialPowerCtor.cpp`. No source or ledger change survives.

`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/SpecialPower/`
reports no routing proof for either source, and a stale committed TU map. The
planner grants no approval; `tu_skeleton.py` rebuilds placement in memory and
reports 15 approved rows for this destination, three mixed sources, and no
refused sources. The approved constructor is 0x004C23A4, 42 bytes.

## Trials and target facts

- `tu_skeleton.py --merge .../InvisibilitySpecialPower.cpp --dry-run` accepts
  no donor. Compilation reports C2373 on the explicit declaration of
  `??_7SpecialPowerModule@@6BBehaviorModuleInterface@@@` (different type modifiers).
  The donor declares that compiler-owned name as an external const-pointer
  array and manually stores its address at `this + 0x0C`. The seed declares
  SpecialPowerModule with BehaviorModuleInterface as an actual base, so the
  compiler also owns that table spelling. This is a declaration collision,
  not proof that either private hierarchy is a complete retail definition.
- `tu_views.py .../InvisibilitySpecialPower.cpp --dry-run` proposes common
  SpecialPowerModule and InvisibilitySpecialPower declarations. Applying the
  tool reverts both proposals: the constructor lacks definitions of ModuleBase,
  BehaviorModuleInterface and SpecialPowerModuleInterface; the derived-class
  proposal separately lacks `m_moduleData`. Accepted donors remain 0 -> 0.
- The seed models a 0x14-byte prefix with ModuleBase and two interfaces. The
  independently rowed SpecialPowerModule constructor source instead derives
  from BehaviorModule and SpecialPowerModuleInterface and documents additional
  fields through +0x30. A prefix used to access fields is not evidence for the
  complete constructor layout or emitted vtables. The two address-named table
  objects in the donor also remain placeholders.

## Verification and next step

After the tool restored its trials, `git status --short` was empty.
`./build.sh` on the home TU and constructor passes **12/12** rows, including
the six funclet bindings, the string reference, and EH verification. Both
`find_declared_unmatched.py` checks pass before the trials. No alias was
removed, no protected key retired, and no new matching/link/source-file gain
is claimed. No real link or census was run.

Next: reconcile the complete constructor hierarchy and its three retail table
bindings with the rowed SpecialPowerModule constructor; remove the explicit
compiler-vtable declaration only as part of a verified replacement. Check
emitted table slots and all provider/consumer bindings, not only the 42-byte
body, before retrying composition. Simply adding forward declarations cannot
define bases, and blindly copying the seed's prefix is insufficient.
