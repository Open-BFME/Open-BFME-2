# GameClient Drawable ID blocker: upstream repair verified

Inspected revision: `dd65af9110`, including upstream repair `85b46a09f3`.
No source changes were needed. The queued real-link blocker predates that repair.

Target facts: `GameClient.cpp` references
`?getID@Drawable@@QBE?AW4DrawableID@@XZ`. The current `Drawable.cpp` object
now defines that exact external symbol (COFF storage 2, section 308, value 0).
The ledger places its seven-byte body at `0x0055A88B`; the existing opaque
getter remains a separately named ICF twin. This pass adds no identity claim.

Verification:

- `./build.sh Code/GameEngine/Source/GameClient/GameClient.cpp`: 2/2 matched
  functions and three data rows pass, with no string/float/import failures.
- `./build.sh '?getID@Drawable@@QBE?AW4DrawableID@@XZ'`: 1/1 matched function.
- `find_declared_unmatched.py GameClient.cpp`: passes with existing markers.
- Raw `_coff_symbols` inspection confirms the consumer has an undefined
  external and the current provider defines the exact same spelling.
- Consumer-only `link_check.py` initially reports unresolved because the local
  index (`112a456a2c`, 2026-11-05 15:52) predates the provider repair.
- Checking **both** `GameClient.cpp` and `Drawable.cpp` overlays both current
  objects: 2/2 LINKS, 8,390 -> 8,397 linked bytes in the scoped preview.
  GameClient preserves its five uniquely owned census bytes; Drawable gains
  the seven-byte provider. Four unreferenced GameClient layout diagnostics
  remain nonblocking.

This clears the missing-definition cause in LINK-534 against the current
objects. It does not claim a new real-link run, census, runtime result or
headline gain. The authorized real-link workflow must confirm the obsolete
missing-name errors disappear. No measurement runner was started.
