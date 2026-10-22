# Local x86 compiler and scheduling probes

Inputs: BFME2 a649b275f7 plus the allocator-comment/evidence-only commit
5314e1e7f6; BFME1 37c3022de1ab944c7ffe536440d637dc8199091c. A read-only
export of those Git trees was also transferred to the guest's local disk.
Compiler: pinned MSVC 13.10.3077, cl.exe SHA256
`2ecf86a3edfd3deae498e08298e210e984537ce9e11759930561e43f40bd2515`.
Debian 12 amd64 runs in QEMU TCG on macOS arm64, with Wine 8 win32. A fresh
54-byte existing GeneralAllocator validator reproduced all retail bytes;
this runtime proof is not a new recovery. No gate was changed.

Private trials use the repository Scorer and separately inspect complete COFF
symbol extents with zh_sweep.carve. A target-sized slice is not extent proof.
The diagnostic drivers and their complete results are preserved here. Copy a
driver to build/ and run from the corresponding input snapshot with the pinned
reference and compiler. Scratch outputs live under build/.

## Shader Init: 0x0018C84E, 2333 bytes

The bank reproduces 2333 bytes, with zero unresolved calls after the existing
short-vector-family repair. Nine bytes differ in the known two-bone load-order
block. Target loads both links, then remap[link0] before remap[link1]; the bank
reverses the remap loads and associated register choices. All five new trials
stage the links and first result; four place _ReadWriteBarrier between remap
reads (unsigned/ushort index types, with/without cached remap base), one is a
no-fence control. They emit 2333..2342 bytes and do not improve the bank. The
barrier affects other live ranges/slots; it is not a local solution.

No production source or bank changed. Work stopped when refreshing shared
claims showed another worker owning the body. Newer master handoffs
fxinit-cost-20261022 and fxinit-schedule-20261022 supersede the older evidence
reviewed at the start; read them before any future retry. About eight minutes
of shader probes/review, model gpt-6.

## Debug reallocation: 0x006C4730, 798 bytes, RET12

Read all prior RVA verdicts, the entire bank, and the trailer copy-propagation,
materialization, attractor, header-lifetime and span-lifetime handoffs. The
unchanged bank emits 798 bytes, 18 differing fixed byte positions, confined to
the known backup-allocation trailer. Retail joins an integer size, computes
LEA(base+size-10) and stores through the resulting pointer. The bank joins
pointer values and folds the displacement into the store.

New tests: compiler fences after the end or trailer calculation, switch-based
pointer and named-size joins, integer-returning mapped/size accessors, and
2-/4-byte scaled pointer PHIs (division or shift). None closes the mismatch.
Fences give the unchanged 798-byte bank or the known 784-byte attractor;
switch-pointer gives 798 bytes with the branch polarity reversed (19 differing
positions); switch/named and accessor/named give the 814-byte attractor. Typed
pointer scaling gives 814/816 bytes, not the native trailer. The __restrict
control is rejected by the pinned compiler. Three signature/return controls
repeat earlier inert results and should not be retried.

Existing stronger bank remains unchanged. There is no new body to bank and no
Code/, ledger, pin, header or verifier edit. Prior independent control-flow,
layout, visibility and compiler-profile explanations remain applicable; the
unresolved issue is the compiler's address materialization versus caller
allocation tradeoff. About ten minutes of probes/review, model gpt-6.

## Superseded hero-list lead

A local template getter for the rank comparison reduced the 213-byte bank's
three-register rotation to an EBX/EDI swap. Other accessor combinations did
not improve it. During these trials master acquired the complete recovery in
bf19c4d903, so trials were stopped without replacing the bank or logging a
competing recovery. Read that landed source rather than resuming these trials.

## FESL field replacer: 0x00655B90, 549 bytes

All prior RVA verdicts, the complete bank and the field-replacer/volatile-tail
handoffs were read. The donor-loop plus previously established volatile tail
reproduces 549 bytes and the known EBX/EBP exchange (172 differing positions).
New ordinary pointer wrappers, implicit conversions, indexed wrappers, copy
operations and selective value accessors all emit the same body. Diagnostic
unions expressing the genuinely disjoint class-byte/value-pointer or tail-pointer
lifetimes likewise leave the body unchanged. No inactive union member is read;
these are lifetime diagnostics, not claims about original source structures.
The stronger existing bank is retained. Control flow, lifetime, type, visibility
and authenticated compiler-profile evidence remain exhausted; the register tie
has no new supported source solution. About five minutes, model gpt-6.

## Security cookie check: 0x00629BAB, 14 bytes

The complete manual ASM and all prior verdicts/contract results were read.
Ordinary C++ preserves the required EAX/EDX return contract here; the blocker
remains branch placement (JE/JMP/RET versus retail JNE/RET/JMP). New boolean
switch/default/case forms, XOR switch, a valid-flag loop, do/break, and an
explicit shared-return label were tested with ordinary and noreturn failure
contracts. No exact body: most retain the 14-byte mismatch; explicit cases grow
to 24/27 bytes, XOR is 15, and a returning failure in the valid loop is 20.
The latter's relocation beyond the row was correctly refused by the verifier.
The real ASM owner remains unchanged; no fake extent or alias is admitted.
About four minutes, model gpt-6.
