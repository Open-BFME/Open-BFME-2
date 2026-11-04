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

**Done:** the filter objects `g_Va00DEC018`..`g_Va00DEC1DC`, then the other constructed names in
`Rva007B6880Thunks.cpp`. **Open:** the constructed names outside that file, and a check in `image_report.py` that
compares each global's extent with the size its constructor writes.
