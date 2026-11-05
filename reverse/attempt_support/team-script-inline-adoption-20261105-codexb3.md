# Team script consumers: preserve inline definitions during header adoption

Inspected revision: `4777346de5d7994101713c046d41bc3ab531a338`.

Two consumers now include the existing `TeamBFME2.h` instead of defining
private Team layouts:

- `ScriptActions_doTeamAvailableForRecruitment.cpp` retains the inline
  `Team::setRecruitable` definition, using canonical fields
  `m_isRecruitablitySet` and `m_isRecruitable` at +0x110 and +0x111.
- `ScriptActions_doMoveTeamTowardsNearest.cpp` retains the inline
  `Team::iterate_TeamMemberList` definition, using canonical
  `m_dlinkhead_TeamMemberList` at +0x38 and the existing Object member pointer.

The automatic adoption trial failed both consumers because replacing their
private class declarations also removed these inline definitions. Keeping the
same definitions as out-of-class inline members restores the byte matches.
The header and ledger bodies, names and ownership paths are unchanged.

Checks:

- `find_declared_unmatched.py` on both sources: all defined functions matched.
- `./build.sh` on both sources: 8/8 matched; four renumbered funclet labels
  verified through their parent's EH data; string, float and import checks pass.
- `header_adopt_lane.py accept --class Team` on both sources: PASS/PASS;
  the tool retired exactly two rows from `reverse/header_queue.tsv`.
- `link_check.py` on both current objects, against census
  `2026-11-05 05:17`, revision `c95fcfcfcd`: both LINKS;
  recruitment 74 -> 74 bytes, movement 348 -> 348 bytes, total 422 -> 422.
  This is a preview preserving the published census coverage, not a new census.

The same automatic trial failed `ScriptActions_doTeamDelete.cpp`; it remains
unchanged and queued. Its integer-shaped member-pointer call needs separate
investigation against Team's multiple-inheritance contract. No shared header
change, alias removal, new hatch or source move is part of this repair.
