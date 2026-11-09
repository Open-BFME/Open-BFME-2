### Two ModuleInfo map getter rows have enclosing-template receivers

Status: blocked on reviewed inferred names and a prepared identity migration.
Updated: 2026-11-09; inspected revision: 3a7b59cb3d.

Rows0033C259/47B and0033C288/43B currently name ModuleInfo members, but native
callers load Object's ThingTemplate pointer. Their+0x3A0/+0x3AC maps are not
members of canonical twelve-byte ModuleInfo. Direct header substitution would
conceal that identity mismatch. Neither body is lost; these are cleanup items.

Committed BFME1/ZH evidence supplies no canonical getter names. A supported
ordinary function respell needs independently reviewed readable identifiers,
final owner/signatures and prepared caller/provider C++. The placeholder-slot
--to-class route does not apply. A pre-existing ThingTemplate-named C259 pin
also needs supported reconciliation; all four cached objects require current
verification. No source, pin, ledger or queue row changes in this investigation.

[Native caller proof, donor limits and exact handoff scope](../../reverse/attempt_support/moduleinfo-map-owner-naming-prerequisite-20261109.md).
No byte-coverage regression, global linking gain or runtime result is claimed.
