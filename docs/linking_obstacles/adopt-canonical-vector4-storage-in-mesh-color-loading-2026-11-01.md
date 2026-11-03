### Adopt canonical Vector4 storage in mesh color loading (2026-11-01)

Mesh DCG loading uses registered Vector4 storage; the native read/color conversion flow is retained, including alpha and x87 behavior. Normal/frozen/EH/strict and owning acceptance pass and retire the Vector4 key. This is source reconciliation, not measured memory or runtime improvement.
[Evidence](../../reverse/attempt_support/mesh-dcg-vector4-20261101.md).
