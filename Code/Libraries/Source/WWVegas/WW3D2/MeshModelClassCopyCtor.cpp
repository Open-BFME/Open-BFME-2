// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// platformsdk
//
// ??0MeshModelClass@@QAE@ABV0@@Z at retail 0x00172940 (361 bytes).
//
// MeshModelClass copy constructor: retail MeshClass::Make_Unique at
// 0x00149C10 calls it with the fresh allocation as this and the shared model
// as the argument right after operator new (Zero Hour NEW_REF idiom).
//
// BFME1 donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/
// meshmdl.cpp (MeshModelClass::MeshModelClass(const MeshModelClass &)).
// BFME 2 carries the same spine (base copy, fresh DefMatDesc, conditional
// AlternateMatDesc copy, CurMatDesc alias, clone_materials tail) with a
// wider tail layout and an instance-tracking list BFME 1 lacks:
//
// - MeshGeometryClass base is 0x8C with vptrs at +0/+8 (W3DMPO empty,
//   RefCountClass vptr +0, MultiListObjectClass vptr +8), matching the two
//   vptr stores and the proven sizeof downstream.
// - DefMatDesc +0x8C, AlternateMatDesc +0x90, CurMatDesc +0x94,
//   MatInfo +0x98 (left NULL here; clone_materials allocates it).
// - PolygonRendererList at +0x9C: a DX8PolygonRendererList (GenericMultiList
//   family, vtable 0xBD34E0 whose slot 0 reaches the 0x144690 list dtor).
//   Its construction inlines exactly the multilist.h spellings: the node
//   ctor's five NULL stores, then Head.Next = Head.Prev = &Head plus the
//   Object/NextList re-zeroes. The pool base is omitted: retail shows plain
//   data stores, no extra vptr.
// - Global instance list: NextMesh +0xB8 and PrevMeshLink +0xB4 link every
//   model through the head in .data (retail 0xDF6F90). Stores run Next,
//   Prev, head, then the member re-read guards the back-link; the reload is
//   aliasing-driven and falls out of the plain spelling.
// - GapFiller +0xBC NULL, HasBeenInUse +0xC0 false; total 0xC4.
// - MeshMatDescClass news 0x118 (retail push); /G7 is the unit's tell.
//
// Callees resolve to the MeshGeometryClass copy pin 0x16A230, the
// MeshMatDescClass copy pin 0x15DD10, matched clone_materials 0x1881C0 and
// the game operator new. The state-1 unwind destroys the list member via
// the 0x144690 list-dtor pin; the base unwind uses the 0x16CCC0 pin.

#include <string.h>
#include <new>
#include <windows.h>

// <new> supplies the placement operators; skip always.h's duplicates.
#define _OPERATOR_NEW_DEFINED_
#include "always.h"

#include "../WWLib/RefCountData.h"

class MultiListNodeClass
{
public:
	MultiListNodeClass() { Prev = Next = NextList = NULL; Object = NULL; List = NULL; }

	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	void *Object;
	void *List;
};

#include "../WWLib/MultiListObjectClass.h"

#pragma optimize("s", on)
class GenericMultiListClass
{
public:
	GenericMultiListClass() { Head.Next = Head.Prev = &Head; Head.Object = NULL; Head.NextList = NULL; }
	virtual ~GenericMultiListClass();

	MultiListNodeClass Head;
};
#pragma optimize("", on)

class Rva00144690 : public GenericMultiListClass
{
public:
	virtual ~Rva00144690();
};
// The proven DX8PolygonRendererList vtable slot 0 is rowed at 0x00144690.
typedef Rva00144690 DX8PolygonRendererList;

#include "MeshMatDescClass.h"

// The list declarations above supply the secondary base without the
// reference multilist header's duplicate class definitions.
#define MULTILIST_H
#include "MeshGeometryClass.h"

class GapFillerClass;

class MeshModelClass : public MeshGeometryClass
{
public:
	MeshModelClass(const MeshModelClass &that);
	virtual ~MeshModelClass();

protected:
	void clone_materials(const MeshModelClass &srcmesh);

private:
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;
	void *MatInfo;
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
extern MeshModelClass *MeshModelListHead;  // defined in MeshModelClassDefaultCtor.cpp

// ??0MeshModelClass@@QAE@ABV0@@Z
MeshModelClass::MeshModelClass(const MeshModelClass &that) :
	MeshGeometryClass(that),
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

	DefMatDesc = new MeshMatDescClass(*(that.DefMatDesc));
	if (that.AlternateMatDesc != NULL) {
		AlternateMatDesc = new MeshMatDescClass(*(that.AlternateMatDesc));
	}
	CurMatDesc = DefMatDesc;

	clone_materials(that);
}
