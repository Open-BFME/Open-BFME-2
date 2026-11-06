# Player header adoption: guard, castle and portal consumers

Inspected base: `5099c4bef5`. Adopted the existing canonical
`Code/GameEngine/Include/Common/Player.h` in eleven consumers, removing their
private Player declarations. No shared header, ledger, alias or compiler flag
was edited. Field substitutions preserve the existing accesses: player name
at +0x4C, player index at +0x54, team list at +0x32C, hunt flag at +0x33D
and tunnel tracker at +0x2E8.

Sources, relative to `Code/GameEngine/Source/GameLogic/`:

- `AI/AIGuardInnerTargetRva00369FDF.cpp`
- `AI/AIHuntStateUpdate.cpp`
- `AI/AIStates.cpp`
- `AI/AIStatesBfmeOnExit.cpp`
- `AI/AITNGuard.cpp`
- `AI/AITNGuardReturnStateOnEnter.cpp`
- `AI/AITNGuardStates.cpp`
- `Object/Behavior/CastleBehaviorCapturePermission.cpp`
- `Object/Behavior/CastleBehaviorInitiatePack.cpp`
- `Object/Behavior/MineshaftPortalBehaviour.cpp`
- `Object/Behavior/MineshaftPortalBehaviourLinkStep.cpp`

## Verification

- `find_declared_unmatched.py` passed before and after the edits for every
  adopted source.
- `./build.sh` over the eleven sources passed all 118 functions, two data rows,
  25 funclet pins, string and float checks.
- One `header_adopt_lane.py accept --class Player` invocation over the complete
  adopted cohort passed all eleven sources and retired their eleven queue rows.
- A combined `link_check.py` invocation retained all eleven units and
  19,060 -> 19,060 authored bytes against the 2026-11-05 15:52 census at
  `112a456a2c`. AIStates and the portal link-step unit retain unreferenced
  COMDAT diagnostics. This is an ordinary prediction, not an image or runtime
  result.

## Definition and alias audit

Compared the pre-edit cached objects with the final verified objects using
`link_census.object_symbols`, then searched all 24,966 compiled objects in
`build/match/` for definitions, undefined symbols, `/INCLUDE`, weak externals
and `/alternatename` uses of every removed definition. No alias was removed.

| Removed inline Player symbol | Remaining providers | External references or aliases |
| --- | ---: | ---: |
| `?getUnitsShouldHunt@Player@@QBE_NXZ` | 0 | 0 |
| `?getPlayerTeams@Player@@QBEPAUPlayerTeamNode@@XZ` | 4 | 0 |
| `?getTunnelSystem@Player@@QAEPAVTunnelTracker@@XZ` | 0 | 0 |

The four remaining team-getter providers are ScriptConditionsRva003E8E23,
ScriptConditions_evaluateSkirmishSpecialPowerIsReady,
ScriptConditionsPlayerUnitCounts and ScriptActions_doPlayerForceEmotion.
The tunnel getter disappears from all three adopted AITNGuard objects together;
no other object imports it.

MineshaftPortalBehaviour's final object additionally imports
`?xfer@UpdateModule@@UAEXPAVXfer@@@Z` relative to its pre-edit cached object.
The cached UpdateModule object supplies an existing alias to its `QAE` body;
the current ledger and source name the real `UAE` provider at 0x0044DF9F.
The combined link prediction remains clean.

Local raw receipts: `build/player-header-codexb-20261105/` contains
`manual-build.log`, `final-declarations.log`, `accept.log`,
`final-link-preview.log` and `provider-audit.json`. Scope is these eleven
accepted header rows; the AITNGuard merge's other receiver prerequisites remain.

## Recovery verification, 2026-11-08

Reconciled preserved commit `9786564f78` onto prepared upstream `2d62ba84f2`.
No stash or resync stash is named in `.git/runner-prepare.json`; the original
commit remains at `refs/runner/preparation/1794143909904971383`.
Upstream commits `703c35bee5` and `727316eb2e` already adopt the Player header
in AIGuardInnerTargetRva00369FDF, AIHuntStateUpdate and AIStatesBfmeOnExit;
those changes and retired queue rows were retained without replaying them.
The AITNGuard source conflict preserves upstream's other receiver changes and
uses the canonical Player header and its tunnel-system field. The queue was
restored from upstream, then one current cohort acceptance retired the eight
remaining Player rows; unrelated upstream retirements remain intact.

Current checks: `check_csv.py` passes; declarations pass for all eight sources;
`./build.sh` verifies 80/80 functions, two data rows and 13 funclet pins;
`header_adopt_lane.py accept --class Player` passes all eight consumers,
including its combined link prediction. Local receipts are under
`build/recovery-player-20261108/`.

An all-object symbol audit searched 24,966 compiled objects, including undefined
symbols, forced includes, weak externals and alternatename directives. The
removed Player tunnel getter has no references or aliases and no remaining
provider; the team getter has four providers and no references or aliases.
No alias is removed by this patch. The comparison uses the retained pre-adoption
objects from 2026-11-05, so other differences caused by intervening upstream
receiver/header work are not attributed to this adoption. All removed symbols
in that wider comparison either have another provider or have no references
or aliases. No image or runtime improvement is claimed.
