// cl: /Ireference/shims/bfmeshader /FIshader.h /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIbfme_wwstring_teardown.h /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/bfmestages /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// platformsdk
// dxsdk
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
// Preserve native inline math without a competing Normalize COMDAT.
#include "always.h"
#include "wwmath.h"
#define BFME_VECTOR2_NORMALIZE_INLINE_ONLY
#include "../../../../../reference/shims/wwmath/Vector2.h"
#undef BFME_VECTOR2_NORMALIZE_INLINE_ONLY
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/render2d.cpp); this unit had no counterpart under Code/.

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
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

 /***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/render2d.cpp                           $*
 *                                                                                             *
 *                   $Org Author:: Byon_g                                                                                                                                                                                  $Modtime:: 1/24/01 3:54p                                               $*
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 08/05/02 2:40p                                              $*
 *                                                                                             *
 *                    $Revision:: 48                                                          $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 * 08/05/02 KM Texture class redesign 
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "render2d.h"
#include "mutex.h"
#include "ww3d.h"
#include "refcount.h"
#include "font3d.h"
#include "rect.h"
#include "texture.h"
#include "matrix4.h"
#include "matrix3d.h"
#include "dx8wrapper.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"
#include "vertmaterial.h"
#include "dx8fvf.h"
#include "dx8caps.h"
#include "wwprofile.h"
#include "wwmemlog.h"
#include "assetmgr.h"
// bfme link decl-only begin
template <> bool VectorClass<Vector2>::operator==(VectorClass<Vector2> const &) const;
// bfme link decl-only end

// Retail Vector2/Vector4 resize bodies belong to Vector2Resize.cpp.
// Declare their specializations so this consumer references those owners.
template <> bool VectorClass<Vector2>::Resize(int newsize, Vector2 const *array);

//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")

RectClass							Render2DClass::ScreenResolution( 0,0,0,0 );


// ?Set_Texture@Render2DClass@@ present-unmatched
void Render2DClass::Set_Texture(TextureClass* tex)
{
	REF_PTR_SET(Texture,tex);	
}

// Render2DClass::Enable_Texturing: Zero Hour's out-of-line body (Shader
// Set_Texturing) is not ported. BFME 2 has no out-of-line copy (retail holds
// no body for it) and inlines it as a byte store: W3DDisplay::drawRectClock
// (0x00045B45) writes byte +0x48 of the Render2DClass where Zero Hour calls
// Enable_Texturing(FALSE). A strong copy here would collide with that inline
// definition (W3DDisplayDrawRectClock.cpp) at link time.

// Screen globals read by the coordinate bias below. The resolution words are
// unsigned ints (retail converts them with fild plus the 2^32 fixup); the flag
// byte is WW3D::IsScreenUVBiased (ww3d.cpp), reached through its inline
// accessor so the coordinate bias and getter share the same defined datum.
// Matched DIR32 sites place these screen globals at VA 0x00DB5FD4 and
// 0x00DB5FD8: the data ledger's DX8Wrapper::ResolutionWidth/Height, defined
// in dx8wrapper.cpp (retail stores 640 and 480). They are protected statics,
// read here through a derived accessor (WW3D_RegistryDeviceWrappers.cpp
// precedent).
class Render2DDeviceAccess : public DX8Wrapper
{
public:
	using DX8Wrapper::Get_Device_Resolution_Width;
	using DX8Wrapper::Get_Device_Resolution_Height;
};

void	Render2DClass::Set_Coordinate_Range( const RectClass & range )
{
	// default range is (-1,1)-(1,-1)
	CoordinateScale.X = 2 / range.Width();
	CoordinateScale.Y = -2 / range.Height();
	CoordinateOffset.X = -(CoordinateScale.X * range.Left) - 1;
	CoordinateOffset.Y = -(CoordinateScale.Y * range.Top) + 1;

	// Retail folds the UV-bias straight into CoordinateOffset: no Biased copy
	// and no call. BFME1 derives the same shape for its own retail
	// (Render2DSetCoordinateRangeThunk.cpp over lotrbfme.exe 0x00933A50).
	if ( WW3D::Is_Screen_UV_Biased() ) {	// Global bias setting
		Vector2 bais_add( -0.5f ,-0.5f );	// offset by -0.5,-0.5 in pixels

		// Convert from pixels to (-1,1)-(1,-1) units
		bais_add.X = bais_add.X / ( (unsigned)Render2DDeviceAccess::Get_Device_Resolution_Width() * 0.5f );
		bais_add.Y = bais_add.Y / ( (unsigned)Render2DDeviceAccess::Get_Device_Resolution_Height() * -0.5f );

		CoordinateOffset.X = CoordinateOffset.X + bais_add.X;
		CoordinateOffset.Y = CoordinateOffset.Y + bais_add.Y;
	}
}

#if 0
#else
#endif

// ?Move@Render2DClass@@ present-unmatched
void	Render2DClass::Move( const Vector2 & move )	// Move all verts 
{
	Vector2 scaled_move;
	scaled_move.X = move.X * CoordinateScale.X;
	scaled_move.Y = move.Y * CoordinateScale.Y;
	for ( int i = 0; i < Vertices.Count(); i++ ) {
		Vertices[i] += scaled_move;
	}
}


/*
** Add Tri
*/
// Add_Tri is recovered in Render2DClassAddTri.cpp using the native batch layout.

// Add_Line(a, b, width, color) is recovered in Render2DClassAddQuadColor.cpp (0x00042A4D).


// Add_Line(a, b, width, color, color2) is recovered in Render2DClassAddQuadColor.cpp (0x00042C80).


// ?Set_Font@Render2DTextClass@@ present-unmatched
void	Render2DTextClass::Set_Font( Font3DInstanceClass *font )
{
	REF_PTR_SET(Font,font);

	if ( Font != NULL ) {
		Set_Texture( Font->Peek_Texture() );

	#define	BLOCK_CHAR	0
		BlockUV = Font->Char_UV( BLOCK_CHAR );
		// Inset it a bit to be sure we have no edge problems
		BlockUV.Inflate( Vector2(-BlockUV.Width()/4, -BlockUV.Height()/4) );
	}
}

