// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// Matrix3D / OBBoxClass header bodies (Pre_Rotate_Z Rotate_X In_Place_Pre_Rotate_X/Y/Z Translate(x y z) Set(12 floats)
// Set(axis, s, c) Set(axis, angle) Matrix3D(axis, angle) Matrix3D(const Vector3&) OBBoxClass(const Vector3& const Vector3&) and the Matrix3x3(bool) it calls):
// retail holds one size-optimised (/O1) out-of-line copy of each.
// The pointer constants and the anchor below only make this TU emit them out of line; they are not retail code or data.
//
#include "../../../../../../reference/shims/bfme_vp_math/vector4.h" // keep native inline math without competing Vector4 helpers
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#define DEFINE_SLOWDEATHPHASE_NAMES
#include "Common/GameLOD.h"
#include "Common/INI.h"
#include "Common/RandomValue.h"
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/SlowDeathBehavior.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/SlavedUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/Weapon.h"
#include "GameClient/Drawable.h"
#ifdef _INTERNAL
#endif

#include "WWMath/matrix3d.h"
#include "WWMath/obbox.h"
extern void (Matrix3D::*const g_bfmePreRotateZAnchor)(float);
void (Matrix3D::*const g_bfmePreRotateZAnchor)(float) = &Matrix3D::Pre_Rotate_Z;
extern void (Matrix3D::*const g_bfmeInPlacePreRotateXAnchor)(float);
void (Matrix3D::*const g_bfmeInPlacePreRotateXAnchor)(float) = &Matrix3D::In_Place_Pre_Rotate_X;
extern void (Matrix3D::*const g_bfmeInPlacePreRotateYAnchor)(float);
void (Matrix3D::*const g_bfmeInPlacePreRotateYAnchor)(float) = &Matrix3D::In_Place_Pre_Rotate_Y;
extern void (Matrix3D::*const g_bfmeInPlacePreRotateZAnchor)(float);
void (Matrix3D::*const g_bfmeInPlacePreRotateZAnchor)(float) = &Matrix3D::In_Place_Pre_Rotate_Z;
extern void (Matrix3D::*const g_bfmeTranslate3fAnchor)(float, float, float);
void (Matrix3D::*const g_bfmeTranslate3fAnchor)(float, float, float) = &Matrix3D::Translate;
extern void (Matrix3D::*const g_bfmeSet12fAnchor)(float, float, float, float, float, float, float, float, float, float, float, float);
void (Matrix3D::*const g_bfmeSet12fAnchor)(float, float, float, float, float, float, float, float, float, float, float, float) = &Matrix3D::Set;
extern void (Matrix3D::*const g_bfmeRotateXAnchor)(float);
void (Matrix3D::*const g_bfmeRotateXAnchor)(float) = &Matrix3D::Rotate_X;
extern void (Matrix3D::*const g_bfmeSetAxisSinCosAnchor)(const Vector3 &, float, float);
void (Matrix3D::*const g_bfmeSetAxisSinCosAnchor)(const Vector3 &, float, float) = &Matrix3D::Set;
extern void (Matrix3D::*const g_bfmeSetAxisAngleAnchor)(const Vector3 &, float);
void (Matrix3D::*const g_bfmeSetAxisAngleAnchor)(const Vector3 &, float) = &Matrix3D::Set;
#pragma inline_depth(0)
// ?_bfmeMatrixCtorAnchor@@YAXPAVMatrix3D@@PAVOBBoxClass@@ABVVector3@@@Z absent-from-retail
void _bfmeMatrixCtorAnchor(Matrix3D *m, OBBoxClass *b, const Vector3 &v)
{
	new (m) Matrix3D(v);
	new (m) Matrix3D(v, 0.0f);
	new (b) OBBoxClass(v, v);
}
#pragma inline_depth()
