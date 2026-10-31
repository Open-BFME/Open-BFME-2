# Offset/shroud transform: canonical Vector4 storage

Base `59018891cc`; claimed Vector4 and source scopes. In
`Common/Rva000E48BC.cpp`, replace the private four-float Vector4 with the
existing Vector4Data.h. A file-local force-inline const component accessor
retains the same `(&row.X)[index]` operation in each transform expression.
The target row/component offsets agree with the existing 16-byte contract.
Matrix3D/Vector3 private views and their separate adoption work remain open.

Both rows remain exact: `000E48BC` / 252 bytes updates the world offset and
container flag; `000E49B8` / 541 bytes performs the shroud-bounds query.
All seven retained external code bodies and relocations are identical.
The removed shared Vector4 const subscript copy had only a `.debug$F`
incoming edge. Its replacement emits one internal code copy, also referenced
only by `.debug$F`; retained runtime calls and bodies do not change. This
helper is not claimed as a new native function or matched bytes.

Normal/frozen gates, fresh two-source strict preparation and owning Vector4
acceptance pass. Exactly this source's queue key is retired through the
owning tool. Bounded `3c7a254a38` preview (2026-10-31 13:43) retains
LINKS/793 authored bytes. Shared headers, flags, pins, aliases, data rows,
source paths and baselines are unchanged. Broader consumer/provider
selection and scheduled census confirmation remain separate.

The default picker first served `Code/gen_small/uw_gen_006.cpp`, aggregate
457-byte credit at `007604BD`, with 103 unresolved synthetic lifetime
helpers. Prior records around 5292..5298 and 18483 establish that these are
generator-owned scaffolds, not native parent identities. No prerequisite
has changed, no generated source is hand-edited and no synthetic helper pin
is added. Its claims were released; this review is not a completed task.

Original/final objects, retained-body comparison, debug-only helper-edge
inventory and normal/strict/acceptance/link controls are preserved under
ignored `build/two-each-no-qwen-20261031-1756` and the matching diagnostic
package. No Qwen or other local inference is used. Builds retain the shared
ten-worker cap and leave Unreal processes alone.
