// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil

// ?Draw_Sentence@Render2DSentenceClass@@QAEXKKKK@Z, retail 0x00155B00, 2187 B.
// Donor: ZH render2dsentence.cpp Render2DSentenceClass::Draw_Sentence (one colour),
// the semantic and structural guide. Target facts: BFME2 passes four corner
// colours to the four-colour Render2DClass::Add_Quad (0x00042719), first scales
// the sentence to TargetWidth/TargetHeight from its summed extents, rounds the
// screen rect with WWMath::Floor(x + 0.5f) and clips with the ZH max/min form.
// The WorldBuilder twin (va 0x009ED680) has the same loop, search and clip shape.
// Codegen: Add_Quad is visible here (noinline) so the caller knows it does not
// read the dead screen_rect copy; the rendererStorage Add reads GrowthStep into
// a local as in MaterialCollectorCollectMaterials.cpp (retail adds into the
// Length() register).
// Flags and layouts follow the matched Render2DSentenceAllocateSurfaceBFME2.cpp.

#include <new>
#define _OPERATOR_NEW_DEFINED_
// math.h's inline floorf gets internal linkage (the mapper.cpp form): this
// /G7 unit's public copy is not retail's, and WWMath::Floor inlines it anyway.
extern "C" { static float __cdecl floorf(float); }
#include "vector.h"
#include "vector2i.h"
#include "vector2.h"
#include "../../../../../reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h"
#include <math.h>
// Suppress this TU's non-retail copy of ?ID@?$VectorClass@H@@UAEHPBH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
template <> int VectorClass<int>::ID(int const *);
// Suppress this TU's non-retail copy of ?ID@?$VectorClass@H@@UAEHABH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
template <> int VectorClass<int>::ID(int const &);
// Suppress this TU's non-retail copy of ?Resize@?$VectorClass@H@@UAE_NHPBH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
template <> bool VectorClass<int>::Resize(int,int const *);
// Suppress this TU's non-retail copy of ??8?$VectorClass@H@@UBE_NABV0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class VectorClass;
template <> bool VectorClass<int>::operator==(VectorClass<int> const &) const;
// Suppress this TU's non-retail copy of ?Clear@?$VectorClass@H@@UAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
template <> void VectorClass<int>::Clear();
typedef unsigned long uint32;

class BfmeSurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
};

class W3DRadarResetSurface
{
public:
	__declspec(dllimport) __forceinline W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();

	// Import-inline like the constructor: every use here inlines, so the unit
	// stops publishing its /G7-scheduled copy of the assignment.
	__declspec(dllimport) __forceinline W3DRadarResetSurface &operator=(const W3DRadarResetSurface &that)
	{
		if (that.m_surface)
			that.m_surface->AddRef();
		if (m_surface)
			m_surface->Release();
		m_surface = that.m_surface;
		return *this;
	}

	BfmeSurfaceResource *m_surface;
};

class FontCharsClass;

// SurfaceClass is the one-pointer native wrapper over the COM resource; the
// sentence's current surface is read through it for the texture size.
#include "W3DSurfaceClass.h"

typedef unsigned long BfmeUInt32;

struct BfmeRenderVertex
{
	float x;
	float y;
	float z;
	unsigned char m_unmodelled_0C[0x0C];
	BfmeUInt32 color;
	float u;
	float v;
	unsigned char m_unmodelled_24[0x08];
};

typedef BfmeUInt32 (__cdecl *BfmeColorConverter)(BfmeUInt32 color);

extern "C" float g_BfmeRender2DZ;
extern int g_Va00DB5FC8;

class Render2DClass
{
public:
	Render2DClass();
	void Set_Coordinate_Range(const RectClass &range);
	void Add_Quad(const RectClass &screen, const RectClass &uv, unsigned long color1, unsigned long color2, unsigned long color3, unsigned long color4);

private:
	unsigned char m_unmodelled_00[0x04];
	float m_coordinateScaleX;
	float m_coordinateScaleY;
	float m_biasedCoordinateOffsetX;
	float m_biasedCoordinateOffsetY;
	unsigned char m_unmodelled_14[0x38];

	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);

	void convertPosition006e(BfmeRenderVertex &vertex, float x, float y)
	{
		vertex.x = x * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
		vertex.z = g_BfmeRender2DZ;
	}
};

#include "DX8WrapperClass.h"

class Render2DSentenceClass
{
public:
	struct SentenceDataStruct : public W3DRadarResetSurface
	{
		bool operator==(const SentenceDataStruct &) { return false; }
		bool operator!=(const SentenceDataStruct &) { return true; }
		RectClass ScreenRect, UVRect;
	};

	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		// Retail destruction uses the shared four-byte scalar base table BBB5AC.
		// This is an ABI view; the renderer-pointer element type is donor
		// provenance and has not been established independently in the target.
		DynamicVectorClass<int> rendererStorage;
		// The shared destructor is defined in vector_class_resize.cpp.
		~PendingSurfaceStruct();

