// ?parseBlendTileData@WorldHeightMap@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
// partial score=0.8 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /DNDEBUG /DWIN32 /D_WINDOWS
// BFME2 retail B1173..B1973; WB76E660 names WorldHeightMap::parseBlendTileData.
// Semantic guide: ZH WorldHeightMap.cpp ParseBlendTileData. Native adds
// byte vectors, wider indexes, dynamic blend/cliff tables and versions12..17.
// Field extents follow the native reader and existing texture/vector providers.
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ascii_string.h"
enum ErrorCode { ERROR_CORRUPT_FILE_FORMAT=0xDEAD0005 };
void *__cdecl operator new[](unsigned int);
class DataChunkInput { public: int readInt(); unsigned char readByte(); float readReal(); AsciiString readAsciiString(); void readArrayOfBytes(char *,int); };
struct DataChunkInfo { AsciiString label,parent; unsigned short version; };
class GlobalData { public: char opaque[0x44]; int use3WayTerrainBlends; };
extern GlobalData *TheWritableGlobalData;
class Rva000B0565 { public: unsigned char *first,*last,*limit; void rva000B0565(unsigned,unsigned); };
class Rva000AFAFB { public: short *first,*last,*limit; Rva000AFAFB(unsigned); ~Rva000AFAFB() { if(first)free(first); } };
void rva000AF1C2(int,int,int);
class BfmeGridWM { public: void walk(); };
struct BlendTileRecord { int blendIndex; unsigned char horiz,vert,rightDiagonal,leftDiagonal,inverted,longDiagonal; unsigned short pad; int customBlendEdgeClass; };
class BfmeE16Vector { public: BlendTileRecord *first,*last,*limit; void resize(unsigned); unsigned size() const { return last-first; } BlendTileRecord &operator[](unsigned i) { return first[i]; } };
struct BfmePod36 { float f[8]; unsigned char b0,b1; unsigned short w; };
class BfmePod36Vector { public: BfmePod36 *first,*last,*limit; void resize(unsigned); unsigned size() const { return last-first; } BfmePod36 &operator[](unsigned i) { return first[i]; } };
struct TXTextureClass { int globalTextureClass,firstTile,numTiles,width,isBlendEdgeTile; AsciiString name; char unknown18[16]; };
class TileData;
class WorldHeightMap {
    char opaque00[8]; int m_width,m_height; char opaque10[16]; int m_dataSize; char opaque24[4];
    Rva000B0565 m_cellFlipState; int m_flipStateWidth; Rva000B0565 m_cellCliffState;
    Rva000B0565 m_byte44,m_byte50,m_byte5C,m_byte68,m_byte74,m_byte80,m_byte8C;
    short *m_tileNdxes; int *m_blendTileNdxes,*m_cliffInfoNdxes,*m_extraBlendTileNdxes;
    int m_numBitmapTiles,m_numEdgeTiles; TileData *m_sourceTiles[4096],*m_edgeTiles[4096];
    BfmeE16Vector m_blendedTiles; BfmePod36Vector m_cliffInfo;
    int m_numTextureClasses; TXTextureClass m_textureClasses[512];
    int m_numEdgeTextureClasses; TXTextureClass m_edgeTextureClasses[512];
public: bool parseBlendTileData(DataChunkInput &,DataChunkInfo *);
protected: void readTexClass(TXTextureClass *,TileData **);
};
bool WorldHeightMap::parseBlendTileData(DataChunkInput &file,DataChunkInfo *info)
{
    int i,j;
    int len=file.readInt();
    if(m_dataSize!=len)throw ERROR_CORRUPT_FILE_FORMAT;
    m_tileNdxes=(short*)operator new[](m_dataSize*2);
    m_cliffInfoNdxes=(int*)operator new[](m_dataSize*4);
    m_blendTileNdxes=(int*)operator new[](m_dataSize*4);
    m_extraBlendTileNdxes=(int*)operator new[](m_dataSize*4);
    int numBytesX=(m_width+7)/8;
    int numBytesY=m_height;
    m_flipStateWidth=numBytesX;
    m_cellFlipState.rva000B0565(numBytesX*numBytesY,0);
    m_cellCliffState.rva000B0565(numBytesX*numBytesY,0);
    m_byte5C.rva000B0565(numBytesX*numBytesY,0);
    m_byte68.rva000B0565(numBytesX*numBytesY,0);
    m_byte74.rva000B0565(numBytesX*numBytesY,0);
    m_byte80.rva000B0565(numBytesX*numBytesY,0);
    m_byte8C.rva000B0565(m_width*m_height,0);
    m_byte44.rva000B0565(numBytesX*numBytesY,0);
    m_byte50.rva000B0565(numBytesX*numBytesY,255);
    file.readArrayOfBytes((char*)m_tileNdxes,m_dataSize*2);
    if(info->version>=12) {
        file.readArrayOfBytes((char*)m_blendTileNdxes,m_dataSize*4);
        file.readArrayOfBytes((char*)m_extraBlendTileNdxes,m_dataSize*4);
    } else {
        Rva000AFAFB temporary(m_dataSize);
        file.readArrayOfBytes((char*)temporary.first,m_dataSize*2);
        rva000AF1C2((int)temporary.first,(int)temporary.last,(int)m_blendTileNdxes);
        if(info->version>=6) {
            file.readArrayOfBytes((char*)temporary.first,m_dataSize*2);
            rva000AF1C2((int)temporary.first,(int)temporary.last,(int)m_extraBlendTileNdxes);
        }
    }
    if(!TheWritableGlobalData->use3WayTerrainBlends)
        memset(m_extraBlendTileNdxes,0,m_dataSize*4);
    if(info->version>=14)
        file.readArrayOfBytes((char*)m_cliffInfoNdxes,m_dataSize*4);
    else if(info->version>=5) {
        Rva000AFAFB temporary(m_dataSize);
        file.readArrayOfBytes((char*)temporary.first,m_dataSize*2);
        rva000AF1C2((int)temporary.first,(int)temporary.last,(int)m_cliffInfoNdxes);
    }
    if(info->version>=7) {
        if(info->version==7) {
            int byteWidth=(m_width+1)/8;
            file.readArrayOfBytes((char*)m_cellCliffState.first,m_height*byteWidth);
        } else file.readArrayOfBytes((char*)m_cellCliffState.first,m_height*m_flipStateWidth);
    }
    if(info->version<9)((BfmeGridWM*)this)->walk();
    if(info->version>=11)file.readArrayOfBytes((char*)m_byte68.first,m_height*m_flipStateWidth);
    if(info->version>=10)file.readArrayOfBytes((char*)m_byte5C.first,m_height*m_flipStateWidth);
    if(info->version>=13)file.readArrayOfBytes((char*)m_byte74.first,m_height*m_flipStateWidth);
    if(info->version>=15)file.readArrayOfBytes((char*)m_byte80.first,m_height*m_flipStateWidth);
    if(info->version>=16)file.readArrayOfBytes((char*)m_byte8C.first,m_height*m_width);
    if(info->version>=17)file.readArrayOfBytes((char*)m_byte50.first,m_height*m_flipStateWidth);
    m_numBitmapTiles=file.readInt();
    int numBlendedTiles=file.readInt();
    int numCliffInfo=1;
    if(info->version>=5)numCliffInfo=file.readInt();
    m_numTextureClasses=file.readInt();
    for(i=0;i<m_numTextureClasses;++i) {
        m_textureClasses[i].globalTextureClass=-1;
        m_textureClasses[i].firstTile=file.readInt();
        m_textureClasses[i].numTiles=file.readInt();
        m_textureClasses[i].width=file.readInt();
        file.readInt();
        m_textureClasses[i].name=file.readAsciiString();
        readTexClass(&m_textureClasses[i],m_sourceTiles);
    }
    m_numEdgeTextureClasses=0;
    m_numEdgeTiles=0;
    Sleep(0);
    if(info->version>=4) {
        m_numEdgeTiles=file.readInt();
        m_numEdgeTextureClasses=file.readInt();
        for(i=0;i<m_numEdgeTextureClasses;++i) {
            m_edgeTextureClasses[i].globalTextureClass=-1;
            m_edgeTextureClasses[i].firstTile=file.readInt();
            m_edgeTextureClasses[i].numTiles=file.readInt();
            m_edgeTextureClasses[i].width=file.readInt();
            m_edgeTextureClasses[i].name=file.readAsciiString();
            readTexClass(&m_edgeTextureClasses[i],m_edgeTiles);
        }
    }
    m_blendedTiles.resize(numBlendedTiles);
    for(unsigned k=1;k<m_blendedTiles.size();++k) {
        m_blendedTiles[k].blendIndex=file.readInt();
        m_blendedTiles[k].horiz=file.readByte();
        m_blendedTiles[k].vert=file.readByte();
        m_blendedTiles[k].rightDiagonal=file.readByte();
        m_blendedTiles[k].leftDiagonal=file.readByte();
        m_blendedTiles[k].inverted=file.readByte();
        if(!TheWritableGlobalData->use3WayTerrainBlends)m_blendedTiles[k].inverted &= ~2;
        if(info->version>=3)m_blendedTiles[k].longDiagonal=file.readByte();
        else m_blendedTiles[k].longDiagonal=0;
        if(info->version>=4)m_blendedTiles[k].customBlendEdgeClass=file.readInt();
        else m_blendedTiles[k].customBlendEdgeClass=-1;
        if(file.readInt()!=0x7ADA0000)throw ERROR_CORRUPT_FILE_FORMAT;
    }
    m_cliffInfo.resize(numCliffInfo);
    if(info->version>=5) {
        for(unsigned k=1;k<m_cliffInfo.size();++k) {
            m_cliffInfo[k].w=(unsigned short)file.readInt();
            m_cliffInfo[k].f[0]=file.readReal();
            m_cliffInfo[k].f[1]=file.readReal();
            m_cliffInfo[k].f[2]=file.readReal();
            m_cliffInfo[k].f[3]=file.readReal();
            m_cliffInfo[k].f[4]=file.readReal();
            m_cliffInfo[k].f[5]=file.readReal();
            m_cliffInfo[k].f[6]=file.readReal();
            m_cliffInfo[k].f[7]=file.readReal();
            m_cliffInfo[k].b0=file.readByte()!=0;
            m_cliffInfo[k].b1=file.readByte()!=0;
        }
    }
    if(info->version==1) {
        int newWidth=(m_width+1)/2,newHeight=(m_height+1)/2;
        for(i=0;i<newHeight;++i) {
            for(j=0;j<newWidth;++j) {
                m_tileNdxes[i*newWidth+j]=m_tileNdxes[2*i*m_width+2*j];
                m_blendTileNdxes[i*newWidth+j]=0;
                m_extraBlendTileNdxes[i*newWidth+j]=0;
                m_cliffInfoNdxes[i*newWidth+j]=0;
            }
        }
        m_blendedTiles.resize(1);
        m_cliffInfo.resize(1);
        m_width=newWidth;
        m_height=newHeight;
        m_dataSize=m_width*m_height;
    }
    return true;
}
