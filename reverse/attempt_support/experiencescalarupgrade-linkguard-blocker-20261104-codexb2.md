# ExperienceScalarUpgrade constructor merge blocker (2026-11-04)

Allocated `Code/GameEngine/Source/GameLogic/Object/Upgrade/ExperienceScalarUpgrade.cpp`;
the unchanged dry run accepted no donors. Its constructor donor triggers the
same LinkGuard provider-closure failure recorded in LINK-246:
`UpgradeModule::GetSnapshotName`, `UpgradeMux::isSubObjectsUpgrade`, and
`UpgradeModule::loadPostProcess` become unresolved. Both current census units
link separately. No source edits or claims were made.
