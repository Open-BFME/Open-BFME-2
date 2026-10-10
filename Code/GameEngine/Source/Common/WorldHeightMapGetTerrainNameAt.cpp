// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /DNDEBUG /arch:SSE
// ?getTerrainNameAt@WorldHeightMap@@QAE?AVAsciiString@@MM@Z
#include <math.h>
#include "ascii_string.h"
static __forceinline int terrainRound(float f){int r;__asm {fld f
fistp r}
return r;}
struct TerrainTextureClassRecord {int firstTile,numTiles;char pad[8];AsciiString name;char tail[20];};
class WorldHeightMap {public:AsciiString getTerrainNameAt(float x,float y);private:char pad0[8];int width,height,border;char pad14[0x20-0x14];int dataSize;char pad24[0x98-0x24];short*tileIndices;char pad9C[0x80C8-0x9C];int numClasses;char padCC[4];TerrainTextureClassRecord classes[1];};
AsciiString WorldHeightMap::getTerrainNameAt(float x,float y){
 int xi=terrainRound(floor(x*0.1f));int yi=terrainRound(floor(y*0.1f));
 xi+=border;yi+=border;if(xi<0)xi=0;if(yi<0)yi=0;if(xi>=width)xi=width-1;if(yi>=height)yi=height-1;
 int index=yi*width+xi;if(index<0||index>=dataSize)return AsciiString::TheEmptyString;
 int tile=tileIndices[index]>>2;
 for(int i=0;i<numClasses;++i){if(tile>=classes[i].firstTile&&tile<classes[i].firstTile+classes[i].numTiles)return classes[i].name;}
 return AsciiString::TheEmptyString;
}
