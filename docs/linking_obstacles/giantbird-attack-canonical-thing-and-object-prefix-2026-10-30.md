### GiantBird attack canonical Thing and Object prefix (2026-10-30)

Cleared for the remaining Thing key in `AIGiantBirdAttackStateOnEnter.cpp`:
the current header already declares the native Thing::getDrawable owner.
Adopt its +0x60 base, remove Object's overlapping position/padding and preserve
position+0x38, transform+8, ID+0x74 and later fields. All six rows, EH and the
30 retained external code definitions/relocations stay exact. The sole added
compiler iterator is the complete native 34-byte ATL owner at 0x00001423,
referenced only by debug information. The owning acceptance tool retires one
Thing key; preview retains LINKS/1,359 bytes against `ccafe54d1d`. No census
gain is claimed. getContain's unchanged shadow finding and broader consumer
receipt/census prerequisites remain open.
[Layout reconciliation and compiler-helper proof](../../reverse/attempt_support/thing-giantbird-object-prefix-20261030/README.md).
