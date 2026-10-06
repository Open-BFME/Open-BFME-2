// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /arch:SSE2 /Ireference/shims/bfmeshader /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// readable body of ?Invert_Backface_Culling@ShaderClass@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
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
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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
 *                     $Archive:: /Commando/Code/ww3d2/shader.cpp                             $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 12/11/01 5:15p                                              $*
 *                                                                                             *
 *                    $Revision:: 21                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   ShaderClass::Init_From_Material3 -- Initialize a shader from a Material3 structure        *
 *   ShaderClass::Apply -- Apply the renderstates for this shader                              *
 *   ShaderClass::Invert_Backface_Culling -- Globally invert the sense of all backface culling *
 *   ShaderClass::Is_Backface_Culling_Inverted -- Is backface culling inverted?                *
 *   ShaderClass::Get_SS_Category -- Helper function for static sort system                    *
 *   ShaderClass::Guess_Sort_Level -- Guess the static sort level                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <dx8caps.h> // BFME2 layout must win the reference include guard.

#include "shader.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include "Dx8Wrapper.h"
#include "dx8caps.h"

extern unsigned long _PolygonCullMode;


/*
** Definitions of the preset shaders:
*/

// Texturing, zbuffer, primary gradient, no blending

#define SC_OPAQUE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_ENABLE, COLOR_WRITE_ENABLE, SRCBLEND_ONE, \
	DSTBLEND_ZERO, FOG_DISABLE, GRADIENT_MODULATE, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetOpaqueShader(SC_OPAQUE);

// Texturing, zbuffer, disabled zbuffer write, primary gradient, additive blending
#define SC_ADDITIVE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_ONE, \
	DSTBLEND_ONE, FOG_DISABLE, GRADIENT_MODULATE, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetAdditiveShader(SC_ADDITIVE);

// Texturing, zbuffer, disabled zbuffer write, primary gradient, additive blending, bumpenvmap
#define SC_BUMPENVMAP ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_ONE, \
	DSTBLEND_ONE, FOG_DISABLE, GRADIENT_BUMPENVMAP, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_ADD, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetBumpenvmapShader(SC_BUMPENVMAP);

// Texturing, zbuffer, disabled zbuffer write, primary gradient, alpha blending
#define SC_ALPHA ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_SRC_ALPHA, \
	DSTBLEND_ONE_MINUS_SRC_ALPHA, FOG_DISABLE, GRADIENT_MODULATE, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetAlphaShader(SC_ALPHA);

// Texturing, zbuffer, disabled zbuffer write, primary gradient, multiplicative blending
#define SC_MULTIPLICATIVE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_ZERO, \
	DSTBLEND_SRC_COLOR, FOG_DISABLE, GRADIENT_MODULATE, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetMultiplicativeShader(SC_MULTIPLICATIVE);

// Texturing, no zbuffer reading/writing, no gradients, no blending, no
// fogging - mostly for opaque 2D objects.
#define SC_OP_2D ( SHADE_CNST(PASS_ALWAYS, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_ONE, \
	DSTBLEND_ZERO, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetOpaque2DShader(SC_OP_2D);

// Texturing, default zbuffer reading, no zbuffer writing, no gradients, no blending, no
// fogging - mostly for opaque sprite objects.
#define SC_OP_SPRITE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_ONE, \
	DSTBLEND_ZERO, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetOpaqueSpriteShader(SC_OP_SPRITE);


// Texturing, no zbuffer reading/writing, no gradients, additive blending,
// no fogging - mostly for additive 2D objects.
#define SC_ADD_2D ( SHADE_CNST(PASS_ALWAYS, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_ONE, \
	DSTBLEND_ONE, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetAdditive2DShader(SC_ADD_2D);

// Texturing, no zbuffer reading/writing, no gradients, alpha blending, no
// fogging - mostly for alpha-blended 2D objects.
#define SC_ALPHA_2D ( SHADE_CNST(PASS_ALWAYS, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_SRC_ALPHA, DSTBLEND_ONE_MINUS_SRC_ALPHA, FOG_DISABLE, GRADIENT_DISABLE, \
	SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetAlpha2DShader(SC_ALPHA_2D);

// Texturing, default zbuffer reading, no zbuffer writing, no gradients,
// additive blending, no fogging - mostly for use in additive sprite
// objects.
#define SC_ADD_SPRITE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_ONE, DSTBLEND_ONE, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, \
	TEXTURING_ENABLE, ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetAdditiveSpriteShader(SC_ADD_SPRITE);

