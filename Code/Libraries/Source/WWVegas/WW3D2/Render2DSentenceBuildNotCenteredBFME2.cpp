// ?Build_Sentence_Not_Centered@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z @0x00159700 2230B.
// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
// Render2DSentenceClass::Build_Sentence_Not_Centered: lays a sentence out glyph by glyph
// (Zero Hour semantics) on BFME 2's private sentence view, hands Thai text to the native
// builder at 0x00158E90 and centers each finished line. Evidence and earlier rounds:
// reverse/attempt_support/159700-claude3-20261020.md and sentence-159700-20261019/.

#include <new>
#define _OPERATOR_NEW_DEFINED_
#include "vector.h"
#include "vector2i.h"
#include "vector2.h"
#include <math.h>
// Suppress this TU's non-retail copy of ?Clear@?$VectorClass@PAVRender2DClass@@@@UAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Render2DClass;
template <> void VectorClass<Render2DClass *>::Clear();
template <> bool VectorClass<Render2DClass *>::Resize(int, Render2DClass *const *);
template <> VectorClass<Render2DClass *>::~VectorClass();
template <> DynamicVectorClass<Render2DClass *>::~DynamicVectorClass();
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"
class Rva00116680 { public: void *rva00116680(int *,bool); };
class Member0C00739C70 { public: void clear(); };

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
    __forceinline int Get_Extra_Overlap(){return pixel_overlap;}
    void Blit_Char(unsigned short,unsigned short *,int,int,int);

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
#include "W3DSurfaceClass.h"

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


static __forceinline unsigned short NextSentenceChar(const unsigned short *&p) {
    unsigned short ch=*p;
    ++p;
    return ch;
}

// Copies the Thai builder's extent field by field: both fields are read
// first (X, then Y), then stored Y before X.  Retail's return-path join
// (+0x836) reloads extent.X before extent.Y only with this store order;
// a plain Vector2 assignment stores X first and reverses those reloads.
static inline void Copy_Extent(Vector2 &dst,const Vector2 &src)
{
    float x=src.X;
    float y=src.Y;
    dst.Y=y;
    dst.X=x;
}

