### LINK-597: particle factories emit placeholder names instead of retail export signatures
Status: Repair landed / awaiting verification. Updated: 2026-11-05; inspected revision: `d1c843526e`.
Evidence / completed: 27 exact exported factory signatures now compile, with 27/27 bodies byte-matched and 2/2 ordinary previews linking; duplicate first-factory row removed. [Checks and symbol audit](../../reverse/attempt_support/particle-factory-export-signatures-20261105/README.md).
Remaining / next check: the next scheduled real link must stop listing these 27 names for `ModuleTemplateFactorySlots.cpp` and `Rva003AD6DFCreate.cpp`; constructor identity recovery remains separate.
Clearance / census confirmation: pending real-link verification; no census gain claimed.
