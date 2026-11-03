### Allocator lock wrapper SDK declarations (2026-10-30)

At base `335b60649d17`, Rva00035080Finish.cpp replaces two local critical-section
API declarations with the VS2003 Platform SDK and leaves the Microsoft-header
queue through the owning auditor. `/EHsc` preserves their original
nonthrowing C contract. The 120-byte row, both imports, the EXACT EH graph,
all three external COMDAT fingerprints and the object-reference graph are
preserved. Strict preparation passes; preview retains LINKS 119 -> 119 authored
bytes against `85f6b7f40c`. The staged audit is INCONCLUSIVE on that older
index and the missing current Common/0CreateAHeroManager21FE49.cpp consumer
receipt. Carry this wrapper and consumer into the next scheduled census;
broader confirmation remains pending. No census gain is claimed.
[Checks and scope](../../reverse/attempt_support/allocator-lock-msheaders-20261030-codexb5.md).
