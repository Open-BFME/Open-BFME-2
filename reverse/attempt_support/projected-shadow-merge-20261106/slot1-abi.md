# Shadow-family slot 1 ABI, bounded read-only pass, 2026-11-06

Current owner fold `fc7590d725`, constructor/base cleanup `88ce76fc44`.
No builds, Code/ledger edits, claims, publication, network or child workers.
Only retail, current non-decoder project sources and narrow current ledger
filters were examined. No VP6 decoder material was read.

## Result

No actual indirect caller tied to the projected-shadow owner was found within
the bounded scopes below. There is useful **target sibling-slot evidence** for
a no-stack-argument update hook; there is not yet a demonstrated caller whose
return-value use proves the empty BCF9E0 slot's return type. Do not represent
this pass as full slot-1 ABI clearance or as permission to borrow an unrelated
B3FD0 member.

## Target facts

Retail's three-word tables (words shown as code RVAs) are:

| Table VA | Extent | Slot 0 RVA | Slot 1 RVA | Slot 2 RVA |
| --- | --- | --- | --- | --- |
| BCEFA0 | 12 bytes, to BCEFAC | EFAD2 | B3FD0 | 3B810 (__purecall) |
| BCEFC8 | 12 bytes, to BCEFD4 | F2B81 | **F42F7** | F168B |
| BCF9E0 | 12 bytes, to BCF9EC | 10BA45 | **B3FD0** | 109DA6 |
| BCF9F4 | 12 bytes, to BCFA00 | 10B9C9 | **B3FD0** | 10BB04 |

Those ends are not inferred merely from data_ledger upper bounds. BCEFAC is
an independently installed VectorClass table: constructor F0D2F stores it at
instruction F0D46 (immediate F0D48); its deleting destructor F1CF7 also stores
it. BCEFD4 is independently installed by constructor F1B37 at instruction
F1B57 (immediate F1B59), and destructor F1B8F likewise stores it. BCFA00 is
independently installed by Rva00109610 constructor 10BA71 at instruction
10BA79 (immediate 10BA7B), and destructor 109610 likewise stores it. Thus the
following code-pointer runs belong to separate native tables. BCF9E0's
fourth/fifth words at BCF9EC/BCF9F0 are the float bit patterns C04CCCCD /
404CCCCD (-3.2/+3.2); they are not slots. The corresponding raw VA words are:

    BCEFA0: 004EFAD2 004B3FD0 0043B810
    BCEFC8: 004F2B81 004F42F7 004F168B
    BCF9E0: 0050BA45 004B3FD0 00509DA6
    BCF9F4: 0050B9C9 004B3FD0 0050BB04

### Independently shared native base constructor

This relationship is stronger than ICF-table similarity. Both constructors
directly call **the same F0F2B body on their original receiver**:

    F1535: mov esi,ecx
    F153B: call 4F0F2B      ; within W3DVolumetricShadow ctor F1528/355

    10BA2D: mov esi,ecx
    10BA2F: call 4F0F2B     ; within owner ctor 10BA2C/25

F1528 is the rowed `??0W3DVolumetricShadow@@QAE@XZ`; 10BA2C is now rowed
`??0Rva007AFF00Owner@@QAE@XZ`. F0F2B constructs the measured 0x68-byte base
over the 0x58-byte prefix and installs BCEFA0. This supplies direct target
base-construction evidence for comparing BCEFC8 and BCF9E0's slot-1
interfaces, without renaming two classes merely because their tables fold.

BCEFC8's nonempty slot 1 is already rowed as
`Rva000F42F7Host::rva000F42F7()` (8 bytes) in
`Code/GameEngine/Source/Common/VslotMiscForwarders.cpp`. Actual retail bytes:

    RVA F42F7: push 1
    RVA F42F9: call 4F4017          ; callee RVA F4017
    RVA F42FE: ret

The receiver remains ECX. This entry consumes **no stack arguments of its
own** and supplies the one true argument to the existing 736-byte body at
F4017, whose exact current ledger spelling is
`?Update@W3DVolumetricShadow@@QAEX_N@Z`: public, nonvirtual `__thiscall`,
return `void`, one `bool` parameter. Its source is
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowUpdate.cpp`,
declared/defined as `void Update(Bool forceUpdate)` with `Bool = bool`.
The existing forwarding source likewise declares a void no-argument member.
The current ledger notes explicitly distinguish its BFME1/ZH donor lead from
the byte-verified BFME2 body and target +4900 force flag. Its effect is a real
same-family forced-update lead, not a donor-only hypothesis. The eight-byte
wrapper alone does not independently prove a C++ void return: it leaves EAX
as the callee left it. An actual caller ignoring/using the result remains the
stronger requested evidence.

Native B3FD0 is a one-byte plain RET, with no immediate stack cleanup or
explicit EAX result. The identical index across the shadow-prefix tables and
the nonempty volumetric override corroborate a shared interface position.
They do not prove that the address-named classes with ICF-shared BCEFA0 are
one class, establish an original member name, or identify which unrelated
B3FD0 ledger alias should be reassigned. No naming proposal is made.

## Exact bounded caller search

Retail bytes were decoded with Capstone at each current matched row's native
start, using a streaming narrow filter of functions.csv (never loading it
wholesale). Duplicate (RVA,size) pairs were removed per scope.

1. All rows whose source is under
   `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/`:
   **364 distinct rows / 62,104 bytes**. No indirect CALL/JMP memory operand
   `[non-stack-register+4]` was found.
2. W3DModelDraw named members or W3DModelDraw-prefixed sources, plus row starts
   in the immediate native consumer interval **B1C00..B3FBF**:
   **273 rows / 28,515 bytes**. Three `[register+4]` indirect calls occur at
   **B1E0D, B1E53, B1E97**, all in W3DDebrisDraw::xfer at B1DC3. Their
   receivers are Xfer/state objects or a member at this+0xC; the first two
   test AL. They are not the shadow receiver at model-draw+0x58 and are not
   evidence for this slot. The rowed ModelDraw releaseShadows B2E14 source
   independently identifies shadow+0x58 and its release slot 2.
3. The union, **637 rows / 90,619 bytes**, was also checked for
   `mov functionReg,[non-stack-register+4]` followed within eight instructions
   by CALL/JMP through that same register before a clobber/other branch.
   **No such candidate was found.**

Contexts and scope counts are retained in
`build/projected-shadow-slot1-abi-20261106.json`. Searches are bounded native
instruction patterns, not proof of globally exhaustive call-graph coverage.
Unknown consumers outside these rows, alternate table-address arithmetic,
longer register propagation, and unavailable/unrowed source identities remain
outside the pass. No broad whole-image call sweep was run.

## Next evidence boundary

The direct common-base calls plus the existing void-no-argument forwarding
declaration make **a void/no-argument shared update hook a supported ABI
inference**, stronger than the empty RET alone. The inference does not prove
an original method name, nor does it assign an unrelated B3FD0 ledger owner
to this family. It is not an observed caller-return-use proof.

The concrete next lead is a caller of the **F42F7/BCEFC8 slot-1 interface**,
or another independently identified shadow receiver dispatching through +4,
with argument setup and post-call EAX/AL use inspected. The existing
F42F7 -> Update(true) wrapper is appropriate corroboration for that work.
Until such a receiver/caller or equivalent class/interface evidence is found,
keep the empty slot's signature/inheritance qualification explicit. No new
pin, alias, copied empty method or reassigned ICF owner is justified here.
