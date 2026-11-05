# Camera list template reconciliation

Prerequisite: canonical list-header adoption in `b336831c6c`.
Scope: `Code/GameEngineDevice/Source/W3DDevice/GameClient/camerashakesystem.cpp`.

The destination's `MultiListClass` now exposes the same two inherited list
operations that the verified timestep fragment uses. Public using-declarations
change access only; they introduce no function body, symbol or layout field.
This reconciles the seed template with the fragment without changing the
registered base header or importing the fragment's private class view.

- `./build.sh` on the destination: 13/13 rows exact.
- `find_declared_unmatched.py`: all defined functions already matched.
- `link_check.py`: LINKS, 282 -> 282 census-linked bytes.
- `tu_skeleton.py --merge <destination> --dry-run`: both seed and timestep
  fragment accepted, 17 rows, no rejected donors; census-linked guard passes
  for both sources. The mixed `camerashakesystem_shaker.cpp` stays separate.

Commit this prerequisite before applying the verified merge. No path or ledger
row moved in this change; no headline link gain is claimed.
