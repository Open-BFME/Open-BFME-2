// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// Size-optimised (/O1) emission of the CameraClass::Set_Viewport header inline.
//
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "texproject.h"
#include "vertmaterial.h"
#include "shader.h"
#include "texture.h"
#include "rendobj.h"
#include "rinfo.h"
#include "camera.h"
#include "matpass.h"
#include "bwrender.h"
#include "assetmgr.h"
#include "dx8wrapper.h"
#include "mpu.h"
#define DEBUG_SHADOW_RENDERING					0

extern void (CameraClass::*const g_bfmeCameraSetViewportAnchor)(const Vector2 &, const Vector2 &);
void (CameraClass::*const g_bfmeCameraSetViewportAnchor)(const Vector2 &, const Vector2 &) = &CameraClass::Set_Viewport;
