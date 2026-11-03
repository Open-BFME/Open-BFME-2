### VersionBlockParser CRT header cleanup (2026-10-30)

The TU takes four CRT declarations from the toolchain headers, retaining
the imported `sscanf` call and direct string-operation bindings. All 22 rows,
both EXACT EH graphs, 52 non-debug section byte sequences, 69 external symbol
records and 44 external COMDAT fingerprints remain unchanged. The owning scan
retires this source's four-declaration header queue entry. Strict preparation
passes; ordinary preview retains LINKS and 1,341 authored bytes against
`12b9e7a7c0` (2026-10-30 10:11 UTC).

The complete staged outgoing audit against `7ed98efdf86e` is INCONCLUSIVE on
the older index and 33 objects without current receipts, first
Common/Rva003A5DA0Write.cpp. Carry this provider and affected consumers into
the next scheduled census/current-receipt audit; full selection and loss
verification remains open. No census gain is claimed.
[Checks and publication scope](../../reverse/attempt_support/versionblock-crt-header-20261030-codexb4.md).
