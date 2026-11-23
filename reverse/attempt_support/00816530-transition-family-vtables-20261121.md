# 0x816530..0x8166BC transition vftables: bridge retirement handoff

Every retail transition table here has 8 slots: 0 deleting dtor, 1 init,
2 update, 3 reverse, 4 draw, 5 the empty 0x000B3FD0, 6 a finish body,
7 the zero-returning 0x000D43D0. Slots 3/5/6/7 are shared, ICF-folded bodies
(0x0035D1BD reverse, 0x0035D1E7 `update(+0x14)`, 0x0035E2DE,
0x0035F63B `if (!finished) update(+0x14)`, ...).

Landed (inline bodies + `add_match.py --icf-owner` rows, hatches removed):
- 0x0081669C TextOnFrameTransition (f4907a6198)
- 0x0081663C FullFadeTransition (c0a0ad26ba, `??1` alternatename gone)
- 0x00816574 MainMenuMediumScaleUpTransition (de6b57be1d, 3 alternatenames gone)

Still blocked: each table's installing rows (ctor/dtor/`??_G`) are rowed under
an address placeholder whose view declares only a destructor, while slots
1/2/4 are rowed under the real class:

| table | placeholder | real class (slots 1/2/4 rows) |
|---|---|---|
| 0x816530 | Rva0035D74A (novtable ctor here, dtor FamilyTailDtors1DBAC3.cpp) | ControlBarArrowTransition |
| 0x816554 | Rva0035DA01 | MainMenuSmallScaleDownTransition |
| 0x816594 | Rva0035E00F | MainMenuScaleUpTransition |
| 0x8165D0 | Rva0035E2E6 | ScoreScaleUpTransition |
| 0x8165F0 | Rva0035E60B | ButtonFlashTransition |
| 0x81661C | Rva0035EE66 | FlashTransition (slot 1 `rva0035EDA1@Rva0035EE66`) |
| 0x81665C | Rva0035F4A6 | FadeTransition (slot 1 shared with 0x81661C) |
| 0x8166BC | Rva0035FD0A | TextTypeTransition (slot 3 `copy@Rva005A0430`) |

Routes tried (dry runs, 2026-11-21):
- `rename.py class --fold Rva0035D74A --into ControlBarArrowTransition` (and
  DA01 -> MainMenuSmallScaleDownTransition): refused, the table is named only
  `??_7<placeholder>@@6B@`, "nothing ties <real> to it", and slot 3 holds the
  shared 0x0035D1BD ("an inherited or folded slot this route does not judge").
- `--fold` the other way is refused: a readable name never folds.
- `rename.py class --name Rva0035D74A --new ControlBarArrowTransition
  --merge-existing`: refused, the placeholder is not in canonical_classes.csv.
- Giving the placeholder views slots 1/2/4 needs a second name at an address
  with a real row (no ICF twin: the bodies are 100-250 B, defined once).

Needed: a fold route that accepts the real class proven by its rowed slots
1/2/4 in the placeholder's own table (tooling seat, `Verifier-Change`), or
registering the placeholders so `--merge-existing` applies. After the fold,
add the 5/6/7 inline bodies as done for the three landed tables and drop
FamilyTailDtors1DBAC3.cpp's remaining Rva0035E00F alternatenames.

## 2026-11-23 follow-up

The published queue at `3ca788d138` still lists `_vtbl_00C16574` even though
the decorated medium-scale table already has eight correct slots. Referencing
the compiler's own vtable symbol directly in the 80-byte constructor removes
the old external reference while retaining the retail store order. The new
32-byte table matches the existing provider's bytes and eight relocations.
The next published link can now check retirement of the raw alias.

The same source adopted the shared `Image`, `GameWindow`, and
`WinInstanceData` declarations. Both queued adoptions passed and retired.
The draw path retains the retail loads at `WinInstanceData +0x17C` and
`+0x180`. The combined transition cohort matched all 144 function rows.
The obstacle record covers the remaining class-fold blockers.
[Current obstacle and native evidence](../../docs/linking_obstacles/link-698-window-transition-vtable-identity.md)