// ZH Build_Sentence_Not_Centered semantics adapted to target2230-byte body.
// Native159700..159FB6: device mutex guard, Thai dispatch, local lock data,
// separator95, retry after break skipping, and post-render line centering.
// Font/sentence layout is supported by newly verified allocator/record siblings.
// Rva00158E90's original method name remains unknown; callsite proves Vector2
// hidden return plus text/hotkey pointers/calc, and its full native helper is read.
// Retail hard wrapping includes the terminal zero before the extent is finalized.
// Centering snapshots the sentence count and processes the final line before exiting.
Vector2 Render2DSentenceClass::Build_Sentence_Not_Centered(const unsigned short *text,int *hkX,int *hkY,bool justCalcExtents) {
    Vector2 cursor=Cursor;
    int textureStartX=TextureStartX;
    float maxX=0;
    int hotKeyPosX=0,hotKeyPosY=0;
    bool calcHotKeyX=false;
    Vector2i textureOffset=TextureOffset;
    BFMEDX8DeviceLock device_lock;
    // Start fresh
    if (!justCalcExtents) Reset_Sentence_Data();
    Cursor.Set(0,0);
    bool thai=false;
    for (const unsigned short *scan=text;*scan;++scan) {
        unsigned short ch=*scan;
        if ((ch>=0xE01 && ch<=0xE3A)||(ch>=0xE3F && ch<=0xE5B)) {thai=true;break;}
    }
    Vector2 extent;
    if (thai) {
        Copy_Extent(extent,Rva00158E90(text,hkX,hkY,justCalcExtents));
    } else {
        // Ensure we have a surface to start with
        if (!CurSurface.m_surface) Allocate_New_Surface(text,justCalcExtents);
        TextureOffset.Set(2,0);
        TextureStartX=2;
        float char_height=font->Get_Char_Height();
        unsigned short *locked=0;
        int stride=0;
        // Ensure the surface is locked
        if (!justCalcExtents) {
            locked=(unsigned short *)reinterpret_cast<Rva00116680 *>(&CurSurface)->rva00116680(&stride,false);
            if (!locked) return Vector2(0,0);
        }
        // Loop over all the characters in the string
        while(text) {
            unsigned short ch=*text++;
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
                    else hotKeyPosX=(int)(Cursor.X+TextureOffset.I-TextureStartX);//TextureOffset.I;
                    ch=*text++;
                    dontBlit=true;
                }
                char_spacing=(float)font->Get_Char_Spacing(ch);
                bool encountered_break_char=(ch==' ' || ch=='\n' || ch==0x95 || ch==0);
                bool wordBiggerThenLine=useHardWordWrap && WrapWidth!=0 && (Cursor.X+TextureOffset.I-TextureStartX+char_spacing)>=WrapWidth;
                // Do we need to record this portion of the sentence to its own chunk?
                if (encountered_break_char || wordBiggerThenLine) {
                    if (!justCalcExtents) Record_Sentence_Chunk();
                    // Adjust the positions
                    Cursor.X += TextureOffset.I-TextureStartX;
                    maxX=max(maxX,Cursor.X);
                    TextureStartX=TextureOffset.I;
                    // Adjust the output coordinates
                    if (ch==' ' || ch==0x95) {
                        //Cursor.X += char_spacing;
                        //maxX = max(maxX, Cursor.X);
                        // Check to see if we need to wrap on this word-break
                        if (WrapWidth>0) {
                            // Find the length of the next word
                            const unsigned short *word=text;
                            float word_width=char_spacing;
                            while (*word!=0 && *word>' ' && *word!=0x95) {
                                if (ParseHotKey && *word=='&') ++word;
                                word_width+=font->Get_Char_Spacing(*word++);
                            }
                            // Should we wrap the next word?
                            if (Cursor.X+word_width>=WrapWidth) {
                                Cursor.X=0;
                                Cursor.Y+=char_height;
                                calcHotKeyX=true;
                                do {ch=*text++;} while(ch==' ' || ch==0x95);
                                retry=true;
                            }
                        }
                        if (ch==0x95) {
                            do {ch=*text++;} while(ch==0x95);
                            retry=true;
                        }
                    } else if (ch=='\n') {
                        Cursor.X=0;
                        Cursor.Y+=char_height;
                        do {ch=*text++;} while(ch==' ');
                        retry=true;
                    } else if (wordBiggerThenLine) { // we've entered this loop because we're greater then the wordwrap so we need to force a wordwrap
                        Cursor.X=0;
                        Cursor.Y+=char_height;
                    }
                }
            } while(ch && retry);
            if (!ch) break;
            // Did the text extend past the edge of the texture?
            if (TextureOffset.I+char_spacing>=CurrTextureSize) {
                if (!justCalcExtents) Record_Sentence_Chunk();
                Cursor.X+=TextureOffset.I-TextureStartX;
                maxX=max(maxX,Cursor.X);
                TextureStartX=2;
                TextureOffset.I=TextureStartX;
                TextureOffset.J+=char_height;
                // Did the text extent completely off the texture?
                if (TextureOffset.J+char_height>=CurrTextureSize) {
                    if (locked) {
                        reinterpret_cast<Member0C00739C70 *>(&CurSurface)->clear();
                        locked=0;
                    }
                    Allocate_New_Surface(text,justCalcExtents);
                    if (!justCalcExtents) {
                        locked=(unsigned short *)reinterpret_cast<Rva00116680 *>(&CurSurface)->rva00116680(&stride,false);
                        if (!locked) return Vector2(0,0);
                    }
                }
            }
            // Blit the character to the surface
            if (!justCalcExtents && !dontBlit) font->Blit_Char(ch,locked,stride,TextureOffset.I,TextureOffset.J);
            TextureOffset.I+=char_spacing;
        }
        if (locked) reinterpret_cast<Member0C00739C70 *>(&CurSurface)->clear();
        extent.X=maxX+font->Get_Extra_Overlap();
        extent.Y=Cursor.Y+font->Get_Char_Height();
        if (!justCalcExtents && Centered) {
            const int count=sentence_data.Count();
            if (count>0) {
                int start=0;
                float top=sentence_data[0].screen_top;
                float left=sentence_data[0].screen_left;
                float right=sentence_data[0].screen_right;
                for (int i=1;;++i) {
                    if (i>=count || sentence_data[i].screen_top!=top) {
                        float width=font->Get_Extra_Overlap()*0.5f+right-left;
                        float shift=(float)floor((double)((extent.X-width)*0.5f-left+0.5f));
                        for (int j=start;j<i;++j) {
                            sentence_data[j].screen_left+=shift;
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
    }
    Cursor=cursor;
    TextureOffset=textureOffset;
    TextureStartX=textureStartX;
    if (hkX) {*hkX=hotKeyPosX;*hkY=hotKeyPosY;}
    return extent;
}
