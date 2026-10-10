// ?readTiles@WorldHeightMap@@SA_NPAVInputStream@@0PAPAVTileData@@H@Z
// partial score=0.8450573945053876 date=2026-10-10
// ?readTiles@WorldHeightMap@@SA_NPAVInputStream@@0PAPAVTileData@@H@Z
// cl: /O1 /Oy- /MD /EHsc /DNDEBUG
// Reference reviewed at pinned BFME1 575ba2b04.
// Semantic guide: ZH WorldHeightMap::readTiles; target BFME2 adds normal
// input, block reads and direct mip resampling. Native ABEA0..AC296.
// Target facts: signed 18-byte TGA headers; normal-map switch at writable
// GlobalData +49; TileData allocation 2AC0/refcount4/companion2AB4; 64-row
// blocks; shared zero-initialized 256-byte default normal row.
// Original helper/member names remain unknown and retain rowed RVA names.
#include <string.h>
void* __cdecl operator new(unsigned int);
void* __cdecl operator new[](unsigned int);
void __cdecl operator delete[](void*);
#pragma pack(push,1)
struct TTargaHeader {
 unsigned char idLength,colorMapType,imageType;
 short colorMapOrigin,colorMapLength;
 unsigned char colorMapDepth;
 short xOrigin,yOrigin,imageWidth,imageHeight;
 unsigned char pixelDepth,imageDescriptor;
};
#pragma pack(pop)
class InputStream {public: virtual int read(void*,int)=0;};
class GlobalData {public:char prefix[0x49];bool useNormalMaps;};
extern GlobalData *TheWritableGlobalData;
class Rva00111784DwordField {public:int get() const;};
class TileData {public:
 virtual void Delete_This();
 int refs;
 unsigned char rest[0x2AC0-8];
 TileData();
 void rva0011178B(TileData*);
 void rva00111A05(const unsigned char*,int);
 __forceinline TileData*companion(){return (TileData*)((Rva00111784DwordField*)this)->get();}
 __forceinline void Release_Ref(){if(--refs==0)Delete_This();}
};
class WorldHeightMap {public:static bool readTiles(InputStream*,InputStream*,TileData**,int);};
static unsigned char defaultNormals[256];
bool WorldHeightMap::readTiles(InputStream*pStr,InputStream*nStr,TileData**tiles,int numRows)
{
 TTargaHeader hdr;
 pStr->read(&hdr,sizeof(hdr));
 int tileWidth=hdr.imageWidth/64;
 int tileHeight=hdr.imageHeight/64;
 if(hdr.imageHeight==32)tileHeight=1;
 if(hdr.imageWidth==32)tileWidth=1;
 if(tileWidth<numRows&&tileHeight<numRows)return false;
 if((hdr.imageType&8)||hdr.imageWidth>1024)return false;
 int bytesPerPixel=(hdr.pixelDepth+7)/8;
 if(bytesPerPixel<3||bytesPerPixel>4)return false;
 int nBytes=0;
 if(nStr){
  TTargaHeader nhdr;nStr->read(&nhdr,sizeof(nhdr));
  if(nhdr.imageHeight!=hdr.imageHeight||nhdr.imageWidth!=hdr.imageWidth||(nhdr.imageType&8))return false;
  nBytes=(nhdr.pixelDepth+7)/8;
  if(nBytes<3||nBytes>4)return false;
 }
 for(int i=0;i<numRows*numRows;i++){
  if(!tiles[i])tiles[i]=new TileData;
  if(TheWritableGlobalData->useNormalMaps&&!tiles[i]->companion()){
   TileData*normal=new TileData;
   tiles[i]->rva0011178B(normal);
   if(normal)normal->Release_Ref();
  }
 }
 unsigned char*buf=(unsigned char*)operator new[](hdr.imageWidth*64*4);
 unsigned char*nbuf=0;
 if(nStr)nbuf=(unsigned char*)operator new[](hdr.imageWidth*64*4);
 for(int tileRow=0;tileRow<numRows;tileRow++){
  for(int row=0;row<64;row++){
   if(tileRow*64+row<hdr.imageHeight){
    pStr->read(buf+row*hdr.imageWidth*4,hdr.imageWidth*bytesPerPixel);
    unsigned char*dst;
    if(bytesPerPixel==3){
     dst=buf+row*hdr.imageWidth*4;
     unsigned char*src=dst+hdr.imageWidth*3;dst+=hdr.imageWidth*4;
     for(int col=hdr.imageWidth;col>0;col--){
      dst-=4;src-=3;dst[3]=0;dst[2]=src[2];dst[1]=src[1];dst[0]=src[0];
     }
    }
    if(nStr){
     nStr->read(nbuf+row*hdr.imageWidth*4,hdr.imageWidth*nBytes);
     if(nBytes==3){
      dst=nbuf+row*hdr.imageWidth*4;
      unsigned char*src=dst+hdr.imageWidth*3;dst+=hdr.imageWidth*4;
      for(int col=hdr.imageWidth;col>0;col--){
       dst-=4;src-=3;dst[2]=src[2];dst[1]=src[1];dst[0]=src[0];
      }
     }
     unsigned char*dstAlpha=nbuf+row*hdr.imageWidth*4;const unsigned char*srcAlpha=buf+row*hdr.imageWidth*4+3;
     for(int col=hdr.imageWidth;col>0;col--,srcAlpha+=4,dstAlpha+=4)*dstAlpha=*srcAlpha;
    }
   }else{
    memset(buf+row*hdr.imageWidth*4,0,hdr.imageWidth*4);
    if(nStr){
     unsigned char*dst=nbuf+row*hdr.imageWidth*4;
     for(int col=0;col<hdr.imageWidth;col++,dst+=4){dst[3]=0;dst[0]=0;dst[2]=127;dst[1]=127;}
    }
   }
  }
  unsigned char*pBuf=buf; unsigned char*pNormal=nbuf;
  for(int i=0,width=64;i<numRows;i++,width+=64,pBuf+=256,pNormal+=256){
   if(width>hdr.imageWidth)break;
   tiles[i]->rva00111A05(pBuf,hdr.imageWidth*4);
   if(tiles[i]->companion()){
    const unsigned char*p;int stride;
    if(nbuf){p=pNormal;stride=hdr.imageWidth*4;}
    else{
     if(!defaultNormals[1]){
      for(int j=0;j<64;j++){defaultNormals[j*4+2]=127;defaultNormals[j*4+1]=127;}
     }
     p=defaultNormals;stride=0;
    }
    tiles[i]->companion()->rva00111A05(p,stride);
   }
  }
  tiles+=(numRows ? *(volatile int*)&numRows : *(volatile int*)&numRows);
 }
 operator delete[](nbuf);operator delete[](buf);
 return true;
}
