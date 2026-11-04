# GarrisonUpgrade consolidation: inherited provider prerequisite

2026-11-04, inspected `b501d83d1c5a`; published census index `5a13f2cd61`
(2026-11-04 02:25). No source or ledger change retained.

Scope: `Code/GameEngine/Source/GameLogic/Object/Upgrade/GarrisonUpgrade.cpp`
and `GarrisonUpgradeCtor.cpp` in that directory. The current map approves the
constructor at RVA `0x004B5839` into the former provisional TU. The evidence
planner reports no original-path proof for these files; the existing TU-map
approval, rather than the planner's unresolved naming hints, authorizes a merge.

Unlike the earlier C2504/C2511 attempts, the current dry-run compiles the pair
but accepts no donor: the inherited canonical declarations would cost the
constructor its census-linked 49 bytes. A separate trial with
`header_adopt_lane.py adopt --class UpgradeModule --header
Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h .../GarrisonUpgradeCtor.cpp
--apply` passes its byte check. Its link preview, however, reports eight missing
names:

```
?GetSnapshotName@UpgradeModule@@MBEPBDXZ
?isSubObjectsUpgrade@UpgradeMux@@UAE_NXZ
?loadPostProcess@UpgradeModule@@MAEXXZ
?muxSlot15@UpgradeModule@@MAEXXZ
?setUpgradeExecuted@UpgradeMux@@MAEX_N@Z
?slot07@UpgradeModule@@UBEEXZ
?upgradeMuxLoadPostProcess@UpgradeMux@@MAEXXZ
?wouldUpgrade@UpgradeMux@@UBE_NABV?$BitFlags@$0IA@@@@Z
```

The seed's two implementation rows still link (252 bytes). These results prove
a declaration/provider prerequisite, not that eight retail bodies are absent;
the existing placeholder owners and native slots must be investigated before
renaming, rowing or suppressing anything. The next useful step is to reconcile
these inherited providers and native derived overrides, then rerun the bounded
adoption and merge. No new pins, hatches or header-debt retirements were made.

The adoption trial was restored. Final `./build.sh` verifies 3/3 rows across
both original files, with string, float and import checks passing.
`link_check.py` then reports both originals LINKS, retaining 301/301 bytes.
`find_declared_unmatched.py` reports all defined functions already matched.
The unused-class cleanup tool also reports no candidates in these two files.
No source-file reduction, link gain or census change is claimed.
