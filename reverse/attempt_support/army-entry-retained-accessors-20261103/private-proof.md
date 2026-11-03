# ArmySummaryEntry retained accessor boundaries: two private proofs

2026-11-03. Exactly **one candidate compile per source**, two sanctioned
tu_skeleton.Verifier compiles total. No alternate body/profile was tried.
The private header was restored byte-for-byte in `finally`; both tracked source
files were never edited, and final tracked Git status is empty (exit 0).
No main source/header, ledger, pin, claim, commit, push or network operation.

The temporary canonical header additions are ordinary in-class inline APIs:

```cpp
bool hasUpgrade() const { return m_bc != 0; }
int getMoveTarget() const { return m_b8; }
```

These are existing private APIs, not proposed new native method identities.
No force-inline/import/optimization hatch was added. Actual original source was
read from private Git HEAD and class replacement used header_adopt_lane.swap
with the **include PATH only**. The qualified field mappings were preserved;
local variables named target and unrelated declarations were not renamed.

| Source | Existing rows | Result | Complete provider result versus saved MAIN control |
|---|---:|---|---|
| Code/GameEngine/Source/GameClient/ArmyUnitSwapperSelection.cpp | 16 | 16/16, zero errors/missing; previously lost CanCancelAnyUpgrades 5F59F6 restored | All 21 definitions, complete bytes/relocations and properties unchanged; no added/removed provider. |
| Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp | 174 | 174/174, zero errors/missing; previously lost GetArmoryToUpgradeTroop 2B6DC4 restored; **36 EH graphs EXACT** | All 427 provider names/properties retained, no additions/removals. One spelling-only local-label difference is proved below. |

Relative to the earlier manual candidates, candidate 0 restores the single
original `->hasUpgrade()` call in CanCancelAnyUpgrades; its two direct fieldBC
uses stay direct. Candidate 1 restores all four original `->getMoveTarget()`
calls, leaving actual field stores and assignments mapped to m_b8. Full diffs
against the prior candidates are archived in proof.json. The immutable main
control-facts inventory contains all 18 original cohort controls; no control was
recompiled in this task.

For LivingWorldLogic::logicMessageDispatcher, all **3170 raw bytes** remain
identical. Exactly **29 DIR32 relocation labels** are renumbered. Each old/new
target was inspected in its actual COFF object and proved to be in the same
parent function section at the identical relative offset. These include the
switch-table pointer and all affected case entries. No case target moved.
The parent row still byte-verifies and its EH graph is EXACT. This is a scoped
same-target binding proof, not a blanket local-label normalization.

For both sources, weak routes, alternates, defined/undefined names, directive
roots and .drectve contents are unchanged. No new provider's native address is
inferred; this proof does not assign any previously unknown native placement.

`proof.json` contains both complete provider/property inventories, symbol facts,
native row results, all EH results, previous failing rows' complete bytes and
relocations, label-target bindings, original/trial/restored header hashes and
clean-status evidence. Candidate sources and objects are `candidate-0.*` and
`candidate-1.*`; `trial-header.h` is reviewable proposed header text only. Root
must perform owning adoption and broader shared-header validation before any
publication; neither is done by this bounded proof.
