### Physics transformation Vector4 adoption (2026-10-31)

DrawableApplyPhysicsXform now uses the existing Vector4 storage header.
A local inline accessor preserves the original pointer-based component
expression; direct field accesses changed the SSE schedule and were rejected.
All 875 bytes and relocations, the sole code definition and bounded LINKS/875
remain unchanged. Normal/strict gates and owning acceptance retire one header
key. No shared header, compiler flag or provider changes. Broader consumer
and census verification remain separate.
[Native/actual-object controls](../../reverse/attempt_support/physics-vector4-adoption-20261031.md).
