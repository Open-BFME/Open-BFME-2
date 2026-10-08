// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "vector.h"

// BFME1 donor9cbfb551fe20 Rva0093F310RecordSentence.cpp; native156390..156489/249B.
// BFME2 /G7 /arch:SSE and target COM lifetime/float fields support the transfer.
// The rendering-family caller and the upstream Render2DSentenceClass
// declaration establish the native Record_Sentence_Chunk identity.

class BfmeSurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
};

// This is the already-matched one-pointer surface wrapper.  Its destructor
// is the existing 0x008FC5B0 body; the two virtual calls below deliberately
// use the COM ABI visible in retail: AddRef at vtable +4 and Release at +8,
// with the receiver pushed for each __stdcall call.
class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();
    W3DRadarResetSurface &operator=(const W3DRadarResetSurface &that) {
        if (that.m_surface) that.m_surface->AddRef();
        if (m_surface) m_surface->Release();
        m_surface=that.m_surface;
        return *this;
    }

	BfmeSurfaceResource *m_surface;
};

// Upstream Render2DSentenceClass stores a FontCharsClass pointer and calls its
// public Get_Char_Height accessor; the +0x30 height field in this ABI witness
// agrees with that class's retail layout.
class FontCharsClass
{
public:
	int Get_Char_Height() const { return char_height; }

private:
	char pad[0x2c];
	int char_height;
};

// The existing 155630/84-byte append owner uses this placeholder spelling.
// Native Record_Sentence_Chunk calls it with the 36-byte sentence record;
// its matched154AF0 assignment takes the COM surface then copies nine dwords.
// Keep that provider spelling without adding a second name or callee pin.
struct TextureStatisticsStructWide;
template<class T> class DynamicVectorClassWide {
public:
    bool Add(const T &object);
};

class Render2DSentenceClass
{
public:
	// The retail local and vector element are 36 bytes: one four-byte surface
	// wrapper followed by eight four-byte geometry values.  The canonical nested
	// spelling is intentional: DynamicVectorClass::Add below is the existing
	// verified callee whose implementation is BfmeSentenceDataVector::Add.
	struct SentenceDataStruct : public W3DRadarResetSurface
	{
		// Native record stubs, used by the existing vector implementation.
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

	virtual void reset();
private:
	void Record_Sentence_Chunk();

private:
	DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct> sentence_data;
	char pending_surfaces[0x18];
	char renderers[0x18];
	FontCharsClass *font;
	float base_location_x;
	float base_location_y;
	float location_x;
	float location_y;
	float cursor_x;
	float cursor_y;
	int texture_offset_i;
	int texture_offset_j;
	int texture_start_x;
	int current_texture_size;
	int texture_size_hint;
	W3DRadarResetSurface cur_surface;
};

typedef char rva0093f310_surface_wrapper_must_be_4[(sizeof(W3DRadarResetSurface) == 4) ? 1 : -1];
typedef char rva0093f310_sentence_record_must_be_36[
	(sizeof(Render2DSentenceClass::SentenceDataStruct) == 36) ? 1 : -1];
typedef char rva0093f310_sentence_vector_must_be_24[
	(sizeof(DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct>) == 24) ? 1 : -1];

void Render2DSentenceClass::Record_Sentence_Chunk()
{
	int width = texture_offset_i - texture_start_x;
	if (width > 0)
	{
		float char_height = font->Get_Char_Height();

		Render2DSentenceClass::SentenceDataStruct sentence_data;
		static_cast<W3DRadarResetSurface &>(sentence_data)=cur_surface;
		sentence_data.screen_left = cursor_x;
		sentence_data.screen_right = cursor_x + width;
		sentence_data.screen_top = cursor_y;
		sentence_data.screen_bottom = cursor_y + char_height;
		sentence_data.uv_left = texture_start_x;
		sentence_data.uv_top = texture_offset_j;
		sentence_data.uv_right = texture_offset_i;
		sentence_data.uv_bottom = texture_offset_j + char_height;

		reinterpret_cast<DynamicVectorClassWide<TextureStatisticsStructWide> *>(&this->sentence_data)->Add(
            reinterpret_cast<const TextureStatisticsStructWide &>(sentence_data));
	}
}

