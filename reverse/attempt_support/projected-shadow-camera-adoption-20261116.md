# Projected-shadow writer header adoption

The DX8MeshRendererClass adoption is banked separately from the unsuccessful
CameraClass experiment. The writer now uses the canonical opaque mesh renderer
declaration and a TU-local layout view for the existing camera pointer at +4.
Official build: 10/10 functions; one EXACT EH graph. All 17 COMDAT byte/relocation
fingerprints are unchanged. header_adopt_lane.py accept retired one queue row.

Replacing the writer's private CameraClass with the canonical header and moving
its volatile-this Get_Frustum inline body outside the class preserved the ten
rows, but emitted an additional 22-byte Get_Frustum COMDAT. Retail's getter at
RVA 0x0004CB06 is 16 bytes; the provider comparison rejected the new copy. The
scoped link preview still said LINKS (2,583 bytes), demonstrating that this
preview alone did not establish correctness of every emitted provider.

Keeping dllimport on that out-of-class definition instead fails compilation
with C2375 because the canonical declaration does not have dllimport. Both
Camera changes were reverted. No canonical CameraClass header or compiler gate
was changed, and the final mesh-only object has no added COMDAT.

Next work must reconcile the canonical getter and the caller's volatile-this
inlining without producing a non-retail out-of-line provider. This is a real
code-generation difference, not a false rejection. It does not justify an alias,
provider pin, access-control workaround or relaxing the verifier.

Local logs: build/decal-diagnostic/writer-camera-mesh-master-*,
writer-camera-mesh-preserved-build.log, writer-mesh-master-* and
writer-mesh-accept.log. No merged image or selection-rendering runtime result is
claimed by this header prerequisite.

## Verified follow-up

With the CameraClass and getter claims available, the writer now adopts the
canonical class. Get_Frustum itself performs Update_Frustum and returns field100;
its emitted copy is 16 bytes and RetailTruth judges it retail. The render
caller's existing volatile camera home is retained in the local force-inline
shadowFrustum helper, which refreshes through that getter and reads the frustum
through the saved camera pointer. The helper emits no additional external
provider. Keeping the volatile pointer directly in the caller instead changed
its stack home from -0x18 to -8 and failed the byte test; that variant was not
banked as source.

The final version matches all 10 rows and the one EH graph. All existing
provider fingerprints agree; the only added provider is the retail 16-byte
Get_Frustum. Official header adoption passes and retires the writer's CameraClass
queue item. Evidence: build/decal-diagnostic/writer-camera-* in decal-merge.
This resolves the getter-copy blocker above; it does not establish merged or
runtime correctness by itself.
