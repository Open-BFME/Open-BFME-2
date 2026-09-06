# Danetta timing patch and BFME 2 analogues

This note records the reverse-engineering evidence from the `game.dat` supplied
as Danetta's file and maps it onto the committed BFME 2 1.06 baseline. It is an
evidence record for follow-up work; it is not a source conversion or a shipped
runtime patch.

## Reference file

The supplied file is an unpacked/modified RotWK-family executable rather than
the BFME 2 1.06 baseline. Its identifying facts are:

| fact | value |
|---|---|
| size | 11,346,944 bytes |
| MD5 | `daed3668006cd90f01c34e5a7da1901f` |
| SHA-256 | `5481de75b63e22483660ea8097478faef594f90b9ade7de893e092256ba68a26` |
| image base | `0x00400000` |
| PE timestamp | `2007-03-30 23:43:26 UTC` |

The `stxt*` and `.mackt` sections are SafeDisc/ImpREC remnants. The custom
`.danetta` section is executable/read/write at RVA `0x00ACA000` (VA
`0x00ECA000`), with a byte of `08` at VA `0x00ECA400`. A scan found no normal
`.text` call, jump, or data reference into this section. The section therefore
looks like an experimental payload or scratch area; the active timing edits are
in `.text` and the value at `0x00ECA400`.

## What Danetta changed

The two active instruction edits share the same integer-division shape. The
global values in the supplied image are `5` at VA `0x00D9F608` and `30` at VA
`0x00D9F60C`.

| role | address | original bytes/meaning | Danetta bytes/meaning |
|---|---:|---|---|
| animation division helper | VA `0x00632535` | `idiv dword ptr [0x00D9F608]` (divide by logic tick rate) | `F7 3D 00 A4 EC 00`, divide by `[0x00ECA400]` (`8`) |
| delay/frame-loop edit | VA `0x00632A9B` | `F7 3D 08 F6 D9 00` followed by `mov ecx,eax` | `B8 02 00 00 00 EB 19` (`eax = 2`, jump to the loop tail) |

The surrounding routines identify the intended roles:

* The helper starts at VA `0x0063252F`: it loads the FPS value (`30`), executes
  `cdq`/`idiv`, then pushes `6`. The edit changes only its divisor.
* The delay routine starts at VA `0x006329B0`. At VA `0x00632A95` it loads the
  FPS value, and the edit at `0x00632A9B` bypasses the original division and
  compare path before continuing at VA `0x00632ABB` (`mov esi,eax`). Other
  `idiv [0x00D9F608]` sites remain, so this is a localized loop change rather
  than a global replacement.

The custom divisor `8` is not a BFME 2 address or a portable constant. It is a
value in Danetta's private section and must not be copied into the BFME 2
binary without a separately proven semantic and storage location.

## BFME 2 1.06 mapping

The BFME 2 baseline is fixed-base `0x00400000`; repository ledger addresses are
RVAs, so subtract `0x00400000` from the VA shown by a disassembler. The exact
Danetta byte signatures do not occur in BFME 2, but the surrounding instruction
sequence and the two global values do.

| target | Danetta VA | BFME 2 VA | BFME 2 repo RVA | evidence and status |
|---|---:|---:|---:|---|
| logic tick-rate value | `0x00D9F608` (`5`) | `0x00DBA4E4` (`5`) | `0x009BA4E4` | matching value and the divisor used by the analogue sequence |
| FPS value | `0x00D9F60C` (`30`) | `0x00DBA4E8` (`30`) | `0x009BA4E8` | matching value loaded immediately before `cdq` |
| animation helper start | `0x0063252F` | `0x00625D38` | `0x00225D38` | BFME 2 Ghidra boundary `FUN_00625d38`, 48 bytes |
| animation division helper edit | `0x00632535` | `0x00625D3E` | `0x00225D3E` | BFME 2 bytes begin `F7 3D E4 A4 DB 00 56 6A 06`; strong structural match |
| delay routine start | `0x006329B0` | `0x0062634F` | `0x0022634F` | prologue and control flow match; function boundary/identity still pending |
| delay/frame-loop edit | `0x00632A9B` | `0x0062643A` | `0x0022643A` | BFME 2 bytes begin `F7 3D E4 A4 DB 00 8B C8 83 F9 06`; strong edit-site analogue |

The BFME 2 delay sequence is:

```text
00626434  mov eax, [0x00DBA4E8]
00626439  cdq
0062643A  idiv dword ptr [0x00DBA4E4]
00626440  mov ecx, eax
00626442  cmp ecx, 6
00626445  jge 006264A2
00626447  lea eax, [edi-1]
0062645A  mov esi, eax
```

That makes `0x0022643A` the direct BFME 2 counterpart of Danetta's
`0x00632A9B`. It does not prove that the same replacement bytes are correct:
the original bytes must be guarded, the complete function boundary must be
confirmed, and the resulting behavior must be measured in the 1.06 process.

## BFME 1 comparison

BFME 1 supplies semantic and workflow evidence, not addresses to transplant.
Its already matched `GameEngine::update` is at RVA `0x0006E910` (392 bytes). The
FPS field is `GameEngine + 0x08`; the six simulation sub-step immediates are at
RVAs `0x0006E986` and `0x0006E9D9`. Its 5 Hz network quantum is documented at
RVA `0x00682074`, and its animation milliseconds-per-step global is VA
`0x012BB1CC` (retail value `33`). See BFME 1's `docs/fps60.md` and
`mods/features/037-fps60/src/fps60.cpp`.

That work established two constraints relevant here. Raising the logic rate
changes authored frame-based gameplay, and doubling simulation steps requires
an animation-clock correction; a higher render ceiling alone does not create
new simulation steps. It also established the repository practice of treating
the timing probes and patches as measured experiments rather than byte-match
conversions. The BFME 2 plan likewise defers a delay fix unless it improves on
the existing community fixes.

## Work order

1. Recover the 48-byte BFME 2 helper at RVA `0x00225D38` as ordinary C++ and
   verify its identity and bytes. Keep the `idiv` operand tied to the proven
   BFME 2 global at RVA `0x009BA4E4`.
2. Confirm the caller and true boundary of the delay routine around RVA
   `0x0022634F`; do not pin it from adjacency alone. If its body proves large,
   keep the helper work ahead of it as requested.
3. Treat RVA `0x0022643A` as an original-byte-guarded experiment only after the
   routine identity is settled. Measure logic cadence, animation clock,
   frame pacing, single-player behavior, and multiplayer/desync risk.
4. Keep any experimental payload separate from `Code/` conversions. A future
   implementation commit must use the normal `build.sh`/byte-verification and
   ledger workflow; this note intentionally changes neither ledger.

## Open questions

* The Danetta `.danetta` routine has not been shown to be live, so its SSE/float
  code is not treated as the source of the timing behavior.
* The BFME 2 delay routine's exact identity and end boundary are unresolved.
* The matching addresses show a structural analogue, not proof that Danetta's
  `eax = 2` or divisor `8` has the same meaning in BFME 2.
* No runtime patch or gameplay result is claimed by this documentation commit.
