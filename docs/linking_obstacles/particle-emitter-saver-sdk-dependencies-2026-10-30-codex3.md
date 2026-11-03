### Particle-emitter saver SDK dependencies (2026-10-30, codex3)

Cleared for SaveInfoBool, SaveInfoV2Bool, SaveLinePropertiesBool and
SaveW3DBool: replace their local Microsoft definitions and winbase shim with
real Platform SDK component headers. Normal builds retain 4/4 rows; the
before/after objects have identical definitions, normalized code/relocation
digests and reference edges. Strict provider receipts succeed, and the
ordinary preview against `12b9e7a7c0` retains four clean units and 399 bytes.
This is header-debt retirement, with no census gain. SaveHeaderBool and
SaveUserDataBool still need their independently verified unsuffixed kernel32
import identities preserved before migrating; they retain their shim and queue
entries. [Scope and checks](../../reverse/attempt_support/particle-emitter-sdk-headers-20261030-codex3.md).
