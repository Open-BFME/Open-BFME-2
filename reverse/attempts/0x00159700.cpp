// ?Build_Sentence_Not_Centered@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z
// partial score=0.66 date=2026-10-09
// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

void __cdecl operator delete[](void *) throw();
#include "vector.h"
#include "vector2i.h"
#include "vector2.h"
extern "C" __declspec(dllimport) double __cdecl floor(double);
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock { public: BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();} ~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();} };
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

// ZH Build_Sentence_Not_Centered semantics adapted to target2230-byte body.
// Native159700..159FB6: device mutex guard, Thai dispatch, local lock data,
// separator95, retry after break skipping, and post-render line centering.
// Font/sentence layout is supported by newly verified allocator/record siblings.
// Rva00158E90's original method name remains unknown; callsite proves Vector2
// hidden return plus text/hotkey pointers/calc, and its full native helper is read.
// ?Build_Sentence_Not_Centered@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z present-unmatched
Vector2 Render2DSentenceClass::Build_Sentence_Not_Centered(const unsigned short *text,int *hkX,int *hkY,bool justCalcExtents) {
    Vector2 cursor=Cursor;
    int textureStartX=TextureStartX;
    float maxX=0;
    int hotKeyPosX=0,hotKeyPosY=0;
    bool calcHotKeyX=false;
    Vector2i textureOffset=TextureOffset;
    BFMEDX8DeviceLock device_lock;
    if (!justCalcExtents) Reset_Sentence_Data();
    Cursor.Set(0,0);
    bool thai=false;
    for (const unsigned short *scan=text;*scan;++scan) {
        unsigned short ch=*scan;
        if ((ch>=0xE01 && ch<=0xE3A)||(ch>=0xE3F && ch<=0xE5B)) {thai=true;break;}
    }
    Vector2 extent;
    if (thai) {
        extent=Rva00158E90(text,hkX,hkY,justCalcExtents);
    } else {
        if (!CurSurface.m_surface) Allocate_New_Surface(text,justCalcExtents);
        TextureOffset.Set(2,0);
        TextureStartX=2;
        float char_height=font->Get_Char_Height();
        unsigned short *locked=0;
        int stride=0;
        if (!justCalcExtents) {
            locked=(unsigned short *)reinterpret_cast<Rva00116680 *>(&CurSurface)->rva00116680(&stride,false);
            if (!locked) return Vector2(0,0);
        }
        while(text) {
            unsigned short ch=NextSentenceChar(text);
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
                    ch=NextSentenceChar(text);
                    dontBlit=true;
                }
                char_spacing=(float)font->Get_Char_Spacing(ch);
                bool encountered_break_char=(ch==' ' || ch=='\n' || ch==0x95 || ch==0);
                bool wordBiggerThenLine=useHardWordWrap && WrapWidth!=0 && (Cursor.X+TextureOffset.I-TextureStartX+char_spacing)>=WrapWidth;
                if (encountered_break_char || wordBiggerThenLine) {
                    if (!justCalcExtents) Record_Sentence_Chunk();
                    Cursor.X += TextureOffset.I-TextureStartX;
                    maxX=max(maxX,Cursor.X);
                    TextureStartX=TextureOffset.I;
                    if (ch==' ' || ch==0x95) {
                        if (WrapWidth>0) {
                            const unsigned short *word=text;
                            float word_width=char_spacing;
                            while (*word!=0 && *word>' ' && *word!=0x95) {
                                if (ParseHotKey && *word=='&') ++word;
                                word_width+=font->Get_Char_Spacing(NextSentenceChar(word));
                            }
                            if (Cursor.X+word_width>=WrapWidth) {
                                Cursor.X=0;
                                Cursor.Y+=char_height;
                                calcHotKeyX=true;
                                do {ch=NextSentenceChar(text);} while(ch==' ' || ch==0x95);
                                retry=true;
                            }
                        }
                        if (ch==0x95) {
                            do {ch=NextSentenceChar(text);} while(ch==0x95);
                            retry=true;
                        }
                    } else if (ch=='\n') {
                        Cursor.X=0;
                        Cursor.Y+=char_height;
                        do {ch=NextSentenceChar(text);} while(ch==' ');
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
                if (!justCalcExtents) Record_Sentence_Chunk();
                Cursor.X+=TextureOffset.I-TextureStartX;
                maxX=max(maxX,Cursor.X);
                TextureStartX=2;
                TextureOffset.I=TextureStartX;
                TextureOffset.J+=char_height;
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
            if (!justCalcExtents && !dontBlit) font->Blit_Char(ch,locked,stride,TextureOffset.I,TextureOffset.J);
            TextureOffset.I+=char_spacing;
        }
        if (locked) reinterpret_cast<Member0C00739C70 *>(&CurSurface)->clear();
        extent.X=maxX+font->Get_Extra_Overlap();
        extent.Y=Cursor.Y+font->Get_Char_Height();
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
                float shift=(float)floor((extent.X-(font->Get_Extra_Overlap()*0.5+right-left))*0.5-left+0.5);
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
    }
    Cursor=cursor;
    TextureOffset=textureOffset;
    TextureStartX=textureStartX;
    if (hkX) {*hkX=hotKeyPosX;*hkY=hotKeyPosY;}
    return extent;
}
