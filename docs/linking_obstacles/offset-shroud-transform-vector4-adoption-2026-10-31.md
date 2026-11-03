### Offset/shroud transform Vector4 adoption (2026-10-31)

Rva000E48BC.cpp now includes canonical Vector4 storage. Both 252/541-byte
rows and all seven retained external code bodies/relocations are unchanged.
The removed shared const subscript and its replacement internal component
helper each have only debug incoming edges; no runtime call changes.
Fresh strict preparation and owning acceptance retire one Vector4 key;
bounded LINKS/793 remains unchanged. Matrix3D/Vector3 adoption and full
affected-consumer/census validation remain separate.
[Controls and limits](../../reverse/attempt_support/offset-transform-vector4-adoption-20261031.md).
