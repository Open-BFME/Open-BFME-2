# Shatter material getter prerequisites

No production source, shim, row or register key changes. The normal paired
preview still blocks both shattersystem and dynamesh; no gain is claimed.

Target facts: the existing native MeshMatDescClass::Peek_Single_Material owner
at 0x002C8ECF is 14 bytes and reads Material at +0xA4. Shatter's current emitted
copy reads +0xA8. Its out-of-line body has only debug relocation references,
but that does not establish that its inline behavior is unused. The native
MeshModelClass getter already has a separate 20-byte row at 0x000D1AC1.

Private probes retain the single 133-byte Scale row exactly:

- Force-inline on the definition alone leaves the wrong copy present.
- Force-inline on both declaration and definition likewise leaves every
  definition unchanged, including the wrong copy.
- A declaration-only shim branch removes that copy, but also changes
  MeshModelClass::Peek_Single_Material and ShatterSystem::Process_Clip_Pools.
  It therefore fails the proposed narrow retained-code invariant.

The JSON records native bytes, the debug reference edges, both saved probe
outcomes and the two changed callers' sizes, digests and relocation targets.
The raw-copy observation is not proof of a harmless suppression opportunity.
Next reconcile the MeshMatDesc layout and actual inline callers against their
native owners; MaterialInfoClass::Add_Vertex_Material also has executable
references and remains a separate wrong-selected provider. Wider dynamesh
RenderObj, dynamic-VB and material dependencies remain open under LINK-012.
