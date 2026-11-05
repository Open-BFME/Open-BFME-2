# Player::hasScience canonical-header adoption, 2026-11-05

Inspected base: `1ed7dd708e`. Scope: `Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp`,
`?hasScience@Player@@QBE_NW4ScienceType@@@Z`, RVA `0x002AB7D5`, complete 40-byte body.

The consolidation picker claimed the Player.cpp donor group. Before any edits,
all 158 claimed source files passed `find_declared_unmatched.py --fail`.
The existing Player.cpp separately passed its normal build (12 code rows and one data row).
The broad `tu_skeleton.py --merge Code/GameEngine/Source/Common/RTS/Player.cpp --dry-run`
was interrupted after approximately 166 minutes to address a concrete private-view prerequisite.
It produced no final merge verdict; no merge, source-path move or ledger repoint was applied.

A read-only header-adoption probe found that the old private Player flattened its
science vector into pointers. Automatic field renaming could not map its 4-byte
`m_begin` at +0x2F0 to the canonical 12-byte `m_sciences` vector. The native vector
placement was already established in Player.h and this body's existing row evidence;
this change makes no new donor-layout or source-provenance claim.

The source now includes `<vector>` before `Common/Player.h` and uses `m_sciences.begin()/end()`.
The const casts preserve the already admitted mutable-iterator `find` specialization
(`reverse/symbols.csv`, RVA 0x0020E873); no pin, alias, global, class copy or shared header was added.
No `/alternatename` directive was removed. No data or code-identity debt key names this file.
The only debt change is the Player/header-queue row retired by the acceptance command below.

## Verification receipts

Commands were run against the same source and ledger inputs; the two link previews use
the existing census index (2026-11-05 05:17, revision `c95fcfcfcd`). These are previews:
the unit was already census-linked at 40 bytes, and no LINKED headline increase is claimed.

```sh
python3 tools/header_adopt_lane.py adopt --class Player --header Code/GameEngine/Include/Common/Player.h Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp
python3 tools/link_check.py Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp # before and after
./build.sh Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp
python3 tools/header_adopt_lane.py accept --class Player Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp
python3 tools/check_csv.py
git diff --check
```

`find_declared_unmatched.py`: all defined functions are already matched (before and after).
`check_csv.py`: OK, 99,462 function rows, 9,318 symbol rows, 2,268 data rows.
`git diff --check`: passed.

### Initial canonical-header probe

```text
  FAIL Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp: field renames: Player::m_begin (+0x2F0, 4 bytes) has no canonical field of that offset and size
```
Log SHA-256: `66dbc22d93e825727c5155402f99a0fe5e4ab54a076468e980477bcbc9cf63ea`.

### Before link preview

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp: LINKS  LINKED 40 -> 40 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 40)
link_check: 1 of 1 link cleanly; LINKED 40 -> 40 bytes (6.1s)
```
Log SHA-256: `7ed26d7f201b638ec2a63c51455ec33242d7f334824cd93863e316567e1ce0da`.

### After byte verification

```text
Source claims: OK (1 sources, scoped byte-verified)
Functions: OK 1/1 matched
  ?hasScience@Player@@QBE_NW4ScienceType@@@Z (Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp)
String-ref verify: OK (0 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```
Log SHA-256: `e210dbe5b98fd2203a437944a4506cb54dc34471ba1967c0ad36ec55a15f9962`.

### After link preview

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp: LINKS  LINKED 40 -> 40 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 40)
link_check: 1 of 1 link cleanly; LINKED 40 -> 40 bytes (5.7s)
```
Log SHA-256: `af7f1f5ccdb92489d089ad532ab259869f3e6a714ea188fa889d69422b68cbc2`.

### Header acceptance

```text
  PASS Code/GameEngine/Source/Common/RTS/PlayerHasScience.cpp
  retired 1 row(s) from reverse/header_queue.tsv; commit it with the adoption
```
Log SHA-256: `89004610dd4a8cacc0c2d0b938f2617dc1b718608ac8f6f16a0209aba8c7aea1`.

Index SHA-256: `fc8fb85e6cb11b8514bf608e38196a7ec85c5a49e1d1d2ed6b096b11557093f1`.

The one-unit private-view prerequisite is cleared. Broader Player.cpp consolidation
still needs its own completed merge verdict and the remaining private-view reconciliation;
the interrupted broad search provides no proof of a compile, byte or link regression.