// Texturing, default zbuffer reading, no zbuffer writing, no gradients,
// alpha blending, no fogging - mostly for use in alpha-blended sprite
// objects.
#define SC_ALPHA_SPRITE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_SRC_ALPHA, DSTBLEND_ONE_MINUS_SRC_ALPHA, FOG_DISABLE, GRADIENT_DISABLE, \
	SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetAlphaSpriteShader(SC_ALPHA_SPRITE);

// No texturing, default zbuffer reading/writing, primary gradient, no
// blending, no fogging - mostly for use in solid-colored opaque objects.
#define SC_OPAQUE_SOLID ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_ENABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_ONE, DSTBLEND_ZERO, FOG_DISABLE, GRADIENT_MODULATE, SECONDARY_GRADIENT_DISABLE, \
	TEXTURING_DISABLE, ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetOpaqueSolidShader(SC_OPAQUE_SOLID);

// No texturing, default zbuffer reading, no zbuffer writing, primary
// gradient, additive blending, no fogging - mostly for use in solid-colored
// additive objects.
#define SC_ADDITIVE_SOLID ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_ONE, DSTBLEND_ONE, FOG_DISABLE, GRADIENT_MODULATE, SECONDARY_GRADIENT_DISABLE, \
	TEXTURING_DISABLE, ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetAdditiveSolidShader(SC_ADDITIVE_SOLID);

// No texturing, default zbuffer reading, no zbuffer writing, primary
// gradient, alpha blending, no fogging - mostly for use in solid-colored
// alpha objects.
#define SC_ALPHA_SOLID ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_SRC_ALPHA, DSTBLEND_ONE_MINUS_SRC_ALPHA, FOG_DISABLE, GRADIENT_MODULATE, \
	SECONDARY_GRADIENT_DISABLE, TEXTURING_DISABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetAlphaSolidShader(SC_ALPHA_SOLID);

// Texturing, no zbuffer reading/writing, no gradients, no blending, alpha
// testing, no fogging - mostly for "pure" alpha-tested 2D objects.
#define SC_ATEST_2D ( SHADE_CNST(PASS_ALWAYS, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_ONE, DSTBLEND_ZERO, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, \
	TEXTURING_ENABLE, ALPHATEST_ENABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetATest2DShader(SC_ATEST_2D);

// Texturing, default zbuffer reading and writing, no gradients, no
// blending, alpha testing, no fogging - mostly for "pure" alpha-tested
// sprite objects.
#define SC_ATEST_SPRITE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_ENABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_ONE, DSTBLEND_ZERO, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, \
	TEXTURING_ENABLE, ALPHATEST_ENABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetATestSpriteShader(SC_ATEST_SPRITE);

// Texturing, no zbuffer reading/writing, no gradients, alpha blending AND
// alpha testing, no fogging - mostly for alpha-tested and blended 2D
// objects.
#define SC_ATESTBLEND_2D ( SHADE_CNST(PASS_ALWAYS, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_SRC_ALPHA, DSTBLEND_ONE_MINUS_SRC_ALPHA, FOG_DISABLE, GRADIENT_DISABLE, \
	SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_ENABLE, CULL_MODE_ENABLE, DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetATestBlend2DShader(SC_ATESTBLEND_2D);

// Texturing, default zbuffer reading and writing, no gradients, alpha
// blending AND alpha testing, no fogging - mostly for use in alpha-tested
// and blended sprite objects.
#define SC_ATESTBLEND_SPRITE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_ENABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_SRC_ALPHA, DSTBLEND_ONE_MINUS_SRC_ALPHA, FOG_DISABLE, GRADIENT_DISABLE, \
	SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_ENABLE, CULL_MODE_ENABLE, DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetATestBlendSpriteShader(SC_ATESTBLEND_SPRITE);

// Texturing, no zbuffer reading/writing, no gradients, screen blending,
// no fogging - mostly for screen-blended 2D objects.
#define SC_SCREEN_2D ( SHADE_CNST(PASS_ALWAYS, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_ONE, \
	DSTBLEND_ONE_MINUS_SRC_COLOR, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, \
	TEXTURING_ENABLE, ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetScreen2DShader(SC_SCREEN_2D);

// Texturing, default zbuffer reading, no zbuffer writing, no gradients,
// screen blending, no fogging - mostly for use in screen-blended sprite
// objects.
#define SC_SCREEN_SPRITE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_ONE, DSTBLEND_ONE_MINUS_SRC_COLOR, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, \
	TEXTURING_ENABLE, ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetScreenSpriteShader(SC_SCREEN_SPRITE);

