### LINK-079: a StateMachine subclass's xfer slot is the shared 0x0033FB0B fold
Status: Repair landed / awaiting verification. Updated: 2026-10-26; inspected revision:
`55e3ea8048` (index 2026-10-26 19:02 at `5ce093a71a`).
Evidence / affected units:
- `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp`
  declared `DozerPrimaryStateMachine::xfer` for its vtable but nothing defined it.
  Retail slot 3 of vtable 0x0084B668 is 0x0033FB0B, the 21-byte
  `StateMachine::xfer` + `Xfer::Version1` body shared by 16 tables and rowed
  as `?xfer@Rva0033FB0B` (`VslotSmallBodiesAM.cpp`). Completed: the TU now
  includes the shared `BfmeXfer.h` and defines the override, rowed as an
  ICF twin (`add_match.py --icf-owner`); `./build.sh` 62/62;
  `tools/link_check.py` 0 -> 8,003 B.
- No other indexed unit has this as its only blocker; `HackInternetAIUpdate.cpp`
  and `JetAIUpdate.cpp` also miss their machines' xfer, among many other blockers.
Clearance: pending.
Census confirmation: awaiting the next census.
