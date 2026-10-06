// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4
// BFME1 byte-identical donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/light.cpp
// Split from light.cpp (whose nested-ZH scene.h puts Scene::Register at +0x3C);
// direct BFME1 scene.h keeps Register at retail +0x38 (Get_Scene_ID non-virtual).
#include "light.h"
#include "ww3d.h"
#include "rinfo.h"
#include "scene.h"

/***********************************************************************************************
 * LightClass::Notify_Added -- lights add themselves to the VP list when added                 *
 *=============================================================================================*/
void LightClass::Notify_Added(SceneClass * scene)
{
	RenderObjClass::Notify_Added(scene);
	scene->Register(this,SceneClass::LIGHT);
}

/***********************************************************************************************
 * LightClass::Notify_Removed -- lights remove themselves from the VP list when removed        *
 *=============================================================================================*/
void LightClass::Notify_Removed(SceneClass * scene)
{
	scene->Unregister(this,SceneClass::LIGHT);
	RenderObjClass::Notify_Removed(scene);
}
