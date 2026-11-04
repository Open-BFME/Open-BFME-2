# AptAnimation scalar-header adoption, 2026-11-04

Inspected revision: `63884f6c6db799bb343803b4e4c5b129115c6c71`.
Scope: `Code/Libraries/Source/Apt/AptAnimation.cpp` only; shared headers unchanged.

The private two-slot AptValue declaration and factory-only AptInteger declaration
are replaced by their existing canonical headers. The unit already included
`BfmeAptValue006DCD20.h`, but its queue row was blocked by the same byte failure.

## Target facts and trials

The matched loader is `?rva006E5050@Rva006E58D0@@QAEXPAX00@Z`, RVA
`0x006E5050`, extent 2,172 bytes including its 12-entry switch table. Prior
header attempts are recorded at this symbol in `reverse/re_attempts.log`.

With canonical declarations, putting the loader before the Apt declarations, or
keeping its old location and introducing a constant-file local alias, left
exactly four byte differences: offsets `0xE7`, `0xE9`, `0xEB`, `0xED`. These
encode the order of two independent loop-head loads of pBase/pConstantFile.
Moving its unchanged definition after the pool methods restores an exact match.
This demonstrates sensitivity to definition placement; it does not establish a
retail source order or compiler-internal explanation.

The final loader body was compared with the original and is textually unchanged.
The abandoned alias and earlier-placement trials are absent from the source.
The ledger's outdated placement note now describes the verified arrangement.

## Verification

- `./build.sh Code/Libraries/Source/Apt/AptAnimation.cpp`: **8/8 matched**;
  **85 string references**, **1 float reference** verified. Both renamed local
  funclet labels remain verified through the parent's EH data at retail
  `0x007A9160` and `0x007A9168`.
- `header_adopt_lane.py accept` individually passes AptInteger, AptValue and
  BfmeAptValue006DCD20 for this source and retires **three queue rows**.
- Current-object `link_check.py`: **LINKS**, **4,274 -> 4,274 linked bytes**
  against census `2026-11-04 07:28`, revision `a62ac1c10b`. It reports an
  unreferenced key-assignment COMDAT diagnostic, not a link blocker.
- `find_declared_unmatched.py`: all defined functions already matched.
- `check_csv.py` and `git diff --check`: pass.

No new matched bytes or census gain is claimed. Other AptInteger cohort units
retain their separate shared-header, constructor and data obstacles; this
clearance covers AptAnimation.cpp only.
