// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/bfmevector /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// platformsdk
// dxsdk
// stlport

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
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
 *                     $Archive:: /Commando/Code/ww3d2/render2dsentence.cpp                   $*
 *                                                                                             *
 *                       $Author:: Patrick                  $*
 *                                                                                             *
 *								$Modtime:: 8/29/01 11:16a                                             $*
 *                                                                                             *
 *                    $Revision:: 13                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// This TU's retail Compare_No_Case calls msvcr71!_strcmpi.
#include <string.h>
#define _stricmp _strcmpi
// Prime the teardown view after this TU's allocation/pool declarations.
// Preserve the established BFME vector view before mutex dependencies see it.
#include "vector.h"
#include "bfme_wwstring_teardown.h"
#include "Render2DSentenceDonorView.h"
#include "surfaceclass.h"
#include "texture.h"
#include "wwprofile.h"
#include "wwmemlog.h"
#include "dx8wrapper.h"
// Suppress this TU's non-retail copy of ??8?$VectorClass@PAVRender2DClass@@@@UBE_NABV0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Render2DClass; class VectorClass;
template <> bool VectorClass<Render2DClass *>::operator==(VectorClass<Render2DClass *> const &) const;
// Suppress this TU's non-retail copy of ?ID@?$VectorClass@PAVRender2DClass@@@@UAEHPBQAVRender2DClass@@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Render2DClass;
template <> int VectorClass<Render2DClass *>::ID(Render2DClass * const *);
// Suppress this TU's non-retail copy of ?ID@?$VectorClass@PAVRender2DClass@@@@UAEHABQAVRender2DClass@@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Render2DClass;
template <> int VectorClass<Render2DClass *>::ID(Render2DClass * const &);
// Suppress this TU's non-retail copy of ?Resize@?$VectorClass@PAVRender2DClass@@@@UAE_NHPBQAVRender2DClass@@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Render2DClass;
template <> bool VectorClass<Render2DClass *>::Resize(int,Render2DClass * const *);
// VectorClass<Render2DClass *>::Clear is out of line in retail (0x000F0CD4): the
// vector destructors here then take the 11/34-byte shapes the kept copies have.
template <> void VectorClass<Render2DClass *>::Clear();

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma message("************************************** WARNING, optimization disabled for debugging purposes")
#endif

////////////////////////////////////////////////////////////////////////////////////
//	Local constants
////////////////////////////////////////////////////////////////////////////////////
#define no_TEST_PLACEMENT 1	 // Shows alignment markers for text.

#define TEXTURE_OFFSET 2
////////////////////////////////////////////////////////////////////////////////////
//
//	Render2DSentenceClass
//
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
//
//	~Render2DSentenceClass
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's body is the row 0x00157C70 in Render2DSentenceDestructorBFME2.cpp; Zero Hour's copy here duplicated it.


