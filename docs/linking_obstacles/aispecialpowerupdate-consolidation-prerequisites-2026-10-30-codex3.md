### AISpecialPowerUpdate consolidation prerequisites (2026-10-30, codex3)

The Update TU and its update donor now share their existing private class
contracts. Six rows byte-verify; external COMDAT digests, strong definitions
and undefined/weak/COMMON bindings are unchanged. Ordinary preview retains
LINKS, 199 and 211 authored bytes, against index `6fe1089c24`. This clears the
pair's declaration prerequisite only. Constructor/destructor/xfer base views,
post-init declarations and the map-load secondary interface still need separate
reconciliation before those donors can merge; the two mixed sources stay put.
[Target facts and remaining work](../../reverse/attempt_support/aispecialpower-consolidation-20261030-codex3.md).

The repaired pair is now composed by tu_skeleton: one source removed, the
0x004B327F row repointed into its approved TU, all six rows and exact parent
EH retained. Seven external COMDAT digests, five strong definitions and the
28 external dependencies equal the inputs' union; the merge link guard passes.
The broader outgoing audit remains INCONCLUSIVE: index 6fe1089c24 predates
base 8b26704cf8, and affected consumer Common/AIBuildable.cpp lacks a current
receipt. Carry the retired provider, surviving destination, earlier outgoing
providers and affected consumers into the next scheduled census. No census
gain is claimed; the other five donors and two mixed sources stay separate.
