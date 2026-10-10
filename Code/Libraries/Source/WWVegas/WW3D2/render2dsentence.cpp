// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /Ireference/shims/bfmevector /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
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
#include "render2dsentence.h"
#include "surfaceclass.h"
#include "texture.h"
#include "wwprofile.h"
#include "wwmemlog.h"
#include "dx8wrapper.h"

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
// ??0Render2DSentenceClass@@QAE@XZ present-unmatched
Render2DSentenceClass::Render2DSentenceClass (void) :
	Font (NULL),
	Location (0.0F,0.0F),
	Cursor (0.0F,0.0F),
	TextureOffset (0, 0),
	TextureStartX (0),
	CurSurface (NULL),
	CurrTextureSize (0),
	MonoSpaced (false),
	IsClippedEnabled (false),
	ClipRect (0, 0, 0, 0),
	BaseLocation (0, 0),
	LockedPtr (NULL),
	LockedStride (0),
	TextureSizeHint (0),
	WrapWidth (0),
	Centered (false),
	DrawExtents (0, 0, 0, 0),
	ParseHotKey( false ),
	useHardWordWrap( false)
{
	Shader = Render2DClass::Get_Default_Shader ();
	return ;
}


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
void
// byte-exact reconstruction: Code/GameEngine/Source/Common/Render2DSentenceClass_Build_TexturesMethodThunk.cpp
// ?Build_Textures@Render2DSentenceClass@@AAEXXZ present-unmatched
Render2DSentenceClass::Build_Textures (void)
{
	WWMEMLOG(MEM_TEXTURE);

	//
	//	Make sure we unlock the current surface
	//
	if (LockedPtr != NULL) {
		CurSurface->Unlock ();
		LockedPtr = NULL;
	}
	
	//
	//	Release our hold on the current surface
	//
	REF_PTR_RELEASE (CurSurface);
	TextureOffset.Set (0, 0);
	TextureStartX = 0;

	//
	//	Convert all pending surfaces to textures
	//
	for (int index = 0; index < PendingSurfaces.Count (); index ++) {		
		PendingSurfaceStruct &surface_info = PendingSurfaces[index];
		SurfaceClass *curr_surface = surface_info.Surface;

		//
		//	Get the dimensions of the surface
		//
		SurfaceClass::SurfaceDescription desc;
		curr_surface->Get_Description (desc);
		
		//
		//	Create the new texture
		//
		TextureClass *new_texture = W3DNEW TextureClass (desc.Width, desc.Width, WW3D_FORMAT_A4R4G4B4, MIP_LEVELS_1);
		SurfaceClass *texture_surface = new_texture->Get_Surface_Level ();

		new_texture->Get_Filter().Set_U_Addr_Mode(TextureFilterClass::TEXTURE_ADDRESS_CLAMP);
		new_texture->Get_Filter().Set_V_Addr_Mode(TextureFilterClass::TEXTURE_ADDRESS_CLAMP);
		new_texture->Get_Filter().Set_Min_Filter(TextureFilterClass::FILTER_TYPE_NONE);
		new_texture->Get_Filter().Set_Mag_Filter(TextureFilterClass::FILTER_TYPE_NONE);
		new_texture->Get_Filter().Set_Mip_Mapping(TextureFilterClass::FILTER_TYPE_NONE);

		//
		//	Copy the contents of the texture from the surface
		//
		DX8Wrapper::_Copy_DX8_Rects (curr_surface->Peek_D3D_Surface (), NULL, 0, texture_surface->Peek_D3D_Surface (), NULL);
		REF_PTR_RELEASE (texture_surface);
	
		//
		//	Assign this texture to any renderers that need it
		//
		for (int renderer_index = 0; renderer_index < surface_info.Renderers.Count (); renderer_index ++) {
			Render2DClass *renderer = surface_info.Renderers[renderer_index];
			renderer->Set_Texture (new_texture);
		}

		//
		//	Release our hold on the objects
		//
		REF_PTR_RELEASE (new_texture);
		REF_PTR_RELEASE (curr_surface);
	}

	//
	//	Reset the list
	//
	if (PendingSurfaces.Count()>0) {
		PendingSurfaces.Delete_All ();
	}
	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Draw_Sentence
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Draw_Sentence@Render2DSentenceClass@@QAEXK@Z present-unmatched
Render2DSentenceClass::Draw_Sentence (uint32 color)
{
	Render2DClass *curr_renderer	= NULL;
	SurfaceClass *curr_surface		= NULL;

	DrawExtents.Set (0, 0, 0, 0);

	int offset = 0;
	//
	//	Loop over all the parts of the sentence
	//
	for (int index = 0; index < SentenceData.Count (); index ++) {
		SentenceDataStruct &data = SentenceData[index];

		//
		//	Has the surface changed?
		//
		if (data.Surface != curr_surface) {
			curr_surface = data.Surface;

			//
			//	Try to find a renderer that uses the same "texture"
			//
			bool found = false;
			for (int renderer_index = 0; renderer_index < Renderers.Count (); renderer_index ++) {
				if (Renderers[renderer_index].Surface == curr_surface) {
					found = true;
					curr_renderer = Renderers[renderer_index].Renderer;
					break;
				}
			}
			
			//
			//	Create a new renderer if we couldn't find an appropriate one
			//
			if (found == false) {

				//
				//	Allocate a new renderer
				//
				curr_renderer = W3DNEW Render2DClass;
				curr_renderer->Set_Coordinate_Range (Render2DClass::Get_Screen_Resolution ());
				ShaderClass *curr_shader = curr_renderer->Get_Shader ();
				(*curr_shader) = Shader;
				
				//
				//	Add it to our list
				//
				RendererDataStruct render_info;
				render_info.Renderer	= curr_renderer;
				render_info.Surface	= curr_surface;
				Renderers.Add (render_info);

				//
				//	Now, add this renderer to the surface pending list
				//
				for (int surface_index = 0; surface_index < PendingSurfaces.Count (); surface_index ++) {
					PendingSurfaceStruct &surface_info = PendingSurfaces[surface_index];
					if (surface_info.Surface == curr_surface) {
						surface_info.Renderers.Add (curr_renderer);
					}
				}
			}
		}

		//
		//	Get the dimensions of the surface
		//
		SurfaceClass::SurfaceDescription desc;
		curr_surface->Get_Description (desc);

		//
		//	Add a quad that contains this sentence chunk
		//
		RectClass screen_rect	= data.ScreenRect;
		screen_rect					+= Location;
		RectClass uv_rect			= data.UVRect;

		//
		//	Clip the quad (as necessary)
		//
		bool add_quad = true;
		if (IsClippedEnabled) {
			
			//
			//	Check for completely clipped
			//
			if (	screen_rect.Right <= ClipRect.Left ||
					screen_rect.Bottom <= ClipRect.Top)
			{
				add_quad = false;
			} else {

				//
				//	Clip the polygons to the specified area
				//
				RectClass clipped_rect;
				clipped_rect.Left		= max (screen_rect.Left, ClipRect.Left);
				clipped_rect.Right	= min (screen_rect.Right, ClipRect.Right);
				clipped_rect.Top		= max (screen_rect.Top, ClipRect.Top);
				clipped_rect.Bottom	= min (screen_rect.Bottom, ClipRect.Bottom);

				//
				//	Clip the texture to the specified area
				//
				RectClass clipped_uv_rect;
				float percent				= ((clipped_rect.Left - screen_rect.Left) / screen_rect.Width ());
				clipped_uv_rect.Left		= uv_rect.Left + (uv_rect.Width () * percent);

				percent						= ((clipped_rect.Right - screen_rect.Left) / screen_rect.Width ());
				clipped_uv_rect.Right	= uv_rect.Left + (uv_rect.Width () * percent);

				percent						= ((clipped_rect.Top - screen_rect.Top) / screen_rect.Height ());
				clipped_uv_rect.Top		= uv_rect.Top + (uv_rect.Height () * percent);

				percent						= ((clipped_rect.Bottom - screen_rect.Top) / screen_rect.Height ());
				clipped_uv_rect.Bottom	= uv_rect.Top + (uv_rect.Height () * percent);

				//
				//	Use the clipped rectangles to render
				//
				screen_rect = clipped_rect;
				uv_rect		= clipped_uv_rect;

				if (screen_rect.Right <= screen_rect.Left ||
						screen_rect.Bottom <= screen_rect.Top)
				{
					add_quad = false;
				}
			}
		}

		if (add_quad) {
			//uv_rect.Bottom += 0.5f;
			uv_rect *=  1.0F / ((float)desc.Width);
#ifdef TEST_PLACEMENT	 
			screen_rect.Left += offset*3;
			screen_rect.Right += offset*3;
#endif
			offset++;
			curr_renderer->Add_Quad (screen_rect, uv_rect, color);

			//
			//	Add this rectangle to the total draw extents
			//
			if (DrawExtents.Width () == 0) {
				DrawExtents = screen_rect;
			} else {
				DrawExtents += screen_rect;
			}
		}
	}

	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Record_Sentence_Chunk
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Record_Sentence_Chunk@Render2DSentenceClass@@AAEXXZ present-unmatched
Render2DSentenceClass::Record_Sentence_Chunk (void)
{
	//
	//	Do we have anything to store?
	//
	int width = TextureOffset.I - TextureStartX;
	if (width > 0) {
		float char_height = Font->Get_Char_Height ();
		
		//
		//	Build a structure that contains enough information
		// to hold this portion of the sentence
		//
		SentenceDataStruct sentence_data;
		sentence_data.Surface = CurSurface;
		sentence_data.Surface->Add_Ref ();
		sentence_data.ScreenRect.Left		= Cursor.X;
		sentence_data.ScreenRect.Right	= Cursor.X + width;
		sentence_data.ScreenRect.Top		= Cursor.Y;
		sentence_data.ScreenRect.Bottom	= Cursor.Y + char_height;
		sentence_data.UVRect.Left			= TextureStartX;
		sentence_data.UVRect.Top			= TextureOffset.J;
		sentence_data.UVRect.Right			= TextureOffset.I;
		sentence_data.UVRect.Bottom		= TextureOffset.J + char_height;		

		//
		//	Add this information to our list
		//
		SentenceData.Add (sentence_data);
	}

	return ;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Allocate_New_Surface
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Allocate_New_Surface@Render2DSentenceClass@@AAEXPBG_N@Z present-unmatched
Render2DSentenceClass::Allocate_New_Surface (const WCHAR *text, bool justCalcExtents)
{
	if (!justCalcExtents)
	{
		//
		//	Unlock the last surface (if necessary)
		//
		if (LockedPtr != NULL) {
			CurSurface->Unlock ();
			LockedPtr = NULL;
		}
	}

	//
	// Calculate the width of the text
	//	
	int text_width = 0;
	for (int index = 0; text[index] != 0; index ++) {
		text_width += Font->Get_Char_Spacing (text[index]);
	}
	
	int char_height = Font->Get_Char_Height ();

	//
	//	Find the best texture size for the remaining text
	//
	CurrTextureSize = 256;
	int best_tex_mem_usage = 999999999;
	for (int pow2 = 6; pow2 <= 8; pow2 ++) {		
		
		int size					= 1 << pow2;
		int row_count			= (text_width / size) + 1;
		int rows_per_texture	= size / (char_height + 1);
		
		//
		//	Can we even fit one character on this texture?
		//
		if (rows_per_texture > 0) {			

			//
			//	How many textures (at this size) would it take to render
			// the remaining text?
			//
			int texture_count	= row_count / rows_per_texture;
			texture_count		= max (texture_count, 1);

			//
			//	Is this the best usage of texture memory we've found yet?
			//
			int texture_mem_usage = (texture_count * size * size);
			if (texture_mem_usage < best_tex_mem_usage) {
				CurrTextureSize		= size;
				best_tex_mem_usage	= texture_mem_usage;
			}
		}
	}

	//
	//	Use whichever is larger, the hint or the calculated size
	//
	CurrTextureSize = max (TextureSizeHint, CurrTextureSize);

	if (!justCalcExtents)
	{
		//
		//	Release our extra hold on the old surface
		//
		REF_PTR_RELEASE (CurSurface);

		//
		//	Create the new surface
		//	
		CurSurface = NEW_REF (SurfaceClass, (CurrTextureSize, CurrTextureSize, WW3D_FORMAT_A4R4G4B4));
		WWASSERT (CurSurface != NULL);
		CurSurface->Add_Ref ();

		//
		//	Add this surface to our list
		//
		PendingSurfaceStruct surface_info;
		surface_info.Surface = CurSurface;
		PendingSurfaces.Add (surface_info);
	}

	//
	//	Reset to the upper left corner
	//
	TextureOffset.Set (0, 0);
	TextureStartX = 0;	
	return ;
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
// ?Build_Sentence_Centered@Render2DSentenceClass@@AAEXPBGPAH1@Z present-unmatched
void	Render2DSentenceClass::Build_Sentence_Centered (const WCHAR *text, int *hkX, int *hkY)
{
	float char_height = Font->Get_Char_Height ();
	int		wordWidth = 0;
	int notCenteredHotkeyX = 0;
	int notCenteredHotkeyY = 0;
	Vector2 extent = Build_Sentence_Not_Centered(text,&notCenteredHotkeyX, &notCenteredHotkeyY, TRUE); //Get_Formatted_Text_Extents(text);
	
	//
	//	Start fresh
	//
	Reset_Sentence_Data ();
	Cursor.Set (0, 0);
	
	//
	//	Ensure we have a surface to start with
	//
	if (CurSurface == NULL) {
		Allocate_New_Surface (text);
	}
	
	
	
	//
	//	Loop over all the characters in the string
	//
	bool end = false;
	const WCHAR *word;
	int word_width	= 0;
	int line_width	= 0;
	int charCount = 0;
	int wordCount = 0;
	int hotKeyPosX = 0;
	int hotKeyPosY = 0;
	bool calcHotKeyX = false;
	bool dontBlit = false;
	while (!end)
	{
		//
		// Re-init everything for the next line
		//
		word	= text;
		word_width	= 0;
		line_width	= 0;
		charCount = 0;
		wordCount = 0;
		//
		//first find the length of the line till we wrap
		//
		while ( 1 )
		{
			//
			// read a word
			//
			int charWidth = 0;
			while ((*word != 0) && (*word > L' ') && (*word != L'\n')) {
				if( ParseHotKey && (*word == L'&') && (*word+1 != 0) && (*word+1 > L' ') && (*word+1 != L'\n'))
				{
					int offset = 0;
					//Added By Saad
					if (word_width != 0 )
					{
						const WCHAR *word_back = word;
						*word_back--;
						if (*word_back == L' ')
						{
							line_width -= word_width;
							offset =-1;
						}
					}
					//
					*word++;
					calcHotKeyX = true;
				}
				
				charWidth = Font->Get_Char_Spacing (*word++);
				word_width += charWidth;
				wordCount++;
				
				if (WrapWidth > 0 && word_width >= WrapWidth && useHardWordWrap)
					break;
			}
			// 
			// If this word is unworthy to be on the current line, decrement the space and break
			//
			if(WrapWidth > 0 && (line_width + word_width >= WrapWidth))
			{
				//
				//Take care of the case that the word is too big for the allocated space...
				//If that's the case, drop out and process the word anyway
				//
				if(charCount == 0)
				{	
					charCount +=wordCount - 1;
					line_width += word_width - charWidth;	
					if(*word == 0)
						end = true;
					break;
				}
				charCount--;
				break;
			}
			//
			// if we reached the end of the text, set the values and break, also set the end flag
			//
			if( *word == 0 )
			{
				charCount +=wordCount;
				line_width += word_width;
				end = true;
				break;
			}
			//
			// otherwise, increment the counts
			//
			charCount +=wordCount + 1;
			line_width += word_width;	
			//
			// We were some a new line character break and process
			//
			if(*word != L' ')
				break;
			//
			// add the space to our width
			//
			word_width = Font->Get_Char_Spacing (*word++);
			wordCount = 0;
			//Added By Saad
			line_width += word_width;
		}
		//
		// we now hold the length of the line and it's width lets set our cursor position to center it
		//
		Cursor.X = (int)((extent.X - line_width) / 2);
		if(Cursor.X < 0)
			Cursor.X = 0;
		if(calcHotKeyX)
		{
			calcHotKeyX = false;
			hotKeyPosX = Cursor.X + notCenteredHotkeyX;
		}
		
		for(int i = 0; i <= charCount; i++) {
			WCHAR ch = *text++;
			dontBlit = false;
			//
			//	Determine how much horizontal space this character requires
			//
			if(ParseHotKey && (ch == L'&') && (*text != 0) && (*text > L' ') && (*text != L'\n'))
			{
				ch = *text++;
				dontBlit = true;
			}
			float char_spacing = Font->Get_Char_Spacing (ch);
			
			bool exceeded_texture_width	= ((TextureOffset.I + char_spacing) >= CurrTextureSize);
			bool encountered_break_char	= (ch == L' ' || ch == L'\n' || ch == 0);
			
			//
			//	Do we need to record this portion of the sentence to its own chunk?
			//
			if (exceeded_texture_width || encountered_break_char) {
				Record_Sentence_Chunk ();
				
				//
				//	Adjust the positions
				//
				Cursor.X			+= (TextureOffset.I - TextureStartX);
				TextureStartX	= TextureOffset.I;
				
				//
				//	Adjust the output coordinates
				//
				if (ch == L' ') {
					Cursor.X += char_spacing;
				} else if ((ch == 0 )|| (ch == L'\n')) {
					break;
				}
								
				//
				//	Did the text extend past the edge of the texture?
				//
				if (exceeded_texture_width) {
					TextureStartX		= 0;
					TextureOffset.I	= TextureStartX;
					TextureOffset.J	+= char_height;
					
					//
					//	Did the text extent completely off the texture?
					//
					if ((TextureOffset.J + char_height) >= CurrTextureSize) {
						Allocate_New_Surface (text);
					}
				}
			}
			//
			//	Adjust the output coordinates
			//
			if (ch != L'\n' && ch != L' ') {
				
				//
				//	Ensure the surface is locked	
				//
				if (LockedPtr == NULL) {
					LockedPtr = (uint16 *)CurSurface->Lock (&LockedStride);
					WWASSERT (LockedPtr != NULL);
				}
				
				//
				//	Check to ensure the text will fit on this texture
				//
				WWASSERT (((TextureOffset.I + char_spacing) < CurrTextureSize) && ((TextureOffset.J + char_height) < CurrTextureSize));
				
				//
				//	Blit the character to the surface
				//
				if(!dontBlit)
					Font->Blit_Char (ch, LockedPtr, LockedStride, TextureOffset.I, TextureOffset.J);
				
				if (dontBlit) {
					// we don't blit for a hot key character.  So add extra spacing.
					char_spacing += Font->Get_Extra_Overlap();
					// Brutal hack #27 Gamma - Bolded M's are just a problem.	jba.
					if (ch=='M') {
						char_spacing++;
					}
				}
				
				TextureOffset.I += char_spacing;
			}
		}
		//
		// reset our cursor and add a line of text to the cursor position
		//
		Cursor.X = 0;
		Cursor.Y += char_height;
		line_width = 0;
		}
		
		if(hkX)						
			*hkX = hotKeyPosX;
		if(hkX)
			*hkY = hotKeyPosY;
	return ;
}
////////////////////////////////////////////////////////////////////////////////////
//
//	Build_Sentence_NotCentered
//
////////////////////////////////////////////////////////////////////////////////////
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceBuildNotCenteredThunk.cpp
// ?Build_Sentence_Not_Centered@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z present-unmatched
Vector2	Render2DSentenceClass::Build_Sentence_Not_Centered (const WCHAR *text, int *hkX, int *hkY, bool justCalcExtents)
{
	Vector2 cursor = Cursor;
	int textureStartX = TextureStartX;
	float maxX = 0;

	int hotKeyPosX = 0;
	int hotKeyPosY = 0;
	bool calcHotKeyX = false;
	bool dontBlit = false;
	Vector2i textureOffset = TextureOffset;


	//
	//	Start fresh
	//
	if (!justCalcExtents)
	{
		Reset_Sentence_Data ();
	}
	Cursor.Set (0, 0);

	//
	//	Ensure we have a surface to start with
	//
	if (CurSurface == NULL) {
		Allocate_New_Surface (text, justCalcExtents);
	}

	TextureOffset.Set (TEXTURE_OFFSET, 0);
	TextureStartX = TEXTURE_OFFSET;	

	float char_height = Font->Get_Char_Height ();

	//
	//	Loop over all the characters in the string
	//
	while (text != NULL) {
		WCHAR ch = *text++;
		dontBlit = false;
		//
		//	Determine how much horizontal space this character requires
		//
		if(ParseHotKey && (ch == L'&') && (*text != 0) && (*text > L' ') && (*text != L'\n'))
		{
				hotKeyPosY = Cursor.Y;
			if (calcHotKeyX)
				hotKeyPosX = 0;
			else
				hotKeyPosX = Cursor.X + TextureOffset.I -TextureStartX;//TextureOffset.I;

			ch = *text++;
			dontBlit = true;
		}
		float char_spacing = Font->Get_Char_Spacing (ch);

		bool exceeded_texture_width	= ((TextureOffset.I + char_spacing) >= CurrTextureSize);
		bool encountered_break_char	= (ch == L' ' || ch == L'\n' || ch == 0);
		bool wordBiggerThenLine = ((useHardWordWrap) && ( WrapWidth != 0 ) &&((Cursor.X + TextureOffset.I -TextureStartX + char_spacing) >= WrapWidth));
		//
		//	Do we need to record this portion of the sentence to its own chunk?
		//
		if (exceeded_texture_width || encountered_break_char|| wordBiggerThenLine) {
			if (!justCalcExtents)
			{
				Record_Sentence_Chunk ();
			}

			//
			//	Adjust the positions
			//
			Cursor.X			+= (TextureOffset.I - TextureStartX);
			maxX = max(maxX, Cursor.X);
			TextureStartX	= TextureOffset.I;

			//
			//	Adjust the output coordinates
			//
			if (ch == L' ') {
				//Cursor.X += char_spacing;
				//maxX = max(maxX, Cursor.X);

				//
				// Check to see if we need to wrap on this word-break
				//
				if (WrapWidth > 0) {
					
					//
					//	Find the length of the next word
					//
					const WCHAR *word	= text;
					float word_width	= char_spacing;
					while ((*word != 0) && (*word > L' ')) {
						if(ParseHotKey && (*word == L'&') && (*word+1 != 0) && (*word+1 > L' ') && (*word+1 != L'\n'))
							*word++;
						word_width += Font->Get_Char_Spacing (*word++);
					}

					//
					//	Should we wrap the next word?
					//
					if ((Cursor.X + word_width) >= WrapWidth) {
						Cursor.X = 0;
						Cursor.Y += char_height;
						calcHotKeyX = true;
					}
				}

			} else if (ch == L'\n') {
				Cursor.X = 0;
				Cursor.Y += char_height;
			} else if (ch == 0) {
				break;
			} else if (wordBiggerThenLine){ // we've entered this loop because we're greater then the wordwrap so we need to force a wordwrap
				Cursor.X = 0;
				Cursor.Y += char_height;
			}

			
			//
			//	Did the text extend past the edge of the texture?
			//
			if (exceeded_texture_width) {
				TextureStartX		= TEXTURE_OFFSET;
				TextureOffset.I	= TextureStartX;
				TextureOffset.J	+= char_height;

				//
				//	Did the text extent completely off the texture?
				//
				if ((TextureOffset.J + char_height) >= CurrTextureSize) {
					Allocate_New_Surface (text, justCalcExtents);
				}
			}
		}
		
		if (ch != L'\n' ) {

			//
			//	Ensure the surface is locked	
			//
			if (!justCalcExtents)
			{
				if (LockedPtr == NULL) {
					LockedPtr = (uint16 *)CurSurface->Lock (&LockedStride);
					WWASSERT (LockedPtr != NULL);
				}
			}

			//
			//	Check to ensure the text will fit on this texture
			//
			WWASSERT (((TextureOffset.I + char_spacing) < CurrTextureSize) && ((TextureOffset.J + char_height) < CurrTextureSize));

			//
			//	Blit the character to the surface
			//
			if (!justCalcExtents && !dontBlit )
			{
				Font->Blit_Char (ch, LockedPtr, LockedStride, TextureOffset.I, TextureOffset.J);			
			}
			TextureOffset.I += char_spacing;
		} 
	}

	Vector2 extent;
	extent.X = maxX + Font->Get_Extra_Overlap();
	extent.Y = Cursor.Y + char_height;

	Cursor = cursor;
	TextureOffset = textureOffset;
	TextureStartX = textureStartX;
	
	if(hkX)						
		*hkX = hotKeyPosX;
	if(hkX)
		*hkY = hotKeyPosY;

	return extent;
}


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
// ??1FontCharsClass@@UAE@XZ present-unmatched
FontCharsClass::~FontCharsClass (void) 
{
	while ( BufferList.Count() ) {
		delete [] BufferList[0];
		BufferList.Delete(0);
	}

	Free_GDI_Font();
	Free_Character_Arrays();
	return ;
}


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
const FontCharsClassCharDataStruct *
// ?Store_GDI_Char@FontCharsClass@@AAEPBVFontCharsClassCharDataStruct@@G@Z present-unmatched
FontCharsClass::Store_GDI_Char (WCHAR ch)
{
	int width	= PointSize * 2;
	int height	= PointSize * 2;

	//
	//	Draw the character into the memory DC
	//
	RECT rect = { 0, 0, width, height };
	int xOrigin = 0;
	if (ch == 'W') {
		xOrigin = 1;
	}
	::ExtTextOutW( MemDC, xOrigin, 0, ETO_OPAQUE, &rect, &ch, 1, NULL);

	//
	//	Get the size of the character we just drew
	//
	SIZE char_size = { 0 };
	::GetTextExtentPoint32W( MemDC, &ch, 1, &char_size );	
	char_size.cx += PixelOverlap + xOrigin;
	//
	//	Get a pointer to the surface that this character should use
	//
	Update_Current_Buffer( char_size.cx );
	uint16* curr_buffer_p = BufferList[BufferList.Count () - 1]->Buffer;
	curr_buffer_p += CurrPixelOffset;
	
	//
	//	Copy the BMP contents to the buffer
	//
	int stride = (((width * 3) + 3) & ~3);
	for (int row = 0; row < char_size.cy; row ++) {
		
		//
		//	Compute the indices into the BMP and surface
		//
		int index = (row * stride);

		//
		//	Loop over each column
		//
		for (int col = 0; col < char_size.cx; col ++) {
			
			//
			//	Get the pixel color at this location
			//
			uint8 pixel_value = GDIBitmapBits[index];
			index += 3;
#ifdef TEST_PLACEMENT
 			if (row==CharHeight-1&&col==0) {
 				pixel_value = 0xff;
 			}
 			if (row==CharHeight-2&&col==1) {
 				pixel_value = 0xff;
 			}
 			if (row==0&&col==0) {
 				pixel_value = 0xff;
 			}
 			if (row==1&&col==1) {
 				pixel_value = 0xff;
 			}
 			if (row==CharHeight-1&&col==char_size.cx-1-PixelOverlap) {
 				pixel_value = 0xff;
 			}
 			if (row==CharHeight-2&&col==char_size.cx-2-PixelOverlap) {
 				pixel_value = 0xff;
 			}
 			if (row==0&&col==char_size.cx-1-PixelOverlap) {
 				pixel_value = 0xff;
 			}
 			if (row==1&&col==char_size.cx-2-PixelOverlap) {
 				pixel_value = 0xff;
 			}
 			if (pixel_value == 0x00) {
 				pixel_value = 0x40;
 			}
#endif

			uint16 pixel_color = 0;
			if (pixel_value != 0) {
				pixel_color = 0x0FFF;
			}
			
			//
			//	Convert the pixel intensity from 8bit to 4bit and
			// store it in our buffer
			//
			uint8 alpha_value	= ((pixel_value >> 4) & 0xF);
			*curr_buffer_p++	= pixel_color | (alpha_value << 12);
		}
	}

	//
	//	Save information about this character in our list
	//
	FontCharsClassCharDataStruct *char_data	= W3DNEW FontCharsClassCharDataStruct;
	char_data->Value				= ch;
	char_data->Width				= char_size.cx;
	char_data->Buffer				= BufferList[BufferList.Count () - 1]->Buffer + CurrPixelOffset;

	//
	//	Insert this character into our array
	//
	if ( ch < 256 ) {
		ASCIICharArray[ch] = char_data;
	} else {
		UnicodeCharArray[ch - FirstUnicodeChar] = char_data;
	}	

	//
	//	Advance the character position
	//
	CurrPixelOffset += ((char_size.cx+PixelOverlap) * CharHeight);

	//
	//	Return the index of the entry we just added
	//
	return char_data;
}


////////////////////////////////////////////////////////////////////////////////////
//
//	Update_Current_Buffer
//
////////////////////////////////////////////////////////////////////////////////////
void
// ?Update_Current_Buffer@FontCharsClass@@AAEXH@Z present-unmatched
FontCharsClass::Update_Current_Buffer (int char_width)
{
	//
	//	Check to see if we need to allocate a new buffer
	//
	bool needs_new_buffer = (BufferList.Count () == 0);
	if (needs_new_buffer == false) {
		
		//
		//	Would we extend past this buffer?
		//
		if ( (CurrPixelOffset + (char_width * CharHeight)) > CHAR_BUFFER_LEN ) {
			needs_new_buffer = true;
		}
	}

	//
	//	Do we need to create a new surface?
	//
	if (needs_new_buffer) 
	{
		FontCharsBuffer* new_buffer = W3DNEW FontCharsBuffer;
		BufferList.Add( new_buffer );
		CurrPixelOffset = 0;
	}

	return ;
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