// Texturing, no zbuffer reading/writing, no gradients, multiplicative
// blending, no fogging - mostly for multiplicatively blended 2D objects.
#define SC_MUL_2D ( SHADE_CNST(PASS_ALWAYS, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, SRCBLEND_ZERO, \
	DSTBLEND_SRC_COLOR, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, TEXTURING_ENABLE, \
	ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetMultiplicative2DShader(SC_MUL_2D);

// Texturing, default zbuffer reading, no zbuffer writing, no gradients,
// multiplicative blending, no fogging - mostly for use in multiplicatively
// blended sprite objects.
#define SC_MUL_SPRITE ( SHADE_CNST(PASS_LEQUAL, DEPTH_WRITE_DISABLE, COLOR_WRITE_ENABLE, \
	SRCBLEND_ZERO, DSTBLEND_SRC_COLOR, FOG_DISABLE, GRADIENT_DISABLE, SECONDARY_GRADIENT_DISABLE, \
	TEXTURING_ENABLE, ALPHATEST_DISABLE, CULL_MODE_ENABLE, \
	DETAILCOLOR_DISABLE, DETAILALPHA_DISABLE) )
ShaderClass ShaderClass::_PresetMultiplicativeSpriteShader(SC_MUL_SPRITE);


/***********************************************************************************************
 * ShaderClass::Init_From_Material3 -- Initialize a shader from a Material3 structure          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/24/2001  gth : Created.                                                                 *
 *=============================================================================================*/
void ShaderClass::Init_From_Material3(const W3dMaterial3Struct & mat3)
{
	if ( mat3.Attributes & W3DMATERIAL_USE_ALPHA ) {
		Set_Depth_Mask( DEPTH_WRITE_DISABLE );
		Set_Dst_Blend_Func( DSTBLEND_ONE_MINUS_SRC_ALPHA );
		Set_Src_Blend_Func( SRCBLEND_SRC_ALPHA );
	}
}


/***********************************************************************************************
 * ShaderClass::Enable_Fog -- Turn on fog for this shader.                                     *
 *                                                                                             *
 * Enable most appropriate fog mode (FOG_ENABLE, FOG_SCALE_FRAGMENT or FOG_WHITE) for given	  *
 *	source and destination blends.																				  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:																												  *
 *		05/02/00    IML : Created.																					  *	
 *=============================================================================================*/

void ShaderClass::Enable_Fog (const char *source)
{
	// Enable the appropriate fog mode based on shader's source and destination blends.
	switch (Get_Src_Blend_Func()) {

		case ShaderClass::SRCBLEND_ZERO:
			if (Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_SRC_COLOR) {
				Set_Fog_Func (ShaderClass::FOG_WHITE);
			} else {
				Report_Unable_To_Fog (source);
			}	
			break;

		case ShaderClass::SRCBLEND_ONE:
			switch (Get_Dst_Blend_Func()) {
				
				case ShaderClass::DSTBLEND_ZERO:							// Opaque.
					Set_Fog_Func (ShaderClass::FOG_ENABLE);
					break;

				case ShaderClass::DSTBLEND_ONE:							// Additive.
				case ShaderClass::DSTBLEND_ONE_MINUS_SRC_COLOR:		// Screen.
					Set_Fog_Func (ShaderClass::FOG_SCALE_FRAGMENT);
					break;

				default:
					Report_Unable_To_Fog (source);
					break;
			}
			break;

		case ShaderClass::SRCBLEND_SRC_ALPHA:
			if (Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_ONE_MINUS_SRC_ALPHA) {
				Set_Fog_Func (ShaderClass::FOG_ENABLE);
			} else {
				Report_Unable_To_Fog (source);
			}	
			break;

		case ShaderClass::SRCBLEND_ONE_MINUS_SRC_ALPHA:
			if (Get_Dst_Blend_Func() == ShaderClass::DSTBLEND_SRC_ALPHA) {
				Set_Fog_Func (ShaderClass::FOG_ENABLE);
			} else {
				Report_Unable_To_Fog (source);
			}	
			break;
	}
}


/***********************************************************************************************
 * ShaderClass::Report_Unable_To_Fog --																		  *	
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:																												  *
 *		10/04/00    IML : Created.																					  *	
 *=============================================================================================*/
