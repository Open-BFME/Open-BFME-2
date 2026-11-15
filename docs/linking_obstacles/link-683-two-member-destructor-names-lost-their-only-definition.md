### LINK-683: two member-destructor names lost their only definition

Status: Cleared on master by f46017b0e53 ("Restore five cross-unit alias providers removed as redundant",
2026-11-15), which put the two pragmas back. Confirmed by the census of 2026-11-16 18:02 UTC at `f3a6e23db6`:
`reverse/link_status.csv` records the four referrers below as linked, and `reverse/exit_link_blockers.tsv` at
`61a11e4e11` names neither destructor. Updated: 2026-11-16 (seat halilkkaya-lead).
Found 2026-11-15 by halilkkaya-init while checking siblings of HordeSiegeEngineContain.cpp.

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

**A hatch-free replacement, verified but not landed (2026-11-16).** On tree `e9c6c9136fa`, before the restore was
seen, the two names were given real definitions instead of the pragmas: both have canonical headers
(`Rva003623E5Member.h`, `Rva003623E5Filter.h`) that declare the destructor out of line, and both are pinned at
0x00360D26 in `reverse/symbols.csv`; ObjectFilterRelease.cpp included the two headers and defined both destructors
with the forwarder's body (`Rva00360CB0Release((int *)this)`), and
`tools/add_match.py --icf-owner '??1Rva00360D26Member@@QAE@XZ'` rowed each at 0x00360D26 (8 bytes), which it does
only when the compiled body is retail's. Checks there: `./build.sh` of the unit exact, `find_declared_unmatched`
clean, `check_csv` and `pin_consistency --check` OK, and `link_check` over the 90 units naming either class plus the
definer: 87 link, none reports either name. It conflicts with the restored pragmas, so it was held back; whoever
retires those two hatches can take this route (remove the two pragmas, lower `reverse/hatch_baseline.tsv` under a
`Verifier-Change:` trailer). `rename.py class --fold` is no route: it refuses `Rva00360D26Member` (no vftable ties
it to a class table) and `Rva003623E5Filter` (registered canonical class).
