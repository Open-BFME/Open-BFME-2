# ObjectFilter.cpp merge: Player header-queue row of a vanished donor

- 9a5ecae9c4 retired `Player	Code/GameEngine/Source/GameLogic/System/ObjectFilterCollectionXfer.cpp`
  from `reverse/header_queue.tsv` through `header_adopt_lane.py accept --class Player` (PASS).
- c970780750 (`tu_skeleton --merge`) then absorbed that donor into its approved TU
  `Code/GameEngine/Source/GameLogic/System/ObjectFilter.cpp`, which keeps the canonical
  `Include/Common/Player.h` include and the accessor calls in testKindOf/testTemplate.
- Over the outgoing range, `repair_queue.py verify-removed --range` saw a removed row whose
  source no longer exists and the pre-push hook refused the batch
  ("retired debt has no passing outgoing verdict").
- Re-adding a `Player` row under ObjectFilter.cpp would invent debt, so the key carries a
  per-key `Debt-Retired` trailer (same remedy as 0a792735d9 for ControlBar).
- Check after the trailer: `python3 tools/repair_queue.py verify-removed --range origin/master HEAD` exit 0.
