### Real-link blockers in GameLogic/GameNetwork (2026-11-03, seat halilkkaya-lk19)

From `reverse/exit_link_blockers.tsv` (real link at `96cfeda7ba`; 234 errors, 214 names in this slice).

- **FlightDeckBehavior.cpp, 49 names: repaired.** BFME 2 has no FlightDeckBehavior (no module string
  in game.dat, no native row). The Zero Hour port's out-of-line destructor emitted Zero Hour's
  FlightDeckBehavior and AIUpdateInterface vtables, whose 49 slots nothing defines. The unit now holds
  only its two retail rows: ExitInterface's base `getNaturalRallyPoint` (0x004624A7) out of line against
  canonical `ExitInterface.h`, and the runway-element `_Destroy` thunk (0x0008A64A) by explicit
  instantiation over the element view `FlightDeckBehaviorRunwayInfoDestructor.cpp` already uses. 2/2
  exact; scoped DIR32 OK; `link_check`: FlightDeckBehavior.cpp does not link -> LINKS (35 B); the
  consumers of its removed COMDATs (SupplyTruck/Dozer AIUpdate ctors) are unchanged (every removed
  definition referenced elsewhere has another definer). One present-unmatched hatch removed.
