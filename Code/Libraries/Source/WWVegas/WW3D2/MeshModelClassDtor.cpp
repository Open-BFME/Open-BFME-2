// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// platformsdk
//
// ??1MeshModelClass@@UAE@XZ at retail 0x00172AB0 (306 bytes).
//
// MeshModelClass destructor. BFME1 donor:
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.cpp
// (MeshModelClass::~MeshModelClass). Same spine as the copy/default TUs
// (same TU context, same /G7 tell) with BFME 2's teardown shape:
//
// - vptr reinstall, then the renderer unregister and the GapFiller delete
//   helper, both guarded by their global availability pointers (pointer
//   null-checks compile to mov+test, which is how the shape proves both
//   globals are pointers; the GapFiller helper ignores its own this and
//   only takes the model, but the caller still passes the global as this).
// - CurMatDesc renderer-state guard around the renderer-teardown helper
//   (MeshMatDescClass +0xC, field_0C; the helper re-checks it).
// - Reset(0, 0, 0, skin) where skin is the SKIN bit (Flags 0x400, bit 10).
//   The extraction is (Flags >> 10) with a bool mask: cl7.1 keeps `& true`
//   byte-wide (and al,1) while `& 1` widens to and eax,1 and mismatches;
//   micro-probes prove the rule. Reset's fourth parameter and the
//   Reset_Geometry third it forwards to are therefore bool; the chunk
//   reader at 0x18BAB9 passes its own header-attribute bool the same way.
// - MatInfo REF_PTR_RELEASE inlined (decref at +4, slot-0 Delete_This),
//   explicit Def/Alternate deletes (MeshMatDesc has no virtual dtor, so
//   delete emits the dtor call plus the operator delete call), the global
//   instance-list unlink (PrevMeshLink only; NextMesh is left alone),
//   then the automatic PolygonRendererList and base destructions.
//
// Callees: Unregister pin 0x1445E0, GapFiller-helper pin 0x1732E2,
// renderer-teardown pin 0x199FA5, Reset pin 0x171F70, MeshMatDesc dtor pin
// 0x15DC40 (same folded bytes as the BfmeHolderBY row at that address),
// the shared 0x144690 list-dtor pin, the 0x16CCC0 base-dtor pin and the
// matched scalar operator delete.

#include <string.h>
#include <new>
#include <windows.h>

#define SKIN_BIT_INDEX 10

// <new> supplies the placement operators; skip always.h's duplicates.
#define _OPERATOR_NEW_DEFINED_
#include "always.h"

#include "../WWLib/RefCountData.h"

#include "../WWLib/GenericMultiListClass.h"
#include "../WWLib/MultiListObjectClass.h"

// These canonical list declarations replace the reference multilist header
// that MeshGeometryClass.h includes for its secondary base.
#define MULTILIST_H
#include "MeshGeometryClass.h"

class DX8PolygonRendererList : public GenericMultiListClass
{
public:
	virtual ~DX8PolygonRendererList();
};

#include "MeshMatDescClass.h"

#include "MaterialInfoClass.h"

class MeshModelClass;

#include "DX8MeshRendererClass.h"

extern DX8MeshRendererClass *TheDX8MeshRenderer;

// Opaque context behind the GapFiller-delete gate (retail .data pointer).
// The helper takes the model on the stack and ignores its own this, but
// the caller still passes the global through ecx, which is what proves
// the thiscall shape.
class Rva00DF6F94GapFillerContext
{
public:
	void DeleteModelGapFiller(MeshModelClass *mmc);
};

extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

class GapFillerClass;

#include "WW3DClass.h"

class MeshModelClass : public MeshGeometryClass
{
public:
	MeshModelClass();
	virtual ~MeshModelClass();

	void Reset(int polycount, int vertcount, int passcount, bool skinned);
	void rva001716E0UnregisterMeshModel();
	void Enable_Alternate_Material_Description(bool onoff);
	bool Is_Alternate_Material_Description_Enabled(void);

protected:
	void compute_static_sort_levels(void);

private:
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;
	MaterialInfoClass *MatInfo;
	DX8PolygonRendererList PolygonRendererList;
	MeshModelClass **PrevMeshLink;
	MeshModelClass *NextMesh;
	GapFillerClass *GapFiller;
	bool HasBeenInUse;
public:
	// retail vftable slot: the rowed override
	virtual bool Load_W3D(ChunkLoadClass &);
};

