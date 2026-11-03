/* Target facts: constructor RVA 0x00111850 clears pointer +0x2AB4, initializes the reference count at +4 to 1 and installs vtable VA 0x00BCFAC0 at +0. Destructor 0x0011172A restores that table at 0x0011173C, releases pointer +0x2AB4 through its count at +4 and virtual slot 0, then restores RefCountClass's table VA 0x00BC650C at 0x00111761. The differing tables belong to derived destruction and base teardown. RefCountClass's constructor/destructor 0x00072882/0x00072892 establish its eight-byte prefix. TileData is polymorphic: its table has inherited Delete_This (RVA 0x0006CE57) and the public deleting destructor (0x00111867, calling 0x0011172A). LookupTablePostEffect's constructor 0x00111B84 stores the next table VA 0x00BCFAC8, bounding TileData to two slots. There is no secondary vptr or vbptr.
 * Target facts: allocations at RVAs 0x000ABFA9, 0x000ABFE5 and 0x000AC77C request 0x2AC0 bytes before constructor calls at 0x000ABFC0, 0x000AC000 and 0x000AC793. Getter 0x000ABC71 and mip builders 0x00111883/0x00111A05 establish buffer offsets +8, +0x2008, +0x2808, +0x2A08, +0x2A88, +0x2AA8 and +0x2AB0. Downsampler 0x001117E3 reads and writes words, proving two bytes per pixel and a final two-byte mip followed by alignment before +0x2AB4. Setter 0x0011178B retains the incoming TileData and releases the old pointer at +0x2AB4. WorldHeightMap::getUVForNdx reads signed coordinate dwords at +0x2AB8/+0x2ABC at 0x000AC331/0x000AC337, completing the 0x2AC0 extent.
 * Names: GeneralsMD's TileData.h proves RefCountClass inheritance, the seven buffer names, m_tileLocationInTexture (ICoord2D), getRGBDataForWidth, hasRGBDataForWidth and updateMips. Retail ledger rows at 0x00111850, 0x0011172A, 0x000ABC71, 0x001117B4, 0x00111883, 0x0011178B and 0x00111A05 prove the out-of-line declarations below; m_2AB4 retains a neutral name. The donor's four-byte pixels do not describe BFME2's word pixels. */

#ifndef BFME2_TILEDATACLASS_H
#define BFME2_TILEDATACLASS_H

#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"

class TileData : public RefCountClass
{
public:
    TileData();
    virtual ~TileData();

    unsigned char *getRGBDataForWidth(int width);
    bool hasRGBDataForWidth(int width);
    void updateMips();
    void rva0011178B(TileData *value);
    void rva00111A05(const unsigned char *source, int stride);

    unsigned char m_tileData[0x2000];
    unsigned char m_tileDataMip32[0x800];
    unsigned char m_tileDataMip16[0x200];
    unsigned char m_tileDataMip8[0x80];
    unsigned char m_tileDataMip4[0x20];
    unsigned char m_tileDataMip2[0x8];
    unsigned char m_tileDataMip1[0x2];
    RefCountClass *m_2AB4;
    ICoord2D m_tileLocationInTexture;
};

typedef char TileDataSizeIs0x2AC0[(sizeof(TileData) == 0x2AC0) ? 1 : -1];

#endif
