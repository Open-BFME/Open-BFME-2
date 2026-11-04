# GeneralAllocator query: Microsoft header cleanup (2026-11-04)

Inspected revision: `107d746ee8`. Scope:
`Code/GameEngine/Source/Common/System/Rva00033A80Query.cpp`.

Replace the handwritten EnterCriticalSection/LeaveCriticalSection declarations
with `<windows.h>` and cast the existing opaque lock pointer to the SDK's
CRITICAL_SECTION pointer type at the calls. `/EHsc` retains the previous
nonthrowing C API contract: without it, the SDK declarations introduce an extra
EH-state store before LeaveCriticalSection and the query fails byte comparison.
The retained source has no local Microsoft declarations.

Verification:

- `./build.sh` before and after: both rows match (269-byte query at 0x00033A80
  and 10-byte compiler EH handler at 0x0075CC48); both named imports verified.
- `find_declared_unmatched.py`: PASS before and after.
- `eh_verify.py`: EXACT 1/1 EH graph, no missing object or baseline exception.
- COFF comparison using link_census helpers: all three external COMDAT payload
  and relocation fingerprints and all eight external symbol records unchanged.
  Lock constructor: `6db6132d5e89` (35 bytes); lock destructor:
  `71bf7adb1412` (23 bytes); query: `633ea2048881` (269 bytes).
- `ms_header_audit.py scan SOURCE --write-queue`: zero local definitions or
  declarations; owning tool removes the source's one queue row (two API copies).
- `link_check.py --prepare-current SOURCE`: strict reusable receipt passes.
- Ordinary link preview: LINKS, 278 -> 278 authored bytes, against census
  `a62ac1c10b` (2026-11-04 07:28). No census gain or runtime result claimed.

No source path, ledger row, pin, alias or class identity changed. The separate
GeneralAllocator canonical-header queue entry is retained; this cleanup does
not resolve its nested BinNode prerequisite.
