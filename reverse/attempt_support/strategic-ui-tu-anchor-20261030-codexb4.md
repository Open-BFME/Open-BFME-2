# Strategic UI TU-evidence boundary

Inspected base: `5d9b06e825`. The default picker claimed the 42-row EH run
`0x007A13A7..0x007A156B` and its sixteen source files. No game source,
name, row ownership or TU-map assignment changed in this investigation.

Target facts:

- `tu_evidence.py --source Code/GameEngine/Source/Common/Rva005CC287Destructor.cpp`
  produces only its CSV header: no layout signal reaches this source's rows.
- `tu_map.py --dir` for that source, rebuilt in memory, reports three code
  addresses, all unassigned, and zero approved TUs. The source also owns the
  folded seven-byte base destructor at `0x005E186A`; shared bytes do not
  establish an original file name.
- The EH run's lower bracket is `0x007A139D`, assigned by P to
  `GameClient/LivingWorld/LivingWorld.cpp`. Its upper bracket is
  `0x007A15AB`, assigned by P to `GameClient/GUI/StrategicInGameUI.cpp`.
  They name different TUs and cannot assign the intervening run.
- Every claimed source passes `find_declared_unmatched.py`. The apparent
  missing ownership is an evidence gap in already matched code.

Donor facts, kept separate from target placement:

- WorldBuilder contains the original paths ending in
  `LivingWorld/InGameUI/StrategicInGameUIRegionDetailsPanel.cpp` and
  `LivingWorld/InGameUI/StrategicInGameUIChecklist.cpp`. The committed path
  inventory records them only in WorldBuilder, not game.dat.
- `wb_show.py 0x005CC698` pairs the 240-byte retail constructor with WB
  `0x015BF460` (685 bytes), score 2, callgraph. Its two assertions at lines
  291/292 test the region parameters and TheLivingWorldLogic; neither
  self-asserts the class/function name.
- `wb_show.py 0x005CD049` pairs the 121-byte AddItem with WB `0x015B43D0`
  (321 bytes), score 2, callgraph. The line-557 assertion says
  `newItem.IsBound()`, not the function's name. The current named rows and
  their notes already cite WB. Reusing those names to corroborate the same
  WB path would supply no independent anchor.
- BFME 1's catalogue contribution for the checklist path is `wb2-run`.
  The source-layout planner deliberately preserves that propagated route as
  context, without promoting it to a BFME 1 donor home.

The supported Common/ consolidation report and its currency check pass.
The destructor packet has no target, alternatives or placement evidence.
The checklist packet is incomplete; `tu_skeleton.py --plan` for its named
destination reports zero approved rows. Existing hatch, include-context and
mixed-source prerequisites elsewhere in the claimed family remain separate
from this missing-anchor problem.

Verification: `./build.sh` over Rva005CC287Destructor.cpp,
StrategicInGameUIRegionDetailsPanel.cpp and StrategicInGameUIChecklist.cpp
passes 32/32 rows with current dependency receipts and all reference checks.
No reconstruction was attempted or left in Code/.

Resume when independent target path/name evidence or a qualifying donor-body
identity supplies an anchor. Use the naming tools for any proven identity,
then rebuild the TU map in memory and rerun the picker pass test. Do not
borrow the neighbouring TUs, promote the WB hints by hand, or merge into the
current readable paths merely because they already exist. No source-file,
TU-approval, debt, census-linking or ownership gain is claimed.
