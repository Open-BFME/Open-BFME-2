# Retire stale forward-range string identity keys

Inspected upstream `fce2c6327a`, with verified BFME 1 reference `f633d0e97a`.
The default identity queue served BfmeConv1486.cpp at RVA 0x0002A730.
The complete source already calls the recovered owner at 0x00028820,
`Rva008314E0String::insertRange`, with its existing tag-reference ABI.
The old `bfmeImplV44` binding survives only in the debt register and legacy
pin, not in this source's call. No source, pin or function row is changed.

The earlier [caller repair](string-forward-owner-link-20261020/readme.md)
and [insertion recovery](string28820-recovery-20261020/readme.md) were read.
Their older paths and provider limitations are historical evidence, not a
new claim about the current provider's closure.

## BfmeConv1486.cpp

- The full source and prior verdicts were inspected; its frozen-file check
  passes. Normal byte/reference verification preserves its one 285-byte row.
- The initial retirement refused because the latest upstream consolidation
  introduced two ledger sources whose local objects were missing. Normal
  `build.sh` for MoneyCrateCollide.cpp and HealContain.cpp passes all three
  rows and supplies those objects; neither source is edited here.
- With that prerequisite repaired, `repair_queue.py retire identity` passes,
  retires the one old `bfmeImplV44` key and reports zero remaining findings
  for this source. The register is changed only by its owning tool.
- The committed census already lists this caller as linked. Its existing
  inline-assembly wrapper is retained; this is stale-debt retirement, not a
  C++ conversion, new body recovery or new linked-byte gain.

One identity key is retired. Shared insertion-provider closure and the
remaining string family are separate work.
