// Target facts: RVAs 0x00157EA8 and 0x00157C91 store VA 0x00BD3C80 at +0; its sole slot is Reset (RVA 0x00155A20), followed by the separately installed table at VA 0x00BD3C84. The destructor at RVA 0x00157C70 is nonvirtual; there are no base constructor calls. Member-vector tables at +4/+0x1C/+0x34 are VA 0x00BD3C18/68/30 in the constructor and VA 0x00BD3BB0/0x00BD3C48/0x00BD3BC8 during destruction, so those differences describe member teardown, not a second sentence table.
// Target facts: RVA 0x00157E80 initializes through +0xC0; RVA 0x00106088 constructs adjacent sentences at +0x14/+0xD8 then writes +0x19C, proving sizeof 0xC4. Constructor stores prove Font +0x4C; float pairs +0x50/58/60; integer pair +0x68; integers +0x70/74/78; surface holder +0x7C; flags +0x80/88/AC/AD/AE; WrapWidth +0x84; rectangles +0x8C/9C; texture holder +0xB0; floats +0xB4/B8 (1.0) and +0xBC/C0 (0.0). Set_Location 0x00154EF0 copies two words to +0x58/5C; Set_Wrapping_Width 0x00105D3B, Set_Word_Wrap_Centered 0x00105D63 and Set_Clipping_Rect 0x00105D96 prove the corresponding accesses. Destructor array strides are 0x24/1C/8; PendingSurfaceStruct constructor/assignment/destructor are 0x00156A10/0x001568E0/0x0000290D. SentenceDataStruct assignment is rowed at 0x0053FFCE and RendererDataStruct destruction at 0x00001E13. Unidentified storage retains neutral names; vector instantiation identities are not asserted.
// Target facts: rowed out-of-line methods are constructor/destructor 0x00157E80/0x00157C70, Set_Font 0x001542D0, Set_Location 0x00154EF0, Reset_Polys 0x00154EC0, Reset_Sentence_Data 0x00154F10, Release_Pending_Surfaces 0x00154F70, Reset 0x00155A20, Draw_Sentence 0x00104D97/0x00155B00, rva00156540 0x00156540, Record_Sentence_Chunk 0x00156390, Allocate_New_Surface 0x00158C60, Rva00158990 0x00158990, Rva00158E90 0x00158E90, Build_Sentence_Not_Centered 0x00159700 and text extents 0x00158BA0/0x00159FF0. Names for the established members and unrowed inline accessors follow GeneralsMD WW3D2/render2dsentence.h; Vector2 and RectClass are forward declarations, and the internal float pairs and rectangle storage assert no donor type identity.

#ifndef BFME2_RENDER2DSENTENCECLASS_H
#define BFME2_RENDER2DSENTENCECLASS_H

class FontCharsClass;
class Render2DClass;
class SurfaceClass;
class TextureClass;
class Vector2;
class RectClass;
struct Rva00156540Param;

// Target facts: RendererDataStruct's +4 is a COM-style reference. Its destructor 0x00001E13 adds 4 and reaches 0x00176CB0,
// which releases a non-null pointer through its table's slot 2 (__stdcall); the renderer vector's Resize 0x00155690
// assigns elements by add-ref of the new pointer and release of the old through slots 1 and 2.
class Rva0093E4D0SurfaceResource
{
public:
	virtual void unused00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

class Rva0093E4D0Surface
{
public:
	Rva0093E4D0Surface() : m_surface(0) {}
	~Rva0093E4D0Surface();

	Rva0093E4D0Surface &operator=(const Rva0093E4D0Surface &that)
	{
		if (that.m_surface)
			that.m_surface->addRef();
		if (m_surface)
			m_surface->release();
		m_surface = that.m_surface;
		return *this;
	}

private:
	Rva0093E4D0SurfaceResource *m_surface;
};

class Render2DSentenceClass
{
public:
    struct FloatPair
    {
        float X;
        float Y;
    };

    struct IntegerPair
    {
        int X;
        int Y;
    };

    struct RectangleStorage
    {
        float Left;
        float Top;
        float Right;
        float Bottom;
    };

