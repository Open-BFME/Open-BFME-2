// ?rawTile@Rva000ADDCEWorldHeightMapView@@QAE_NFHPAEHH@Z
// partial score=0.6 date=2026-10-08
// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc
// Native AC88E..AC9DA (332B): existing neutral WorldHeightMap call owner.
// Semantic guide: ZH WorldHeightMap::getRawTileData and TileData mip access,
// reviewed at BFME1 dae380faa5f6fa536eec8d6ebbe877321d4cb51d.
// Retail supplies the fifth mode argument, optional tile copy at 111784,
// source table +B0/4096 entries and RGB555-to-32-bit expansion instead of
// the donor's 4BPP memcpy. Original BFME2 method name remains unknown.
class TileData {
public:
 bool hasRGBDataForWidth(int width);
 unsigned char *getRGBDataForWidth(int width);

};
class Rva00111784DwordField { public: int get() const; };
class Rva000ADDCEWorldHeightMapView {
public:
 bool rawTile(short tile,int width,unsigned char *buffer,int bytes,int mode);
private:
 char prefix[0xb0];
 TileData *tiles[0x1000];
};
// ?expandTerrainRGB555 present-unmatched
static __forceinline unsigned int expandTerrainRGB555(unsigned int value) {
 unsigned int low=value<<3;
 low=(low&0xff)|((low<<3)&0xff00);
 unsigned int color=(value>>10)<<19;
 color=(color&0xffff0000)|(low&0xffff);
 return color+((color>>5)&0x003f3f3f);
}
// ?rawTile@Rva000ADDCEWorldHeightMapView@@QAE_NFHPAEHH@Z present-unmatched
bool Rva000ADDCEWorldHeightMapView::rawTile(short tile,int width,
 unsigned char *buffer,int bytes,int mode) {
 TileData *source=0;
 if(tile/4<0x1000) {
  source=tiles[tile/4];
  if(mode==1) {
   if(!source) return false;
   source=reinterpret_cast<TileData *>(reinterpret_cast<const Rva00111784DwordField *>(source)->get());
   if(!source) return false;
  }
 }
 int destinationBytes=width*width*4;
 if(bytes<destinationBytes) return false;
 if(!source) return false;
 int sourceWidth=width*2;
 if(!source->hasRGBDataForWidth(sourceWidth)) return false;
 unsigned short *pixels=reinterpret_cast<unsigned short *>(source->getRGBDataForWidth(sourceWidth));
 if(tile&1) pixels+=width;
 if(tile&2) pixels+=width*width*2;
 unsigned int *destination=reinterpret_cast<unsigned int *>(buffer);
 int rows=width;
 do {
  unsigned int blocks=static_cast<unsigned int>(width)>>2;
  do {
   destination[0]=expandTerrainRGB555(pixels[0]);
   destination[1]=expandTerrainRGB555(pixels[1]);
   destination[2]=expandTerrainRGB555(pixels[2]);
   destination[3]=expandTerrainRGB555(pixels[3]);
   pixels+=4;
   destination+=4;
  } while(--blocks);
  pixels+=width;
 } while(--rows);
 return true;
}
