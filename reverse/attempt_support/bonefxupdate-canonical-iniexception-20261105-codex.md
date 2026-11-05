# BoneFXUpdate canonical INI declarations

Base: `9832af4935`, 2026-11-05. This is header debt retirement, with no
new function, source-path move, pin, alias, class name or runtime claim.

BoneFXUpdate's local INIException already has the canonical eight-byte
message/code storage and constructor/copy/destructor signatures. Including
FieldParse.h previously collided with FieldParse and MultiIniFieldParse in
its dedicated bfme2_bonefxupdate/Common/INI.h shim. Replace those two donor
class definitions with the canonical header and replace the TU-local exception
with a direct canonical include. The shim remains at its existing path;
its existing line endings and license are preserved. A source search finds
exactly one Code .cpp using this shim directory: BoneFXUpdate.cpp.

Checks:

- `find_declared_unmatched.py BoneFXUpdate.cpp` passes before and after.
- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp`
  passes 34/34 function rows, one data row, ten renumbered funclet rows,
  18 string literals, three empty-string references and four named imports.
- `header_adopt_lane.py accept --class INIException` passes and retires exactly
  this source's one header_queue.tsv row through the owning tool.
- Ordinary `link_check.py BoneFXUpdate.cpp` retains LINKS, 2,638 -> 2,638
  authored bytes, against census index f44cbcf5b0 (2026-11-05 15:19).
- `check_csv.py` passes: 99,475 functions, 9,321 symbols, 2,268 data rows.
- Existing code-identity debt and the Thing header-queue entry remain;
  no baseline, escape hatch or ledger identity is changed.

The initial default picker served the already-repaired BoneFXDamage blocker.
The fetched published index still lacks its current destructor and DamageModule
providers, and the pool-key merge guard reports the same prerequisite recorded
in LINK-113. No merge or source change was retained there; its claims were
released. The obstacle's next step is unchanged, so its entry was not edited.
No real-link, census, ownership or smoke measurement was run or claimed.
