# FireSpecialPowerAtPosition special-power interface adoption

Base: `165d5ee85a`. Scope: the 192-byte row at RVA `0x003C069B` in
`Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsFireSpecialPowerAtPosition.cpp`.

The private declaration used twelve placeholder slots before `s12`. The
existing shared `SpecialPowerModule.h` documents retail implementation table
`0x00C5E080`: slot 12 targets the rowed `doSpecialPowerAtLocation` body at
RVA `0x004949D8`, with location and unsigned command-options arguments.
The script action already passes that slot a location and `0x40000`.
Replace the private declaration with the shared include and use its existing
method spelling. No shared header or ledger identity changes.

Checks:

- `find_declared_unmatched.py`: all defined functions already matched.
- `./build.sh` on the source: 1/1 matched, 192 bytes; string, float and import
  reference checks pass.
- `header_adopt_lane.py accept --class SpecialPowerModuleInterface`: PASS;
  retires the source's one SpecialPowerModuleInterface header-queue key.
- `link_check.py` on the source: LINKS, predicted LINKED 192 -> 192 against
  census `8661f15284` (2026-11-03 20:03). This is a preview, not a census gain.
- `git diff --check`: clean.

The file's remaining Player and PlayerList header keys were inspected; both
class claims are peer-held, so neither adoption was attempted. Their existing
queue entries retain the next steps. No new linking obstacle was found.
