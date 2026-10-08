// ?Rva00158E90@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z
// partial score=0.707 date=2026-10-09
// stlport
// cl: /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

// CRT math/string calls remain DLL imports; allocator free uses the game wrapper.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#include <math.h>
#undef _CRTIMP
#define _CRTIMP
#include <vector>
#define _OPERATOR_NEW_DEFINED_
void __cdecl operator delete[](void *) throw();
#include "vector.h"
#include "vector2i.h"
#include "vector2.h"

struct BfmeWordVec : std::vector<unsigned short> { void resize(unsigned int,unsigned short); };
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
    void rva001588A0(unsigned short,unsigned short *,int,int,int);
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
// ?Rva00158E90@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z present-unmatched
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
    glyph[length]=0xFFFF;
    Vector2 extent;
    if (!CurSurface.m_surface) Rva00158990(active,text,glyph,justCalcExtents);
        TextureOffset.Set(2,0);
        TextureStartX=2;
        unsigned short *locked=0;
        int stride=0;
        if (!justCalcExtents) {
            locked=(unsigned short *)reinterpret_cast<Rva00116680 *>(&CurSurface)->rva00116680(&stride,false);
            if (!locked) return Vector2(0,0);
        }
        float char_height=active->Get_Char_Height();
        while(text) {
            unsigned short ch=*text++;
            unsigned short glyphCh=NextGlyphIndex(glyph);
            bool dontBlit=false;
            bool retry;
            float char_spacing;
            do {
                retry=false;
                dontBlit=false;
                if (ParseHotKey && ch=='&' && *text!=0 && *text>' ' && *text!='\n' && *text!=0x95) {
                    hotKeyPosY=(int)Cursor.Y;
                    if (calcHotKeyX) hotKeyPosX=0;
                    else hotKeyPosX=(int)(Cursor.X+TextureOffset.I-TextureStartX);
                    ch=*text++;
                    glyphCh=NextGlyphIndex(glyph);
                    dontBlit=true;
                }
                char_spacing=(float)active->Get_Glyph_Advance(glyphCh);
                bool encountered_break_char=(ch==' ' || ch=='\n' || ch==0x95 || ch==0);
                bool wordBiggerThenLine=useHardWordWrap && WrapWidth!=0 && (Cursor.X+TextureOffset.I-TextureStartX+char_spacing)>=WrapWidth;
                if (encountered_break_char || wordBiggerThenLine) {
                    if (!justCalcExtents) rva00156540(reinterpret_cast<const Rva00156540Param *>(active));
                    Cursor.X += TextureOffset.I-TextureStartX;
                    maxX=max(maxX,Cursor.X);
                    TextureStartX=TextureOffset.I;
                    if (ch==' ' || ch==0x95) {
                        if (WrapWidth>0) {
                            const unsigned short *word=text;
                            const unsigned short *wordGlyph=glyph;
                            float word_width=char_spacing;
                            while (*word!=0 && *word>' ' && *word!=0x95) {
                                if (ParseHotKey && *word=='&') {++word;++wordGlyph;}
                                word_width+=active->Get_Glyph_Advance(*wordGlyph++);
                                ++word;
                            }
                            if (Cursor.X+word_width>=WrapWidth) {
                                Cursor.X=0;
                                Cursor.Y+=char_height;
                                calcHotKeyX=true;
                                do {ch=*text++;glyphCh=NextGlyphIndex(glyph);} while(ch==' ' || ch==0x95);
                                retry=true;
                            }
                        }
                        if (ch==0x95) {
                            do {ch=*text++;glyphCh=NextGlyphIndex(glyph);} while(ch==0x95);
                            retry=true;
                        }
                    } else if (ch=='\n') {
                        Cursor.X=0;
                        Cursor.Y+=char_height;
                        do {ch=*text++;glyphCh=NextGlyphIndex(glyph);} while(ch==' ');
                        retry=true;
                    } else if (wordBiggerThenLine && ch!=0) {
                        Cursor.X=0;
                        Cursor.Y+=char_height;
                    }
                }
                if (!ch) break;
            } while(retry);
            if (!ch) break;
            if (TextureOffset.I+char_spacing>=CurrTextureSize) {
                if (!justCalcExtents) rva00156540(reinterpret_cast<const Rva00156540Param *>(active));
                Cursor.X+=TextureOffset.I-TextureStartX;
                maxX=max(maxX,Cursor.X);
                int adjustment=active->Get_Left_Adjust(glyphCh,Cursor);
                TextureStartX=2;
                TextureOffset.I=2-adjustment;
                TextureOffset.J+=char_height;
                if (TextureOffset.J+char_height>=CurrTextureSize) {
                    if (locked) {
                        reinterpret_cast<Member0C00739C70 *>(&CurSurface)->clear();
                        locked=0;
                    }
                    Rva00158990(active,text,glyph,justCalcExtents);
                    if (!justCalcExtents) {
                        locked=(unsigned short *)reinterpret_cast<Rva00116680 *>(&CurSurface)->rva00116680(&stride,false);
                        if (!locked) return Vector2(0,0);
                    }
                }
            }
            if (!justCalcExtents && !dontBlit) active->rva001588A0(glyphCh,locked,stride,TextureOffset.I,TextureOffset.J);
            TextureOffset.I+=char_spacing;
        }
        if (locked) reinterpret_cast<Member0C00739C70 *>(&CurSurface)->clear();
        extent.X=maxX+active->Get_Extra_Overlap();
        extent.Y=Cursor.Y+active->Get_Char_Height();
        if (!justCalcExtents && Centered && sentence_data.Count()>0) {
            int start=0;
            float left=sentence_data[0].screen_left;
            float top=sentence_data[0].screen_top;
            float right=sentence_data[0].screen_right;
            for (int i=1;i<=sentence_data.Count();++i) {
                if (i<sentence_data.Count() && sentence_data[i].screen_top==top) {
                    right=sentence_data[i].screen_right;
                    continue;
                }
                float shift=(float)floor((extent.X-(active->Get_Extra_Overlap()*0.5+right-left))*0.5-left+0.5);
                for (int j=start;j<i;++j) {
                    sentence_data[j].screen_left+=shift;
                    sentence_data[j].screen_right+=shift;
                }
                if (i<sentence_data.Count()) {
                    start=i;
                    left=sentence_data[i].screen_left;
                    top=sentence_data[i].screen_top;
                    right=sentence_data[i].screen_right;
                }
            }
        }

    if (hkX) {*hkX=hotKeyPosX;*hkY=hotKeyPosY;}
    return extent;
}
