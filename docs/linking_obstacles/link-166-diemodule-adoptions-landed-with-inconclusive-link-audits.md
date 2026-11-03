### LINK-166: DieModule adoptions landed with INCONCLUSIVE link audits; census confirms clear (2026-10-31, seat nleigh-codex)

c99acf1f83 adopted the canonical DieModule header in
GameLogic/Object/Behavior/InstantDeathBehaviorOnDie.cpp and
GameLogic/Object/Die/UpgradeDieOnDie.cpp. Their pre-push link_batch_audit
was INCONCLUSIVE (index 840db2d676 older than outgoing base b92e718066; both
sources lacked current receipts), which per the shared-obstacle rule awaits
the next census. Census 3c7a254a38 (2026-10-31 13:43) measures both units
LINKS with no byte loss: InstantDeathBehaviorOnDie LINKED 412 -> 412 and
UpgradeDieOnDie LINKED 118 -> 118. The audit's pending cases are confirmed
clear; no consumer regression. (The KeepObjectDie adoption and the
CreateObjectDie_onDie adoption were covered by other seats' master commits
6262bfcd98bb/787db7c5538c and 6399435ecad; both duplicate commits were
skipped at rebase.)
