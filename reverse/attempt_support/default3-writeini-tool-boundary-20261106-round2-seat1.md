# Default physics writer: unsupported virtual/class reconciliation

2026-11-06; base `85d0ac929f8`; worker `codex-20261106-round2-seat1`.
Status: blocked at the supported rename boundary; no source or identity change.

The first default picker and its coordinated `--shard 0/3` served the already
landed Point writer. Source, ledger and commit `8858a90aa54` confirmed freshness;
its temporary claims were released without repeating its repair. Root then
authorized freshness filtering of the supported ranked shard. The first fresh
non-deferred target was the existing 326-byte owner `0x0055F368` in
`Code/GameEngine/Source/GameClient/Rva0055F368Write.cpp`; its RVA and file were
claimed before investigation.

## Target facts

`reverse/exports.csv` ordinal 1938 gives that exact RVA the spelling
`?writeINI@?$DefaultModuleTemplate@$02@FXParticleSystem@@UBEXAAVFile@@I@Z`:
`FXParticleSystem::DefaultModuleTemplate<3>::writeINI(File &, unsigned) const`.
The current row is the sole owner there,
`?rva0055F368@Rva0055F368@@QAEXPAVFile@@I@Z`. Its local C++ class is
nonvirtual with 12 bytes of padding before the drift velocity. A successful
reconciliation must preserve field offsets while recovering the virtual member,
namespace, template owner and signature; another body is not needed.

The canonical-class register has no header for this template. Source/pin/data
searches find the placeholder only in its owner, plus a comment in the header
writer identifying its caller's address. The dated published index `47fd56b879`
(2026-11-06 05:39 UTC) attributes the old name only to this owner and contains
no alternatename edge naming it. That bounded evidence is not current full-link
or provider/consumer closure.

## Reproduced tool boundary

All commands are dry runs; no proposed rename was applied.

1. `rename.py function --rva 0x0055F368 --new <exact-export>
   --basis canonical:export --evidence <ordinal> --dry-run` refuses a mangled
   signature change beyond the identifier.
2. `rename.py function --rva 0x0055F368 --to-class
   'FXParticleSystem::DefaultModuleTemplate<3>' --new <exact-export> --dry-run`
   refuses the scoped template as "not a class identifier". The implementation
   supports a global identifier and does not support this scoped template.
3. `rename.py function --rva 0x0055F368 --virtual --dry-run` refuses the
   placeholder's ownership proof: retail tables `0x00C1BCC0` and `0x00C1BF60`
   contain the target in slot 3, but the ledger cannot attribute those tables
   to the placeholder or a class derived from it.

`docs/naming.md`'s hand-signature exception explicitly excludes a nonvirtual
decoration contradicted by a retail vtable. No combined hand rename was made.
This is a supported-mode/tool-grammar limitation plus missing installer ownership
evidence, not a demonstrated broken gate. An initial false-reject label was
retracted through `re_log.py void` and replaced with a blocked tool-boundary
verdict; the log was never hand-edited. No gate or tool code is edited here.

## Verification and next step

- `./build.sh Code/GameEngine/Source/GameClient/Rva0055F368Write.cpp`:
  **1/1 matched**, **5 string literals** verified, zero unverified/skipped.
- `find_declared_unmatched.py <source>`: all defined functions already matched.
- `check_csv.py`: **99,515 function rows**, **9,320 symbols**, **2,272 data
  rows**, OK before the attempt.

The source remains untouched. Resume when the rename planner supports an
evidence-gated scoped-template reconciliation, or when real installer/header
ownership evidence makes the supported virtual path possible. Such tool work
belongs in a separate verifier change with a regression test; keep every gate
exploit refusal intact. The exact exported writer remains unresolved in the
last inspected automated run `42174078539` (**308** unresolved, **0** duplicates,
no image). No new link, runtime or CRC result is claimed.
