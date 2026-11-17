# HLod interface preflight

The served primary table007D6780 still has six queued source-slot differences.
The owning hlod.cpp normal build passes166/166 rows, one string,19 float
literals and two imports. Sixteen existing admitted unclaimed definitions
remain. No source, header, ledger row, pin or flag was changed.

Current native providers are already C++:

| Slot | Target | Existing owner |
| --- | --- | --- |
|11|001A5F00|CompositeRenderObjClass::Get_Num_Verts,71B|
|41|0019CEA0|HLodClass::Removed_Added_Sub_Objects_From_Bones,168B|
|53|001A4E70|Animatable3DObjClass::rva001A4E70(int),72B|
|59|001A5460|Animatable3DObjClass::Rva001A5460(Animatable3DObjClass*),75B|
|124|0019B9C0|HLodClass::Create_Decal(DecalGeneratorClass*,int),87B|
|126|0019BA70|HLodClass::rva0019BA70(int,int),87B|

The existing constructor/shim graph leaves inherited RenderObj placeholders
at several of these positions. Its decal declaration instead takes bool;
the old dependency-list declaration also has different parameters. Correcting
these calls requires a consistent shared base/derived contract and supported
naming or prototype transactions, not new aliases or misplaced body copies.
The canonical RenderObjClass class claim is held by other workers. HLodClass's
own claim was acquired for inspection and released with its file/table scopes;
no shared base-contract edit was attempted. Composite and Animatable dry scopes
were reported free, but no acquisition or edit was made.

The old155330 ModelNodeClass-vector misidentification is already retracted
(see LINK-109's Nov9 update); its stale attempt is not a new regression.
Existing linking-obstacle notes retain the separate bounding-getter provider
order and mixed-TU consolidation limitations. Once the base contract is
available, test one shared explanation for the six slots, preserve all166
rows, and wait for the published real-link pass before declaring retirement.
Scratch: continuation-20261117c-hlod-baseline-build.log and next-work-3.log.
