### Holder placement-new header cleanup (2026-10-29)

At base `d17e3dcdeb82`, the real Microsoft `<new>` replaces the local placement
allocator in `Rva004F6B69Construct.cpp`. The called leaf copy constructor's
nonthrowing contract is declared in both units, preserving both complete rows
and all COMDAT/external object facts. Strict preparation passes; both previews
retain LINKS for 50 existing authored bytes against index `85f6b7f40c`. The
owning header auditor removes one queue finding. The outgoing audit remains
INCONCLUSIVE on the older index and a missing current CreateAHeroManager
consumer receipt; full consumer and census confirmation remain pending. No
census gain is claimed. [Evidence and failed direct substitution](../../reverse/attempt_support/holder-placement-new-header-20261029-codex4.md).