// 0x00199FA5 is rowed as rva00199FA5 (Rva00199FA5Check.cpp); called by that name.
class Rva00199FA5Rec;
bool __cdecl rva00199FA5(Rva00199FA5Rec *p);

// ??1MeshModelClass@@UAE@XZ
MeshModelClass::~MeshModelClass(void)
{
	if (TheDX8MeshRenderer != NULL) {
		TheDX8MeshRenderer->Unregister_Mesh_Type(this);
	}
	if (TheMeshGapFillerContext != NULL) {
		TheMeshGapFillerContext->DeleteModelGapFiller(this);
	}
	if (CurMatDesc->field_0C != NULL) {
		rva00199FA5((Rva00199FA5Rec *)CurMatDesc);
	}
	Reset(0, 0, 0, (static_cast<unsigned int>(Flags) >> SKIN_BIT_INDEX) & true);
	if (MatInfo != NULL) {
		MatInfo->Release_Ref();
		MatInfo = NULL;
	}
	if (DefMatDesc != NULL) {
		delete DefMatDesc;
	}
	if (AlternateMatDesc != NULL) {
		delete AlternateMatDesc;
	}
	if (PrevMeshLink != NULL) {
		*PrevMeshLink = NextMesh;
		if (NextMesh != NULL) {
			NextMesh->PrevMeshLink = PrevMeshLink;
		}
		PrevMeshLink = NULL;
	}
}

// Retail 0x001716E0, 58 bytes. Renderer/gapfiller/UV unregister head shared
// with the destructor above, as a standalone thiscall method: the two global
// guards, then the CurMatDesc renderer-state guard around the teardown helper.
void MeshModelClass::rva001716E0UnregisterMeshModel(void)
{
	if (TheDX8MeshRenderer != NULL) {
		TheDX8MeshRenderer->Unregister_Mesh_Type(this);
	}
	if (TheMeshGapFillerContext != NULL) {
		TheMeshGapFillerContext->DeleteModelGapFiller(this);
	}
	MeshMatDescClass *curDesc = CurMatDesc;
	if (curDesc->field_0C != NULL) {
		rva00199FA5((Rva00199FA5Rec *)curDesc);
	}
}

// Retail 0x00171790, 180 bytes. ZH meshmdl.cpp body with BFME 2's DX8 data
// handling: switching to the alternate description unregisters through the
// out-of-line 0x001716E0 helper, switching back spells the same three guarded
// steps out; both arms then rerun the munge-sort pass (Flags SORT 0x10) instead
// of ZH's overbright pass and renderer invalidate.
void MeshModelClass::Enable_Alternate_Material_Description(bool onoff)
{
	if ((onoff == true) && (AlternateMatDesc != NULL)) {
		if (CurMatDesc != AlternateMatDesc) {
			rva001716E0UnregisterMeshModel();
			CurMatDesc = AlternateMatDesc;
			if ((Flags & 0x10) && WW3D::Is_Munge_Sort_On_Load_Enabled())
				compute_static_sort_levels();
		}
	} else {
		if (CurMatDesc != DefMatDesc) {
			if (TheDX8MeshRenderer != NULL) {
				TheDX8MeshRenderer->Unregister_Mesh_Type(this);
			}
			if (TheMeshGapFillerContext != NULL) {
				TheMeshGapFillerContext->DeleteModelGapFiller(this);
			}
			if (CurMatDesc->field_0C != NULL) {
				rva00199FA5((Rva00199FA5Rec *)CurMatDesc);
			}
			CurMatDesc = DefMatDesc;
			if ((Flags & 0x10) && WW3D::Is_Munge_Sort_On_Load_Enabled())
				compute_static_sort_levels();
		}
	}
}

// Retail 0x00171830, 20 bytes (ZH meshmdl.cpp).
bool MeshModelClass::Is_Alternate_Material_Description_Enabled(void)
{
	return CurMatDesc == AlternateMatDesc;
}
