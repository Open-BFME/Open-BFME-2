# MeshModelClass header adoption, 2026-11-05

Inspected revision: `7d2817eea5`. Worker: `yasinschroeder-codex2`.
The default picker claimed the class, existing header and fourteen source files.
All fourteen passed the pre-edit frozen-file check. This is header-debt cleanup,
not newly recovered code or a new census measurement.

## Applied scope and target facts

- `MeshModelReset.cpp`: replace the private derived class with
  `MeshModelClass.h`; the existing descriptor and material calls are unchanged.
  Three rows remain exact.
- `MeshMatDescFXShaderConversion.cpp`: replace the empty private derived class
  with the header. Stop suppressing `multilist.h`, since the complete model
  contains `MultiListClass<DX8PolygonRendererClass>`. The game Debug declaration
  already included in this TU takes precedence over the reference singleton:
  `DEBUG_DEBUG_H` prevents their duplicate class definitions. Nine rows remain
  exact, including the parent and its EH cleanup bodies. Renumbered funclet
  labels were verified through the parent's EH data by the normal byte gate.
- `Rva00171720Finish.cpp`: remove the padded private model view. The existing
  canonical header documents the target pointer at +0xBC and list at +0x9C.
  Return that pointer as bool and use the list's `Is_Empty()` accessor, which
  tests next-at-+0xA4 against the head-at-+0xA0. The 55-byte predicate remains
  exact. No original name is inferred for the predicate or pointer.

## Checks

`./build.sh` passed for every applied source (13/13 rows); FX conversion also
verified 57 string literals, two empty-string references and four floating
literals. Post-edit `find_declared_unmatched.py` passes all three sources.
`check_csv.py` passes (99,471 function rows).

Final combined `header_adopt_lane.py accept --class MeshModelClass` passes all
three sources and retires three queue rows in total through the owning tool.
The combined current-object link preview uses census 2026-11-04 22:01 at
`3fbce7bcb2`:

| Source | Prediction | Census-linked bytes before/after |
| --- | --- | --- |
| MeshMatDescFXShaderConversion.cpp | LINKS | 3,845 / 3,845 |
| MeshModelReset.cpp | LINKS | 214 / 214 |
| Rva00171720Finish.cpp | LINKS | 55 / 55 |

The unreferenced ShaderClass copy-constructor diagnostic in FX conversion is
not a blocker. The 4,114 total bytes are preserved; no linked-byte gain or
census confirmation is claimed.

## Remaining packet members (unchanged)

The automated adoption trial rejected eleven units; their original sources
and queue rows remain. No nonmatching attempt was retained in Code/.

- `MeshModelClassCopyCtor.cpp`: the existing Rva00144690 list member identity
  differs from the canonical MultiListClass specialization. Reconcile its
  destructor/provider identity before substituting the member type.
- `MeshModelClassDefaultCtor.cpp`, `MeshModelClassDtor.cpp`, `meshmdl.cpp`:
  existing MULTILIST_H suppression omits the complete list template needed by
  the model header. Preserve their proven deleting-destructor/list codegen
  when reconciling the includes; see LINK-357's earlier geometry adoption.
- `MeshModelClass_get_deformed_vertices.cpp`,
  `Rva0016BF40DeformedVertices.cpp`: opaque prefix arrays cross several real
  canonical fields. The automatic offset mapper cannot replace them. Manual
  adoption must reconcile the shared-buffer/geometry declarations and then
  verify each complete deformation body.
- `MeshModelLegacyMaterials.cpp`: automatic substitution compiles but the
  per-triangle reader fails the byte gate. The private model's material
  forwarding methods are inline, while the canonical header declares them
  out of line. Reconcile that codegen contract before retrying.
- `RenderAssetSwitchTexturesBFME2.cpp`, `bfmedynamicvertexbuffer.cpp`: canonical
  layout probe fails with C2084 duplicate definitions. Resolve the reference
  include/placement-operator context before a byte trial.
- `bfme2_mesh_material_pass.cpp`: automatic List-token rename would also alter
  MultiListNodeClass::List. Use a member-scoped replacement and reconcile the
  existing template/include boundary (also LINK-420).
- `../WWLib/BfmeAssignRecord32.cpp`: canonical layout probe reports C2084 and
  C1083. Reconcile its include roots and duplicate definitions first.

No shared header, function identity, pin, alternatename or source path changed.
