// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep -ICode/Libraries/Source/WWVegas/WW3D2
//
// ?Unregister_Mesh_Type@DX8MeshRendererClass@@QAEXPAVMeshModelClass@@@Z at
// retail 0x001445E0 (54B). Dedicated TU: BFME1's dx8renderer.cpp body also
// removes the model from _RegisteredMeshList and deletes the GapFiller, but
// retail is trimmed to just the PolygonRendererList drain, so the body
// cannot ride the donor TU verbatim.
//
// Minimal TU-local hierarchy copied from the matched Clear_Pending_Delete_
// Lists TU in this folder: MultiListClass<T>::Remove_Head is the
// header-inline forwarder to the matched Internal_Remove_List_Head @0x6109A0
// (27B, multilist.cpp); the polygon-renderer list lives at MeshModelClass
// +0x9C; `::delete` lowers to the virtual vf0(0) call plus the matched
// scalar operator delete @0x2FD60, the same idiom as the matched Invalidate
// and Clear loops. No pins needed (both callees already matched).

#include "../WWLib/MultiListObjectClass.h"

#include "../WWLib/GenericMultiListClass.h"


template <class ObjectType>
class MultiListClass : public GenericMultiListClass
{
public:
	ObjectType *Remove_Head()
	{
		return (ObjectType *)Internal_Remove_List_Head();
	}
};

#include "dx8polygonrendererClass.h"

class MeshModelClass
{
public:
	char _pad[0x9C];
	MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
};

#include "DX8MeshRendererClass.h"

// ?Unregister_Mesh_Type@DX8MeshRendererClass@@QAEXPAVMeshModelClass@@@Z
void DX8MeshRendererClass::Unregister_Mesh_Type(MeshModelClass *mmc)
{
	while (DX8PolygonRendererClass *dX8PolygonRenderer = mmc->PolygonRendererList.Remove_Head()) {
		::delete dX8PolygonRenderer;
	}
}
