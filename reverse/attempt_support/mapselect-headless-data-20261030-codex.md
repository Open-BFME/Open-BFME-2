# MapSelectMenu headless counter ownership (2026-10-30)

Base: `d453af1733`. Scope: `MapSelectMenu.cpp`, claimed as a file.
Reverified and retired through the owning tool at `459d69de971f` after
reclaiming that file scope.

The picker served duplicate-def `_isShuttingDown` at RVA `0x00A045C4`.
That name is already absent from the source; the existing external
`mapSelectIsShuttingDown` owns the shutdown state. Prior attempts at
`reverse/re_attempts.log` lines 89693 and 94588 explain why retirement
remained blocked by other data findings. The current refusal isolates
`?mapSelectHeadlessCount@@3HA` at RVA `0x00A045C8`.

## Target and object facts

The following DIR32 relocations bind that existing signed `Int` definition.
Each object's in-place addend is zero and each native operand is VA
`0x00E045C8`:

| Row | RVA | Offset | Role visible in recovered C++ |
|---|---|---|---|
| MapSelectMenuSystem | 0x0050D672 | +0x36A | Pass counter address to the headless combo selection getter |
| Rva0050CF3CStartHeadless | 0x0050CF3C | +0x129 | Read counter for startHeadlessClients |
| doGameStart | 0x0050D099 | +0x31 | Test counter before choosing headless startup |

An explicit data row now owns the existing four-byte signed symbol at that
address. `./build.sh` independently verifies its compiler size and four
loader-zero bytes. No source identifier or ABI changes. The heuristic ledger's
unowned `?g_Va00E045C8@@3HA` spelling does not establish a separate global.
No original target identifier is claimed; the current name is retained.
Donor history is context only, not proof of this data name or extent.

## Verification

- `./build.sh Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/MapSelectMenu.cpp`:
  47/47 code rows, one data row, 29 literals and one empty-string reference pass.
- `find_declared_unmatched.py`: all defined functions are matched.
- `repair_queue.py retire data <source>`: PASS, one key retired, zero remain.
  The owning verdict finds no new data findings.
- `check_csv.py`: passes with 2,238 data rows.
- `data_check.py --enforce <source>`: zero findings, zero outside baseline.
- Ordinary link preview against index `85f6b7f40c`: MapSelectMenu retains
  LINKS for 3,397 bytes and the split-out reader retains LINKS for 345 bytes.
- `link_check.py --prepare-current` on both units: 48/48 code rows, one
  data row, 30 literals and two empty-string references pass with strict
  reusable receipts. No census or index is updated.

The staged-tree batch audit against `459d69de971f` remains INCONCLUSIVE:
the index predates the base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. The counter owner and split reader have strict current receipts;
full affected-consumer closure remains unverified. Carry that scope into the
next scheduled census. Link compatibility results are also recorded in the
obstacle register. This change retires data debt and establishes explicit
ownership; it makes no census claim.
