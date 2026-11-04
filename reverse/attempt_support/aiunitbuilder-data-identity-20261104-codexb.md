# AIUnitBuilder data identity: hatch counter refusal

2026-11-04, codexb; inspected master `370febb6d2`.

The data queue serves `AIUnitBuilder.cpp`'s wrong-name key for
`?g_00E063D4@@3VAsciiString@@A` at RVA `0x00A063D4`.
`reverse/data_rows.csv` names `?g_Va00E063D4@@3IA`, defined in
`Common/Rva007AB85CAtexitInits.cpp`. Its initializer at `0x007B434E`
constructs `AsciiString("CreateAHero")` in that storage.

Attempt: replace the builder's `AsciiString g_00E063D4` definition with
`extern unsigned int g_Va00E063D4`, and pass
`*(const AsciiString *)&g_Va00E063D4` to the existing `push_back` call at
`0x00598CBC`. No class layout or function identity changed.

Checks on the attempted source:

- `./build.sh Code/GameEngine/Source/GameLogic/SkirmishAI/AIUnitBuilder/AIUnitBuilder.cpp`:
  24/24 matched, including parent-EH-backed funclet label resolution; literal,
  float and import reference checks passed.
- `find_declared_unmatched.py`: all defined functions already matched.
- `repair_queue.py retire data` for that source: PASS, one key retired and
  zero still found.
- `link_check.py`: LINKS, 829 -> 829 bytes, using the 2026-11-04 07:28 census
  index at `a62ac1c10b`. This is a prediction, not a census gain.

Pre-commit refused `address_global +2 ... g_Va00E063D4 (register grants 0)`.
The old alias lacks the `Va`/`Rva`/`DAT` token required by
`hatch_counters.ADDR_GLOBAL`, so its replacement cannot spend old counted
occurrences under the ledger-respelling rule. The fix follows the data queue's
instruction to declare the ledger's real global and cast to its view, but that
canonical spelling requires an admission not provided by this lane.

Source and baseline changes were reverted; the original debt remains. No
hatch was admitted. Next: a tooling seat should reproduce this alias-to-owner
case, decide the intended admission/counting rule, and add a regression test
in a separate verifier change before retrying the source repair.