    struct SentenceDataStruct
    {
        SentenceDataStruct &operator=(const SentenceDataStruct &);
        SurfaceClass *Surface;
        RectangleStorage ScreenRect;
        RectangleStorage UVRect;
    };

    struct PendingSurfaceStruct
    {
        PendingSurfaceStruct();
        ~PendingSurfaceStruct();
        PendingSurfaceStruct &operator=(const PendingSurfaceStruct &);
        SurfaceClass *Surface;
        unsigned char field04[0x18];
    };

    // Target facts: Resize 0x00155690 constructs its elements through ??_L with 0x00554300 (pushed at 0x00155701), which
    // clears +4 only, and copies them by +0 and the reference at +4; the destructor is out of line at 0x00001E13.
    struct RendererDataStruct
    {
        RendererDataStruct() {}
        ~RendererDataStruct();

        RendererDataStruct &operator=(const RendererDataStruct &that)
        {
            Renderer = that.Renderer;
            Surface = that.Surface;
            return *this;
        }

        Render2DClass *Renderer;
        Rva0093E4D0Surface Surface;
    };

    Render2DSentenceClass();
    ~Render2DSentenceClass();
    virtual void Reset();
    void Reset_Polys();
    void Set_Font(FontCharsClass *font);
    void Set_Location(const Vector2 &location);
    bool Set_Wrapping_Width(float width);
    bool Set_Word_Wrap_Centered(bool centered);
    void Set_Clipping_Rect(const RectClass &rect);
    Vector2 Get_Text_Extents(const unsigned short *text);
    Vector2 Get_Formatted_Text_Extents(const unsigned short *text);
    void Draw_Sentence(unsigned long color = 0xFFFFFFFF);
    void Draw_Sentence(unsigned long color0, unsigned long color1, unsigned long color2, unsigned long color3);
    void rva00156540(const Rva00156540Param *param);

    FontCharsClass *Peek_Font() { return Font; }
    void Set_Hot_Key_Parse(bool value) { ParseHotKey = value; }
    void Set_Use_Hard_Word_Wrap(bool value) { useHardWordWrap = value; }
    bool Is_Clipping_Enabled() const { return IsClippedEnabled; }
    void Enable_Clipping(bool value) { IsClippedEnabled = value; }
    void Set_Texture_Size_Hint(int hint) { TextureSizeHint = hint; }
    int Get_Texture_Size_Hint() const { return TextureSizeHint; }
    void Set_Mono_Spaced(bool value) { MonoSpaced = value; }

private:
    friend class Gen_00942BC0;
    void Reset_Sentence_Data();
    void Release_Pending_Surfaces();
    void Record_Sentence_Chunk();
    void Allocate_New_Surface(const unsigned short *text, bool justCalcExtents = false);
    void Rva00158990(FontCharsClass *font, const unsigned short *text, const unsigned short *glyphs, bool justCalcExtents);
    Vector2 Rva00158E90(const unsigned short *text, int *hkX, int *hkY, bool justCalcExtents);
    Vector2 Build_Sentence_Not_Centered(const unsigned short *text, int *hkX, int *hkY, bool justCalcExtents = false);

    unsigned char field04[0x18];
    unsigned char field1C[0x18];
    unsigned char field34[0x18];
    FontCharsClass *Font;
    FloatPair BaseLocation;
    FloatPair Location;
    FloatPair Cursor;
    IntegerPair TextureOffset;
    int TextureStartX;
    int CurrTextureSize;
    int TextureSizeHint;
    SurfaceClass *CurSurface;
    bool MonoSpaced;
    float WrapWidth;
    bool Centered;
    RectangleStorage ClipRect;
    RectangleStorage DrawExtents;
    bool IsClippedEnabled;
    bool ParseHotKey;
    bool useHardWordWrap;
    TextureClass *fieldB0;
    FloatPair fieldB4;
    float fieldBC;
    float fieldC0;
};

typedef char Render2DSentenceClassSize[(sizeof(Render2DSentenceClass) == 0xC4) ? 1 : -1];
typedef char Render2DSentenceRendererDataSize[(sizeof(Render2DSentenceClass::RendererDataStruct) == 8) ? 1 : -1];

#endif
