# Real-link Libraries/Common handoff (halilkkaya-codex, 2026-11-04)

Codex wrote this session's nine commits on base `efb5fcbb60`. They landed
as `f0b43e499c` through `1fbd44eddc`. Seat halilkkaya-cx-o5 finished the
handoff on `20f35184b7`.

## resolved-symbols.tsv

These are the real-link error names that the landed commits remove. The
names come from the real-link artifacts at `612abfbebb` and `efbd3f2cb2`
(run 41825144174), which both list all eleven. `commit` is the landed SHA.
`required_followup` names a second commit the first one needs.
W6 (`ec9762d9dd`) is a retraction. `1fbd44eddc` readmits the correct
operation. No full-image result is claimed. A later scheduled real-link
run will measure these names.

## @_RTC_CheckStackVars@8 duplicate (LNK2005): blocked

Target facts:

- `vendor/msvc71crt/msvcrt.lib` member `..\build\intel\dll_obj\stack.obj`
  defines exactly two functions, each in its own `.text` section:
  `__RTC_CheckEsp` (35 B, one REL32 to `?_RTC_Failure@@YAXPAXH@Z`) and
  `@_RTC_CheckStackVars@8` (90 B, one REL32 to
  `?_RTC_StackFailure@@YAXPAXPBD@Z`).
- With every relocation site masked, both sections equal retail: 0x0075A5A2
  (35 B) and 0x0075A5C5 (90 B). Retail's REL32 targets are 0x0075A904 and
  0x0075AAD6. Both are rowed C++ in `Code/Libraries/Source/CRT/RtcError.cpp`.
- Row 0x0075A5A2 is the vendored archive member (`6fc1671ceb`). Row
  0x0075A5C5 is clean C++ in `Code/Libraries/Source/CRT/RtcStack.cpp`
  (`65164d38a3`). The real link pulls in stack.obj for `__RTC_CheckEsp`,
  and stack.obj brings a second strong `@_RTC_CheckStackVars@8` with it.
- Neither RVA has an approved TU in `reverse/tu_map.csv`.

Routes and why each is closed:

1. Attribute 0x0075A5C5 to the same stack.obj member and drop the C++
   body. `tools/conversion_gate.py` Rule B refuses this. A probe that staged
   only that ledger change printed "0x0075A5C5 (@_RTC_CheckStackVars@8)
   was clean C++ at Code/Libraries/Source/CRT/RtcStack.cpp, repointed to
   vendor/msvc71crt/msvcrt.lib" and exited 1. The probe was then reverted.
   `vendor/msvc71crt/PROVENANCE.txt` records the same policy.
2. Put `__RTC_CheckEsp` in RtcStack.cpp. Its entry reads the caller's ZF
   (`jne` first), so ordinary C++ cannot express it. A naked or `__asm`
   body under `Code/` is refused by Rule A.
3. Restore the MASM owner `Code/masm_dumps/RTC_CheckEsp.asm` from
   `ecbefd2e35` and repoint row 0x0075A5A2 to it. The conversion gate
   allows this (archive to assembly, and compiler machinery qualifies).
   Codex reports a focused no-FORCE, no-stub link at 0x20000000 that went
   from one duplicate to 0 unresolved and 0 duplicates. However, the row
   would move into a unit that is not the address's approved TU, and the
   file is a fresh one-function file. AGENTS.md forbids both. This needs an
   explicit owner or maintainer exception.

`rtc-restore-awaiting-approval.patch` is route 3. It applies with
`git apply --check` on `20f35184b7`. Its asm body is byte-identical to
`ecbefd2e35`'s file. It is review-only and has not been applied under `Code/`.

## ProductionPrerequisite.cpp `?freeBytes@AsciiString@@AAEXXZ`: blocked

Retail facts:

- The ledger rows 0x004EE1E2 (41 B) and 0x004EE20B (40 B) are spelled
  `__uninitialized_copy` / `__uninitialized_fill_n` over
  `ProductionPrerequisite::PrereqUnitRec`. Both call 0x004EE1A9, which is
  rowed `??0PerTurnStats@LivingWorldScoreKeeper@@QAE@ABV01@@Z`.
- 0x004EE233 (`_M_allocate_and_copy`, same PrereqUnitRec spelling) calls
  0x004EE1E2.
- `reverse/tu_map.csv` approves 0x004EE1A9..0x004EE233 for
  `Code/GameEngine/Source/Common/LivingWorldScoreKeeper.cpp`.
- `reverse/symbols.csv` pins the PrereqUnitRec spellings of both helpers to
  0x004F5097 / 0x004F50BD. Those addresses are rowed as
  `BfmeStringRecord002CF5B1` helpers.
- Inference: the PrereqUnitRec family is spelled in three different ways.

Trial (Codex, `re_log` 0x004EE1E2) and its result:

- Force BFME 2's AsciiString through `/FIzh_ascii.h`. This removes the
  Zero Hour `releaseBuffer`, so freeBytes goes away. But both helpers gain
  EH, because BFME 2's out-of-line `StringBase<char>` copy may throw.
- Adding `_STLP_NO_EXCEPTIONS` removes the EH, but the helpers then call
  `_Construct` and lose the native inline copy with its null checks.
- The other four rows stayed exact. The original 6/6 was restored.

Prerequisite: recover the two helpers (and 0x004EE233) as `PerTurnStats`
instantiations in the approved LivingWorldScoreKeeper TU. After that,
ProductionPrerequisite.cpp can take the canonical BFME 2 string.
