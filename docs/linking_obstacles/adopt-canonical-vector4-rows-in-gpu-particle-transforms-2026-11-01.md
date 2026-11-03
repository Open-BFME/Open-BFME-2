### Adopt canonical Vector4 rows in GPU particle transforms (2026-11-01)

GPU particle transform rows use canonical Vector4 storage. Existing native particle flow, rendering state and EH cleanup are retained; complete normal/frozen/EH/strict checks and owning acceptance pass. Only the Vector4 key is retired; complete image and runtime proof remain separate.
[Evidence](../../reverse/attempt_support/gpu-particle-transform-vector4-20261101.md).
