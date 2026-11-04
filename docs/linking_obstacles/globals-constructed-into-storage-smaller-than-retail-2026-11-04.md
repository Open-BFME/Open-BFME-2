### Globals constructed into storage smaller than retail's object (2026-11-04, seat ancalgonn-ops-srv1)

**Status: Open. A runtime risk the linker cannot see; `image_report.py` now counts it (`constructed_undersized`).**

Many address-named globals are defined as `unsigned int g_Va...;`, 4 bytes, while an initializer constructs a
whole object there: `Rva007AC6DDGlobalInits.cpp` placement-news a 52-byte filter into `g_Va00DEC140`, and
`g_Va00DEDC80` has a 656-byte gap. The link succeeds and the object's constructor then overwrites whatever
follows it in our image, during startup. `image_report.py`'s byte comparison misses this because it bounds each
comparison by our own symbol's extent, so it lists these separately (`undersized_rows`).

**Measured 2026-11-04 on the census's objects:** of 3,247 globals an object defines, 963 are smaller than the
ledger's gap to the next known symbol, 406 of those at exactly 4 bytes. The gap is an upper bound on the true
size, so that figure is not a count of bugs. The hard subset: 44 names that source visibly constructs in place
(`new (&g_...)` or a cast-and-construct) and that are smaller than their gap, 22 of them in
`Rva007B6880Thunks.cpp`.

**Repair, for a name with no data row:** keep the mangled name every other unit declares and give the definition
the ledger's extent, for example `extern "C" { unsigned int __identifier("?g_Va00DEC140@@3IA")[13]; }`. The braces
matter: without them `extern "C"` only declares, and the object is undefined at link. Byte verification is unaffected,
because references are masked. Too large wastes bytes; too small corrupts memory, so the gap is the safe choice until
the class's real size is known.

**Repair, for a name with a data row:** `tools/data_rows.py` measures `sizeof` of the plain name and refuses a macro,
and a mangled scalar cannot be larger than its type. So make it a real array in every file that names it,
`unsigned int g_X[N];`, and change the row to `?g_X@@3PAIA` with size `N * 4`. Uses that take `&g_X` compile unchanged.

**Check the gap against the object first.** It is only an upper bound, and two names here show why. `g_Va00DFF0C4` has
a gap of 12 and holds a 4-byte `UnicodeString`: it needs nothing, and retyping it renumbered `GameText.cpp`'s EH labels.
`g_Va00E06634` has a gap of 12 and another row inside it, below.

**Done, data-rowed names, as arrays:** `g_Va00E065EC`, `g_Va00DF2984`, `g_Va00E06620`, `g_Va00DEBC64`,
`g_Va00E06360`, `g_Va00E08D48`, `g_Va00E0631C`.

**Done, in `Rva007ABD4BGeometryInits.cpp` and `Rva007B401CButtonNameInits.cpp`:** the names those files construct.

**Done, all in `Rva007B6880Thunks.cpp`:** seven filter objects (`g_Va00DEC018`, `g_Va00DEC080`, `g_Va00DEC0E0`, `g_Va00DEC140`,
`g_Va00DEC174`, `g_Va00DEC1CC`, `g_Va00DEC1DC`), `g_Va00A1F4E8`, `g_Va00DFDD0C`, `g_Va00E0669C`, `g_Va00E06778`, `g_Va00DE2008`,
`g_Va00E03168`, `g_Va00DF29B4`, `g_Va00DFF494`, `g_Va00E04508`, `g_Va00E04938`, `g_Va00E03174`, `g_Va00E06E60`, `g_Va009F6F30`
and `g_Va00DEDC80`.

**Open:**

- `g_Va00E06634` (gap 12): its `Rva005D00A6` object has a vtable and, per `Rva005CFC12`, two parsed floats, so it spans
  12 bytes. The row `?delay@Rva005CF9FF@@2IA` at 0x00E0663C, in `StrategicInGameUIBattleResolver.cpp`, sits at its +8, so
  that "static" looks like the object's second float. Both rows must become one: `data_check.py` refuses the overlap.
- `g_Va00E01E08` (gap 16): `AIBurningDeathStateUpdate.cpp` names it and another worker held that file. It has no data
  row, so the first repair works without touching that file.
- `g_Va00E02FF8` (gap 20): has a data row, so it needs the array form, and `BfmeConv1292DeferredWalkers.cpp` names it. That
  file is frozen (`PointerSJATable::_M_bkt_num_key` and `::_M_delete_node` have no rows), so remedy those first.
- `g_Va00DE1D00` and `g_Va00DE1D60` (gap 96), and `g_00E02EAC` (ours 16, gap 20).

The measured figures predate these repairs. `constructed_undersized` in the next real link's `image_report.json` gives
the current count; the source pattern only sees direct construction, so it can miss others.
