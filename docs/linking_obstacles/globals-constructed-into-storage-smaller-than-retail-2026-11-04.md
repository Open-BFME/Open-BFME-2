### Globals constructed into storage smaller than retail's object (2026-11-04, seat ancalgonn-ops-srv1)

**Status: Open. A runtime risk the linker and `image_report.py` cannot see.**

Many address-named globals are defined as `unsigned int g_Va...;`, 4 bytes, while an initializer constructs a
whole object there: `Rva007AC6DDGlobalInits.cpp` placement-news a 52-byte filter into `g_Va00DEC140`, and
`g_Va00DEDC80` has a 656-byte gap. The link succeeds and the object's constructor then overwrites whatever
follows it in our image, during startup. `image_report.py` misses this because it bounds each comparison by our own
symbol's extent.

**Measured 2026-11-04 on the census's objects:** of 3,247 globals an object defines, 963 are smaller than the
ledger's gap to the next known symbol, 406 of those at exactly 4 bytes. The gap is an upper bound on the true
size, so that figure is not a count of bugs. The hard subset: 44 names that source visibly constructs in place
(`new (&g_...)` or a cast-and-construct) and that are smaller than their gap, 22 of them in
`Rva007B6880Thunks.cpp`.

**Repair:** keep the mangled name every other unit declares and give the definition the ledger's extent, for
example `extern "C" unsigned int __identifier("?g_Va00DEC140@@3IA")[13];`. Byte verification is unaffected, because
references are masked. Too large wastes bytes; too small corrupts memory, so the gap is the safe choice until the
class's real size is known.

**Done, all in `Rva007B6880Thunks.cpp`:** seven filter objects (`g_Va00DEC018`, `g_Va00DEC080`, `g_Va00DEC0E0`, `g_Va00DEC140`,
`g_Va00DEC174`, `g_Va00DEC1CC`, `g_Va00DEC1DC`), `g_Va00A1F4E8`, `g_Va00DFDD0C`, `g_Va00E0669C`, `g_Va00E06778`, `g_Va00DE2008`,
`g_Va00E03168`, `g_Va00DF29B4`, `g_Va00DFF494`, `g_Va00E04508`, `g_Va00E04938`, `g_Va00E03174`, `g_Va00E06E60`, `g_Va009F6F30`
and `g_Va00DEDC80`.

**Open:** the constructed names defined in other files, among them `g_Va00E06634` (`Rva007ABBB3CtorInits.cpp`, gap 12),
`g_Va00DE1D00` and `g_Va00DE1D60` (gap 96), `g_Va00DF2984` (36), `g_Va00E02FF8` (20) and `g_00E02EAC` (ours 16, gap 20). The
measured figures predate these repairs, and the source pattern only sees direct construction, so it can miss others. Also open: a check in
`image_report.py` that compares each global's extent with the size its constructor writes.
