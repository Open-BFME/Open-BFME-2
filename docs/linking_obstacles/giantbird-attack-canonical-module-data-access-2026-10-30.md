### GiantBird attack canonical Module data access (2026-10-30)

Cleared for `AIGiantBirdAttackStateOnEnter.cpp`: use the registered Module and
an access view exposing its existing protected data getter. Native module+4
and subsequent data+0x3C accesses are preserved. The emitted getter changes
only its public/protected access spelling; both four-byte bodies are identical,
the index's admitted-reference graph has no incoming public-name edge, and other public and
protected providers remain. Six rows and EH stay exact; all 30 external code
definitions/relocations are conserved under that one identity normalization.
The owning acceptance tool retires one Module key; preview preserves
LINKS/1,359 bytes against `ccafe54d1d`. No census gain is claimed.
[Observed provider scope and native accesses](../../reverse/attempt_support/module-giantbird-data-access-20261030/README.md).
