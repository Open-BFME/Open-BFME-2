// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
//
// MaterialInfoClass::Get_Vertex_Material (0x000B49A8) and UVBufferClass(int,const char*) (0x000D1EF8): retail holds one size-optimised (/O1) out-of-line copy of each header body.
// The pointer constants or anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//

// Retail's kept Vector2 destructor (0x000D1DC8, 26 bytes, vtable store 0xBCE328) is
// emitted by sharebuf_vector2_ctor.cpp.  The sweep shim's own body is the GeneralsMD
// shape (null test plus RawBuffer/Array clears), which retail's kept object does not
// have, so this unit must only call it.  The declaration has to precede dynamesh.h,
// whose inline UVBufferClass members instantiate the base class destructor.
#include "sharebuf.h"
class Vector2;
template <> ShareBufferClass<Vector2>::~ShareBufferClass(void);

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
// The UVBufferClass bodies this unit hosts destroy the ShareBufferClass<Vector2>
// buffer through the free below: it must be the nothrow form so the inlined
// destructor comes out at retail's 26 bytes (0x000D1DC8, no EH frame) instead of
// the 68-byte throwing shape.

#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "dynamesh.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "rinfo.h"
#include "camera.h"
#include "dx8fvf.h"

extern VertexMaterialClass *(MaterialInfoClass::*const g_bfmeGetVertexMaterialAnchor)(int);
VertexMaterialClass *(MaterialInfoClass::*const g_bfmeGetVertexMaterialAnchor)(int) = &MaterialInfoClass::Get_Vertex_Material;
// ?_bfmeUVBufferAnchor@@YAPAVUVBufferClass@@HPBD@Z absent-from-retail
UVBufferClass *_bfmeUVBufferAnchor(int count, const char *msg)
{
	return new UVBufferClass(count, msg);
}
