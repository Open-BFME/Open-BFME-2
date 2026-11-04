# BFME 2 consolidation shard 2/5, session 9

Fresh allocated trials accepted no publishable merge. The allocation checks passed;
each tested TU had a fresh scoped planner and passing snapshot check before its
`--plan` and `--merge --dry-run`. No source changes remain and no claims are held.

- `WargBehavior.cpp`: ctor donor fails on an undeclared `WargBehavior` constructor.
  The mixed `ConstIntGetters4.cpp` row compiles alone, but its guarded split would
  move selected COMDAT `WargBehavior` without private/weak-free context.
- `HealCrateCollide.cpp`: ctor and execute donors need class declarations. Its two
  mixed splits would move selected COMDATs for `HealCrateCollide` and
  `Rva004BC83F` without private/weak-free context.
- `BfmeHub982.cpp`: renderer donor fails on missing `DX8Wrapper::bfmeRva00120650`.
  One mixed split redefines `D3DTRANSFORMSTATETYPE`; the other is refused because
  the hatch count would grow.
- `PorcupineFormationBody.cpp`: LinkGuard cannot judge the merge or its mixed
  splits because the census index lacks the seed TU. All three split dry runs
  report the same missing-index blocker; no index download/build was attempted.
- `SquishCollide.cpp`: ctor donor lacks the declared constructor. Its mixed file
  has no rows approved for this destination, so the split tool cannot carve it.
- `AptWindowLayout.cpp`: ctor donor needs `GameWindowManager::v48/v49` declarations.
  Its mixed file has no rows approved for this destination.
- `SubObjectsUpgrade.cpp`: donor needs `Rva004B4E56` members (`m_obj08`, `m_mem10`);
  its mixed file has no rows approved for this destination.
- `W3DGameFont.cpp`: both donors are rejected by LinkGuard: the destructor donor
  loses `loadFontData` and the `W3DFontLibrary` COMDAT; the load donor ceases to
  define a census-referenced overload.
- `AptTimeLine.cpp`: neither donor compiles unchanged (duplicate `_STL::__false_type`
  definitions; missing `Rva005205DAElement`). Inspected all 11 mixed files with
  `--split` and guarded `--dry-run`: six had no row that could be carved; four
  carved rows but failed on duplicate STL vector definitions, missing
  `TheMappedImageCollection`, or a compile diagnostic with no detail; and one
  `ConstIntGetters4.cpp` carve was accepted. The accepted split was not applied:
  the target TU has no accepted merge donor to pair with it, so a split alone
  would increase the file count. Exact plans and dry runs are under ignored
  `build/consolidation-split-checks/`.
- `W3DTornadoDraw.cpp`: dry run accepted the destructor donor, but the applied
  trial moved row `0x000CEB6F` into this TU even though `tu_ownership --staged`
  reports its approved TU as `W3DTreeDraw.cpp`. The check correctly refused it;
  the staged trial was fully restored and all file/RVA claims released. Build
  before restoration passed 6/6 matched rows. Do not bypass the ownership gate.

Other checked candidates (`Made002CCB67`, `Made002CCC2D`, `AerialPathfinder`,
`AptObject`) either match existing same-day handoffs or fail their fresh dry run;
no unchanged blocker was edited or worked around.

Checks: `check_csv.py` passed; scoped planner currency passed for every fresh TU;
the accepted `W3DTornadoDraw` trial built and passed `find_declared_unmatched`,
but was restored after the ownership refusal. No TU merge or split landed. Net
source-file change, merged TUs and moved matched rows: 0, 0, 0. Code/data identity
and provider/consumer audits for the rejected trial are not claimed as clean.
