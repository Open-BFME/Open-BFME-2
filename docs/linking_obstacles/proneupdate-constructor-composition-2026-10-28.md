### ProneUpdate constructor composition (2026-10-28)

Status: Blocked on constructor and polymorphic-base reconciliation. At base
`fc86ff7e0c`, both original files are census-linked. A declaration and
offset-store trial preserves each file's rows separately, but the supported
dry merge rejects the composed bytes. The trial was reverted; no source path
moved or linking gain is claimed. Compare emitted constructor and vtable
context before retrying. [Trial details](../../reverse/attempt_support/prone-update-consolidation-20261028-codex4.md).
