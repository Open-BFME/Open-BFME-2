### Drawable destructor math-header reconciliation (2026-10-30)

Current Matrix3DData already includes canonical Vector4Data, and both now
provide the formerly missing inline math methods. Matrix3D acceptance passes
without a source edit; an explicit Vector4Data include satisfies that class's
guard. Both owning acceptance paths retire their keys, leaving the source's
header queue empty. All 12 rows, parent EXACT EH, 24 code definitions and all
non-debug sections/data/references are identical to the verified pre-include
object. Preview retains LINKS/643 bytes; no census gain is claimed.
[Current headers and complete object comparison](../../reverse/attempt_support/drawable-math-headers-20261030/README.md).