		bool operator==(const PendingSurfaceStruct &) { return false; }
		bool operator!=(const PendingSurfaceStruct &) { return true; }
	};

	struct RendererDataStruct
	{
		Render2DClass *Renderer;
		W3DRadarResetSurface Surface;
		bool operator==(const RendererDataStruct &) { return false; }
		bool operator!=(const RendererDataStruct &) { return true; }
	};

	void Draw_Sentence(uint32 color1, uint32 color2, uint32 color3, uint32 color4);
	virtual void reset();

private:
	DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct> sentence_data;
	DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct> pending_surfaces;
	DynamicVectorClass<RendererDataStruct> renderers;
	FontCharsClass *font;
	float base_location_x;
	float base_location_y;
	Vector2 Location;
	float cursor_x;
	float cursor_y;
	Vector2i texture_offset;
	int texture_start_x;
	int current_texture_size;
	int texture_size_hint;
	W3DRadarResetSurface cur_surface;
	char remaining_fields[0x0C];
	RectClass ClipRect, DrawExtents;
	bool IsClippedEnabled; char padAD[3];
	unsigned short *locked_ptr;
	Vector2 DefaultScale;
	float TargetWidth, TargetHeight;
};

// Suppress this TU's /G7 copy of the compiler-generated
// ??_EPendingSurfaceStruct@Render2DSentenceClass@@QAEPAXI@Z, which only these
// unused virtuals' delete[] would need: the kept copy serves the link.
// Plain declaration-only form (no __imp_).
template <> void VectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Clear();
template <> bool VectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Resize(int, Render2DSentenceClass::PendingSurfaceStruct const *);

template<> inline bool DynamicVectorClass<int>::Add(int const & object)
{
	if (ActiveCount >= Length()) {
		if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
			int growth = GrowthStep;
			if (!Resize(Length() + growth)) {
				return(false);
			}
		} else {
			return(false);
		}
	}
	(*this)[ActiveCount++] = object;
	return(true);
}

typedef char rva00155b00_surface_wrapper_must_be_4[(sizeof(W3DRadarResetSurface) == 4) ? 1 : -1];
typedef char rva00155b00_sentence_data_must_be_24[
	(sizeof(Render2DSentenceClass::SentenceDataStruct) == 0x24) ? 1 : -1];
typedef char rva00155b00_pending_surface_must_be_1c[
	(sizeof(Render2DSentenceClass::PendingSurfaceStruct) == 0x1c) ? 1 : -1];
// The emitted Add_Quad copy is a COMDAT the link may keep, so it must be
// retail's 430 bytes: retail's Add_Quad unit (Render2DClassAddQuadColor.cpp)
// is /O1, and only size optimisation gives its frame (push ebp ... leave).
#pragma optimize("s", on)

__declspec(noinline) inline void Render2DClass::Add_Quad(const RectClass &screen, const RectClass &uv,
	BfmeUInt32 color0, BfmeUInt32 color1,
	BfmeUInt32 color2, BfmeUInt32 color3)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], screen.Left, screen.Top);
	convertPosition006e(vertices[1], screen.Left, screen.Bottom);
	convertPosition006e(vertices[2], screen.Right, screen.Top);
	convertPosition006e(vertices[3], screen.Right, screen.Bottom);

	vertices[0].u = vertices[1].u = uv.Left;
	vertices[2].u = vertices[3].u = uv.Right;
	vertices[0].v = vertices[2].v = uv.Top;
	vertices[1].v = vertices[3].v = uv.Bottom;

	vertices[0].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color0);
	vertices[1].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color2);
	vertices[2].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color1);
	vertices[3].color = (*(BfmeColorConverter *)&g_Va00DB5FC8)(color3);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}
#pragma optimize("", on)

