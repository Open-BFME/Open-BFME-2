# AudioLoopUpgrade update helper: canonical UpdateModule adoption

Base: `2974791b3e`. Scope:
`Code/GameEngine/Source/GameLogic/Object/Upgrade/AudioLoopUpgradeUpdate.cpp`.

Replaced the private, one-method `UpdateModule` declaration with the canonical
header. A local derived access view exposes the inherited protected
`setWakeFrame` declaration without changing the canonical class or the existing
adjusted-this call. The view is implementation scaffolding, not a recovered
retail class name or layout. No source path or ledger identity moved.

Verification:

- `./build.sh` passed both before and after: 2/2 matched (81 bytes).
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept --class UpdateModule` passed and retired the
  source's single queue row through the owning tool.
- `link_check.py` before and after: LINKS, 81 -> 81 census-linked bytes against
  the 2026-11-04 07:28 index at `a62ac1c10b`. This is a scoped prediction, not a
  new real-link or census measurement.

Other AudioLoopUpgrade declaration and consolidation prerequisites remain as
recorded in `audioloop-consolidation-prerequisites-20261104.md`.
