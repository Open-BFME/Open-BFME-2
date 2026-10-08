// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

void __cdecl operator delete[](void *) throw();
#include "vector.h"
#include "vector2i.h"

// Donor BFME1 9cbfb551fe20 Render2DSentenceClass_Allocate_New_Surface.cpp.
// BFME2 native 158C60..158E87/551B: no leading Unlock; spacing uses loadCharacterData.
// Target class fields and complete COM surface and PendingSurface lifecycle match donor.
// Target sentence layout/font pointer4C and resource operations attest owner.
// Font record layout and integer vector type are carried from BFME1 source;
// native width/extra and68/6C texture-offset clears independently support use.

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
	W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();

	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &that)
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

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short ExtraSpacing;
};

// The callsite sets ecx to this font object, pushes one WCHAR, and the body
// returns a character-record pointer with RET 4.  This name and ABI are
// already pinned independently by the matching font-spacing thunk.
class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short character);

	__forceinline int Get_Char_Height() const
	{
		return char_height;
	}

	__forceinline int Get_Char_Spacing(unsigned short character)
	{
		const FontCharsClassCharDataStruct *data = loadCharacterData(character);
		if (data != 0 && data->Width != 0) {
			if ((character >= 0x0e01 && character <= 0x0e3a)
				|| (character >= 0x0e3f && character <= 0x0e5b)) {
				return data->Width + data->ExtraSpacing;
			}
			return data->Width - pixel_overlap - char_overhang;
		}
		return 0;
	}

private:
	char fields00[0x2c];
	int char_height;
	char fields30[4];
	int char_overhang;
	int pixel_overlap;
};

enum WW3DFormat
{
	// The retail constructor receives 0x15; the semantic format name is
	// intentionally neutral pending an enum witness.
	WW3D_FORMAT_008FC560 = 0x15
};

enum _D3DPOOL
{
	D3DPOOL_SYSTEMMEM = 2
};
typedef _D3DPOOL D3DPOOL;

// SurfaceClass is the one-pointer native wrapper whose constructor writes
// the COM resource at offset zero.  Its implicit destructor invokes the
// native W3DRadarResetSurface base destructor for the temporary lifetime.
class SurfaceClass
	: public W3DRadarResetSurface
{
public:
	SurfaceClass(unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool);
	void Unlock();
};

class Render2DClass;

class Render2DSentenceClass
{
public:
	struct SentenceDataStruct : public W3DRadarResetSurface
	{
		bool operator==(const SentenceDataStruct &) { return false; }
		bool operator!=(const SentenceDataStruct &) { return true; }
		float screen_left;
		float screen_top;
		float screen_right;
		float screen_bottom;
		float uv_left;
		float uv_top;
		float uv_right;
		float uv_bottom;
	};

	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		DynamicVectorClass<Render2DClass *> Renderers;

		bool operator==(const PendingSurfaceStruct &) { return false; }
		bool operator!=(const PendingSurfaceStruct &) { return true; }
	};

	virtual void reset();
	private:
	void Allocate_New_Surface(const unsigned short *text, bool justCalcExtents);

	DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct> sentence_data;
	DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct> pending_surfaces;
	char renderers[0x18];
	FontCharsClass *font;
	float base_location_x;
	float base_location_y;
	float location_x;
	float location_y;
	float cursor_x;
	float cursor_y;
	Vector2i texture_offset;
	int texture_start_x;
	int current_texture_size;
	int texture_size_hint;
	W3DRadarResetSurface cur_surface;
	char remaining_fields[0x30];
	unsigned short *locked_ptr;
};

// Keep the native PendingSurfaceStruct Add body out-of-line at its already
// matched address; the generic header definition is otherwise small enough
// for this TU to inline it into the caller.
template <>
bool DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Add(
	const Render2DSentenceClass::PendingSurfaceStruct &object);

typedef char rva00941a00_surface_wrapper_must_be_4[(sizeof(W3DRadarResetSurface) == 4) ? 1 : -1];
typedef char rva00941a00_pending_surface_must_be_1c[
	(sizeof(Render2DSentenceClass::PendingSurfaceStruct) == 0x1c) ? 1 : -1];
typedef char rva00941a00_pending_vector_must_be_18[
	(sizeof(DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>) == 0x18) ? 1 : -1];

void Render2DSentenceClass::Allocate_New_Surface(
	const unsigned short *text, bool justCalcExtents)
{

	int text_width = 0;
	for (int index = 0; text[index] != 0; index++) {
		text_width += font->Get_Char_Spacing(text[index]);
	}

	int char_height = font->Get_Char_Height();

	current_texture_size = 256;
	int best_tex_mem_usage = 999999999;
	for (int pow2 = 6; pow2 <= 8; pow2++) {
		int size = 1 << pow2;
		int row_count = (text_width / size) + 1;
		int rows_per_texture = size / (char_height + 1);

		if (rows_per_texture > 0) {
			int texture_count = row_count / rows_per_texture;
			texture_count = max(texture_count, 1);
			int texture_mem_usage = texture_count * size * size;
			if (texture_mem_usage < best_tex_mem_usage) {
				current_texture_size = size;
				best_tex_mem_usage = texture_mem_usage;
			}
		}
	}

	current_texture_size = max(texture_size_hint, current_texture_size);

	if (!justCalcExtents)
	{
		if (cur_surface.m_surface) {
			cur_surface.m_surface->Release();
			cur_surface.m_surface = 0;
		}

		cur_surface = SurfaceClass(current_texture_size, current_texture_size,
			WW3D_FORMAT_008FC560, D3DPOOL_SYSTEMMEM);

		Render2DSentenceClass::PendingSurfaceStruct surface_info;
		static_cast<W3DRadarResetSurface &>(surface_info) = cur_surface;
		pending_surfaces.Add(surface_info);
	}

	texture_offset.Set(0,0);
	texture_start_x = 0;
}
