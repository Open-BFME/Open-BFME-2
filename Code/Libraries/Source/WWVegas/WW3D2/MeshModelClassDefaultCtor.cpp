// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// platformsdk
//
// ??0MeshModelClass@@QAE@XZ at retail 0x001727E0 (335 bytes).
//
// MeshModelClass default constructor. BFME1 donor:
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.cpp
// (MeshModelClass::MeshModelClass(void)). Same spine as the copy ctor in the
// sibling MeshModelClassCopyCtor TU (same TU context, same /G7 tell): base
// default, NULL members, the inlined GenericMultiList init at +0x9C, the
// global instance-list link through the .data head, then Set_Flag,
// a fresh 0x118 MeshMatDescClass aliased to CurMatDesc and a fresh 0x38
// MaterialInfoClass. Differences from the copy: no that argument, the flag
// or (DIRTY_BOUNDS, from the meshgeom shim's proven Flags at +0x18), and no
// Alternate branch. Trailing int3 pad excluded (335, not 336).
//
// Callees resolve to matched MeshGeometryClass default 0x168F30, the
// MeshMatDescClass default pin 0x15B480, the MaterialInfoClass default pin
// 0x1708D0, the game operator new and the 0x144690 list-dtor pin shared
// with the copy ctor.

#include <string.h>
#include <new>
#include <windows.h>

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

// The derived list owns the native vptr; its base's emitted table and deleting
// destructor belong to the retail provider, not this local layout view.

#include "../../../../GameEngine/Include/Common/Rva00144690.h"
// The proven DX8PolygonRendererList vtable slot 0 is rowed at 0x00144690.
typedef Rva00144690 DX8PolygonRendererList;

#include "MeshMatDescClass.h"

#include "MaterialInfoClass.h"

class GapFillerClass;

class MeshModelClass : public MeshGeometryClass
{
public:
	MeshModelClass();
	virtual ~MeshModelClass();

protected:
	void clone_materials(const MeshModelClass &srcmesh);

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

// Head of the global MeshModelClass instance list (retail .data head).
MeshModelClass *MeshModelListHead;

// ??0MeshModelClass@@QAE@XZ
MeshModelClass::MeshModelClass(void) :
	MeshGeometryClass(),
	DefMatDesc(NULL),
	AlternateMatDesc(NULL),
	CurMatDesc(NULL),
	MatInfo(NULL),
	PrevMeshLink(NULL),
	NextMesh(NULL),
	GapFiller(NULL)
{
	HasBeenInUse = false;

	NextMesh = MeshModelListHead;
	PrevMeshLink = &MeshModelListHead;
	MeshModelListHead = this;
	if (NextMesh != NULL) {
		NextMesh->PrevMeshLink = &NextMesh;
	}

	Set_Flag(static_cast<int>(DIRTY_BOUNDS), true);

	DefMatDesc = new MeshMatDescClass;
	CurMatDesc = DefMatDesc;

	MatInfo = new MaterialInfoClass;
}