void Render2DSentenceClass::Draw_Sentence(uint32 color1, uint32 color2, uint32 color3, uint32 color4)
{
	Render2DClass *curr_renderer = 0;
	W3DRadarResetSurface curr_surface;

	Vector2 scale(DefaultScale);
	DrawExtents.Set(0, 0, 0, 0);

	int index;
	if (TargetWidth > 0 && TargetHeight > 0)
	{
		for (index = 0; index < sentence_data.Count(); index++)
		{
			SentenceDataStruct &data = sentence_data[index];
			if (DrawExtents.Width() == 0)
				DrawExtents = data.ScreenRect;
			else
				DrawExtents += data.ScreenRect;
		}
		float width = DrawExtents.Width();
		if (width != 0)
			scale.X = TargetWidth / width;
		float height = DrawExtents.Height();
		if (height != 0)
			scale.Y = TargetHeight / height;
		DrawExtents.Set(0, 0, 0, 0);
	}

	for (index = 0; index < sentence_data.Count(); index++)
	{
		SentenceDataStruct &data = sentence_data[index];

		if (data.m_surface != curr_surface.m_surface)
		{
			curr_surface = data;

			bool found = false;
			for (int renderer_index = 0; renderer_index < renderers.Count(); renderer_index++)
			{
				if (renderers[renderer_index].Surface.m_surface == curr_surface.m_surface)
				{
					found = true;
					curr_renderer = renderers[renderer_index].Renderer;
					break;
				}
			}

			if (found == false)
			{
				curr_renderer = new Render2DClass;
				curr_renderer->Set_Coordinate_Range(RectClass(0, 0, (float)(unsigned)DX8Wrapper::Get_Device_Resolution_Width(), (float)(unsigned)DX8Wrapper::Get_Device_Resolution_Height()));

				RendererDataStruct render_info;
				render_info.Renderer = curr_renderer;
				render_info.Surface = curr_surface;
				renderers.Add(render_info);

				for (int surface_index = 0; surface_index < pending_surfaces.Count(); surface_index++)
				{
					PendingSurfaceStruct &surface_info = pending_surfaces[surface_index];
					if (surface_info.m_surface == curr_surface.m_surface)
						surface_info.rendererStorage.Add((int)curr_renderer);
				}
			}
		}

		{
		RectClass screen_rect = data.ScreenRect;
		RectClass uv_rect = data.UVRect;
		Vector2 size(screen_rect.Width(), screen_rect.Height());
		screen_rect.Left *= scale.X;
		screen_rect.Top *= scale.Y;
		screen_rect.Right = size.X * scale.X + screen_rect.Left;
		screen_rect.Bottom = size.Y * scale.Y + screen_rect.Top;
		screen_rect += Location;
		screen_rect.Left = WWMath::Floor(screen_rect.Left + 0.5f);
		screen_rect.Top = WWMath::Floor(screen_rect.Top + 0.5f);
		screen_rect.Right = WWMath::Floor(screen_rect.Right + 0.5f);
		screen_rect.Bottom = WWMath::Floor(screen_rect.Bottom + 0.5f);

		bool add_quad = true;
		if (IsClippedEnabled)
		{
			if (screen_rect.Right <= ClipRect.Left || screen_rect.Bottom <= ClipRect.Top)
			{
				add_quad = false;
			}
			else
			{
				RectClass clipped_rect;
				clipped_rect.Left = max(screen_rect.Left, ClipRect.Left);
				clipped_rect.Right = min(screen_rect.Right, ClipRect.Right);
				clipped_rect.Top = max(screen_rect.Top, ClipRect.Top);
				clipped_rect.Bottom = min(screen_rect.Bottom, ClipRect.Bottom);

				RectClass clipped_uv_rect;
				float percent = ((clipped_rect.Left - screen_rect.Left) / screen_rect.Width());
				clipped_uv_rect.Left = uv_rect.Left + (uv_rect.Width() * percent);

				percent = ((clipped_rect.Right - screen_rect.Left) / screen_rect.Width());
				clipped_uv_rect.Right = uv_rect.Left + (uv_rect.Width() * percent);

				percent = ((clipped_rect.Top - screen_rect.Top) / screen_rect.Height());
				clipped_uv_rect.Top = uv_rect.Top + (uv_rect.Height() * percent);

				percent = ((clipped_rect.Bottom - screen_rect.Top) / screen_rect.Height());
				clipped_uv_rect.Bottom = uv_rect.Top + (uv_rect.Height() * percent);

				screen_rect = clipped_rect;
				uv_rect = clipped_uv_rect;

				if (screen_rect.Right <= screen_rect.Left || screen_rect.Bottom <= screen_rect.Top)
				{
					add_quad = false;
				}
			}
		}

		if (add_quad)
		{
			SurfaceClass::SurfaceDescription desc;
			((SurfaceClass *)&curr_surface)->Get_Description(desc);

			uv_rect.Left *= 1.0F / ((float)desc.Width);
			uv_rect.Right *= 1.0F / ((float)desc.Width);
			uv_rect.Top *= 1.0F / ((float)desc.Height);
			uv_rect.Bottom *= 1.0F / ((float)desc.Height);

			curr_renderer->Add_Quad(screen_rect, uv_rect, color1, color2, color3, color4);

			if (DrawExtents.Width() == 0)
				DrawExtents = screen_rect;
			else
				DrawExtents += screen_rect;
		}
		}
	}
}