// ?Report_Unable_To_Fog@ShaderClass@@IAEXPBD@Z present-unmatched
void ShaderClass::Report_Unable_To_Fog (const char *source)
{
	#ifdef WWDEBUG
	static unsigned _reportcount = 0;

	const char		*unabletofogtext		= "WARNING: Unable to fog shader in %s with given blending mode.\r\n";
	const char		*unabletofogmoretext = "WARNING: Unable to fog additional shaders (further warnings will be suppressed).\r\n";
	const unsigned  maxreportcount		= 10;

	// Limit the no. of warning messages to some practical maximum. Suppress all subsequent warnings.
	if (_reportcount < maxreportcount) {
		WWDEBUG_SAY ((unabletofogtext, source));
		_reportcount++;
	} else {
		if (_reportcount == maxreportcount) {
			WWDEBUG_SAY ((unabletofogmoretext));
			_reportcount++;
		}
	}
	#endif
}

class Blend
{
public:

	Blend(D3DBLEND f, bool ab)
	{
		func = f;
		useAlpha = ab;
	}

	D3DBLEND	func;
	bool		useAlpha;
};

const Blend srcBlendLUT[ShaderClass::SRCBLEND_MAX] = 
{
	Blend(D3DBLEND_ZERO, false),
	Blend(D3DBLEND_ONE, false),
	Blend(D3DBLEND_SRCALPHA, true),
 	Blend(D3DBLEND_DESTCOLOR, true)
};

const Blend dstBlendLUT[ShaderClass::DSTBLEND_MAX] = 
{
	Blend(D3DBLEND_ZERO, false),
	Blend(D3DBLEND_ONE, false),
 	Blend(D3DBLEND_SRCCOLOR, false),
 	Blend(D3DBLEND_INVSRCCOLOR, false),
 	Blend(D3DBLEND_SRCALPHA, true),
 	Blend(D3DBLEND_INVSRCALPHA, true)
};


/***********************************************************************************************
 * ShaderClass::Apply -- Apply the renderstates for this shader                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/24/2001  gth : Created.                                                                 *
 *=============================================================================================*/


/***********************************************************************************************
 * ShaderClass::Invert_Backface_Culling -- Globally invert the sense of all backface culling   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/24/2001  gth : Created.                                                                 *
 *=============================================================================================*/
void ShaderClass::Invert_Backface_Culling(bool onoff)
{
	if (onoff == true) {
		_PolygonCullMode = D3DCULL_CCW;
	} else {
		_PolygonCullMode = D3DCULL_CW;
	}
	Invalidate();
}


/***********************************************************************************************
 * ShaderClass::Get_SS_Category -- Helper function for static sort system                      *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   7/13/2001  hy : Created.                                                                  *
 *=============================================================================================*/
// ?Get_SS_Category@ShaderClass@@QBE?AW4StaticSortCategoryType@1@XZ
ShaderClass::StaticSortCategoryType ShaderClass::Get_SS_Category(void) const
{
	// category: Opaque
	if ( (ALPHATEST_DISABLE==Get_Alpha_Test()) && (DSTBLEND_ZERO==Get_Dst_Blend_Func()) )
		return SSCAT_OPAQUE;
	// category: Alpha Test
	if ((ALPHATEST_ENABLE==Get_Alpha_Test()) || (ALPHATEST_MAX==Get_Alpha_Test()))	{
		if (DSTBLEND_ZERO==Get_Dst_Blend_Func()) return SSCAT_ALPHA_TEST;
		if ( (SRCBLEND_SRC_ALPHA==Get_Src_Blend_Func()) &&
			  (DSTBLEND_ONE_MINUS_SRC_ALPHA==Get_Dst_Blend_Func()) )
			  return SSCAT_ALPHA_TEST;
	}
	// category: Additive
	if ( (SRCBLEND_ONE==Get_Src_Blend_Func()) && (DSTBLEND_ONE==Get_Dst_Blend_Func()) )
		return SSCAT_ADDITIVE;
	// category: Screen
	if ( (SRCBLEND_ONE==Get_Src_Blend_Func()) && (DSTBLEND_ONE_MINUS_SRC_COLOR==Get_Dst_Blend_Func()) )
		return SSCAT_SCREEN;
	// category: Everything else
	return SSCAT_OTHER;
}


/***********************************************************************************************
 * ShaderClass::Guess_Sort_Level -- Guess the static sort level                                *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   8/27/2001  hy : Created.                                                                  *
 *=============================================================================================*/
