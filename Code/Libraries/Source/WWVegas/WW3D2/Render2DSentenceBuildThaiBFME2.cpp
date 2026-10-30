// ?Rva00158E90@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z @0x00158E90 2151B.
// stlport
// cl: /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /G7 /DNDEBUG /MD /EHs /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Render2DSentenceClass::Rva00158E90 (original name unknown): the Thai sentence builder that
// Build_Sentence_Not_Centered (0x00159700) hands Thai text to. Evidence and earlier rounds:
// reverse/attempt_support/158e90-claude3-20261020.md and the 158e90-* handoffs beside it.

// CRT math/string calls remain DLL imports; allocator free uses the game wrapper.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#include <math.h>
#undef _CRTIMP
#define _CRTIMP
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include <new>
#include "vector.h"
#include "vector2i.h"
#include "vector2.h"
// Suppress this TU's non-retail copy of ??$fill_n@PAGIG@_STL@@YAPAGPAGIABG@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short * fill_n<unsigned short *,unsigned int,unsigned short>(unsigned short *,unsigned int,unsigned short const &); }
// Suppress this TU's non-retail copy of ?Clear@?$VectorClass@PAVRender2DClass@@@@UAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Render2DClass;
template <> void VectorClass<Render2DClass *>::Clear();

// These word helpers retain STLport's inline operations and external providers.
namespace _STL {
// Keep the allocator operation inline without publishing this TU's non-retail copy.
template <> __declspec(dllimport) __forceinline void
allocator<unsigned short>::deallocate(unsigned short *p, size_type n) const
{
    _STLP_ASSERT((p == 0) == (n == 0))
    if (p != 0)
        ::free((void *)p);
}

template <> __declspec(dllimport) __forceinline void
fill<unsigned short *, unsigned short>(unsigned short *first, unsigned short *last, const unsigned short &value)
{
    for (; first != last; ++first)
        *first = value;
}
template <> __declspec(dllimport) __forceinline unsigned short *
__uninitialized_copy<unsigned short *, unsigned short *>(unsigned short *first, unsigned short *last, unsigned short *result, const __true_type &)
{
    return __copy_aux(first, last, result, _BothPtrType<unsigned short *, unsigned short *>::_Ret());
}
}

struct BfmeWordVec : std::vector<unsigned short> {
    __declspec(noinline) void resize(unsigned int n,unsigned short x) {
        if (n < size()) erase(begin() + n, end());
        else _M_fill_insert(end(), n - size(), x);
    }
};
class Rva0093C4A0Target { public: bool Check(const unsigned short *,unsigned short *,int); };
struct Rva00156540Param;

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock { public: BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();} ~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();} };
class Rva00116680 { public: void *rva00116680(int *,bool); };
class Member0C00739C70 { public: void clear(); };

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
    __forceinline int Get_Extra_Overlap(){return pixel_overlap;}
    void Blit_Char(unsigned short,unsigned short *,int,int,int);
    void Blit_Char_Thai(unsigned short,unsigned short *,int,int,int);
    __forceinline FontCharsClass *AlternateFont(){return *(FontCharsClass **)((char *)this+8);}
    __forceinline int Get_Left_Adjust(unsigned short ch,Vector2 &cursor) {
        const FontCharsClassCharDataStruct *data=Get_Char_Data(ch);
        if (data) {
            int adjustment=data->ExtraSpacing;
            if (adjustment<0) {cursor.X+=(float)adjustment;return adjustment;}
        }
        return 0;
    }
    __forceinline int Get_Glyph_Advance(unsigned short ch) {
        const FontCharsClassCharDataStruct *data=Get_Char_Data(ch);
        return data ? data->ExtraSpacing + data->Width : 0;
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
    const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short);
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
		PendingSurfaceStruct();
		~PendingSurfaceStruct();
		DynamicVectorClass<Render2DClass *> Renderers;

		bool operator==(const PendingSurfaceStruct &) { return false; }
		bool operator!=(const PendingSurfaceStruct &) { return true; }
	};

	virtual void reset();
	private:
	void Allocate_New_Surface(const unsigned short *text, bool justCalcExtents);
    void Reset_Sentence_Data();
    void Record_Sentence_Chunk();
    Vector2 Rva00158E90(const unsigned short *,int *,int *,bool);
    Vector2 Build_Sentence_Not_Centered(const unsigned short *,int *,int *,bool);
    void Rva00158990(FontCharsClass *,const unsigned short *,const unsigned short *,bool);
public:
    void rva00156540(const Rva00156540Param *);
