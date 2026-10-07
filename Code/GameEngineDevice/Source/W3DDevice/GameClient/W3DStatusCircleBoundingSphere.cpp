// cl: /Ireference/shims/bfme2_vector3 /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/W3DStatusCircle.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x0008E5B0 (68B). Only Get_Obj_Space_Bounding_Sphere is
// carried; the donor's other W3DStatusCircle definitions are omitted.
#define Matrix4x4 Matrix4  // BFME renamed it

#include <string.h>
#pragma intrinsic(memcpy)
#include "vector3.h" // use the verified BFME2 three-word constructor
#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"  // game/ WW3D2 BFME RenderObjClass must win over the reference tree's same-directory copy
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// BFME ShaderClass is 16 bytes (3 extra dwords after ShaderBits) — pull the
// shadow shim in before any WW3D2 header grabs the real 4-byte shader.h via
// a same-directory quoted include (assetmgr.h etc.). See shim header comment.
#include "WW3D2/Shader.h"

// BFME's index_count is a full 32-bit slot and its index-buffer constructor
// takes the count at full width; use the BFME declaration of DX8IndexBufferClass
// rather than the Zero Hour one the include path would otherwise find.
#define BFME_DYNAMIC_IB_UINT_CTOR_ABI
#include "../../../../Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h"

#include "W3DDevice/GameClient/W3DStatusCircle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assetmgr.h>
#include <texture.h>
#include <tri.h>
#include <colmath.h>
#include <coltest.h>
#include <rinfo.h>
#include <camera.h>
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/Shader.h"
#include "Common/GlobalData.h"
#include "common/MapObject.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ScriptEngine.h"

#define SC_DETAIL_BLEND ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_ONE, \
	ShaderClass::DSTBLEND_ZERO, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::DETAILCOLOR_SCALE, ShaderClass::DETAILALPHA_DISABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, \
	ShaderClass::DETAILCOLOR_SCALE, ShaderClass::DETAILALPHA_DISABLE) )

// Texturing, no zbuffer, disabled zbuffer write, primary gradient, alpha blending
#define SC_ALPHA ( SHADE_CNST(ShaderClass::PASS_ALWAYS, ShaderClass::DEPTH_WRITE_DISABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_SRC_ALPHA, \
	ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

// Texturing, no zbuffer, disabled zbuffer write, primary gradient, alpha blending
#define SC_ALPHA_Z ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_DISABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_SRC_ALPHA, \
	ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE, ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

// Texturing, no zbuffer, disabled zbuffer write, no gradient, add src to dest.
#define SC_ADD ( SHADE_CNST(ShaderClass::PASS_ALWAYS, ShaderClass::DEPTH_WRITE_DISABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_ONE, \
	ShaderClass::DSTBLEND_ONE, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_DISABLE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, \
	ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) )

#define VERTEX_BUFFER_TILE_LENGTH	32		//tiles of side length 32 (grid of 33x33 vertices).
#define VERTS_IN_BLOCK_ROW			(VERTEX_BUFFER_TILE_LENGTH+1)	



// BFME's DX8 vertex-buffer objects are four bytes larger than the vendored Zero
// Hour views.  This standalone view keeps the allocation size used by the retail
// body; the pinned constructor alias resolves its calls to the real class.
class BfmeDX8VertexBuffer
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	BfmeDX8VertexBuffer(unsigned fvf, unsigned short count, UsageType usage,
		unsigned size);

private:
	unsigned char m_bfmeBody[0x20];
};



// ??0W3DStatusCircle@@QAE@XZ
// Body in W3DStatusCircle_ctor.asm (exact 90B retail @ 0x00726000).
// Queue 0x0098914C was misplaced (inside unrelated x87 math). True body is
// the only non-dtor store of vtbl 0x01121018; C++ blocked by ShaderClass
// member-default (Reset→0x8441b) vs retail 4-dword shader init shape.


// ?Cast_Ray@W3DStatusCircle@@UAE_NAAVRayCollisionTestClass@@@Z present-unmatched



//@todo: MW Handle both of these properly!!
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DStatusCircleCtorThunk.cpp
// ??0W3DStatusCircle@@ present-unmatched


// ??4W3DStatusCircle@@QAEAAV0@ABV0@@Z present-unmatched


void W3DStatusCircle::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	Vector3 ObjSpaceCenter; ObjSpaceCenter.Set((float)1000*0.5f,(float)1000*0.5f,(float)0);
	float length = ObjSpaceCenter.Length();
	
	sphere.Init(ObjSpaceCenter, length);
}








struct W3DStatusCircleRetailResources
{
	char m_head[0xd8];
	DX8IndexBufferClass *m_indexBuffer;
	unsigned m_shaderBits;
	VertexMaterialClass *m_vertexMaterialClass;
	DX8VertexBufferClass *m_vertexBufferCircle;
	DX8VertexBufferClass *m_vertexBufferScreen;
};



#define NUM_TRI 20
//Allocate a heightmap of x by y vertices.
//data must be an array matching this size.



/** updateCircleVB puts a circle with a team color vertex buffer. */



/** updateCircleVB puts a circle with a team color vertex buffer. */



// ?Render@W3DStatusCircle@@UAEXAAVRenderInfoClass@@@Z present-unmatched

