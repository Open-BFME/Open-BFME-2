### Tree-erase header queue retirement (2026-10-29)

At `36091192a6`, the four helpers repaired by `ae0a668f96` still had stale
local-free findings. Current verification retains all four rows (188 bytes),
the header auditor reports clean, and its scoped refresh removes exactly four
queue entries. Preview retains 4/4 LINKS against `85f6b7f40c`; no source or
census change is claimed. Selection review also confirms LINK-064's existing
pair-identity failures in Rva00566695Assign.cpp and leaves LINK-139's locale
duplicate prerequisite unchanged. No source trial was repeated for either.
[Current checks and scope](../../reverse/attempt_support/tree-erase-crt-header-20261027.md#scoped-queue-retirement-2026-10-29).
