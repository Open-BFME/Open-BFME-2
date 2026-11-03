### Owning-return clone STLport 4.6 ABI (2026-10-30)

`Rva004E74A0Clone.cpp` now uses STLport 4.6. Its class-key return mangling,
EH-handler name and cleanup parent token agree with 4.6's `class auto_ptr`.
All four rows remain byte-exact; the parent EH graph is EXACT, and all seven
normalized COMDAT bodies plus undefined/weak bindings are unchanged. Strict
provider preparation passes; ordinary preview retains 73 -> 73 linked bytes
against index `85f6b7f40c`. The outgoing batch audit is **INCONCLUSIVE**:
the index predates the base, and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt in the prepared
worktree. Carry this provider, its class-key spellings and affected consumers
into the next scheduled census. No linked-byte gain is claimed.
[Evidence](../../reverse/attempt_support/stlport46-4e74a0-20261030-codexb5/README.md).
