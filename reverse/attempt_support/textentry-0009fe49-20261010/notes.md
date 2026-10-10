# drawTextEntryText: 149 source variants

This is an unsuccessful full-byte recovery attempt with an improved bank.
No matched rows, pins, production sources, or linking results were added.

The target is `?drawTextEntryText@@YAXPAVGameWindow@@HHHHHH@Z` at
`0x0009FE49`, size **1,398 bytes**. The Ghidra inventory records that entry
and size; the native return ends immediately before the already matched
`W3DGadgetTextEntryDraw` at `0x000A03BF`. The target's two matched text-entry
callbacks and its existing seven-argument symbol pin support the identity
and calling convention. The private class layouts are inherited target
reconstruction views, not newly established canonical class contracts.

The prior bank was already attempted repeatedly (see `re_attempts.log`,
including the 2026-10-10 score `0.9737465417522531`). The Zero Hour
`GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DTextEntry.cpp`
supplies the text/IME drawing purpose, but its helper lacks this target's
selection implementation and has a different argument list. Its source is
a semantic lead, not proof of the target's offsets or instruction sequence.
The BFME 1 helper's recorded seven-versus-ten-argument ABI discrepancy also
precludes importing its existing declaration as evidence for BFME 2.

Work used a separate worktree at BFME 2
`65ea26e095d5bead63396e2054cb389c4a29ecac`. Existing BFME 1 files at
`575ba2b04743f190f069805fbdc59936123c45da` supplied the toolchain through
local child symlinks; no submodule clone, recursion, update, or pointer
change was performed. All experiments used the repository's
`build.try_compile_source` with isolated `build/` outputs, followed by the
ordinary relocation resolver. No speculative symbol mappings were supplied.

## Experiments

`trials.json` preserves **151 distinct source snapshots**: baseline 0,
149 variants 1–149, and cleaned-bank validation 150. Exactly 150 compiled;
trial 48 failed because a volatile reference made the `max` template's
argument deduction ambiguous. Each snapshot has its hash, source delta,
description, emitted size, diagnostic score, and result. Overlong emitted
bodies were compared in full, not truncated to the claimed extent.

| Trials | Hypothesis |
| --- | --- |
| 1–12 | First endpoint/cursor store order and common-value assignment |
| 13–22 | Selection x memory accesses and nested composition lifetime |
| 23–46 | Temporary/reference/const endpoint forms with or without the inherited volatile cursor read |
| 47–50 | Selection-local x references and scope |
| 51–66 | Move the selective cursor memory access to an actual store or argument |
| 67–71 | Combine nested composition memory access with first-block stores |
| 72–82 | Scheduling, optimization, inlining, frame-pointer and floating-point compiler controls |
| 83–110 | Combine the improved trial 59 with endpoint and selection changes |
| 111–122 | Read/write compiler barriers at the observed differing stores |
| 123–149 | Combine trial 118 with common sums, operand order and nested-update barriers |
| 150 | Clean comments/formatting and recompile the selected bank |

The best body (118, then cleaned 150) still emits 1,398 bytes with no
unresolved calls. Its `permute.fitness` diagnostic improves from
**0.9737465417522531 to 0.9832740490862433**. This weighted instruction/byte
similarity is not a percentage of verified bytes. All candidates remain
nonexact. In particular, the resolver copies DIR32 addresses at candidate
offsets; when preceding instructions shift, those diagnostic operands can
become nonsense until the instruction alignment is repaired. The score
does not establish data identity or relax any gate.

The retained changes are a volatile store of the initialized initial
cursor position, a volatile read of initialized x in the nested composition
draw argument, and a `_WriteBarrier` after the selection x update. The
previous bank's volatile final cursor-rectangle read is removed. These
changes add no calls or runtime barrier instructions and preserve the
target-supported rendering/control flow.

## Remaining differences

The first differing byte is `+0x222` (`0x000A006B`): a conditional jump's
displacement is one byte longer because of the endpoint reload sequence.
At retail `0x000A00B5`, the expected sequence is:

```asm
mov eax, [ebp-24h]
mov [ebp+1Ch], eax
mov [ebp-10h], eax
mov edi, eax
```

The best candidate instead loads EDI from `[ebp-28h]` before loading EAX
from `[ebp-24h]`, then stores x through EDI. Both temporaries contain the
endpoint, but their separate compiler lifetimes survive the call.

At retail `0x000A0259`, x is restored through EAX into its argument home;
the candidate restores it through EDI. Retail's nested composition tail
uses `add [ebp+1Ch], eax` and reloads EDI at the branch join `0x000A02C1`;
the candidate adds directly to EDI and stores it back. The barrier fixes
the relative scheduling of the selection store and comparison, but does
not fix this allocation/lifetime difference. A subsequent attempt should
target that shared lifetime cause rather than repeat the recorded variants.

## Reproduction

From the repository root, with the pinned inputs and MSVC 7.1 available:

```sh
python3 reverse/attempt_support/textentry-0009fe49-20261010/replay.py --all --materialize-only
python3 reverse/attempt_support/textentry-0009fe49-20261010/replay.py
python3 reverse/attempt_support/textentry-0009fe49-20261010/replay.py 59 118
```

The first command checks and materializes every exact source snapshot.
The second recompiles baseline and final bank and checks recorded size,
score, unresolved calls and nonexact verdict. `--all` without
`--materialize-only` recompiles every experiment. Outputs stay in
`build/textentry-replay/`. An exact diagnostic result would still require
the normal identity, class, relocation/data, and full-byte admission gates.
