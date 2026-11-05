# `Upgrade.cpp` consolidation screen (2026-11-05)

Allocated TU: `Code/GameEngine/Source/Common/System/Upgrade.cpp` (shard 0/5).
The current name-lane snapshot was regenerated for
`Code/GameEngine/Source/Common/System/` and passed
`name_lane.py consolidate --check build/consolidation`. Its evidence catalogues
original retail paths but reports no retail-routed rows for this subsystem.
The TU plan contains 85 approved rows, 16 donor files, five mixed files, and no
refused files.

`python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/System/Upgrade.cpp
--dry-run` exited 2 with `accepted: []` and `blocked: no verified merge of two
or more donors`. The accepted unchanged-donor requirement is therefore unmet.
Rejected whole donors fall into these groups:

- Duplicate declarations/bodies and incompatible combined declarations in
  `UpgradeCtor.cpp`, `UpgradeCenterFindUpgradeByKey.cpp`, and
  `UpgradeTemplateResolveSubUpgradeNames.cpp`.
- Existing header/shim view conflicts (`SubsystemInterface`, `MemoryPoolObject`,
  `Overridable`, `INI`, `FieldParse`, and `NameKeyGenerator`) in the
  `Upgrade*` and `UpgradeCenter*` donors.
- Missing or incompatible class/member views in
  `UpgradeTemplate_cacheButtonImage.cpp` and other `UpgradeTemplate` donors.
- Byte mismatches in `Rva0026F684Dtor.cpp` and `Rva0026F684Assign.cpp`.

The tool recommends canonical view adoption for `Player`, `UpgradeCenter`,
`UpgradeTemplate`, `ImageCollection`, and `SubsystemInterface`, plus a separate
`tu_views.py --dry-run` reconciliation for `OpaqueRefPtr`, `Rva0026F684`, and
`Rva002A9BF2`. These source/header and byte repairs are prerequisites outside
the mechanical consolidation seat. The report's `link_guard` lists the TU and
all donor objects as census-linked; no donor passed far enough to establish a
merge or require a link-loss repair. No source, ledger, claim, or merge-plan
changes were made by this screen.
