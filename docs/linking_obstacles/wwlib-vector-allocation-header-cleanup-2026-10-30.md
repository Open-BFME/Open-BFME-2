### WWLib vector allocation-header cleanup (2026-10-30)

At base `e3570ba43c`, the float cleanup and Vector3 destructor units replace
local array-delete declarations with toolchain `<new>`, selecting the existing
`always.h` allocation guard. All 12 rows and 20 external COMDAT fingerprints
remain identical. Strict preparation passes, and both previews retain LINKS
for 402 authored bytes against `6fe1089c24`. The owning auditor retires two
Microsoft-header findings. No census or source-file gain is claimed.

The scoped staged audit is INCONCLUSIVE on its older index and missing current
`Common/0CreateAHeroManager21FE49.cpp` consumer receipt. The wider outgoing
batch also lacks three changed-source receipts, first `Common/FprintfAppendLine.cpp`.
Full affected-consumer selection and loss checks remain pending; carry these
providers and consumers into the next scheduled census.
[Scoped evidence and verification](../../reverse/attempt_support/simplevec-msheaders-20261030-codexb5.md).
