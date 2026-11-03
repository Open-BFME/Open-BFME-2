### Pointer-tree copy native clone binding (2026-10-29)

At base 7cce6ba90783, the 115-byte copy at 0x00603B9C now calls the existing
ModuleFactory tree clone owner at 0x00413E55 directly. All ten source rows,
its EH graph and the other 46 of 48 scoped bindings remain exact/unchanged;
the source retains its 747-byte LINKS preview against index 85f6b7f40c.
Debt retirement remains blocked on 231 missing ledger objects, three stale
providers and an unchanged base-constructor binding outside this source's
register. The second insert-helper trial is restored: the native State-tree
method is private, and VS2003 rejects the explicit __thiscall function-pointer
adapter (C4234). Its provider cohort also retains its existing selected-copy
blockers. Strict preparation verifies 19 caller/clone-provider rows; their
previews retain 747 and 1,029 bytes. The outgoing audit is INCONCLUSIVE on the
older index and missing receipt for Common/0CreateAHeroManager21FE49.cpp.
No census gain or register retirement is claimed. Carry that consumer and
the removed legacy clone copy into the next scheduled census.
[Proof and boundaries](../../reverse/attempt_support/uint-ptr-tree-identity-20261029-bce2/README.md).
