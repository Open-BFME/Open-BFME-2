### Matrix3D setter Vector4 adoption (2026-10-31)

Matrix3D_Set_Matrix3_Vector3 includes the existing Vector4 storage header.
Per-row input capture preserves the original load-before-store sequence and
avoids the extra shared Set or internal helper copies from intermediate
variants. Both 118/10-byte code functions and all relocations are unchanged;
no code definition is added or removed. Normal/strict gates and owning
acceptance retire one header key, retaining bounded LINKS/128. With the
separate physics adoption this retires two keys and preserves three rows and
1,003 authored preview bytes. Broader consumer/census checks remain separate.
[Controls and scope](../../reverse/attempt_support/matrix-set-vector4-adoption-20261031.md).

The outgoing audit after fresh strict preparation is INCONCLUSIVE: the
`3c7a254a38` index predates base `c38e282bad`, and the affected
CreateAHeroManager21FE49 consumer has no current receipt. The scoped
three-row preservation does not clear this broader selection/census scope.
