### Hero-select CRT allocation declarations (2026-10-29, codexb4)

Status: conflicting local `free` declaration replaced by the toolchain's
`malloc.h`, with `_CRTIMP` configured locally to preserve the game allocator
binding. The preceding `stdlib.h` still supplies imported parser calls.
Simply deleting the declaration byte-matches the rows but changes four
container COMDATs from `_free` to `__imp__free`, breaking link selection;
that attempt was reverted before this header configuration was verified.

`InGameHeroSelectInterface.cpp` preserves all 31 rows, all 97 COMDAT
digests/sizes, external symbol sets and relocation/dependency names against
its pre-cleanup object. The strict current receipt passes; ordinary preview
reports LINKS, 4,872 -> 4,872 authored bytes against index `840db2d676`
(2026-10-28 20:44). The scoped Microsoft-header queue refresh removes the
`free:abi` finding; the existing static `floorf` declaration remains to keep
the header inline local. No census gain or ownership improvement is claimed.

Post-rebase batch audit: INCONCLUSIVE. Index `840db2d676` predates the outgoing
base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and this provider into the next scheduled census;
the clean ordinary preview and unchanged object facts establish only the
scoped result above. Rebased verification again passes all 31 rows and LINKS
4,872 -> 4,872 bytes.


2026-11-05 follow-up: The token-identical outer InGameHeroSelectInterface view cannot be adopted alone in three further units. The header also supplies the nested Impl already defined by those units. All trials were restored. [Native trial and prerequisite](../../reverse/attempt_support/header-composition-prerequisites-up-to-hundred-each-20261105-1425.md).
