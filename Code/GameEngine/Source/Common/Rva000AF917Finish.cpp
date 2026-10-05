// ?readTexClass@WorldHeightMap@@IAEXPAUTXTextureClass@@PAPAVTileData@@@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

// BFME2 terrain texture-class loading. Retail builds this family with /O1
// (frame-pointer prologue, push/pop materialization); the ZH-port sibling TU
// (WorldHeightMap.cpp) builds /G7, so the /O1 bodies live here.
//
// Layouts are retail-owned: TerrainType carries its name at +0x04 and its
// texture name at +0x08 with the next link at +0x20 (proven by the rowed
// TerrainTypeCollection::findTerrain in TerrainTypes_findTerrain.cpp, whose
// comment records the two by-value getters copying +0x08). TXTextureClass is
// the ZH struct (globalTextureClass, firstTile, numTiles, width,
// isBlendEdgeTile, name at +0x14, positionInTexture).

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"

class TerrainType
{
	friend class TerrainTypeCollection;
public:
	AsciiString getTexture() const throw();
	AsciiString getNrmTexture() const throw();
private:
	char m_pad0[4];
	AsciiString m_name; // +0x04
	AsciiString m_texture; // +0x08
};

class TerrainTypeCollection
{
public:
	TerrainType *findTerrain(AsciiString name);
};

extern TerrainTypeCollection *TheTerrainTypes;

// ?makeNrmTextureName@@ present-unmatched
AsciiString makeNrmTextureName(const AsciiString &in);




// BFME1 semantic donor:1281192f, WorldHeightMapReadTexClass.cpp.
// Native AF917-AFA92 independently proves the additional normal stream,
// third openFile argument,16-wide search and four-argument tile reader.
#include <stdio.h>
class File {
public:
    virtual void slot0(); virtual void slot1(); virtual void close();
    virtual int read(void *,int); virtual void slot4();
    virtual void seek(int,int);
};
class FileSystem { public: File *openFile(const char *,int,int); };
extern FileSystem *TheFileSystem;
class InputStream { public: virtual int read(void *,int)=0; };
class GDIFileStream : public InputStream {
    File *m_file;
public:
    GDIFileStream(File *f):m_file(f){}
    // ?GDIFileStream::read present-unmatched
    virtual int read(void *p,int n) { return m_file->read(p,n); }
};
// Retail loads the writable GlobalData slot at VA 0x00DFE758 here,
// distinct from TheGameLogic at 0x00DFE78C. The +0x49 access is unchanged.
class GlobalData { public: char unknown00[0x49]; bool normalMaps49; };
extern GlobalData *TheWritableGlobalData;
struct TXTextureClass {
    int globalTextureClass,firstTile,numTiles,width,isBlendEdgeTile;
    AsciiString name;
};
class TileData;
class WorldHeightMap {
public:
    static int countTiles(InputStream *,bool *);
    // ?readTiles@WorldHeightMap@@SA_NPAVInputStream@@0PAPAVTileData@@H@Z present-unmatched
    static bool readTiles(InputStream *,InputStream *,TileData **,int);
protected:
    void readTexClass(TXTextureClass *,TileData **);
};
// ?WorldHeightMap::readTexClass present-unmatched
void WorldHeightMap::readTexClass(TXTextureClass *texClass,TileData **tileData)
{
    File *normalFile=0;
    TerrainType *terrain=TheTerrainTypes->findTerrain(texClass->name);
    if (!terrain) return;
    char texturePath[260];
    sprintf(texturePath,"%s%s","Art/Terrain/",terrain->getTexture().str());
    File *file=TheFileSystem->openFile(texturePath,0x41,0);
    if (TheWritableGlobalData->normalMaps49) {
        sprintf(texturePath,"%s%s","Art/Terrain/",terrain->getNrmTexture().str());
        normalFile=TheFileSystem->openFile(texturePath,0x41,0);
    }
    if (file) {
        GDIFileStream stream(file),normalStream(normalFile);
        int numTiles=WorldHeightMap::countTiles(&stream,0);
        file->seek(0,0);
        if (numTiles>=texClass->numTiles) {
            numTiles=texClass->numTiles;
            int width;
            for (width=16;width>=1;--width) {
                if(numTiles>=width*width) { numTiles=width*width;break; }
            }
            bool ok = WorldHeightMap::readTiles(&stream,normalFile?&normalStream:0,tileData+texClass->firstTile,width);
            (void)ok;
        }
        file->close();
    }
    if(normalFile)normalFile->close();
}

// Pending call pin: ?readTiles@WorldHeightMap@@SA_NPAVInputStream@@0PAPAVTileData@@H@Z ->0x000ABEA0.
// Target call-site exception model is inferred from absence of caller EHframe; getter bodies themselves retain their established exception shape.
