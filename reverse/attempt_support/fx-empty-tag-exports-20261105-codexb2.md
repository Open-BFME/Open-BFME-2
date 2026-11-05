# FX empty-tag export providers

Inspected baseline: `82b9731dd41341c620734f2f830ad375a4c31dcb`.
Source: `Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`.
Claim: source scope and `0x001FD28E`.

## Target facts

`reverse/exports.csv` names eight assignments at RVA `0x001FD28E` that
have no provider in index `f44cbcf5b0` (2026-11-05 15:19 UTC):

| Export | Generic ModuleTag identity |
| --- | --- |
| 605 | DefaultModuleKey/Name<1>; DefaultModule<1> |
| 607 | DefaultModuleKey/Name<2>; DefaultModule<2> |
| 608 | DefaultModuleKey/Name<3>; DefaultModule<3> |
| 611 | ORTHO_EMISSION_VELOCITY; DefaultParticleModule<4> |
| 618 | POINT_EMISSION_VOLUME; DefaultParticleModule<5> |
| 627 | DefaultModuleKey/Name<6>; DefaultModule<6> |
| 628 | DefaultModuleKey/Name<7>; DefaultModule<7> |
| 631 | DefaultModuleKey/Name<0>; DefaultModule<0> |

Each complete retail body is `8B C1 C2 04 00` (return this; RET 4),
with no relocations. The existing matched `ModuleTemplate::operator=` in
this source is a complete byte-and-relocation twin at the same address.
These are exported folded identities, not eight newly recovered ranges.
No donor evidence is used.

## Repair

Give the existing generic ModuleTag view its return-this assignment and
explicitly instantiate the eight exported identities. DefaultModuleKey/Name
static members and DefaultModule types are declarations only: this repair
adds no dynamic registration objects. Add verified gen-alias rows through
`add_match.py --icf-owner`, identifying the existing ModuleTemplate assignment
and this source as fold proof. No pins, aliases or hatch admissions are added.

## Verification

- `./build.sh Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`:
  391/391 function checks and the data row pass; literal/import checks pass.
- `link_check.py --prepare-current` succeeds; the final restored object also
  passes `compile_is_current(..., strict=True)`.
- `link_check.py Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`:
  LINKS, 5,650 -> 5,650 authored bytes, index `f44cbcf5b0`.
- Clean HEAD control: temporarily restore only our source/ledger changes,
  run `./build.sh` (383/383), retain the control object under build/, restore
  the patch and rebuild (391/391). Comparing the two objects finds exactly
  the eight new external definitions and no removed external definitions.
  All 531 pre-existing external code definitions preserve their bytes and
  relocation lists. CRT sections remain one 308-byte section with 77
  relocations: no new runtime initializer registrations.
- Each new symbol has the exact exported decoration, complete five-byte
  body above and no relocation. All eight previously absent exported
  definitions are now emitted by this unit.
- `find_declared_unmatched.py`: all defined functions already matched.
  `check_csv.py` and `git diff --check` pass.

The published index predates other Snapshot changes already on HEAD; its
provider delta alone is not a control for this repair. The clean HEAD object
comparison above separates those existing differences from this change.
No full real link or census was run, and no headline byte gain is claimed.
The next automated real link must confirm these eight exports disappear
from its errors; the rest of FXParticleSystem's export/link work remains.
