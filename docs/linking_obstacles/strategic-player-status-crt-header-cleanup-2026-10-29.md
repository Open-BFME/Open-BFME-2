### Strategic player status CRT header cleanup (2026-10-29)

Scoped cleanup verified at base `8f350110e4`: replacing the two local CRT
declarations with stdio.h preserves 7/7 rows, four literals and two named
imports. The header auditor reports clean and retires two queue findings;
strict preparation passes. Ordinary preview retains LINKS for 684 authored
bytes against index `840db2d676`. The outgoing audit remains INCONCLUSIVE:
the index predates the base and Common/0CreateAHeroManager21FE49.cpp lacks
a current consumer receipt. Carry that consumer and the changed provider
into the next scheduled census. No census gain or full consumer closure is
claimed. [Evidence](../../reverse/attempt_support/strategic-player-stdio-20261029-codex.md).

GettingBuiltBehavior list-node identity repair (2026-10-29, base `8468a420d3`):
the push-back helper at `0x00453B06` now forwards node creation to the existing
28-byte record-node owner at `0x004534A1`. Its emitted insert is a byte-and-
relocation fold of retail `0x00453AB8`; the owning tool retires one identity
key. All 24 rows and the caller EH graph remain exact; helper, provider and
transfer caller retain LINKS for 2,308 authored bytes against index
`840db2d676`. The legacy template identity and caller alias remain, and full
consumer/census confirmation is pending. Carry this provider/caller scope into
the next normal census; no census-linked-byte gain is claimed.
The outgoing audit is INCONCLUSIVE: its index predates the base and affected
consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt.
[Evidence and rejected alternatives](../../reverse/attempt_support/gettingbuilt-list-identity-20261029-codex3.md).