int ShaderClass::Guess_Sort_Level(void) const
{
	int sort_level;
	StaticSortCategoryType scat=Get_SS_Category();

	switch (scat)
	{
	case ShaderClass::SSCAT_OPAQUE:
	case ShaderClass::SSCAT_ALPHA_TEST:
		sort_level=SORT_LEVEL_NONE;
		break;
	case ShaderClass::SSCAT_SCREEN:
		sort_level=SORT_LEVEL_BIN2;
		break;
	case ShaderClass::SSCAT_ADDITIVE:
		sort_level=SORT_LEVEL_BIN3;
		break;
	default:
		sort_level=SORT_LEVEL_BIN1;
		break;
	}
	return sort_level;
}

/***********************************************************************************************
 * ShaderClass::Is_Backface_Culling_Inverted -- Is backface culling inverted?                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/24/2001  gth : Created.                                                                 *
 *=============================================================================================*/
bool ShaderClass::Is_Backface_Culling_Inverted(void)
{
	return (_PolygonCullMode == D3DCULL_CCW);
}

// BFME2 added a 7th primary-gradient value (retail Get_Description at
// 0x138280 prints GRADIENT_MODULATE_OR_2X for bits 10-12 == 6). The shared
// shader.h still ends at GRADIENT_MODULATE2X, so the value lives here until
// the header catches up; unqualified lookup will prefer the enumerator once
// it exists, so this line goes inert on its own.
static const ShaderClass::PriGradientType GRADIENT_MODULATE_OR_2X = (ShaderClass::PriGradientType)6;