////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Font
//
////////////////////////////////////////////////////////////////////////////////////
void
Render2DSentenceClass::Set_Font (FontCharsClass *font)
{
	Reset ();
	REF_PTR_SET (Font, font);
	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Reset_Polys
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's body is the row 0x00154EC0 in Rva00154EC0Cluster.cpp; Zero Hour's copy here duplicated it.


////////////////////////////////////////////////////////////////////////////////////
//
//	Reset
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's body is the row 0x00155A20 in Render2DSentenceClass_Reset.cpp; Zero Hour's copy here duplicated it.


////////////////////////////////////////////////////////////////////////////////////
//
//	Make_Additive
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Make_Additive@Render2DSentenceClass@@QAEXXZ present-unmatched
Render2DSentenceClass::Make_Additive (void)
{
	Shader.Set_Dst_Blend_Func (ShaderClass::DSTBLEND_ONE);
	Shader.Set_Src_Blend_Func (ShaderClass::SRCBLEND_ONE);	
	Shader.Set_Primary_Gradient (ShaderClass::GRADIENT_MODULATE);
	Shader.Set_Secondary_Gradient (ShaderClass::SECONDARY_GRADIENT_DISABLE);

	Set_Shader (Shader);
	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Make_Additive
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Set_Shader@Render2DSentenceClass@@QAEXVShaderClass@@@Z present-unmatched
Render2DSentenceClass::Set_Shader (ShaderClass shader)
{
	Shader = shader;

	//
	//	Change each renderer's shader
	//
	for (int i = 0; i < Renderers.Count (); i ++) {
		ShaderClass *curr_shader = Renderers[i].Renderer->Get_Shader ();
		(*curr_shader) = Shader;
	}

	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Render
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's Render2DSentenceClass::Render is the row 0x00155AD0 (Rva00155AD0.cpp, address-derived name;
// it brackets the renderer loop with two calls Zero Hour lacks); Zero Hour's copy here was a second,
// non-retail definition of the name.


////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Base_Location
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Set_Base_Location@Render2DSentenceClass@@QAEXABVVector2@@@Z present-unmatched
Render2DSentenceClass::Set_Base_Location (const Vector2 &loc)
{ 
	Vector2 dif		= loc - BaseLocation;
	BaseLocation	= loc;
	for (int i = 0; i < Renderers.Count (); i ++) {
		Renderers[i].Renderer->Move (dif);
	}

	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Location
//
////////////////////////////////////////////////////////////////////////////////////
void
Render2DSentenceClass::Set_Location (const Vector2 &loc)
{ 
	Location	= loc; 
	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Text_Extents
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's body (retail 0x00158BA0) is matched in Render2DSentenceExtentBFME2.cpp; the
// Zero Hour copy that stood here was a second strong definition of the rowed name.


////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Formatted_Text_Extents
//
////////////////////////////////////////////////////////////////////////////////////
Vector2
Render2DSentenceClass::Get_Formatted_Text_Extents (const WCHAR *text)
{
	return Build_Sentence_Not_Centered(text, NULL, NULL, true);
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Reset_Sentence_Data
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's body is the row 0x00154F10 in Render2DSentenceClass_Reset_Sentence_Data.cpp; Zero Hour's copy here duplicated it.


////////////////////////////////////////////////////////////////////////////////////
//
//	Release_Pending_Surfaces
//
////////////////////////////////////////////////////////////////////////////////////
// Owned by Render2DSentenceClass_Release_Pending_Surfaces.cpp.


////////////////////////////////////////////////////////////////////////////////////
//
//	Build_Textures
//
////////////////////////////////////////////////////////////////////////////////////
// Render2DSentenceClass::Build_Textures: Zero Hour draft removed; BFME 2's body is rowed in
// Render2DSentenceBuildTexturesBFME2.cpp (0x00154FD0).


////////////////////////////////////////////////////////////////////////////////////
//
//	Draw_Sentence
//
////////////////////////////////////////////////////////////////////////////////////
// Render2DSentenceClass::Draw_Sentence(uint32) is defined with its retail-matched BFME2 body in
// Code/GameEngineDevice/Source/W3DDevice/GameClient/Render2DSentenceDrawSentenceOneColour.cpp (0x00104D97).


////////////////////////////////////////////////////////////////////////////////////
//
//	Record_Sentence_Chunk
//
////////////////////////////////////////////////////////////////////////////////////
// Render2DSentenceClass::Record_Sentence_Chunk is defined with its retail-matched body in Render2DSentenceRecordChunkBFME2.cpp.


////////////////////////////////////////////////////////////////////////////////////
//
//	Allocate_New_Surface
//
////////////////////////////////////////////////////////////////////////////////////
// Render2DSentenceClass::Allocate_New_Surface is defined with its retail-matched body in
// Render2DSentenceAllocateSurfaceBFME2.cpp (0x00158C60). The BFME1 body here was the first user
// of max<int>; keep that instantiation's place in this unit.
int render2dsentenceMaxAnchor(int a, int b)
{
	return max (a, b);
}

float FindStartingXPos( const WCHAR *text )
{

	return 1;
}
////////////////////////////////////////////////////////////////////////////////////
//
//	Build_Sentence_Centered
//
////////////////////////////////////////////////////////////////////////////////////
// Render2DSentenceClass::Build_Sentence_Centered: Zero Hour draft removed (not in BFME 2).
////////////////////////////////////////////////////////////////////////////////////
//
//	Build_Sentence_NotCentered
//
////////////////////////////////////////////////////////////////////////////////////
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceBuildNotCenteredThunk.cpp
// Render2DSentenceClass::Build_Sentence_Not_Centered is defined by its row's unit,
// Render2DSentenceBuildNotCenteredBFME2.cpp (retail 0x00159700).


////////////////////////////////////////////////////////////////////////////////////
//
//	Build_Sentence
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's Render2DSentenceClass::Build_Sentence is the row 0x00159FC0 (Gen_00942BC0.cpp, BFME 1 donor
// name; it always takes the not-centered path); Zero Hour's copy here was a second, non-retail definition.


////////////////////////////////////////////////////////////////////////////////////
//
//	FontCharsClass
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's body is the row 0x00157950 in FontCharsClassConstructorBFME.cpp; Zero Hour's copy here duplicated it.


////////////////////////////////////////////////////////////////////////////////////
//
//	~FontCharsClass
//
////////////////////////////////////////////////////////////////////////////////////
// BFME 2's body is the row 0x00157390 in FontCharsClassDestructorBFME.cpp; Zero Hour's copy here
// duplicated it and was the definition the link kept.


////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Char_Data
//
////////////////////////////////////////////////////////////////////////////////////
// Owned by FontCharsClassGetCharData.cpp.


////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Char_Width
//
////////////////////////////////////////////////////////////////////////////////////
// Retail reads the width at +4 of the char record. The vendored class derives
// from W3DMPO, which puts Value at +4 and Width at +6; BFME's record has no such
// base and carries two bytes between Value and Width that nothing here names.
// Only Width is ever touched in this body, so a local replica is enough.
struct BfmeFontCharRecord
{
	unsigned short m_value;					///< retail this+0x00
	unsigned short m_unreconstructed_002;			///< retail this+0x02
	short m_width;						///< retail this+0x04
};

int
FontCharsClass::Get_Char_Width (WCHAR ch)
{
	const FontCharsClassCharDataStruct	* data = Get_Char_Data( ch );
	if ( data != NULL ) {
		return ((const BfmeFontCharRecord *)data)->m_width;
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Char_Spacing
//
////////////////////////////////////////////////////////////////////////////////////
// ?Get_Char_Spacing@FontCharsClass@@QAEHG@Z is emitted by
// FontCharsClassGetCharSpacingThunk.cpp.


////////////////////////////////////////////////////////////////////////////////////
//
//	Blit_Char
//
////////////////////////////////////////////////////////////////////////////////////
// Owned by FontCharsClassBlitChar.cpp.


////////////////////////////////////////////////////////////////////////////////////
//
//	Store_GDI_Char
//
////////////////////////////////////////////////////////////////////////////////////
// FontCharsClass::Store_GDI_Char: Zero Hour draft removed; it is not retail's body.


////////////////////////////////////////////////////////////////////////////////////
//
//	Update_Current_Buffer
//
////////////////////////////////////////////////////////////////////////////////////
// The buffer-update body lives under FontCharsClass_Update_Current_Buffer.cpp
// (retail 0x00156490); this TU keeps only the class declaration so callers
// bind the kept copy and this unit emits no competing COMDAT.
//
// ?bfmeEmitFontCharsBufferAdd@@YAXPAV?$DynamicVectorClass@PAVFontCharsBuffer@@@@PAVFontCharsBuffer@@@Z present-unmatched
// Emit-anchor: the deleted Update_Current_Buffer was the only referrer of the
// rowed DynamicVectorClass<FontCharsBuffer*>::Add (0x001A3A60); this anchor
// keeps emitting it. It is not retail code.
void bfmeEmitFontCharsBufferAdd(DynamicVectorClass<FontCharsBuffer *> *v, FontCharsBuffer *fontCharsBuffer) { v->Add(fontCharsBuffer); }

// ?bfmeEmitFontCharsBufferTeardown@@YAXPAV?$DynamicVectorClass@PAVFontCharsBuffer@@@@@Z present-unmatched
// Emit-anchor: the deleted ~FontCharsClass duplicate was the only referrer of the rowed
// DynamicVectorClass<FontCharsBuffer*>::Delete and, through the vector destructor, the
// VectorClass<FontCharsBuffer*> ID / operator== slots; this keeps emitting them. It is not
// retail code.
void bfmeEmitFontCharsBufferTeardown(DynamicVectorClass<FontCharsBuffer *> *v)
{
	v->Delete(0);
	v->DynamicVectorClass<FontCharsBuffer *>::~DynamicVectorClass();
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Create_GDI_Font
//
////////////////////////////////////////////////////////////////////////////////////
// byte-exact reconstruction: Code/GameEngine/Source/Common/FontCharsClass_Create_GDI_FontMethodThunk.cpp
// BFME 2's body is the row 0x00154630 in FontCharsClassCreateGDIFont.cpp; Zero Hour's copy here duplicated it.


////////////////////////////////////////////////////////////////////////////////////
//
//	Free_GDI_Font
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Free_GDI_Font@FontCharsClass@@AAEXXZ present-unmatched
FontCharsClass::Free_GDI_Font (void)
{
	//
	//	Select the old font back into the DC and delete
	// our font object
	//
	if ( GDIFont != NULL ) {
		::SelectObject( MemDC, OldGDIFont );
		::DeleteObject( GDIFont );
		GDIFont = NULL;
	}

	//
	//	Select the old bitmap back into the DC and delete
	// our bitmap object
	//
	if ( GDIBitmap != NULL ) {
		::SelectObject( MemDC, OldGDIBitmap );
		::DeleteObject( GDIBitmap );
		GDIBitmap = NULL;
	}

	//
	//	Delete our memory DC
	//
	if ( MemDC != NULL ) {		
		::DeleteDC( MemDC );
		MemDC = NULL;
	}

	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Initialize_GDI_Font
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Initialize_GDI_Font@FontCharsClass@@QAEXPBDH_N@Z present-unmatched
FontCharsClass::Initialize_GDI_Font (const char *font_name, int point_size, bool is_bold)
{
	//
	//	Build a unique name from the font name and its size
	//
	Name.Format ("%s%d", font_name, point_size);

	//
	//	Remember these settings
	//
	GDIFontName	= font_name;
	PointSize	= point_size;
	IsBold		= is_bold;

	//
	//	Create the actual font object
	//
	Create_GDI_Font (font_name);
	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Is_Font
//
////////////////////////////////////////////////////////////////////////////////////
bool
// ?Is_Font@FontCharsClass@@QAE_NPBDH_N@Z present-unmatched
FontCharsClass::Is_Font (const char *font_name, int point_size, bool is_bold)
{
	bool retval = false;

	//
	//	Check to see if both the name and height matches...
	//
	if (	(GDIFontName.Compare_No_Case (font_name) == 0) &&
			(point_size == PointSize) &&
			(is_bold == IsBold))
	{
		retval = true;
	}

	return retval;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Grow_Unicode_Array
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Grow_Unicode_Array@FontCharsClass@@ present-unmatched
FontCharsClass::Grow_Unicode_Array (WCHAR ch)
{
	//
	//	Don't do anything if character is in the ASCII range
	//
	if ( ch < 256 ) {
		return ;
	}

	//
	//	Don't do anything if character is in the currently allocated range
	//
	if ( ch >= FirstUnicodeChar && ch <= LastUnicodeChar ) {
		return ;
	} 

	uint16 first_index	= min( FirstUnicodeChar, ch );
	uint16 last_index		= max( LastUnicodeChar, ch );
	uint16 count			= (last_index - first_index) + 1;

	//
	//	Allocate enough memory to hold the new cells
	//
	FontCharsClassCharDataStruct **new_array = W3DNEWARRAY FontCharsClassCharDataStruct *[count];
	::memset (new_array, 0, sizeof (FontCharsClassCharDataStruct *) * count);

	//
	//	Copy the contents of the old array into the new array
	//
	if ( UnicodeCharArray != NULL ) {
		int start_offset	= (FirstUnicodeChar - first_index);
		int old_count		= (LastUnicodeChar - FirstUnicodeChar) + 1;
		::memcpy (&new_array[start_offset], UnicodeCharArray, sizeof (FontCharsClassCharDataStruct *) * old_count);

		//
		//	Delete the old array
		//
		delete [] UnicodeCharArray;
		UnicodeCharArray = NULL;
	}

	FirstUnicodeChar	= first_index;
	LastUnicodeChar	= last_index;
	UnicodeCharArray	= new_array;
	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Free_Character_Arrays
//
////////////////////////////////////////////////////////////////////////////////////
// Owned by FontCharsClassFreeCharacterArrays.cpp.

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??4BfmeRendererVectorBase@@QAEAAV0@ABV0@@Z=??4?$VectorClass@PAVRender2DClass@@@@QAEAAV0@ABV0@@Z")

// Keep the already rowed container members that the retired donor sentence
// constructor used to instantiate; the native sentence constructor lives in
// Render2DSentenceConstructorBFME2.cpp. Explicit instantiation preserves the
// header's private nested-type identity without altering its declarations.
// Use the complete native record/vector providers. Instantiating the donor
// helpers here would select a different record construction and assignment.
template<> bool VectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Resize(int,const Render2DSentenceClass::PendingSurfaceStruct *);
template<> bool DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Add(const Render2DSentenceClass::PendingSurfaceStruct &);
template class VectorClass<Render2DSentenceClass::PendingSurfaceStruct>;
template class DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>;
// The renderer vector's Resize is the native 0x00155690 (P104): this donor
// record has no destructor, so its own Resize would skip the elements' release.
template<> bool VectorClass<Render2DSentenceClass::RendererDataStruct>::Resize(int,const Render2DSentenceClass::RendererDataStruct *);
template class VectorClass<Render2DSentenceClass::RendererDataStruct>;
template class VectorClass<Render2DSentenceClass::SentenceDataStruct>;

// Preserve the existing native renderer-vector rows after removing their
// accidental implicit-record instantiation path. The vector constructor is not
// instantiated here: its vtables would bring this unit's speed-optimized
// deleting destructors, while the kept copies (W3DGameClient.cpp and others)
// are the size-optimized ones.
template VectorClass<Render2DClass *> &VectorClass<Render2DClass *>::operator=(const VectorClass<Render2DClass *> &);
template DynamicVectorClass<Render2DClass *> &DynamicVectorClass<Render2DClass *>::operator=(const DynamicVectorClass<Render2DClass *> &);
