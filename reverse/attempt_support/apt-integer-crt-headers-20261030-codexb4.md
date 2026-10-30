# Apt integer conversion CRT header adoption

Inspected base: `f1e25d7b30`. Claimed source:
`Code/Libraries/Source/Apt/AptValue/AptValueToIntegerBFME2.cpp`.

Replace the local `atoi` and `strtol` declarations with the VS2003
`stdlib.h`. The header's supported `_CRTIMP` guard is set empty because
retail uses direct calls to import thunks, rather than indirect IAT calls.
This is a per-body callee check, not an assumption from the CRT names:

- Row `0x006DD360`, call at `0x006DD3CE`: target RVA `0x00629ABA`,
  bytes `FF 25 60 A7 BB 00`, the `strtol` thunk through IAT `0x00BBA760`.
- Call at `0x006DD3E0`: target RVA `0x00629838`,
  bytes `FF 25 24 A6 BB 00`, the `atoi` thunk through IAT `0x00BBA624`.
- Both thunks are already rowed in `Msvcr71ImportThunks.cpp`; the target
  facts agree with their registered `msvcr71.dll` import identities.

The original BFME1 donor attribution and its separation from target layout
facts remain unchanged. No class, row, pin, source path or alias is added.

Verification:

- Ordinary builds before and after verify the existing 250-byte function
  extent, including its switch tables; reference checks pass.
- Frozen-file checks pass before and after.
- The owning Microsoft-header scanner reports clean, with no include-closure
  findings. Its sole remaining occurrence is the supported `_CRTIMP`
  configuration input. `refresh_queue` removes only this file's row and
  retires its two local CRT declaration findings.
- Complete non-debug COFF comparison preserves both sections (380 bytes),
  all 21 relocations and all 14 external symbol records. Local relocation
  targets are compared by section and offset; external targets by name.
  The comparison includes `.drectve` and the existing linker alias.
  Scratch snapshots and facts are under
  `build/apt-integer-ms-headers-20261030-codexb4/`.
- Strict preparation byte-verifies the explicit provider with a reusable
  receipt. Ordinary preview retains LINKS, 250 -> 250 authored bytes, against
  census index `85f6b7f40c` (2026-10-29 15:08).

The outgoing batch audit exits 2, INCONCLUSIVE. The index predates outgoing
base `6fe1089c24`; two earlier providers in the six-source batch lack current
strict receipts: `AptPlayerStatusDtor.cpp` and `LinearCampaignManager.cpp`.
The current integer-conversion object has its strict receipt. Full consumer
selection/loss verification remains unproven; carry the batch and its
affected consumers into the next scheduled census. The prior campaign
handoff records that provider's unsupported include-inventory prerequisite.

This is source/header cleanup. No census-linking or image-ownership gain
is claimed.
