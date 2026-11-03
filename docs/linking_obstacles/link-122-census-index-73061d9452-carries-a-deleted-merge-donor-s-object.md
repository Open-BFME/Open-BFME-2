### LINK-122: census index 73061d9452 carries a deleted merge donor's object, and the bf3dd31211 link queue triage
Status: Open (census hygiene lead; no source change). Updated: 2026-10-27; inspected revision: 9601a55fa8; index 73061d9452 (2026-10-27 14:34 UTC).
Evidence / affected units: `Code/GameEngine/Source/Common/System/INI_parseCrateCreationEntry.cpp` was deleted by the CrateSystem merge 578eb15d7b and is absent from the 73061d9452 tree, yet the published index still lists its object (188 B, linked) and its strong `?parseCrateCreationEntry@CrateTemplate@@SAXPAVINI@@PAX1PBX@Z`. The census itself records `GameLogic/System/CrateSystem.cpp` as linked (259 B; it was `no` at bf3dd31211), so the merge did not regress; but an ordinary preview of CrateSystem.cpp reports a duplicate/wrong-selected parseCrateCreationEntry against that leftover object. The same leftover-donor pattern makes previews of consumers of other post-census merges (boxrobj.cpp f9e70dca51, ww3d.cpp adff7abc28: dx8wrapper.cpp, WW3DShutdownRenderDevice.cpp) report false failures, and `--refresh` does not drop deleted sources' objects.
Completed: link-tier triage at 73061d9452: 11 of 199 served units already LINK in ordinary preview (35,561 B, awaiting census; largest GameLogicInit.cpp 28,191 B, Rva0073F895Fade.cpp 2,027 B, BannerUI.cpp 1,885 B, SidesList_sidesInfo.cpp 1,714 B). Every remaining non-generated failing unit already has a register, target-checklist or re_attempts entry. LANAPILobbyMenuForwarders.cpp's only blocker is `g_Va00E03354`, whose ledger owner is the address-named `?g_Va00A03354@@3HA` (not repaired: address-named global). PoolDeleteDeletingDtors01.cpp trial logged in re_attempts.log (73898a9634).
Remaining / next check: census runners should clear objects of sources absent from the census tree before linking (or link_check should forget them, as it does index `forgotten` entries); until then merge previews stay inconclusive and the CrateSystem duplicate is expected.
Clearance: none. Census confirmation: CrateSystem.cpp linked at 73061d9452.

**2026-10-28 FX SAS consolidation follow-up (`3bfa975ff5` source base):**
The supported merger absorbs 15 approved fragments into the provisional
`WW3D2/FXShaderParameterSourceNamespaceSAS.cpp` TU, preserving all 19 rows
(518 bytes), 23 external COMDAT byte/relocation digests, 16 strong definitions,
one weak alias and 19 external dependencies. The census-linked merge guard and
new-variant check accept it; ordinary preview cannot measure the new TU yet.
The full outgoing batch audit is inconclusive against index `14dc3d2467`
(baseline differs; per-object consumer names missing). Carry the moved scope
to the next normal census; no linked-byte increase or complete outside-consumer
clearance is claimed. Fourteen rejected donors and eight mixed files remain
untouched. [Composition, path audit and prerequisites](../../reverse/attempt_support/fxsas-consolidation-20261028-codex.md).
