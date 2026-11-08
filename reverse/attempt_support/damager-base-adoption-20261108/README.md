# Damager constructor base adoption, 2026-11-08

Rva00588FFAFinish.cpp replaces its private registered BehaviorModule copy
with the canonical header. Its existing constructor-only Rva00588FFA view
uses `__declspec(novtable)` to retain native construction-table stores.
This follows [method 2](../../../docs/linking_obstacles/rows-that-do-not-need-their-class-2026-11-04.md):
the real base supplies inherited polymorphism while explicit matched stores
retain construction state until the complete class is recovered.

The constructor calls BehaviorModule first, then installs the same intermediate
two-pure-slot interface table, clears +0x14, and installs the same primary and
secondary tables. There is no virtual call between base construction and those
stores; the existing barrier is intrinsic. The base remains 0x10 bytes with
two words at +0x10/+0x14, compatible with the existing PillageModule caller's
0x18-byte base view. The annotation is scoped to this view; no original
inheritance hierarchy or complete interface recovery is claimed.

Normal verification passes the complete 53-byte constructor and both data rows:
8 bytes/two pure-call relocations and 48 bytes/twelve relocations. The source
is unfrozen and has no EH rows. The private candidate also passes 1/1 with
unchanged COMDAT facts, no added/removed provider and a clean LinkGuard.
Supported header acceptance passes and retires exactly one BehaviorModule
queue row; strict source preparation passes. Ordinary preview remains
LINKS/52 authored bytes against d171e84869 (2026-11-08 15:35).

The served strong-definition refusal is still open. Both complete manual arrays
are retained. The two-slot table at 0x0086FFFC is folded with many unrelated
interfaces, so its address alone does not identify an interface class. The
primary table at 0x008700C4 connects slot 2 to the six-byte getter at 0x0058902F,
which returns the literal "DamagerModule" at VA 0x00C700F4. `data-proof.json`
records that runtime-name lead separately from the verified array contents.
No name, donor path, data owner, compiler flag, pin or gate changes here.

Next: recover the complete DamagerModule class and its actual +0x10 interface,
reconcile the destructor/xfer/getter owners, and replace both manual arrays
with matching compiler tables. Preserve the native store order and Pillage
caller throughout. Current-image provider selection and runtime verification
remain pending; this prerequisite does not retire a bridge or prove the game runs.

Published as d2cd5a68d5; first attempt landed in45.9 seconds. Required
byte/data/EH/scoped-DIR32 checks pass after rebase. Broader batch audit remains
INCONCLUSIVE: index d171e84869 versus outgoing base
a296f17cfaa3547c81b66793d006906def90a824, affected
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Preserve that
consumer for the next census/image verification; no broader link clearance.