private:

	DynamicVectorClass<Render2DSentenceClass::SentenceDataStruct> sentence_data;
	DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct> pending_surfaces;
	char renderers[0x18];
	FontCharsClass *font;
    Vector2 BaseLocation;
    Vector2 Location;
    Vector2 Cursor;
    Vector2i TextureOffset;
    int TextureStartX;
    int CurrTextureSize;
    int TextureSizeHint;
    W3DRadarResetSurface CurSurface;
    bool MonoSpaced;
    float WrapWidth;
    bool Centered;
    char centeredPadding[3];
    char remaining_fields8C[0xAD-0x8C];
    bool ParseHotKey;
    bool useHardWordWrap;

};

// Keep the native PendingSurfaceStruct Add body out-of-line at its already
// matched address; the generic header definition is otherwise small enough
// for this TU to inline it into the caller.
template <>
bool DynamicVectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Add(
	const Render2DSentenceClass::PendingSurfaceStruct &object);


// Retail reads both WrapWidth compares' 0.0f from the shared zero at 0x007BAEAC. Through the
// named zero (the literal's own alias) cl reloads extent.Y before extent.X at the join after
// the centering pass (+0x806) as retail does; the bare literal reloads X first.
extern const float BfmeZeroRange;
static __forceinline unsigned short NextGlyphIndex(unsigned short *&glyph) {
    unsigned short index=*glyph;
    ++glyph;
    return index;
}

