// cl: /O2 /arch:SSE /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /G7 /Ireference/shims/bfmerendobj /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/linegrp.cpp); this unit had no counterpart under Code/.
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
 *                 Project Name : Linegroup.cpp                                                *
 *                                                                                             *
 *                     $Archive::                                                             $*
 *                                                                                             *
 *              Original Author:: Hector Yee                                                   *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 4:04p                                             $*
 *                                                                                             *
 *                    $Revision:: 2                                                            $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "sharebuf.h"
#include "linegrp.h"
#include "texture.h"
#include "vertmaterial.h"
#include "dx8wrapper.h"
#include "wwmath.h"
#include "rinfo.h"
#include "camera.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"

// Line groups are a rendering primitive similar to point groups
// They are tetrahedra which are aligned with the view plane with their centers
// at StartLineLoc. The apex of the tetrahedron is at EndLineLoc.
// They can be individually colored LineDiffuse
// and the LineUCoord determines the U coordinate of the texture to use
// the V coordinate is always 0 at the flat end of the tetrahedron
// and 1 at the apex
// LineGroupClass::LineGroupClass: defined in LineGroupClassDefaultCtor.cpp (its row's unit).

// LineGroupClass::~LineGroupClass: defined in LineGroupClassDestructor.cpp (its row's unit).

// LineGroupClass::Set_Arrays: defined in LineGroupClassSetArrays.cpp (its row's unit).

// LineGroupClass::Set_Line_Size: defined in linegrp_float_setters.cpp (its row's unit).

float LineGroupClass::Get_Line_Size(void)
{
	return DefaultLineSize;
}

void LineGroupClass::Set_Line_Color(const Vector3 &color)
{
	DefaultLineColor = color;
}

Vector3 LineGroupClass::Get_Line_Color(void)
{
	return DefaultLineColor;
}

void LineGroupClass::Set_Tail_Diffuse(const Vector4 &tdiffuse)
{
	DefaultTailDiffuse = tdiffuse;
}

Vector4 LineGroupClass::Get_Tail_Diffuse(void)
{
	return DefaultTailDiffuse;
}

// LineGroupClass::Set_Line_Alpha: defined in linegrp_float_setters.cpp (its row's unit).

float LineGroupClass::Get_Line_Alpha(void)
{
	return DefaultLineAlpha;
}

// LineGroupClass::Set_Line_UCoord: defined in linegrp_float_setters.cpp (its row's unit).

float LineGroupClass::Get_Line_UCoord(void)
{
	return DefaultLineUCoord;
}

void LineGroupClass::Set_Flag(FlagsType flag, bool on)
{
	if (on) Flags |= 1 << flag; 
	else 
		Flags &= ~(1 << flag);
}

// Get_Flag is emitted by LineGroupClassRender.cpp (its Render inlines it);
// this out-of-line copy was a second, NODUPLICATES definition of retail's
// 15-byte body and made the render unit report LNK2005.

// ?Set_Texture@LineGroupClass@@ present-unmatched
void LineGroupClass::Set_Texture(TextureClass* texture)
{
	TextureClass **next = reinterpret_cast<TextureClass **>(texture);
	if (*next)
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(*next) + 4);
	if (Texture) {
		Texture->Release_Ref();
		Texture = *next;
	} else {
		Texture = *next;
	}
}

// ?Get_Texture@LineGroupClass@@ present-unmatched
TextureClass * LineGroupClass::Get_Texture(void)
{
	if (Texture) ++*(unsigned short *)((char *)Texture + 4);
	return Texture;
}

// ?Peek_Texture@LineGroupClass@@ present-unmatched
TextureClass * LineGroupClass::Peek_Texture(void)
{
	return Texture;
}

void LineGroupClass::Set_Shader(const ShaderClass &shader)
{
	Shader = shader;
}

// ?Get_Shader@LineGroupClass@@ present-unmatched
ShaderClass LineGroupClass::Get_Shader(void)
{
	return Shader;
}

void LineGroupClass::Set_Line_Mode(LineModeType linemode)
{
	LineMode = linemode;
}

// ?Get_Line_Mode@LineGroupClass@@ present-unmatched
LineGroupClass::LineModeType LineGroupClass::Get_Line_Mode(void)
{
	return LineMode;
}

// LineGroupClass::Render: defined in LineGroupClassRender.cpp (its row's unit).

int LineGroupClass::Get_Polygon_Count(void)
{
	switch (LineMode) {
		case TETRAHEDRON:
			return LineCount * 4;
			break;
		case PRISM:
			return LineCount * 8;
			break;
	}
	WWASSERT(0);
	return 0;
}