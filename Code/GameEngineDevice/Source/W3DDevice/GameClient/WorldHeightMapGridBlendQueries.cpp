// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
#include <vector>
// Retail AE37E..AE44B and AE44B..AE490 prove the bounds, origins, 36-byte
// cliff record with signed tile index+22, and texture interval fields+4/+8.
// BFME1 f98983a7d WorldHeightMap.cpp getUVForTileIndex supplies the semantic
// interval test and its std::vector<TCliffInfo> view; unrelated record fields
// remain donor-carried. BFME2 ctor B0C38 constructs the vector at+80BC with
// the existing vector-base worker211E58 and 512 texture records at+80CC.
// Names remain address-derived because the exact target names are unproven.
struct CliffInfo36 { float uv[8]; bool flip; short tileIndex; };
struct TextureClass40 { int unknown00,firstTile,numTiles; char rest[28]; };
class WorldHeightMap { public: void rva000AE44B(int,int,void*); bool rva000AE37E(int,int);
private: char pad0[8]; int width; char padC[0x20-0xc]; int dataSize; char pad24[0x98-0x24]; short*tileNdxes; char pad9C[4]; int*cliffNdxes; char padA4[0x80bc-0xa4]; std::vector<CliffInfo36> cliffInfo; int numTextureClasses; TextureClass40 textureClasses[512]; char padD0CC[0x120e0-0x80cc-40*512]; int originX,originY; };
void WorldHeightMap::rva000AE44B(int x,int y,void*dest) {
 int ndx=(originY+y)*width+originX+x;
 if(ndx<0 || ndx>=dataSize)return;
 int v=cliffNdxes[ndx];
 *(CliffInfo36*)dest=cliffInfo[v];
}
bool WorldHeightMap::rva000AE37E(int x,int y) {
 bool tilesMatch=false;
 int ndx=(originY+y)*width+originX+x;
 if(ndx>=0 && ndx<dataSize) {
  CliffInfo36 info=cliffInfo[cliffNdxes[ndx]];
  int ndx1=tileNdxes[ndx]>>2;
  int ndx2=info.tileIndex>>2;
  int i;
  for(i=0;i<numTextureClasses;i++) {
   if(ndx1>=textureClasses[i].firstTile && ndx1<textureClasses[i].firstTile+textureClasses[i].numTiles) {
    tilesMatch=ndx2>=textureClasses[i].firstTile && ndx2<textureClasses[i].firstTile+textureClasses[i].numTiles;
    break;
   }
  }
 }
 return !tilesMatch;
}
