# PolygonTrigger parser-binding lifetime and table prerequisites

Inspected 2026-11-12, base `e18ea1c5251`. Served table:
`??_7Rva002E3DE3@@6B@`, RVA `0x00804C04`, in
`GameLogic/Map/PolygonTrigger.cpp`. Native slots are the deleting destructor
at `0x0041E6F3` and parser callback at `0x002E41EC`.

## Registration lifetime

Constructor `0x002E3DE3` calls the rowed `Rva002E3D7B` constructor at
`0x002E3D7B`, then installs this derived table and the head pointer at +0x10.
The base constructor registers its input/token at +4/+8 and owner at +0x0C.
Its native table at `0x00804BFC` shares the deleting-destructor slot with
the derived table. That 28-byte wrapper calls the existing 18-byte cleanup
at `0x003B241A`, rowed as `BfmeParserBindingBaseVE::~BfmeParserBindingBaseVE`.
The complete cleanup restores table `0x007C9574`, unregisters token +8 through
the input at +4, and returns.

Replace the local base's undefined destructor with that actual registration
cleanup, retaining a partial class view and the established 16-byte size.
An empty, out-of-line derived destructor compiles to the same 18-byte lifetime.
Its scalar deleting destructor reproduces the native 28-byte wrapper. The
three natural compiler-emitted names are admitted individually through
`add_match.py --icf-owner`, backed by the original providers. These are
byte-and-relocation twins, not additional retail ranges or original-name claims.
No pin or alternate name is added.

Private trials of an ordinary forwarding destructor and a novtable forwarding
destructor failed to reproduce the complete cleanup; neither trial was applied.
The accepted lifetime checks the actual table and unregister callee, without
masked-callee fallback. The deleting-target reservation was initially held;
it became claimable and was acquired before admission.

Normal `./build.sh` passes all 29 code rows and the existing data row, including
the source's string, float and four named-import checks. Frozen-file checks are
clear. A scoped strict preparation before the final wrapper admission verified
the source and original cleanup provider; ordinary preview retained LINKS for
999 authored bytes against index `aa7acf764d` (2026-11-12 19:19). That index
warns of four unrelated source-path changes. Full-source verification and
normal hooks still run after final admission.

The first local commit's shadow identity check exposed a second, five-byte
`Rva002E3D7B` destructor emitted implicitly by `Rva000AEFAA.cpp`. Before any
publication, that constructor view is corrected to declare the existing
out-of-line destructor. Private verification preserves all 30 rows and every
retained COMDAT in that source, removes exactly its obsolete destructor copy,
and adds none. The correct 18-byte definition in PolygonTrigger.cpp is then
the shared provider. Normal verification covers both sources together.

## Remaining table work: naming-tool refusal

The source still lacks the parser callback in slot 1. Its existing body is
`Rva002E41EC::rva002E41EC(void *, void *)` at `0x002E41EC`, 64 bytes, in
`Common/GapBodiesS3H.cpp`. The supported `rename.py function --to-class` dry run
refuses because the old signature ends in `PAX0`: "its parameters name a type
by back-reference; a class move would change what they refer to". Here `0`
repeats the first `void *` parameter, not the enclosing class. The proposed
new decoration is `?rva002E41EC@Rva002E3DE3@@UAE_NPAX0@Z`.

The [unapplied complete patch](polygon-parser-callback-20261112.patch) prepares
both source views and retargets the existing friend declaration in
`PolygonTrigger.h`. Private compilation preserves both files' covered ranges,
including the complete 64-byte callback; the two-slot table is eight bytes with
the verified deleting wrapper and new callback name. A bounded two-object
`vtable_bridge.plan` reports zero bridges, zero refusals and one already-correct
table. This private trial uses an isolated header copy for the friend change;
it is not normal verification or acceptance of a source/header mutation.

No callback/header edit is applied and no check is worked around. A
`false-reject rename.py --to-class` blocked record names the exact refusal.
The tooling lane must decode the parameter back-reference safely, with a
regression test and a separate verifier-change commit, before this move retries.
Neither a private alias nor a new pin is needed.
Only a later real-link receipt can satisfy the picker's published-queue pass
test. This lifetime prerequisite alone does not clear the bridge.

## Previous publication follow-up

The immediately preceding FESL binding repair landed as `e18ea1c5251`. Its final
batch audit remained INCONCLUSIVE because
`Common/FamilyDeletingDtors12.cpp` lacks a current consumer receipt, against the
older index. Carry that consumer and the repaired FESL callee into the next
normal census; its two own previews and identity retirement passed.
