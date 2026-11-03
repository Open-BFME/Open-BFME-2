### Matrix3D comparison Vector4 adoption (2026-10-31)

The comparison unit now uses the existing canonical Vector4 storage header.
Both 61/70-byte rows and the Matrix3D row accessor retain all bytes and
relocations. The removed shared const Vector4 accessor had only a debug
incoming edge; direct component access introduces no helper or runtime call.
Strict preparation and owning acceptance retire one Vector4 queue key,
preserving bounded LINKS/131 at `3c7a254a38`. Matrix3D adoption and the
broader affected-consumer/census verdict remain separate.
[Controls and scope](../../reverse/attempt_support/matrix-equality-vector4-adoption-20261031.md).
