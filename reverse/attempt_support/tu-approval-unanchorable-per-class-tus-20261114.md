# A per-class TU the class name invented, which no anchor can approve

`next_work.py --claim` served TU approval for
`Code/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState.cpp`
(4 proposed rows, "unanchored 3, brackets 1"), asking for an F/Z/S anchor.
None can exist for this file, and the reason generalises.

## The item

The file does not exist; it is a proposed destination. Five rows of class
`AIAttackMeleeHordeApproachTargetState` sit in
`AIStatesBfmeOnExit.cpp`, four of them routed to the proposed TU:

| rva | `by` | evidence |
| --- | --- | --- |
| `0x00344D60` | `-` (displaced) | `N=…/AIAttackMeleeHordeApproachTargetState.cpp` |
| `0x00348BA4` | `N` | `N=…/AIAttackMeleeHorde….cpp  W=…/AIStates.cpp` |
| `0x0034D1C8` | `-` (displaced) | `N=…/AIAttackMeleeHorde….cpp  W=…/AIStates.cpp` |
| `0x00349013` | `N` | `N=…/AIAttackMeleeHorde….cpp` |
| `0x00349217` | `C` | carried from `0x00349013` |

`N` is `tu_map.py`'s naming hint: `dirname(source) + "/" + class + ".cpp"`
(line 962). The file name is the class name, so the proposal is the class name
restated — it cannot anchor itself.

## Why no anchor is reachable

- **Z (Zero Hour)**: none. `MeleeHorde` appears nowhere under
  `reference/open-bfme-1/inputs/reference/`; ZH's own `AIStates.cpp` has zero
  hits. The class is BFME 2's.
- **F / W (retail path)**: both rows that carry one say
  `C:\Projects\bfme2\Code\GameEngine\Source\GameLogic\AI\AIStates.cpp`
  (`reverse/wb_name_leads.csv:417,2140`, score 1.0, kind `strings`) — a
  different file from the one proposed.
- **S (retail string)**: no `string_xrefs.tsv` entry at any of the addresses.
- **Naming the placeholder does not help.** `?rva00344D60@…` is the only
  placeholder among the five. Its only WorldBuilder lead
  (`wb_name_leads.csv:2455`) is `UNROWED` with an **empty** `wb_name` and kind
  `callgraph`, so it names nothing (`rename.wb_lead_names` is False on an empty
  `wb_name`), and there is no string, export or ZH evidence. Any name would be
  *inferred*, and an inferred name is an `N` hint — the same hint that already
  routes the row. It cannot become the F/Z/S anchor the item asks for.

So the item is unsatisfiable as specified: the rows' own retail path evidence
names `AIStates.cpp`, and the proposed per-class file is an artefact of the
naming hint.

## What is NOT wrong

I measured 249 rows routed `by=N` to a file name their own `W=` contradicts
(102 already `approved`) — `MilesMutexGuard.cpp` against `OpenAudioFile.cpp`,
`AptShapeContainer.cpp` against `W3DAptAux.cpp`,
`AnimConditionInfo.cpp` against `W3DScriptedModelDraw.cpp` — and started
writing it up as W being outranked by a weaker hint. That was wrong, and
`tu_map.py` is right:

- `hard = F or Z or S or L` (line 967) deliberately excludes W.
- W is a **confirmer, never a supplier**: the anchor test is
  `use_w and same(x["W"], key) and not x["Wself"]` (line 996). It can confirm a
  candidate key, and it is refused when the lead self-asserts, because then the
  lead would be confirming the name it produced.
- W is calibrated before it is trusted at all: `w_passes` requires agreement
  with retail's own `__FILE__` on at least `W_MIN=20` rows at `W_GATE=0.99`.
  On current data it agrees on **170 of 170 rows, 100%**.

The 249 are therefore rows where W is never offered as the key, because the
only candidate keys are `hard` or `N`. That is a consequence of the design, not
a violation of it.

## The question left for the consolidation lane

W is calibrated at 100% against retail's own strings over 170 rows, and is
already trusted to confirm a key. It is never allowed to *supply* one. For a
row with no hard anchor and a non-self-asserting W, letting W supply the
candidate key would route these 249 to the file retail's strings name instead
of to a file invented from the class name.

That is a real change in placement policy and the lane's call, not a seat's:
it would move rows (102 of the 249 are already `approved`), and `W` supplying a
key is a weaker claim than `W` confirming one — the calibration measures
agreement where F exists, which is exactly where W is least needed.

Until then, items like this one cannot be closed by naming, and the queue will
keep serving them. Recorded rather than worked around.

## Reproducing

    python3 tools/next_work.py --claim          # draws the item
    python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState.cpp
    # 0 approved rows, 0 donor files

The 249 come from reading `reverse/tu_map.csv` for rows with `by == "N"` whose
`evidence` carries both `N=` and `W=` with different basenames; the 170/170
from the same file, counting rows carrying both `W=` and `F=`.
