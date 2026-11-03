### Pathfinder CRT header declarations (2026-10-30)

At base `5b3d2ce4c4`, pathfinder.cpp replaces four handwritten CRT declarations
with toolchain headers and uses `FILE *` for logging. Scoped `_CRTIMP`
configuration preserves direct fprintf and imported floor bindings. All
120 function rows, the data row and 14 EXACT EH graphs pass; all 580 COMDAT
fingerprints, 782 external symbol records and relocation reference graphs
remain identical. Strict preparation passes and ordinary preview retains
LINKS and 50,353 authored bytes against index `12b9e7a7c0` (10:11).
The owning scanner refreshes five actionable local findings to two; the
game allocator macro and LINK-133's local floorf prerequisite remain.

The staged-tree audit is INCONCLUSIVE on that older index and the missing
current `Common/0CreateAHeroManager21FE49.cpp` consumer receipt. Carry this
provider and wider consumers into the next scheduled census; full consumer
selection/loss checks remain pending. No census gain is claimed.
[Bindings, remaining prerequisites and verification](../../reverse/attempt_support/pathfinder-crt-headers-20261030-codexb.md).
