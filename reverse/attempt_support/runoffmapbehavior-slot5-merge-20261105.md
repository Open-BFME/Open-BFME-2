# RunOffMapBehavior.cpp: absorb RunOffMapBehaviorSlot5.cpp (2026-11-05)

Prerequisite `fc8c1dc1de` reconciles the views (bytes unchanged, 10/10):
- TU's AICommandInterface slot 0 spelled as canonical
  `aiDoCommand(const AICommandParms *)` (AIUpdate.h) instead of `v0`;
- both files read CommandSourceType from canonical
  `Code/GameEngine/Source/GameLogic/command_source_type.h` instead of private
  one-member enums (C2065 CMD_FROM_AI in the merged unit before);
- the slot-5 view declares `getModuleNameKey` (Module slot 4), which the TU
  defines (C2509 before).

The TU keeps its local AICommandParms: canonical AICommandParms.h declares an
out-of-line destructor, while retail 0x00462224/0x00462290 inline the
coordinate-vector free, so adopting it would change bytes.

Verification: `tu_skeleton --merge --dry-run` accepted TU + Slot5;
`./build.sh RunOffMapBehavior.cpp` 10/10 matched (string, float literal, EH
funclets); `find_declared_unmatched` clean; `link_check --new-variants` clean.
header_queue.tsv AICommandInterface key moved to the TU path (not retired).

Still rejected: RunOffMapBehaviorCtor.cpp (0x0046217B, C2511): its flat
explicit-vtable-store view conflicts with the polymorphic
BehaviorModule + RunOffMapBehaviorInterface class; needs a real-class ctor
that keeps the four DIR32 stores. Mixed satellites ConstIntGetters4.cpp,
Rva0049B47CThreeVptrDerived.cpp, BehaviorModuleDataBuildFieldParse.cpp stay.

Lead (not acted on): 0x00462213 carries two rows in this TU,
`?bfmeGoBJ@BfmeThingBJ@@QAEXXZ` and `?rva00462213@RunOffMapBehavior@@UAEXXZ`
(primary-table slot 5 = Module::onObjectCreated per Module.h) - a duplicate
claim of one body to settle in the naming/cleanup lane.

Path consumers: only `reverse/link_status.csv` (census output),
`reverse/class_contracts/Thing.json` (sampled unit list) and a historical
obstacle note name the old path; no tool, hook, include or debt key does.