// Native158E90..1596F7/2151B; original method name unknown.
// Reference sentence layout/loop is the semantic guide; target extends it
// with a word-vector glyph buffer, GDI validation and alternate-font fallback.
// Paired text/glyph cursors, nibble blitter1588A0 and font-argument recorder
// 156540 are read from native calls. Real STLport word vector uses rowed resize824F9.
Vector2 Render2DSentenceClass::Rva00158E90(const unsigned short *text,int *hkX,int *hkY,bool justCalcExtents) {
    float maxX=0;
    int hotKeyPosX=0,hotKeyPosY=0;
    bool calcHotKeyX=false;
    int length=(int)wcslen(text);
    BfmeWordVec glyphs;
    glyphs.resize(length+1,0);
    unsigned short *glyph=glyphs.begin();
    FontCharsClass *active;
    if (!reinterpret_cast<Rva0093C4A0Target *>(font)->Check(text,glyph,length) && font->AlternateFont()) {
        reinterpret_cast<Rva0093C4A0Target *>(font->AlternateFont())->Check(text,glyph,length);
        active=font->AlternateFont();
    } else active=font;
    Vector2 extent;
    glyph[length]=0xFFFF;
    W3DRadarResetSurface *cur=&CurSurface;
    // Ensure we have a surface to start with
    if (!cur->m_surface) Rva00158990(active,text,glyph,justCalcExtents);
        TextureOffset.Set(2,0);
        TextureStartX=2;
        unsigned short *locked=0;
        int stride=0;
        // Ensure the surface is locked
        if (!justCalcExtents) {
            locked=(unsigned short *)reinterpret_cast<Rva00116680 *>(cur)->rva00116680(&stride,false);
            if (!locked) return Vector2(0,0);
        }
        float char_height=active->Get_Char_Height();
        unsigned short *glyphPtr=glyph;
        // Loop over all the characters in the string
        while(text) {
            unsigned short ch=*text++;
            unsigned short glyphCh=*glyphPtr;
            ++glyphPtr;
            bool dontBlit=false;
            bool retry;
            float char_spacing;
            do {
                retry=false;
                dontBlit=false;
                // Determine how much horizontal space this character requires
                if (ParseHotKey && ch=='&' && *text!=0 && *text>' ' && *text!='\n' && *text!=0x95) {
                    hotKeyPosY=(int)Cursor.Y;
                    if (calcHotKeyX) hotKeyPosX=0;
                    else hotKeyPosX=(int)(Cursor.X+TextureOffset.I-TextureStartX);
                    ch=*text++;
                    glyphCh=*glyphPtr;
                    ++glyphPtr;
                    dontBlit=true;
                }
                char_spacing=(float)active->Get_Glyph_Advance(glyphCh);
                bool encountered_break_char=(ch==' ' || ch=='\n' || ch==0x95 || ch==0);
                bool wordBiggerThenLine=useHardWordWrap && WrapWidth!=BfmeZeroRange && (Cursor.X+TextureOffset.I-TextureStartX+char_spacing)>=WrapWidth;
                // Do we need to record this portion of the sentence to its own chunk?
                if (encountered_break_char || wordBiggerThenLine) {
                    if (!justCalcExtents) rva00156540(reinterpret_cast<const Rva00156540Param *>(active));
                    // Adjust the positions
                    Cursor.X += TextureOffset.I-TextureStartX;
                    maxX=max(maxX,Cursor.X);
                    TextureStartX=TextureOffset.I;
                    // Adjust the output coordinates
                    if (ch==' ' || ch==0x95) {
                        // Check to see if we need to wrap on this word-break
                        if (WrapWidth>BfmeZeroRange) {
                            // Find the length of the next word
                            const unsigned short *word=text;
                            const unsigned short *wordGlyph=glyphPtr;
                            float word_width=char_spacing;
                            while (*word!=0 && *word>' ' && *word!=0x95) {
                                if (ParseHotKey && *word=='&') {++wordGlyph;++word;}
                                word_width+=active->Get_Glyph_Advance(*wordGlyph++);
                                ++word;
                            }
                            // Should we wrap the next word?
                            if (Cursor.X+word_width>=WrapWidth) {
                                Cursor.X=0;
                                Cursor.Y+=char_height;
                                calcHotKeyX=true;
                                do {ch=*text++;glyphCh=*glyphPtr;++glyphPtr;} while(ch==' ' || ch==0x95);
                                retry=true;
                            }
                        }
                        if (ch==0x95) {
                            do {ch=*text++;glyphCh=*glyphPtr;++glyphPtr;} while(ch==0x95);
                            retry=true;
                        }
                    } else if (ch=='\n') {
                        Cursor.X=0;
                        Cursor.Y+=char_height;
                        do {ch=*text++;glyphCh=*glyphPtr;++glyphPtr;} while(ch==' ');
                        retry=true;
                    } else if (wordBiggerThenLine) {
                        Cursor.X=0;
                        Cursor.Y+=char_height;
                    }
                }
            } while(ch && retry);
            if (!ch) break;
            // Did the text extend past the edge of the texture?
            if (TextureOffset.I+char_spacing>=CurrTextureSize) {
                if (!justCalcExtents) rva00156540(reinterpret_cast<const Rva00156540Param *>(active));
                Cursor.X+=TextureOffset.I-TextureStartX;
                maxX=max(maxX,Cursor.X);
                int adjustment=active->Get_Left_Adjust(glyphCh,Cursor);
                TextureStartX=2;
                TextureOffset.I=2-adjustment;
                TextureOffset.J+=char_height;
                // Did the text extent completely off the texture?
                if (TextureOffset.J+char_height>=CurrTextureSize) {
                    if (locked) {
                        reinterpret_cast<Member0C00739C70 *>(&CurSurface)->clear();
                        locked=0;
                    }
                    Rva00158990(active,text,glyphPtr,justCalcExtents);
                    if (!justCalcExtents) {
                        locked=(unsigned short *)reinterpret_cast<Rva00116680 *>(&CurSurface)->rva00116680(&stride,false);
                        if (!locked) return Vector2(0,0);
                    }
                }
            }
            // Blit the character to the surface
            if (!justCalcExtents && !dontBlit) active->Blit_Char_Thai(glyphCh,locked,stride,TextureOffset.I,TextureOffset.J);
            TextureOffset.I+=char_spacing;
        }
        if (locked) reinterpret_cast<Member0C00739C70 *>(&CurSurface)->clear();
        extent.X=maxX+active->Get_Extra_Overlap();
        extent.Y=Cursor.Y+active->Get_Char_Height();
        if (!justCalcExtents && Centered) {
            const int count=sentence_data.Count();
            if (count>0) {
                int start=0;
                float top=sentence_data[0].screen_top;
                float left=sentence_data[0].screen_left;
                float right=sentence_data[0].screen_right;
                for (int i=1;;++i) {
                    if (i>=count || sentence_data[i].screen_top!=top) {
                        float width=(active->Get_Extra_Overlap()*0.5f+right)-left;
                        float shift=(float)floor((double)((extent.X-width)*0.5f-left+0.5f));
                        for (int j=start;j<i;++j) {
                            sentence_data[j].screen_left=sentence_data[j].screen_left+shift;
                            sentence_data[j].screen_right=sentence_data[j].screen_right+shift;
                        }
                        if (i>=count) break;
                        start=i;
                        top=sentence_data[i].screen_top;
                        left=sentence_data[i].screen_left;
                    }
                    right=sentence_data[i].screen_right;
                }
            }
        }

    if (hkX) {*hkX=hotKeyPosX;*hkY=hotKeyPosY;}
    return extent;
}

// The centering pass snapshots the record count and exits after its final group.
// A hard-width break updates the cursor before the terminating-zero check.
