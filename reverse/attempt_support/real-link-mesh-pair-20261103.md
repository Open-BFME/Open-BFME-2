# Dynamesh / shatter real-link donor cleanup

Base: 02ba74b593 (initial checkout c1325ac0b6). Seat: halilkkaya-codex.
No source path, ledger identity, pin, compiler flag or shared header changes.

The real-link artifact 41678189681 at 96cfeda7ba attributes 21 undefined
names to dynamesh.cpp and 12 to shattersystem.cpp: 32 unique names, 25
attributed only to this pair. Both current objects have zero undefined game
names after the cleanup; shatter retains only the usual __fltused reference.
Seven artifact names also occur in other units and remain open there.

The ledger owns four leaves in dynamesh (two material helpers and the two
seven-byte getters) and one in shatter (uniform Matrix3D::Scale, 133 bytes).
The Zero Hour renderer, constructors and material setter, and both shatter
routines have no rows. Their old native-looking class/layout spellings are
not evidence that these donor routines existed in BFME 2.

Remove the unrowed routines together: shatter was the sole outside consumer
of the dynamesh constructor and Set_Vertex_Material. Retain the two getters
as ordinary definitions at their existing E4/E8 offsets. Taking ordinary
addresses in these bodies retains the existing nonvirtual material inlines.
Shatter takes the address of the nonvirtual uniform Scale header inline
through a TU-local const member pointer, retaining its original select-any
emission without an added wrapper function or a strong duplicate. The old
VCI optimization context is unchanged; removing it changes the compiler helper
and was not retained. The getter views preserve existing identities only;
this does not recover a complete DynamicMesh class or its retail TU.

Provider audit, against index 984a4cdc4d (November 2 08:35): the pair loses
292 external definitions, with no outside reference left without another
provider. All ten common dynamesh COMDAT fingerprints and all three common
shatter fingerprints are identical. No new external definition is emitted.
The pair removes the obsolete RenderObj/DynamicMesh tables, rather than
suppressing them in an instantiated object. The seven shared artifact names
remain tracked as unresolved in other sources.

Verification:

- Normal eight-unit build: 49/49 rows, 21 floating literals, string/import
  checks pass. Scope: dynamesh, shattersystem, MaterialCollectorCollectMaterials,
  matinfo, twiddler, sphereobj, Matrix3DScaleO1, Matrix3DUnmatchedSSE.
- True source-restored base/tip A/B: 4/8 LINKS and 8,218 bytes before;
  6/8 LINKS and 8,464 bytes after. The same four linking peers are preserved.
  matinfo's three ShaderClass vector differences and twiddler's blockers
  already exist at base; neither is a new loss. No census gain is claimed.
- find_declared_unmatched is clean. Scoped DIR32 checks 49 rows and 12
  current witnesses, 23 symbols, with zero new or whitelisted conflicts.
- Full real-link rerun and global current consumer closure remain unmeasured.
  build/seat-link contains base/tip snapshots and all local logs.

The 25 artifact names attributed only to this pair:
- `??0DynamicMeshModel@@QAE@II@Z`
- `??0DynamicVBAccessClass@@QAE@IIG@Z`
- `??0MeshMtlParamsClass@@QAE@PAVMeshModelClass@@@Z`
- `??0PolygonClass@@QAE@XZ`
- `??0WriteLockClass@DynamicVBAccessClass@@QAE@PAV1@@Z`
- `??1DynamicMeshClass@@UAE@XZ`
- `??1MeshMtlParamsClass@@QAE@XZ`
- `??1WriteLockClass@DynamicVBAccessClass@@QAE@XZ`
- `?Add_Texture@MaterialInfoClass@@QAEHPAVTextureClass@@@Z`
- `?Clip_Polygon@BSPClass@@QAEXABVPolygonClass@@@Z`
- `?Clone@DynamicMeshClass@@UBEPAVRenderObjClass@@XZ`
- `?Compute_Plane@PolygonClass@@QAEXXZ`
- `?End_Vertex@DynamicMeshClass@@QAE_NXZ`
- `?Get_Vertex@DynamicMeshClass@@UAEXHAAM00@Z`
- `?Get_Vertex_Normal_Array@MeshGeometryClass@@QAEPBVVector3@@XZ`
- `?Initialize_Material_Array@DynamicMeshModel@@QAEXHPAVVertexMaterialClass@@@Z`
- `?Insert_Triangles@SortingRendererClass@@SAXABVSphereClass@@GGGG@Z`
- `?Location@DynamicMeshClass@@UAEXMMM@Z`
- `?Move_Vertex@DynamicMeshClass@@UAEXHMMM@Z`
- `?Release_Fragments@ShatterSystem@@SAXXZ`
- `?Render@DynamicMeshClass@@UAEXAAVRenderInfoClass@@@Z`
- `?Reset@DynamicMeshModel@@QAEXXZ`
- `?Reset_Clip_Pools@ShatterSystem@@KAXXZ`
- `?Set_Single_Texture@MeshMatDescClass@@QAEXPAVTextureClass@@HH@Z`
- `?Translate_Vertices@DynamicMeshClass@@QAEXABVVector3@@@Z`

# Boundaries found elsewhere in this pass

collect.cpp: an ordinary donor trim and explicit vector instantiations keep
three of five rows but lose the two virtual RenderObj leaf emissions at EFB4C
and 5AD93A. Taking virtual member addresses does not emit them. EFB4C stores
at +7C, which is Container in canonical RenderObj; recover that identity and
ownership before retiring the constructor that currently emits it. All five
rows were restored and pass. The file claim is released.

FamilyDeletingDtors_muse-cd13.cpp: native 4C64E9 is a five-byte jump to the
AIUpdateModuleData destructor at 494BE4. Ordinary derived destruction emits
11 bytes, including a derived-vptr store; it cannot be admitted as the twin.
The actual shared C5DAB0 table/class context still needs reconciliation.
The trial was restored, its existing deleting row passes, and all its claims
are released. No novtable suppression or new pin/alias was retained.

Particle constructor: rename.py function --virtual --dry-run correctly refuses
the primary selector's current ParticleFXShaderParameterSourceNamespace name:
the installing constructor still names Rva001F4B01. The nested real dispatchers
already exist, but the ctor/dtor/selector identity cohort must reconcile first.
No Particle source was changed or claimed.

Twiddler: besides its lone ten-byte setter, it emits the only current
EnumParameterClass::_ENUM_VALUE destructor provider for two other units.
Those consumers model a surface-owning element, unlike the donor's
StringClass/int element. Preserve that known identity/provider prerequisite;
removing the whole donor unit without reconciliation would orphan consumers.
