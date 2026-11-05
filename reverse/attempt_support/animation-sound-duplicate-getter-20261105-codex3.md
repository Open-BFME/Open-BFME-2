# Animation sound duplicate getter declaration repair

Inspected revision: `6e5aff698e`, 2026-11-05.
Scope: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`.

The default picker still serves the historical Drawable::getID missing-name
blocker. The call was already repaired by `fb2936dc85`. A second overlapping
repair, `fd3cf1a982`, added another definition of the same private
`Rva0055A88BDwordField` class. Both definitions occur consecutively in the TU.
The initial scoped build fails compilation during data-row verification.
This is a compile regression in the existing repair, not an unrowed body.

Remove only the second class definition and its redundant comment. Keep the
first declaration, matched-provider call, ledger rows, pins and linker aliases.
No new identity or layout inference is needed.

Verification after the removal:

- `find_declared_unmatched.py` before and after: all defined functions already
  matched; 32 matched rows, two existing accepted unclaimed definitions.
- `./build.sh Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`:
  31/31 functions and one data row byte-verified; seven renumbered funclet rows
  verified; string, float and import-reference checks pass.
- `link_check.py` for the same source: LINKS, 2,316 authored bytes unchanged,
  using census `c95fcfcfcd`, 2026-11-05 05:17. Fetching the published index
  confirms that local index is current and imports 16,965 cached objects.
- `git diff --check`: passes.

No census or full-game link gain is claimed. The next automated real link
still needs to confirm the original missing-name repair.
