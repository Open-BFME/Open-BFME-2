# GameClient missing Drawable ID provider: stale blocker

Inspected revision: `a3018887a1`, 2026-11-05.

The default picker claimed `GameClient.cpp` / `0x002FDB5D` from the real-link
blocker register, reporting unresolved `?getID@Drawable@@QBE?AW4DrawableID@@XZ`.
Master already contains provider repair `85b46a09f3`: `Drawable.cpp` defines that
name, rowed at `0x0055A88B`. No source or ledger change was necessary.

Verification against the current checkout:

- `python3 tools/check_csv.py`: passes (99,474 function rows).
- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameClient/GameClient.cpp`:
  passes; existing unclaimed definitions retain their admitted markers.
- `./build.sh Code/GameEngine/Source/GameClient/GameClient.cpp`: passes, 2/2 code
  rows and 3 data rows verified.
- `python3 tools/link_check.py --fetch-index`: imported the published index
  dated 2026-11-05 15:19 at `f44cbcf5b0` and 16,178 compiled objects.
- `python3 tools/link_check.py Code/GameEngine/Source/GameClient/GameClient.cpp`:
  LINKS, 5 -> 5 unique bytes. Four unreferenced COMDAT differences remain
  diagnostics, not preview blockers.

This verifies only this consumer's current preview, not the full real link or
the twelve-consumer scope of LINK-534. No census or headline gain is claimed.
Next step: let the authorized real-link workflow confirm the old missing-name
errors have gone. No maintainer-only measurement was started.
