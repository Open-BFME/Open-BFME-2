### Object upgrade canonical Module lookup view (2026-10-30)

Cleared for `ObjectUpdateUpgradeModules.cpp`: the full 0x00395708 helper and
Object::findModule return an unadjusted Module pointer; the caller reads its
ObjectID at +0x14. Use the canonical base plus partial storage for that field,
retaining the legacy label without claiming its original semantic name.
All four rows and five code definitions/relocations remain exact. The owning
acceptance tool retires one key; preview preserves LINKS/360 bytes against
`ccafe54d1d`, with no census gain. Other behavior/interface contracts stay open.
[Receiver proof and current object](../../reverse/attempt_support/module-object-upgrade-id-20261030/README.md).
