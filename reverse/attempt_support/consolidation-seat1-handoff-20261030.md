# Mechanical consolidation seat handoff (2026-10-30)

The inherited two blocker commits were handed to the fleet publisher. This seat
then checked allocated shard `1/5`; it merged no TUs and removed no source
files. `python3 tools/check_csv.py` passed. Wind-down was present before the
third target, so no further allocation or unchanged compile trial was started.

## FESL gamebrowser TU

`consolidation_queue.py --check-tu` passed for
`Code/Libraries/Source/Fesl/gamebrowser/gamebrowserdemangler.cpp`. The scoped
planner and `--check` passed. The merge dry run accepted nine unchanged donors
(12 rows) and rejected `Rva00800920FeslCtor.cpp`: C2039 says
`rva00800a40` is not a member of `Rva00800920Owner`; C2065 says `m_14` is
undeclared. The guarded merge tool applied its accepted donors, and
`./build.sh` passed 12/12 rows; declared-unmatched passed.

The staged ownership check then found A2 on three rows: `0x0066CFB0`,
`0x0066D060`, and `0x0066D080` remain approved for
`Code/GameEngine/Source/Common/BfmeH1052.cpp` in `reverse/tu_map.csv`, not the
FESL TU. The map freshness check also reports stale inputs (`functions.csv`,
`tools/tu_map.py`, `tools/tu_evidence.py`, and `reverse/tu_map.csv`). Per lane
rules the complete trial was restored; all 22 file/RVA claims were released.
No map was regenerated. The three A2 records are in `reverse/re_attempts.log`.

## Oathbreakers TU

The scoped planner check passed. No donor was accepted. The private-view compile
blockers are recorded in `reverse/re_attempts.log`: pool-key donor C2039 for
`getModuleNameKey`; xfer donor C2039 for `xfer`; constructor donor C2511 for
the missing overload; update donor C2039 for `calcSleepTime`; and update helper
donor C2039 for `rva004B8B0F`.

Both mixed splits were inspected. The `Rva0024A797Derived.cpp` destructor carve
matched alone but destination compilation failed C2600 because the compiler
generated destructor was not declared in the class. The
`BehaviorModuleDataBuildFieldParse.cpp` carve matched alone but SplitLinkGuard
refused a residual/destination regression and a duplicate
`?m_fieldParse@AimWeaponBehaviorModuleData` provider. Neither split was applied.

## AIReturnTheRingTactic TU

Allocation check passed, but the guarded dry run accepted no donors and could
not judge the merge: LinkGuard reports census-linked
`AIReturnTheRingTactic.cpp` missing from the census index. This is recorded in
`reverse/re_attempts.log`; retry only after the index is available.

No source merge is pending publication. The FESL trial's staged identity scan
reported four shadow alternate-name findings, while staged data checks found
none; `link_check.py --staged --new-variants --staged-peers --shadow` reported
`Compile: 0 of 1 TU(s)`, so it did not provide a current composition verdict.
These trial results do not establish link safety. The fleet publisher still
owns the two inherited blocker commits.
