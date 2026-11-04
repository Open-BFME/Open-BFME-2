# TeamPrototype iterator consumers: canonical header adoption

Inspected base: `2974791b3e`; date: 2026-11-04.
Claim: `class:TeamPrototype` (yasinschroeder-codex).

Four units now include `Code/GameEngine/Include/Common/Team.h` instead of
redeclaring TeamPrototype. Three retain their existing inline
`iterate_TeamInstanceList` bodies as out-of-class definitions; the factory
uses the existing `getFirstItemIn_TeamInstanceList` accessor. The canonical
header establishes ID +0x0C and list head +0x334; no header growth is needed.
The iterator parameter names, ABI and Team declarations are retained.

| Source under Common/RTS | Exact rows | Ordinary preview, authored bytes |
| --- | ---: | ---: |
| TeamPrototypeFindAndCountInstances.cpp | 2/2 | LINKS, 84 -> 84 |
| TeamPrototypeMoveTeamTo.cpp | 1/1 | LINKS, 90 -> 90 |
| TeamPrototypeTeamIterators.cpp | 16/16 | LINKS, 954 -> 954 |
| TeamFactoryRecomputeIDs.cpp | 1/1 | LINKS, 127 -> 127 |

Verification:

- `find_declared_unmatched.py` passes before and after all four edits.
- `./build.sh` passes 20/20 matched rows, string/float/import checks and
  scoped source-claim checks (2-row control and edited build; remaining
  three sources verified together, 18/18).
- `header_adopt_lane.py accept --class TeamPrototype` passes all four and
  retires exactly their four entries from `reverse/header_queue.tsv`.
- A combined ordinary `link_check.py` preview against census `a62ac1c10b`
  (2026-11-04 07:28) reports 4/4 LINKS, 1,255 -> 1,255 authored bytes.
- Existing LINK-154 frame-pointer correction remains intact. No new link
  obstacle, changed prerequisite, or census-linked gain is claimed.

The other TeamPrototype queue entries retain their separate layout/member
and code-generation prerequisites. TeamPrototypeTeamIterators still has
Team-header debt, and TeamFactoryRecomputeIDs still has TeamFactory-header
debt; neither row is retired by this change.
