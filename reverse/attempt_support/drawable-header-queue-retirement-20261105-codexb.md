# Drawable header queue retirement, 2026-11-05

Inspected source revision: `8db6022cb05656e311ec5e51592d946ebf167dc2`. Worker: `yasinschroeder-codexb`.

This is header-debt cleanup after previously landed source adoption. Every accepted source already included `Code/GameEngine/Include/GameClient/Drawable.h`; no game source, shared header, ledger identity, pin, alias or compiler option changed. For example, `7b65aedf4f` adopted the canonical header in CreateCrateDie and ObjectGetSingleLogicalBonePosition without removing their queued failures. The queued diagnostics are historical, not current regressions.

## Verification

- `python3 tools/check_csv.py`: PASS before work (99,452 function rows; 9,326 symbols; 2,268 data rows).
- `python3 tools/find_declared_unmatched.py SOURCE`: PASS for each of the 13 sources; all defined functions already matched.
- `python3 tools/header_adopt_lane.py accept --class Drawable SOURCE...`: PASS in two bounded cohorts (2 then 11 sources), exit 0 in each. The owning tool removed all 13 rows from `reverse/header_queue.tsv`.
- Acceptance ran the normal scoped byte builder for every source, checked the canonical include and absence of private Drawable bodies, and compared ordinary link previews against census-linked bytes. Every source passed; no queue line was hand-deleted.
- `git diff --check`: PASS.

Acceptance cohorts: CreateCrateDie plus ObjectGetSingleLogicalBonePosition first; the other eleven sources in the second cohort. Reproduce with the accept command above and these paths.

| Source | Matched rows checked | Sum of row extents (bytes) |
| --- | ---: | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Die/CreateCrateDie.cpp` | 9 | 1164 |
| `Code/GameEngine/Source/GameLogic/Object/GenericObjectCreationNuggetDoStuffToObj.cpp` | 10 | 3172 |
| `Code/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelper.cpp` | 6 | 667 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectDefectionComplete.cpp` | 6 | 572 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectDoXfer.cpp` | 11 | 3498 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectGetSingleLogicalBonePosition.cpp` | 2 | 281 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectReactToTransformChange.cpp` | 2 | 389 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectRva00297612.cpp` | 2 | 191 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectScriptStatus.cpp` | 15 | 2202 |
| `Code/GameEngine/Source/GameLogic/Object/Rva004ADB1BLerp.cpp` | 2 | 392 |
| `Code/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdateFeedbackLaser.cpp` | 3 | 242 |
| `Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp` | 17 | 1266 |
| `Code/GameEngine/Source/GameLogic/Object/Update/MonsterDockUpdate.cpp` | 7 | 636 |

Total checked: 92 matched rows, 14672 bytes of ledger extents. These are verification scope counts, not link gains.

Local ordinary-preview index provenance:
```json
{
  "date": "2026-11-04 22:40",
  "commit": "3a95b274a2",
  "census_date": "2026-11-04 20:47",
  "census_commit": "f12552d0a7"
}
```

No census, real-link, ownership or smoke runner was invoked. This cleanup retires 13 header-queue entries and makes no new headline linking claim. Other queued Drawable consumers retain their existing prerequisites.