const StringClass& ShaderClass::Get_Description(StringClass& str) const
{
	str="";
	switch (Get_Depth_Compare()) {
	case PASS_NEVER: str+="DEPTH_COMPARE:PASS_NEVER | "; break;
	case PASS_LESS: str+="DEPTH_COMPARE:PASS_LESS | "; break;
	case PASS_EQUAL: str+="DEPTH_COMPARE:PASS_EQUAL | "; break;
	case PASS_LEQUAL: str+="DEPTH_COMPARE:PASS_LEQUAL | "; break;
	case PASS_GREATER: str+="DEPTH_COMPARE:PASS_GREATER | "; break;
	case PASS_NOTEQUAL: str+="DEPTH_COMPARE:PASS_NOTEQUAL | "; break;
	case PASS_GEQUAL: str+="DEPTH_COMPARE:PASS_GEQUAL | "; break;
	case PASS_ALWAYS: str+="DEPTH_COMPARE:PASS_ALWAYS | "; break;
	}

	switch (Get_Depth_Mask()) {
	case DEPTH_WRITE_DISABLE: str+="DEPTH_WRITE_DISABLE | "; break;
	case DEPTH_WRITE_ENABLE: str+="DEPTH_WRITE_ENABLE | "; break;
	}

	switch (Get_Color_Mask()) {
	case COLOR_WRITE_DISABLE: str+="COLOR_WRITE_DISABLE | "; break;
	case COLOR_WRITE_ENABLE: str+="COLOR_WRITE_ENABLE | "; break;
	}

	switch (Get_Dst_Blend_Func()) {
	case DSTBLEND_ZERO: str+="DSTBLEND_ZERO | "; break;
  	case DSTBLEND_ONE: str+="DSTBLEND_ONE | "; break;
 	case DSTBLEND_SRC_COLOR: str+="DSTBLEND_SRC_COLOR | "; break;
 	case DSTBLEND_ONE_MINUS_SRC_COLOR: str+="DSTBLEND_ONE_MINUS_SRC_COLOR | "; break;
 	case DSTBLEND_SRC_ALPHA: str+="DSTBLEND_SRC_ALPHA | "; break;
 	case DSTBLEND_ONE_MINUS_SRC_ALPHA: str+="DSTBLEND_ONE_MINUS_SRC_ALPHA | "; break;
	}

	switch (Get_Fog_Func()) {
	case FOG_DISABLE: str+="FOG_DISABLE | "; break;
 	case FOG_ENABLE: str+="FOG_ENABLE | "; break;
 	case FOG_SCALE_FRAGMENT: str+="FOG_SCALE_FRAGMENT | "; break;
 	case FOG_WHITE: str+="FOG_WHITE | "; break;
	}

	switch (Get_Primary_Gradient()) {
 	case GRADIENT_DISABLE: str+="GRADIENT_DISABLE | "; break;
	// Retail's jump table (+0x3B4, slots 1 and 6) gives MODULATE and
	// MODULATE_OR_2X each other's text: either the shipped enum ordered
	// them differently or the strings were crossed. The labels reproduce it.
	case GRADIENT_MODULATE_OR_2X: str+="GRADIENT_MODULATE | "; break;
	case GRADIENT_ADD: str+="GRADIENT_ADD | "; break;
	case GRADIENT_BUMPENVMAP: str+="GRADIENT_BUMPENVMAP | "; break;
	case GRADIENT_BUMPENVMAPLUMINANCE: str+="GRADIENT_BUMPENVMAPLUMINANCE | "; break;
	case GRADIENT_MODULATE2X: str+="GRADIENT_MODULATE2X | "; break;
	case GRADIENT_MODULATE: str+="GRADIENT_MODULATE_OR_2X | "; break;
	}

	switch (Get_Secondary_Gradient()) {
	case SECONDARY_GRADIENT_DISABLE: str+="SECONDARY_GRADIENT_DISABLE | "; break;
	case SECONDARY_GRADIENT_ENABLE: str+="SECONDARY_GRADIENT_ENABLE | "; break;
	}

	switch (Get_Src_Blend_Func()) {
  	case SRCBLEND_ZERO: str+="SRCBLEND_ZERO | "; break;
  	case SRCBLEND_ONE: str+="SRCBLEND_ONE | "; break;
 	case SRCBLEND_SRC_ALPHA: str+="SRCBLEND_SRC_ALPHA | "; break;
 	case SRCBLEND_ONE_MINUS_SRC_ALPHA: str+="SRCBLEND_ONE_MINUS_SRC_ALPHA | "; break;
	}

	switch (Get_Texturing()) {
	case TEXTURING_DISABLE: str+="TEXTURING_DISABLE | "; break;
	case TEXTURING_ENABLE: str+="TEXTURING_ENABLE | "; break;
	}

	switch (Get_NPatch_Enable()) {
	case NPATCH_DISABLE: str+="NPATCH_DISABLE | "; break;
	case NPATCH_ENABLE: str+="NPATCH_ENABLE | "; break;
	}

	switch (Get_Alpha_Test()) {
	case ALPHATEST_DISABLE: str+="ALPHATEST_DISABLE | "; break;
	case ALPHATEST_ENABLE: str+="ALPHATEST_ENABLE | "; break;
	}

	switch (Get_Cull_Mode()) {
	case CULL_MODE_DISABLE: str+="CULL_MODE_DISABLE | "; break;
	case CULL_MODE_ENABLE: str+="CULL_MODE_ENABLE | "; break;
	}

	switch (Get_Post_Detail_Color_Func()) {
	case DETAILCOLOR_DISABLE: str+="DETAILCOLOR_DISABLE"; break;
	case DETAILCOLOR_DETAIL: str+="DETAILCOLOR_DETAIL"; break;
	case DETAILCOLOR_SCALE: str+="DETAILCOLOR_SCALE"; break;
	case DETAILCOLOR_INVSCALE: str+="DETAILCOLOR_INVSCALE"; break;
	case DETAILCOLOR_ADD: str+="DETAILCOLOR_ADD"; break;
	case DETAILCOLOR_SUB: str+="DETAILCOLOR_SUB"; break;
	case DETAILCOLOR_SUBR: str+="DETAILCOLOR_SUBR"; break;
	case DETAILCOLOR_BLEND: str+="DETAILCOLOR_BLEND"; break;
	case DETAILCOLOR_DETAILBLEND: str+="DETAILCOLOR_DETAILBLEND"; break;
	case DETAILCOLOR_ADDSIGNED: str+="DETAILCOLOR_ADDSIGNED"; break;
	case DETAILCOLOR_ADDSIGNED2X: str+="DETAILCOLOR_ADDSIGNED2X"; break;
	case DETAILCOLOR_SCALE2X: str+="DETAILCOLOR_SCALE2X"; break;
	case DETAILCOLOR_MODALPHAADDCOLOR: str+="DETAILCOLOR_MODALPHAADDCOLOR"; break;
	}
	return str;
}

// ?RvaShaderDx8CapsAnchor@@YAXXZ present-unmatched
void RvaShaderDx8CapsAnchor()
{
	(void)&DX8Caps::Get_Vendor;
	(void)&DX8Caps::Is_Fog_Allowed;
	(void)&DX8Caps::Support_ModAlphaAddClr;
}
