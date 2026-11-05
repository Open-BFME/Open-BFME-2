# SidesInfo consumer header adoption, 2026-11-05

Inspected source revision: `72466cd956`. Claims: `class:SidesInfo`, its
canonical header and all 19 queued consumer files, owner
`yasinschroeder-codexb2`. No shared header or source path changed.

## Result and target evidence

Six consumers now include `GameLogic/SidesInfo.h` instead of defining private
`SidesInfo` classes. Three also replace private `ScriptList` classes with its
canonical header. The canonical layout puts `m_scripts` at +8 and `m_tail` at
+0x54; the existing library-map vector view is applied to that tail without
changing the canonical class. The asset collector likewise retains its existing
pool view through `getScriptList()`. These casts preserve existing structural
views; they do not establish new member identities or donor provenance.

| Consumer (under Code/) | Matched rows | Ledger bytes, including EH |
| --- | ---: | ---: |
| GameEngine/Source/GameLogic/Map/SidesListPlayerScriptsParse.cpp | 1 | 104 |
| GameEngine/Source/GameLogic/Map/SidesListRva00329FF4DataWriters.cpp | 2 | 205 |
| GameEngine/Source/GameLogic/Map/SidesListSwap.cpp | 2 | 359 |
| GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineCollectAssets.cpp | 2 | 189 |
| GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineReset.cpp | 4 | 913 |
| Libraries/Source/WWVegas/WWLib/StlportCopyWrapperPairsFamily.cpp | 5 | 137 |

The parser must call `side->m_scripts.swap(...)` directly. A trial using
`getScriptList()->swap(...)` changed register evaluation and missed the retail
bytes; the direct member call matches. No unsuccessful body remains in Code/.

## Provider audit

Before changing sources, saved all 19 verified consumer objects under
`build/sidesinfo-before/`. Compared COFF external definitions of each of the six
changed objects before and after, using `exit_link.coff_view` and
`external_definitions`. Five units lose no external definition. The asset
collector loses only `?getScripts@SidesInfo@@QAEPAURva00205358ScriptPool@@XZ`,
replaced there by canonical `?getScriptList@SidesInfo@@QAEPAVScriptList@@XZ`.
The data writer also gains that canonical getter. All other provider names are
retained, including the reset TU's Snapshot-related definitions.

Searched all 25,021 objects in `build/match` (not just this cohort), including
binary symbol strings and directive/alias contents:

```sh
rg -a -l -uuu -F -g '*.obj' -- '?getScripts@SidesInfo@@QAEPAURva00205358ScriptPool@@XZ' build/match
```

Exit 1: no remaining occurrence, so no cached compiled object imports the lost
helper directly or through an alias. No `/alternatename` was removed.

## Verification and remaining scope

`find_declared_unmatched.py` passes for every changed file. Baseline build of
all 19 consumers passed 618/618 function checks before edits.

`header_adopt_lane.py accept --class SidesInfo` over all six changed consumers
passed and retired six queue rows. A single `accept --class ScriptList` over
the parser, swap and reset consumers passed and retired three more rows after
adding the direct includes required by acceptance. Nine queue rows retire in
total. The final combined `./build.sh` passes 16/16 matched functions, two
string literals and six float literals, including verification of the reset
parent's renumbered EH funclet label. The provider comparison was repeated on
the final objects and produced the same differences listed above.

The six-unit `link_check.py` preview passed 6/6 against census index
`f44cbcf5b0`, measured 2026-11-05 15:19 UTC, with current objects checked:
1,893 -> 1,893 linked bytes. This is a scoped preview, not a real image or a
new census measurement.

Thirteen SidesInfo consumer queue rows remain. The automatic adoption trial
reported typed vector tails versus canonical `uchar[12]`, partial script-list
views, ambiguous member renames and header-compatibility failures. These need
individual reconciliation; no shared-header change or clearance for them is
claimed. The existing queue retains their specific diagnostics.
