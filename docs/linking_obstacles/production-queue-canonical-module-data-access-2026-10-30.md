### Production queue canonical Module data access (2026-10-30)

Cleared only for ProductionUpdateQueue: replace its private Module with the
canonical header and a partial public access view of the existing protected
ModuleData pointer. Keep the raw-return lookup and cast the data at its one
use. Native 0x0049D960/0x0049D96A/0x0049D96D prove lookup, pointer+4 and flag+18.
All 47 rows/EH and 137 external code bodies/relocations are unchanged. Owning
Module acceptance retires one key; ordinary preview preserves LINKS/8,298
authored bytes against ccafe54d1d. The old request for a new shared accessor
is superseded by this source-local access view. Other production/derived
hierarchy and header debts remain; no census gain is claimed.
[Target evidence and verification](../../reverse/attempt_support/module-production-queue-20261030/README.md).
