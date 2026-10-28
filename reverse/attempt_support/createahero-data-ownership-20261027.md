# CreateAHero accessor storage ownership prerequisite

Inspected at `46e6a22e9f`, 2026-10-27, seat codexb5.

The data picker served `Code/GameEngine/Source/Common/Rva00219B9EAccessor.cpp`
with the historical guard-name finding at RVA `0x009FE434`. Its thirteen
registered keys retain pre-rename local-static names. Current objects instead
produce seventeen findings: thirteen compiler guards and four `AsciiString`
fallbacks. The compiler guards have sole local definitions after the DFE3xx
clearer retirement (`394b97a608`); the fallback strings still conflict with
explicit external owners in `reverse/data_rows.csv`.

| Fallback storage RVA | Existing atexit thunk RVA |
| --- | --- |
| 0x009FE3E8 | 0x007B7650 |
| 0x009FE420 | 0x007B76AA |
| 0x009FE440 | 0x007B766E |
| 0x009FE448 | 0x007B7678 |

`Code/GameEngine/Source/Common/Rva007B6A00AtexitThunks.cpp` still defines the
four address-named unsigned integers and owns their four-byte data rows. The
accessor object emits its own local `AsciiString` definitions at those native
placements. These are observed conflicting owners, not evidence for a new
donor name or a new body. Repair must reconcile the string lifetime, existing
thunks and registered owner before retiring the accessor's data debt.

A bounded trial copied the thirteen generated guard rows at RVAs
`0x009FE3EC` through `0x009FE44C` (stride eight) from
`data_ledger.py --out build/codexb5-createahero-data-ledger.csv`. This removed
their live findings, but `repair_queue.py retire data SOURCE` refused the
four post-rename fallback findings. The entire index trial was restored;
the debt register, function rows and game source are unchanged. This is a
blocked ownership repair, not a verifier false rejection.

Checks: all defined functions are rowed; `./build.sh` passes 87/87 rows and
thirteen literals, including float/import checks; `eh_verify.py` reports
13 EXACT graphs. Ordinary `link_check.py` reports LINKS and 3,046 authored
bytes against index `bf3dd31211` (2026-10-27 00:39, retail-truth-4). Clean symbol
resolution does not resolve the data-owner conflict. No census gain or
image-ownership receipt is claimed. The source claim was released.

## Prerequisite resolved and debt retired (2026-10-28)

Rechecked at `2621cae89b546a3ad861a3131615307b01cb075a`, seat codexb.
Commit `76a2500f64` moved the four atexit cleanups above into the accessor
unit's compiler-emitted cleanup bodies and removed the four external data
owners. The current source, pins and data rows no longer name those globals.
The guard index rows already reflect the current method names, but the four
fallback rows still selected the removed external names as unowned globals.
The first retirement check therefore refused four new-name findings; it
changed no debt entries.

`python3 tools/data_ledger.py --out build/codexb-createahero-data-ledger.csv`
now generates each fallback as an owned four-byte local `AsciiString` in
Rva00219B9EAccessor.cpp, with one definition and two relocation references.
Copied only these four complete generated rows, unmodified, into the index.
The full generator reports 58 unrelated matched sources without objects;
no other inventory rows were accepted. These are compiler-local symbol
identities backed by the existing parent/cleanup bodies, not new retail names.

Verification:

- `./build.sh`: 91/91 function rows and thirteen string literals pass.
- `eh_verify.py`: all thirteen EH graphs EXACT, none baselined or missing.
- `find_declared_unmatched.py`: all defined functions already matched.
- `data_check.py`: zero findings after the four-row refresh.
- Enforced converged-data check: eleven addresses, zero second names or
  unjudged rows.
- `repair_queue.py retire data`: PASS, all thirteen registered keys retired,
  zero remaining findings. The owning tool alone removed the baseline lines.
- Ordinary `link_check.py`: LINKS, unchanged 3,086 authored bytes against
  index `41c28839bf` (2026-10-28 11:08).
- `check_csv.py` and `git diff --check` pass.

This closes the recorded accessor data-ownership prerequisite and its debt.
No game source, function row, pin or source path changes. No new census-linked
coverage or image-ownership result is claimed.
## Resolved data-index follow-up (2026-10-28)

Inspected base `58c6924a71`, seat codex. The prerequisite above was repaired by
`76a2500f64`: the four existing atexit rows now belong to the accessor unit,
and the old address-named definitions and explicit data rows were removed.
The committed data index still selected those four removed names, producing
four current wrong-name findings and preventing retirement of all thirteen
historical register keys.

Generated `build/createahero-data-ledger.csv` with `tools/data_ledger.py --out`
and copied only its four complete, unmodified rows at 0x009FE3E8,
0x009FE420, 0x009FE440 and 0x009FE448. Each generated row is four bytes,
status `owned`, one definition, and names the accessor's function-local
`AsciiString err`. No old global spelling remains in Code, pins, explicit
data rows or the converged register. These are compiler-local identities,
not evidence for retail identifier spelling or new data-row ownership.
The generator reported 54 unrelated sources without objects; the complete
index was not adopted. Both the accessor and former thunk source have
current build receipts.

Verification:

- `./build.sh` accessor: 91/91 rows; all 13 literals verified.
- `./build.sh` former thunk source: 63/63 rows and 31 data rows verified.
- `eh_verify.py` accessor: 13 EXACT graphs, no missing objects.
- `find_declared_unmatched.py`: both sources have every definition rowed.
- `data_check.py --converged` accessor: 11 addresses, no second names or
  unjudged rows.
- `data_check.py --enforce` accessor: zero findings; `check_csv.py` passes.
- Whole-tree `data_check.py --all`: 534 -> 530 findings, 449 -> 445 outside
  the register; the exact finding-set comparison removes only these four
  accessor findings and adds none (21,596 sources inspected).
- `repair_queue.py verify-removed`: PASS against the staged retirement.
- `repair_queue.py retire data` accessor: PASS; all 13 registered keys
  retired by the owning tool, zero still found.

This closes the scoped data-index/debt prerequisite. No game source,
function rows, pins or paths change; no new linked-byte or image-ownership
measurement is claimed.
