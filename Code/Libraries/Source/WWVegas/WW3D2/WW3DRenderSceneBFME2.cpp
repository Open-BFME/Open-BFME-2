// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIbfme_wwstring_teardown.h /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ww3d /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// Native 001182A0..0011842F, 399B, cdecl bool-return ABI, called by
// verified Rva00118660Call. Semantic lead: BFME1 6583b3c1 WW3DRenderScene.cpp
// and ZH ww3d.cpp scene Render; retail supplies an existing RenderInfo.
// Target facts: scene polygon mode +14, ambient vcall +1C, Render +58;
// camera On_Frame_Update +34, camera pointer at RenderInfo+0; renderer+4.
// The original entry name remains unknown. Existing named globals/callees
// are reused from matched WW3DRenderObjRender and DX8SetAmbient.
// The header's Convert_Color x87 rounding helper has the proven
// control-word/codegen requirements, as in matched DX8SetAmbient.
	// dx8wrapper.cpp's protected static at VA 0x00DEDC70.
	// dllimport: inlined at every use, so no out-of-line copy competes with retail's
	// Convert_Color (0x0006E1C0) or Set_Ambient (0x00117F50, DX8SetAmbient.cpp).
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "ww3d.h"	// the bfme2_ww3d shims must win both include guards, ww3d.h first
#include "dx8wrapper.h"	// the bfme2_ww3d shim (BFME 2 DX8Wrapper spellings) has to win the include guard
#include "rinfo.h"
#include "camera.h"
#include "scene.h"
#include "sortingrenderer.h"
#include "static_sort_list.h"

class DX8MeshRendererClass
{
public:
	void Invalidate( bool shutdown );
	void Flush();
	void Set_Camera(CameraClass *camera) { m_camera = camera; }
	void Clear_Pending_Delete_Lists(void);
	char m_pad00[0x4];
private:
	CameraClass *m_camera; // +0x04
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class Rva00DF6F94GapFillerContext
{
public:
	void rva174ba6();
};

extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

// The +0x87 static flush: the callee reads only the global 0x00DEC4F4 and an
// SSE constant: the rowed static SortingRendererClass::Flush (SortingRendererBFME1.cpp).
bool Rva001182A0(void *owner, RenderInfoClass &rinfo)
{
    if (!WW3D::IsInitted) return true;
    SceneClass *scene=static_cast<SceneClass *>(owner);
    rinfo.Camera.On_Frame_Update();
    rinfo.Camera.Apply();
    switch (scene->Get_Polygon_Mode()) {
    case SceneClass::POINT: DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE,D3DFILL_POINT); break;
    case SceneClass::LINE: DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE,D3DFILL_WIREFRAME); break;
    case SceneClass::FILL: DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE,D3DFILL_SOLID); break;
    }
    DX8Wrapper::Set_Ambient(scene->Get_Ambient_Light());
    TheDX8MeshRenderer->Set_Camera(&rinfo.Camera);
    scene->Render(rinfo);
    TheDX8MeshRenderer->Flush();
    TheMeshGapFillerContext->rva174ba6();
    bool old_enable=WW3D::AreStaticSortListsEnabled;
    WW3D::AreStaticSortListsEnabled=false;
    WW3D::CurrentStaticSortLists->Render_And_Clear(rinfo);
    WW3D::AreStaticSortListsEnabled=old_enable;
    SortingRendererClass::Flush();
    TheDX8MeshRenderer->Clear_Pending_Delete_Lists();
    return true;
}
