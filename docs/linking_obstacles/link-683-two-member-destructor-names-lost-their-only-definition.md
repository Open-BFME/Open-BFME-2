### LINK-683: two member-destructor names lost their only definition

Status: open (found 2026-11-15 by halilkkaya-init while checking siblings of HordeSiegeEngineContain.cpp; not caused
by that change and not repaired here).

**Object facts (tree `e9c6c9136fa`, `build/match` after a green full gate).** No object defines
`??1Rva003623E5Member@@QAE@XZ` or `??1Rva003623E5Filter@@QAE@XZ`; 42 objects reference the first and 22 the second.
`reverse/symbols.csv` pins both names at 0x00360D26, the body ObjectFilterRelease.cpp rows as
`??1Rva00360D26Member@@QAE@XZ` (its one definer).

**Cause.** `1cc99cc230d` ("Retire 19 COMDAT-redundant alternatename pragmas across 7 verified files", 19:07 UTC,
after the census run at `3417403f8f`) removed ObjectFilterRelease.cpp's two pragmas
`/alternatename:??1Rva003623E5Member@@QAE@XZ=??1Rva00360D26Member@@QAE@XZ` and the `Filter` twin. Those two were not
redundant: nothing else supplies either name.

**Prediction.** `link_check` (index of the 19:35 census update) reports `unresolved ??1Rva003623E5Member@@QAE@XZ` and
"does not link" for all four referrers tried: HordeSiegeEngineContainModuleDataDtor.cpp (89 -> 0),
SiegeEngineContainModuleDataCtor.cpp (146 -> 0), TransportContainModuleDataDtor.cpp (114 -> 0) and
DamageFieldUpdateModuleDataDtor.cpp (68 -> 0). The other 60 referrers were not run; the next census measures it.

**Repair, not done (inference from the retired comment).** The units that call the record `Rva003623E5Member` or
`Rva003623E5Filter` would name the class the body is rowed under, so their destructor calls bind to the one
definition. Restoring the two pragmas would re-add a hatch.
