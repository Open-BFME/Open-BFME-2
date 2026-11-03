### Exit link imports (2026-11-03)

Real link 41583916028 at `35b9760267`: 775 unresolved, of which 85 mss32 imports and 19 thunk-only
imports (Gdiplus, `Netbios`). mss32.dll is the one DLL whose retail import names keep decoration
(`_AIL_open_stream@12`); `import_def_entries` looked up the undecorated form. A source that declares
an import without dllimport references only `_X@N`, which `undefined_imports` did not see. Both are
fixed in `link_cycle.py`; the census's own unresolved list does not read these helpers. The rest are
one duplicate pair each for `MapCache::addMap` and `_RTC_CheckStackVars`, and about 670 names no
kept object defines. Confirm on the next real link.
