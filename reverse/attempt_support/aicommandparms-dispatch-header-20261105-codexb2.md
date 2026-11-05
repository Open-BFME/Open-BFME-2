# AICommandParms adoption in the AI command dispatcher

Inspected revision: 69591b5f6e (2026-11-05). Scope:
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceAiDoCommand.cpp`,
`?aiDoCommand@AIUpdateInterface@@UAEXPBUAICommandParms@@@Z`, RVA 0x002673F6.

The existing private AICommandParms declaration described vector and damage
members as arrays. Replaced it with the existing canonical AICommandParms.h;
vector and damage arguments now take member addresses, float reads use field38,
and typed const pointer fields explicitly cross the unchanged legacy void *
handler declarations. No handler signature, pin, alias or shared header changed.
The removed private struct contained fields only: it emitted no method or data
provider. No inline definition or /alternatename pragma was removed.

Verification:
- find_declared_unmatched.py before and after: all defined functions matched.
- ./build.sh on the dispatcher: 1/1 matched (2,308-byte ledger extent), including
  string, float and import reference checks.
- header_adopt_lane.py accept --class AICommandParms on this source: PASS;
  the tool retired exactly this source/class row from reverse/header_queue.tsv.
- link_check.py on the source: LINKS, 2,306 -> 2,306 linked bytes against census
  2026-11-05 15:19, measured revision f44cbcf5b0. This is prediction only.

The other AICommandParms cohort entries retain their recorded vector/lifetime
and pointer-view blockers; no unchanged failed trial was repeated. This source's
AICommandInterface and AIUpdateInterface queue rows remain: adoption must
reconcile stored-command representation and the whole AI interface first.
No census gain, source-file reduction or real-link result is claimed.
