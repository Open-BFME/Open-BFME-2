# Point emission-volume writer export reconciliation

2026-11-06; seat `codex-20261106-seat1`; inspected base `d707d2f53bf`.
Picker: `python3 tools/next_work.py --claim` served the existing 186-byte
owner at `0x0055CC35` in
`Code/GameEngine/Source/GameClient/Rva0055CC35Write.cpp`.

## Target evidence and scope

`reverse/exports.csv` ordinal 1953 names that exact address
`?writeINI@PointEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z`.
The ledger already held one body there, spelled
`?rva0055CC35@PointEmissionVolumeModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z`.
This is existing-placeholder cleanup, not new source recovery or a lost row.
The latest inspected real-link errors (run 42174078539, `da59156dc4f2`,
2026-11-06 07:01 UTC) still list the exact exported writer as missing.

There is no registered canonical PointEmissionVolumeModuleTemplate header.
Only this source's local declaration and definition change: `File *` becomes
`File &`, the member becomes const, and helper calls take `&file` where needed.
The existing source path and 186-byte extent remain. No new body, pin, alias,
vtable, initializer, shared header or emit anchor is added.

The ordinary `rename.py function --rva 0x0055CC35 --new <export>
--basis canonical:export --evidence <ordinal> --dry-run` refuses the signature
change beyond the identifier. The documented hand-signature exception in
`docs/naming.md` applies: exact export evidence, old-name tombstone and
`re_log.py` record accompany the change. No inferred name is hand-admitted.

## Provider and consumer checks

`rg -n -i 'rva0055cc35|0x0055cc35' Code reverse/symbols.csv
reverse/data_rows.csv reverse/data_converged.csv` found only the old owner's
comment, declaration and definition. No pin or data relocation names it.
The published index (`47fd56b879`, 2026-11-06 05:39 UTC) reports only that
owner in `link_batch_audit.affected_sources(index, {old_name})`, and no
`alternates` edge contains the old name. This is bounded index evidence;
the outgoing audit still checks the batch before publication.

Comparison of the verified original and repaired COFF objects found:

- writer bytes: 186 before and after, identical;
- writer relocations: 14 before and after; identical after the expected
  compiler-generated EH-handler label follows the function's new decoration;
- external definitions: 550 before and after; the only removed definition is
  the old writer spelling and the only added one is the exact retail export.

## Verification

The host initially lacked Wine. Root brought up its existing x86 QEMU compiler
VM and exposed this worktree read-only at its exact host path; the normal
`./build.sh` and gates ran through the existing Wine wrappers. No verifier or
compiler flags changed. Scratch originals and comparison JSON remain under
ignored `build/seat1-point-writeini/`.

- `./build.sh Code/GameEngine/Source/GameClient/Rva0055CC35Write.cpp`:
  original **1/1 matched**, repaired **1/1 matched**; **1 string literal**
  verified on each run; zero unverified/skipped literals.
- `python3 tools/find_declared_unmatched.py <source>`: all definitions rowed,
  before and after.
- `python3 tools/check_csv.py`: **99,515 function rows**, **9,320 symbol rows**,
  **2,272 data rows**, OK.
- `python3 tools/pin_consistency.py --check`: **0 new, 0 stale**.
- `python3 tools/link_check.py <source>`: **1/1 link cleanly** before and after;
  bounded preview **186 -> 186 bytes** against the dated index. This repair
  supplies a missing export name; it claims no newly linked census bytes.

The inspected authoritative real-link run has **308 unresolved**, **0
duplicates**, **no image**. No new real-link run, startup run, menu, skirmish,
save/load or CRC check was launched here. Disappearance of the one writer
export awaits the automated real link. Other Point module vtable/tag-data
exports are separate remaining work; this local change does not clear them.
