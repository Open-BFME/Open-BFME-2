### Quadruped vector composition prerequisites (2026-10-30, codex3)

Cleared for the two-argument resize donor: replace its private allocator/vector
templates with a shared local specialization preserving the by-value retail ABI.
The seed and donor retain 7/7 exact rows; normalized definition digests and
undefined target sets are unchanged. Resize becomes a strong definition with
the same two call edges. Strict preparation succeeds for both, and ordinary
previews against `12b9e7a7c0` retain two clean units and 440 bytes. The merge
probe accepts that donor. This is consolidation preparation, with no census gain.
Constructor/base-vtable reconciliation, the default-resize constructor view,
Matrix3D/Vector4 adoption and seven mixed files remain prerequisites for the
other rows. [Evidence and consolidation audit](../../reverse/attempt_support/quadruped-vector-consolidation-20261030-codex3.md).
