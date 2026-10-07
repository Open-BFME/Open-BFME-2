// cl: /O1 /Ob2 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /arch:SSE2 /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
//
// AABoxClass::Init_Min_Max / Init(MinMaxAABoxClass) / CollisionMath::Overlap_Test(Plane/Point) and the
// AABTreeLinkClass ctor: retail holds one size-optimised (/O1) out-of-line copy of each header body.
// The pointer constants and anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#include "aabtreecull.h"
#include "chunkio.h"
#include "iostruct.h"
#include <string.h>
#include "sphere.h"
#include "colmath.h"
#include "colmathinlines.h"

extern void (AABoxClass::*const g_bfmeAABoxInitMinMaxAnchor)(const Vector3 &, const Vector3 &);
void (AABoxClass::*const g_bfmeAABoxInitMinMaxAnchor)(const Vector3 &, const Vector3 &) = &AABoxClass::Init_Min_Max;
extern void (AABoxClass::*const g_bfmeAABoxInitAnchor)(const MinMaxAABoxClass &);
void (AABoxClass::*const g_bfmeAABoxInitAnchor)(const MinMaxAABoxClass &) = &AABoxClass::Init;
extern CollisionMath::OverlapType (*const g_bfmeOverlapPlanePointAnchor)(const PlaneClass &, const Vector3 &);
CollisionMath::OverlapType (*const g_bfmeOverlapPlanePointAnchor)(const PlaneClass &, const Vector3 &) = &CollisionMath::Overlap_Test;
// ?_bfmeAABTreeLinkAnchor absent-from-retail
// Emit the constructor without instantiating an unrelated allocation pool.
AABTreeLinkClass *_bfmeAABTreeLinkAnchor(void *storage, AABTreeCullSystemClass *system)
{
	return ::new (storage) AABTreeLinkClass(system);
}
