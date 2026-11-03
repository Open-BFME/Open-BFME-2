### GameLogic registerObject module-header adoption (2026-10-30)

At base `3d899e6ebe`, registerObject adopts the existing ObjectModule and
BehaviorModule headers. The phase virtual moves from its private ObjectModule
view to UpdateModule slot 12 with the existing ledger signature. All 203 bytes,
five external COMDAT fingerprints and external symbol records remain exact or
unchanged. The owning header tool retires one ObjectModule queue row; strict
preparation passes and preview retains LINKS, 203 -> 203 against `85f6b7f40c`.
The separate GameLogic header entry still needs its list tail, update vectors
and lookup method. The staged audit is INCONCLUSIVE on the older index and
missing current receipt for affected CreateAHeroManager consumer. Carry that
consumer/provider scope into the next scheduled census; no census gain or
complete consumer closure is claimed.
[Target facts and checks](../../reverse/attempt_support/registerobject-module-header-20261030-codex.md).
