# VertexMaterialClass header adoption, 2026-11-04

Inspected source revision: `9acaa20c92`. Census index: 2026-11-04 07:28,
`a62ac1c10b`. These are ordinary byte checks and link previews, not a census.

Three files now include the existing `WW3D2/VertexMaterialClass.h` instead
of private VertexMaterialClass definitions:

- `Rva00155AD0.cpp`: also drops its conflicting private StringClass definition.
  The header supplies the same constructor and destructor behavior. Seven
  matched rows, including four EH funclets, pass the normal build.
- `VertexMaterialInitFromMaterial3.cpp`: retains its local inline setters as
  definitions of the canonical declarations. MaterialDyn points to the existing
  0x44-byte material payload; CRCDirty replaces the private +0x68 byte spelling.
- `VertexMaterialParseStruct.cpp`: the same setter reconciliation, with Flags
  replacing only the object's +0xC member. Input `vmat.Attributes` is unchanged.

Target layout evidence is already documented in VertexMaterialClass.h. The
local D3D payload wrappers describe storage; they do not establish donor source
paths or add new recovered names. No shared header, row identity or pin changes.

Verification:

- Normal `./build.sh` passes all nine matched rows in the three adopted files.
- `find_declared_unmatched.py` passes the three files; existing unemitted anchor
  notes remain as before.
- `header_adopt_lane.py accept --class VertexMaterialClass` passes all three
  files and retires precisely their three queue entries. Repeating acceptance
  after reverting the fourth trial also passes all three.
- Preview: renderer 2,877 -> 2,877 linked bytes; material conversion 396 -> 396;
  struct parser 327 -> 327. The renderer's unreferenced Add_Ref copy is a
  diagnostic, explicitly not a blocker.
- After restoring Load_W3D, the final four-file preview reports all four LINKS,
  preserving 3,908 -> 3,908 census-linked bytes, including Load_W3D's 308 bytes.
- The normal commit hook passes nine rows, one EXACT EH parent, converged data
  and three-source checks. Its shadow identity scan reports divergent
  `??4Matrix4@@QAEAAV0@ABV0@@Z` and
  `?Get_Transform@DX8Wrapper@@SAXHAAVMatrix4@@@Z` helper definitions. These
  diagnostics are not identity retirements or a claim of clean helper identity.

The fourth queued file, `VertexMaterialLoadW3D.cpp`, was tried with the canonical
header instead of StringClassData.h and its private class. Its 308-byte row
still passes normal byte verification, but the combined link preview reports
`duplicate ??4StringClass@@QAEABV0@PBD@Z` and 308 -> 0 linked bytes. The
canonical material header includes wwstring.h, whose assignment definition is
absent from the former declaration-only StringClassData.h dependency.

That fourth source edit is reverted and its queue entry remains. Its next step
is to reconcile the material header's StringClass dependency with the canonical
declaration-only storage header while preserving other consumers' required
inline bodies. This shared-header work needs a separate claim and consumer
verification. No failed adoption is left in Code/. The remaining assignment
boundary is tracked as LINK-239.
