// Target facts: constructor RVA 0x00157950 stores the primary vptr VA 0x00BD3C60 at RVA 0x00157978; destructor RVA 0x00157390 restores it at 0x001573AF and restores RefCountClass VA 0x00BC650C at 0x001574D8. The next vector table begins at VA 0x00BD3C68, bounding the primary table to two slots: Delete_This (RVA 0x0006CE57) and the deleting destructor (RVA 0x00157AB0, which calls 0x00157390). The registered RefCountClass supplies these two slots and int NumRefs at +4; this class overrides only the destructor. The separate vector at +0x10 receives VA 0x00BD3BE8 at 0x001579AD and its base table VA 0x00BD3B98 at 0x001574A3 during teardown; neither is the FontCharsClass primary table.
// Target facts: allocation RVA 0x000901BD pushes 0x464 before operator new at 0x000901C2 and the constructor call at 0x000901D5. The constructor writes AlternateUnicodeFont +8, constructs StringClass at +0x0C and +0x44 through Get_String RVA 0x00610B00, initializes vector storage +0x10..+0x27, ints +0x28..+0x38, float +0x3C, int +0x40, font handle +0x48, UnicodeCharArray +0x44C, tree +0x450..+0x45B, words +0x45C/+0x45E and bool +0x460, and clears 256 pointers starting at +0x4C. Create_GDI_Font RVA 0x00154630 proves CharHeight +0x2C, CharAscent +0x30, CharOverhang +0x34, PixelOverlap +0x38 and GDIFont +0x48; Initialize_GDI_Font RVA 0x001551C0 and Is_Font RVA 0x00154840 prove PointSize +0x3C, field40 +0x40, GDIFontName +0x44 and IsBold +0x460. Get_Char_Data RVA 0x00158520 reads the tree at +0x450; Free_Character_Arrays RVA 0x00154890 and ensureCharPage RVA 0x00155220 prove the pointer tables and Unicode bounds. Unresolved aggregate types retain opaque storage.
// Names: Zero Hour WW3D2/render2dsentence.h proves the shared field names and Get_Name, Get_Char_Height and Get_Extra_Overlap. Out-of-line declarations follow the retail ledger: constructor 0x00157950, destructor 0x00157390, Initialize_GDI_Font 0x001551C0, Is_Font 0x00154840, Get_Char_Width 0x00158710, Get_Char_Metric 0x00158690, Get_Char_Spacing 0x00158760, Blit_Char 0x001587C0, Blit_Char_Thai 0x001588A0, loadCharacterData 0x00158580, Create_GDI_Font 0x00154630, Free_Character_Arrays 0x00154890, Get_Char_Data 0x00158520, ensureCharPage 0x00155220, loadCharBitmap 0x00156A60, Store_Thai_GDI_Glyph 0x00157FF0, Update_Current_Buffer 0x00156490, Rva00941450Body 0x001586E0 and Rva009414A0Body 0x00158730. Public storage permits verified consumers to access fields without asserting retail access control.

#ifndef BFME2_WW3D2_FONTCHARSCLASS_H
#define BFME2_WW3D2_FONTCHARSCLASS_H

#include "../WWLib/RefCountData.h"
#include "../WWLib/wwstring.h"

struct FontCharsClassCharDataStruct;

class FontCharsClass : public RefCountClass
{
public:
    FontCharsClass();
    virtual ~FontCharsClass();

    void Initialize_GDI_Font(const char *, float, bool, int);
    bool Is_Font(const char *, float, bool, int);
    const char *Get_Name() { return Name; }
    int Get_Char_Height() { return CharHeight; }
    int Get_Char_Height() const { return CharHeight; }
    int Get_Extra_Overlap() { return PixelOverlap; }
    int Get_Char_Width(unsigned short);
    int Get_Char_Metric(unsigned short);
    int Get_Char_Spacing(unsigned short);
    void Blit_Char(unsigned short, unsigned short *, int, int, int);
    void Blit_Char_Thai(unsigned short, unsigned short *, int, int, int);
    const FontCharsClassCharDataStruct *loadCharacterData(unsigned short);
    int Rva00941450Body(unsigned short);
    int Rva009414A0Body(unsigned short);

private:
    void Create_GDI_Font(const char *);
    void Free_Character_Arrays();
    const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short);
    void ensureCharPage(unsigned short);
    const FontCharsClassCharDataStruct *loadCharBitmap(unsigned short);
    const FontCharsClassCharDataStruct *Store_Thai_GDI_Glyph(unsigned short);
    void Update_Current_Buffer(int);

public:
    FontCharsClass *AlternateUnicodeFont;
    StringClass Name;
    unsigned char field10[0x18];
    int CurrPixelOffset;
    int CharHeight;
    int CharAscent;
    int CharOverhang;
    int PixelOverlap;
    float PointSize;
    int field40;
    StringClass GDIFontName;
    void *GDIFont;
    FontCharsClassCharDataStruct *ASCIICharArray[256];
    FontCharsClassCharDataStruct **UnicodeCharArray;
    unsigned char field450[0x0C];
    unsigned short FirstUnicodeChar;
    unsigned short LastUnicodeChar;
    bool IsBold;
};

#endif
