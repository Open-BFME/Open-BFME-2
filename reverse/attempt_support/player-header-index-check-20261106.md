# Player header acceptance and commit-message tree check

The trial started at 6f332c985e. The five units below were reserved together.
Each private Player declaration was replaced by the canonical header, with
direct member reads at the original offsets. The header itself was unchanged.

| Unit | Native member read |
| --- | --- |
| ScoredKillTracker.cpp | m_playerIndex, +0x54 |
| AptPlayerTribute.cpp | m_playerIndex, +0x54, for both players |
| InGameUIPlaceBuildAvailable.cpp | m_color and m_nightColor, +0x280 and +0x284 |
| InGameUIUpdateFormationPreview.cpp | m_color, +0x280 |
| RadiusDecal.cpp | m_color, +0x280, and canonical getPlayerIndex |

The owning `header_adopt_lane.py accept --class Player` printed PASS for all
five units and removed their five queue rows. The scoped build matched 62 of
62 function rows. Pre-commit passed and confirmed all eight EH graphs EXACT.
Both data checks returned zero findings.

Commit-msg then refused each removal with `staged/outgoing tree unavailable
or changed during debt verification` in `repair_queue verify-missing`. The
message covers both an unavailable `git write-tree` result and a tree change.
This trial did not distinguish those cases. All five source edits and queue
removals were reverted. The current header queue still tracks each unit.
