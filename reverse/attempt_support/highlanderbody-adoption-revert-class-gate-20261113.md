# HighlanderBody.cpp real-link regression: exact revert refused by class_gate (2026-11-13)

Base 196c1cae97. Served by `next_work.py --claim` as the only source in
`reverse/exit_link_blockers.tsv` (real link at 10efe4859e: 35 missing names; the measures at
43fba69119 and e20d57868b list only the 2 unowned exports).

## Cause (measured)

922e561591 "Register canonical HighlanderBody, adopt it in 3 units" replaced HighlanderBody.cpp's
private `ActiveBody`/`HighlanderBody` views with `HighlanderBodyClass.h`, which includes
ActiveBody.h. The unit defines the constructor, so it emits the class's tables, now with every
ActiveBody.h virtual. `python3 tools/link_check.py Code/GameEngine/Source/GameLogic/Object/Body/HighlanderBody.cpp`
at HEAD: does not link, LINKED 241 -> 0, 35 unresolved `...@ActiveBody@@...` names.

Each of the 35 sits on a retail slot whose body already has a row under another name (tables read
from game.dat: primary 0x00C5B440/0x00C5B038, body interface 0x00C5B390/0x00C5B5B0, BodyModule's
0x00C5AC18). No new source is needed; the rows have to move into ActiveBody/BodyModule. That is
LINK-242 and the ActiveBody inventory in LINK-514, walled since 2026-11-04 by rename.py refusals.

## Repair tried: exact revert of 922e561591

    git revert --no-commit 922e561591
    # one conflict: reverse/canonical_classes.csv; keep HEAD's side minus the HighlanderBody row

Result on that tree:
- `./build.sh` on HighlanderBody.cpp, HighlanderBodyFriendNew.cpp, ModuleFactoryInit.cpp: 319/319 matched.
- `link_check.py` on the three: 3 of 3 link, HighlanderBody.cpp LINKED 241 -> 241.
- `check_csv.py`: OK. No other file references HighlanderBodyClass.h or the contract.

Refused at commit: `tools/class_gate.py --staged` reports HighlanderBody.cpp "declares its own
`ActiveBody`" (the view the unit had until 922e561591; the gate compares with HEAD only and has no
credit for the inverse of an adoption). Not committed; tree restored with `git revert --abort`.

## What clears it

Either of:
- the gate credits a staged unit whose private body equals the one an ancestor commit removed, when
  the same commit removes that adoption's registry row (tooling seat, `Verifier-Change:`); or
- the 35 rows move (LINK-242/LINK-514), after which the adoption links as is.

Not checked: the real link itself (maintainer-run); whether the restored short tables are what the
last crash-free image ran (they are what every image before 922e561591 linked).
