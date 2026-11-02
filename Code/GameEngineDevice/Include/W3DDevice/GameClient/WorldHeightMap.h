/* Target facts: retail RVAs 0x000B098A, 0x000B0ACD and 0x000B0C38 initialize RefCountClass's count at +4 and store WorldHeightMap's primary vtable VA 0x00BC967C at +0; 0x000B0028 restores that table before destroying members and restores the base table VA 0x00BC650C at 0x000B0227. The tables differ because the latter belongs to RefCountClass teardown. RefCountClass's 0x00072882/0x00072892 establish its eight-byte prefix and its two virtual slots. WorldHeightMap is polymorphic and has no secondary base or vbptr. WorldHeightMap's table contains Delete_This (RVA 0x0006CE57), the deleting destructor (0x000B0238, calling 0x000B0028), and parseBlendTileData (0x000B1173). The BlendTileData binding constructed at 0x000AEFAA stores table VA 0x00BC95D8; its callback 0x000AF012 loads its WorldHeightMap owner at +0x0C and jumps through the owner's slot 2 (+8), proving the third entry is virtual. The next table word, 0x41800000, is not code.
 * Target facts: the allocation at 0x00092193 pushes 0x120F0, calls operator new at 0x00092198 and calls the stream constructor at 0x000921AB. Reset 0x000B08F7 and ParseHeightMapData 0x000B0DA8 establish width +8, height +0x0C, border +0x10, the twelve-byte boundary vector +0x14, count +0x20 and 16-bit height data pointer +0x24; clamped lookup 0x0006653B reads a word at data[(y * width + x) * 2]. Constructors call vector-base 0x00211E58 at +0x14, +0x28, +0x38, +0x44, +0x50, +0x5C, +0x68, +0x74, +0x80, +0x8C, +0x80B0 and +0x80BC; construct 512 records of stride 0x28 at +0x80CC and +0xD0D0 with 0x000AF215/0x004D9A3C; clear a texture reference at +0x120D0 and construct two four-byte references at +0x120D8. Unknown aggregate storage retains neutral names. Reader 0x000B1173 proves the bit-plane stride +0x34, signed-short tile indices +0x98, 32-bit blend/cliff/extra indices +0x9C/+0xA0/+0xA4, tile counts +0xA8/+0xAC, 4096-pointer arrays +0xB0/+0x40B0, and texture-class counts +0x80C8/+0xD0CC. SetDrawOrg 0x000AC40D and reset prove origins +0x120E0/+0x120E4 and draw extents +0x120E8/+0x120EC. Ledger bodies 0x000AC2F6, 0x000AC40D, 0x000AC4C6, 0x000AC514, 0x000AC6A6, 0x000ABD9A, 0x000ABE0A, 0x000ABEA0, 0x000ADC93, 0x000AE275, 0x000AE37E, 0x000AE44B, 0x000AE989, 0x000AEAA6, 0x000AEC4E, 0x000AF238, 0x000AF917, 0x000B0DA8, 0x000B0F82 and 0x000B1173 establish the out-of-line declarations; pins at 0x000AE13E/0x000AE1DC establish the const bit queries. No inline definition replaces a rowed body.
 * Target fact: the rowed free function Rva000AC6F9SetupAlphaTiles (0x000AC6F9) initializes the twelve shared m_alphaTiles pointers at VA 0x00DEA1C8. Donor facts: GeneralsMD's WorldHeightMap.h supplies the dimension, border, data, index, tile-count, texture-count and draw-field names and the simple accessor names. BFME2's word heights, vector storage, 4096 tiles, 512 records, single RefCountClass base and three-slot table are target facts, independent of the donor's layout. */

#pragma once
#ifndef BFME2_WORLDHEIGHTMAP_H
#define BFME2_WORLDHEIGHTMAP_H

#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"

class AsciiString;
class ChunkInputStream;
class DataChunkInput;
struct DataChunkInfo;
class InputStream;
class TileData;
class TextureClass;
struct TXTextureClass;
struct TBlendTileInfo;
struct RGBColor;
template <class T> class RefCountPtr;

