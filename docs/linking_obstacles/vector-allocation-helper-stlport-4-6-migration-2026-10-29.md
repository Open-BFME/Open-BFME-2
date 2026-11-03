### Vector allocation helper STLport 4.6 migration (2026-10-29)

At base `a1d5808a6c`, Rva00568D68AllocateCopy.cpp replaces its private tag
with STLport 4.6's declaration and leaves the migration queue. Default
initialization preserves its exact 45-byte row and both external references;
the obsolete tag constructor COMDAT disappears. Strict preparation passes and
preview retains LINKS 45 -> 45 against `85f6b7f40c`. The outgoing audit is
INCONCLUSIVE on the older index and missing current CreateAHeroManager
consumer receipt. Carry that consumer/provider scope into the next scheduled
census; no census gain is claimed. The allocator/vector owner views still need
reconciliation. [Checks and trial](../../reverse/attempt_support/allocatecopy-stlport46-20261029-codex.md).
