# Recorder CRT declaration cleanup

Base: `b8a353c950`. Claimed source:
`Code/GameEngine/Source/Common/Recorder.cpp`.

## Existing ownership and change

Recorder already includes `<stdio.h>` and `<new>` and compiles with `/MD`.
The Microsoft-header queue records 19 local definitions/declarations in this
source. Remove its EOF macro, `_iobuf` forward declaration and FILE typedef,
three allocation/deallocation declarations, and thirteen duplicate stdio
prototypes. The existing real headers now supply those names. Includes,
compiler flags, function bodies, ledger rows, pins and source paths stay as
before. This is cleanup of a redundant declaration layer, not
recovery of an uncovered body.

The pinned VC7.1 stdio header defines EOF as -1, FILE as `struct _iobuf`,
size_t as unsigned int and wint_t as unsigned short. Its declarations use
`__cdecl`; `/MD` retains `_CRTIMP` dllimport. The existing `<new>` supplies
the three removed operators. These are toolchain facts, not evidence for
an original BFME source path or a complete recovered Recorder class.

## Byte and object verification

- Before and after, `./build.sh Code/GameEngine/Source/Common/Recorder.cpp`
  passes 133/133 function rows, two data rows, 50 string literals plus 15
  empty-string references, and 76 named import references. The 78 existing
  funclet pins verify through their parent EH data despite label renumbering.
- `find_declared_unmatched.py` passes before and after.
- COFF comparison excludes debug sections and normalizes local relocation
  targets to section/offset. All 198 remaining sections (16,419 bytes), 914
  relocations and 306 external symbol records are identical. Import
  references retain their `__imp__` names and counts. Scratch snapshots and
  comparison script are under `build/recorder-ms-headers-20261030/`.
- `link_check.py --prepare-current` passes the same ordinary gates using
  a strict reusable compiler receipt for this one explicit source.
- Ordinary link preview against `6fe1089c24` (2026-10-30 04:25) retains
  LINKS, 11,146 -> 11,146 authored bytes.

## Header debt and linking scope

The staged-tree outgoing audit is INCONCLUSIVE: its index predates the
source baseline, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Full affected-consumer provider selection and loss checks remain
unverified. Carry Recorder and its wider consumers into the next scheduled
census; the identical emitted object facts and bounded LINKS preview do not
replace that confirmation.

The current owning `ms_header_audit` index reports no analysis error and zero
local occurrences; classification is clean. Its scoped `refresh_queue`
removes exactly Recorder's one 19-occurrence queue row and preserves all
unrelated queue records. It still reports 719 include-closure findings
(513 unknown, 16 mangle, 69 unverified, 11 ABI, 110 source), in the included
shim layer. This retires local CRT declaration debt only, not Windows-SDK
adoption or include-closure debt. The scratch refresh script and full result
are under `build/recorder-ms-headers-20261030/`.

The separate Thing header-adoption row remains open; this change does not
attempt its missing layout/declaration prerequisites or alter the sweep
Windows shim. No census linked-byte or source-file gain is claimed.

In particular, Recorder's private Thing supplies an inline `getTemplate`,
while the canonical header only declares that member. The queued adoption
already records a `dumpCommandHistory` mismatch. The canonical base also
contains the transform/cache layout rather than Recorder's two-word view;
its derived Object view needs reconciliation before that separate adoption.