class WorldHeightMap : public RefCountClass
{
    friend void Rva000AC6F9SetupAlphaTiles();

public:
    WorldHeightMap();
    WorldHeightMap(ChunkInputStream *stream);
    WorldHeightMap(ChunkInputStream *stream, int a, int b, int c);
    virtual ~WorldHeightMap();
    virtual bool parseBlendTileData(DataChunkInput &file, DataChunkInfo *info);

    int getXExtent() { return m_width; }
    int getYExtent() { return m_height; }
    int getXExtent() const { return m_width; }
    int getYExtent() const { return m_height; }
    int getBorderSize() { return m_borderSize; }
    int getBorderSize() const { return m_borderSize; }
    int getBorderSizeInline() const { return m_borderSize; }
    unsigned short *getDataPtr() { return m_data; }
    unsigned short *getDataPtr() const { return m_data; }
    int getDrawOrgX() { return m_drawOriginX; }
    int getDrawOrgY() { return m_drawOriginY; }
    int getDrawWidth() { return m_drawWidthX; }
    int getDrawHeight() { return m_drawHeightY; }
    int getDrawWidth() const { return m_drawWidthX; }
    int getDrawHeight() const { return m_drawHeightY; }

    void getUVForNdx(int index, float *minU, float *minV, float *maxU, float *maxV, bool fullTile);
    bool setDrawOrg(int x, int y);
    int rva000AC4C6(int value);
    void getTerrainColorAt(float x, float y, RGBColor *color);
    unsigned char *getRGBAlphaDataForWidth(int width, TBlendTileInfo *blend);
    static bool ParseWorldDictDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
    static int countTiles(InputStream *stream, bool *halfTile);
    static bool readTiles(InputStream *stream, InputStream *normalStream, TileData **tiles, int rows);
    int rva000ADC93(int x, int y, bool force);
    static bool ParseEnvironmentDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
    bool rva000AE37E(int x, int y);
    void rva000AE44B(int x, int y, void *info);
    RefCountPtr<TextureClass> getFlatTexture(int x, int y, int width, int pixelsPerCell, int format, int tileKind);
    RefCountPtr<TextureClass> rva000AEAA6(int x, int y, int width, int selector);
    AsciiString getTerrainNameAt(float x, float y);
    void parse(DataChunkInput &file, void *polygonOwner, void *owner10, void *owner14);
    bool ParseHeightMapData(DataChunkInput &file, DataChunkInfo *info);
    bool ParseSizeOnly(DataChunkInput &file, DataChunkInfo *info);
    bool getCliffState(int x, int y) const;
    bool rva000AE1DC(int x, int y) const;

protected:
    void readTexClass(TXTextureClass *textureClass, TileData **tiles);
    static TileData *m_alphaTiles[12];

public:
    int m_width;
    int m_height;
    int m_borderSize;
    unsigned char m_field14[12];
    int m_dataSize;
    unsigned short *m_data;
    unsigned char m_field28[12];
    int m_flipStateWidth;
    unsigned char m_field38[12];
    unsigned char m_field44[12];
    unsigned char m_field50[12];
    unsigned char m_field5C[12];
    unsigned char m_field68[12];
    unsigned char m_field74[12];
    unsigned char m_field80[12];
    unsigned char m_field8C[12];
    short *m_tileNdxes;
    int *m_blendTileNdxes;
    int *m_cliffInfoNdxes;
    int *m_extraBlendTileNdxes;
    int m_numBitmapTiles;
    int m_numEdgeTiles;
    TileData *m_sourceTiles[4096];
    TileData *m_edgeTiles[4096];
    unsigned char m_field80B0[12];
    unsigned char m_field80BC[12];
    int m_numTextureClasses;
    unsigned char m_field80CC[512 * 0x28];
    int m_numEdgeTextureClasses;
    unsigned char m_fieldD0D0[512 * 0x28];
    TextureClass *m_field120D0;
    int m_terrainTexHeight;
    TextureClass *m_field120D8[2];
    int m_drawOriginX;
    int m_drawOriginY;
    int m_drawWidthX;
    int m_drawHeightY;
};

#endif
