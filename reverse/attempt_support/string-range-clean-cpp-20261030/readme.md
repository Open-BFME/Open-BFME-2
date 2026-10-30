# Native range replacement recovered as clean C++

Base: 574175bb6d1dce614713b1457770bc4b09db7122. Model GPT-6;
main body t=14 minutes, lane=R, budget=30m. The insert provider prerequisite
was investigated in the same claimed pair of sources (about five minutes).
Both file claims were confirmed by origin before edits.

## Target facts and verified change

The existing 279-byte `BfmeStrV24::bfmeReplaceV24` at 0x0002A610 now uses
clean C++ in its current approved owner, `Common/BfmeS1155.cpp`. It replaces
the register-by-register inline-asm lift and its 208-byte artificial padding.
The ledger name, RVA, extent, source path, calling convention and unused
fifth stack argument are retained. The native three-pointer string storage
is supplied by the existing STLport base; redundant opaque fields are removed.
All twelve owner rows still match. No row or pin is added, and no name or
external donor source identity is inferred from the byte match.

The clean body follows the banked 2026-10-24 C++ attempt, adapted to the
current merged owner, which already includes the real string header. The
local copy support preserves the bank's length calculation and forced-inline
POD dispatch. With the current header helpers alone the frame is 0xc4;
with that semantic copy structure it is retail's 0xd4. The final object
uses the existing native erase owner at 0x00012150 rather than defining an
incorrect new copy of the old placeholder erase. The existing character
assignment binding remains at 0x00013270. No compiler flag/header change,
pragma optimization, new pin, alias, naked body or raw byte emission is used.

The insert owner `STLport/Rva008312E0StringReplace.cpp` marks its existing
848-byte insertRange as `__declspec(noinline) inline`. Plain inline was the
previous frame-changing failure. This spelling preserves both existing row
bodies while replacing the old strong non-COMDAT definition with SELECT_ANY.
The clean owner emits an ordinary inline copy, also SELECT_ANY. Its earlier
native insert owner is therefore retained without the old duplicate-provider
conflict. The complete native insert body is unchanged.

## Verification and limits

`before-build.log` and `after-build.log` each pass all 14 existing rows and
two named imports, using serial ordinary builds. The independent COFF proof
compares the actual copied before/after objects: every one of the fourteen
raw row bodies is identical, and the sole row-relocation change replaces the
old erase spelling with its already-rowed real STLport spelling. The proof
bounds relocation comparison to each ledger extent; the old strong section
also held a following function. COFF selections are recorded directly:
range owner 0 (strong, non-COMDAT) -> 2 (ANY), new owner copy 2 (ANY).

Strict preparation verifies all 18 rows across the changed pair and the
four other current direct insert callers: BfmeConv1429, BfmeConv1436,
BfmeConv1496 and BfmeConv1500. Frozen-file checks pass. The six-object preview
against index 85f6b7f40c preserves all five previously linking sources and
2,070 authored bytes, including BfmeS1155's 1,532 bytes. No linking gain or
new unique matched coverage is claimed; the census/index/status are unchanged.

The range owner's separate replaceBase copy still has its old wrong-selected
finding and remains at zero preview-linked bytes. The grouping/owner identity
prerequisite in LINK-006 is not cleared. This change removes the previously
reported insert strong-definition obstacle and recovers one real C++ body;
it does not certify a complete string-family link or whole-image closure.
Carry the provider/consumer selection scope into the next scheduled census.
The outgoing batch audit must still judge the wider affected scope.

Earlier evidence: [banked C++](../rva008312e0-replacebase-link-20261024/handoff.md)
and [previous link-order boundary](../rva008312e0-replacebase-linkorder-20261028.md).

## Outgoing consumer audit

The explicit six-source audit after commit 7a68deb41c exits 2. Its index
85f6b7f40c predates the outgoing base, and the first wider affected consumer
without a strict current receipt is Common/0CreateAHeroManager21FE49.cpp.
This does not establish complete consumer selection preservation or absence
of linking losses. The 18-row strict cohort and unchanged 2,070-byte preview
remain the bounded evidence. Carry this provider and affected-consumer scope
into the next scheduled census. No census runner was started.
