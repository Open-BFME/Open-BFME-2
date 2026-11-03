### LINK-119: the LOD level-name table 0x009B95F4 held the wrong fifth string

**Status: Repaired; census confirmation pending. Updated: 2026-10-27.**

- **Evidence / scope:** upstream 314387c7cd bound `Rva005189CFText.cpp` to the defined
  table `rva00202B6CNames` (`Rva00202B6CGet.cpp`), but that table held `"VeryHigh"`
  where retail's fifth pointer reads `"UltraHigh"`, and it had no data row.
- **Fix:** the table holds retail's six strings and has a byte-verified data row
  (`0x009B95F4`, 24 B, `.data`). `./build.sh` of both units: data rows byte-verified.
- **Remaining / next check:** the data lane can name the table. The BFME 1 donor spells
  `StaticGameLODNames`, but the target spelling is unproven.
- **Clearance:** build verification only.
- **Census confirmation:** pending.

#### LOD-table debt retirement (2026-10-28)

At base `2451819902`, the already-landed repair `ed75a92689` passes all 12
related code rows and the 24-byte data row. The owner and two consumers retain
LINKS in ordinary preview against index `41c28839bf` (486 authored bytes).
The owning retirement tool removes the table owner's two stale data-debt keys,
with zero remaining findings; no source or identity changes were needed.
[Verification and scope](../../reverse/attempt_support/lod-table-debt-retirement-20261028-codexb.md).
Real-name evidence and census confirmation remain pending; no new linked-byte
gain is claimed.
