// cl: /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
//
// PlaneClass::Compute_Intersection / In_Front and Matrix3D::Rotate_Vector: retail holds one
// size-optimised (/O1) out-of-line copy of each header body.
// The pointer constants and anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#define Matrix4x4 Matrix4  // BFME renamed it
#include "decalmsh.h"
#include "decalsys.h"
#include "rinfo.h"
#include "mesh.h"
#include "meshmdl.h"
#include "plane.h"
#include "statistics.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "simplevec.h"
#include "texture.h"
#include "dx8wrapper.h"
#include "dx8caps.h"
#define DISABLE_CLIPPING	0

extern bool (PlaneClass::*const g_bfmePlaneComputeIntersectionAnchor)(const Vector3 &, const Vector3 &, float *) const;
bool (PlaneClass::*const g_bfmePlaneComputeIntersectionAnchor)(const Vector3 &, const Vector3 &, float *) const = &PlaneClass::Compute_Intersection;
extern bool (PlaneClass::*const g_bfmePlaneInFrontAnchor)(const Vector3 &) const;
bool (PlaneClass::*const g_bfmePlaneInFrontAnchor)(const Vector3 &) const = &PlaneClass::In_Front;
extern void (*const g_bfmeRotateVectorAnchor)(const Matrix3D &, const Vector3 &, Vector3 *);
void (*const g_bfmeRotateVectorAnchor)(const Matrix3D &, const Vector3 &, Vector3 *) = &Matrix3D::Rotate_Vector;
