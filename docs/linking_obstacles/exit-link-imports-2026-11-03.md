### Exit link imports (2026-11-03)

Real link 41583916028 at `35b9760267`: 775 unresolved, of which 85 mss32 imports and 19 thunk-only
imports (Gdiplus, `Netbios`). mss32.dll is the one DLL whose retail import names keep decoration
(`_AIL_open_stream@12`); `import_def_entries` looked up the undecorated form. A source that declares
an import without dllimport references only `_X@N`, which `undefined_imports` did not see. Both are
fixed in `link_cycle.py`; the census's own unresolved list does not read these helpers. The rest are
one duplicate pair each for `MapCache::addMap` and `_RTC_CheckStackVars`, and about 670 names no
kept object defines. Confirm on the next real link.

2026-11-05 follow-up (`Code/Libraries/Source/ATL/atlimage.cpp`, real-link blocker
`?GdiplusShutdown@Gdiplus@@YGXK@Z`): the unit declared `GdiplusStartup`/`GdiplusShutdown` with C++
linkage, so it referenced the namespace-mangled names and reached the thunks only through two
`/alternatename` hatches to address-named `?ji_00628f68`/`?ji_00628f6e` symbols that nothing defines.
The VS2003 SDK `GdiPlusInit.h` declares both `extern "C"`; with that linkage the unit references
`_GdiplusStartup@12` and `_GdiplusShutdown@4`, which `Code/Libraries/Source/Win32/GdiplusImportThunks.cpp`
already defines (rows 0x00628F68 and 0x00628F6E). The two hatches and the two C++-name pins in
`reverse/symbols.csv` are removed. Evidence: `./build.sh` 47/47 matched across both files;
`tools/link_check.py Code/Libraries/Source/ATL/atlimage.cpp` LINKS, LINKED 0 -> 1,901 bytes (census
2026-11-05 05:17 at c95fcfcfcd); `tools/pin_consistency.py --check` OK. Cleared in link-check scope;
confirm on the next real link that `atlimage.cpp` leaves `reverse/exit_link_blockers.tsv`.
