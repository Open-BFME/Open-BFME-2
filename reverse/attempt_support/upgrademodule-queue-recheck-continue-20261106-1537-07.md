# Retire 1 verified UpgradeModule header queue entries

Base: `0d7183faa53296c91d100f0e2f922f35c9038c17`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 4 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Upgrade/BuildableHeroListUpgrade.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h` | 4 |
