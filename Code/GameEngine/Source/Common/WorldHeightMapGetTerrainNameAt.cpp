// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /DNDEBUG /arch:SSE
// ?getTerrainNameAt@WorldHeightMap@@QAE?AVAsciiString@@MM@Z
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "ascii_string.h"
static __forceinline int terrainRound(float value){int roundedValue;__asm {fld value
fistp roundedValue}
return roundedValue;}
struct TerrainTextureClassRecord {int firstTile,numTiles;char pad[8];AsciiString name;char tail[20];};
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h"
AsciiString WorldHeightMap::getTerrainNameAt(float x,float y){
 int cellX=terrainRound(floor(x*0.1f));int cellY=terrainRound(floor(y*0.1f));
 cellX+=m_borderSize;cellY+=m_borderSize;if(cellX<0)cellX=0;if(cellY<0)cellY=0;if(cellX>=m_width)cellX=m_width-1;if(cellY>=m_height)cellY=m_height-1;
 int cellIndex=cellY*m_width+cellX;if(cellIndex<0||cellIndex>=m_dataSize)return AsciiString::TheEmptyString;
 int tileIndex=m_tileNdxes[cellIndex]>>2;
 // The lookup starts at the firstTile word, four bytes into each 0x28-byte record.
 for(int textureClassIndex=0;textureClassIndex<m_numTextureClasses;++textureClassIndex){
  if(tileIndex>=reinterpret_cast<TerrainTextureClassRecord *>(m_field80CC + 4)[textureClassIndex].firstTile &&
     tileIndex<reinterpret_cast<TerrainTextureClassRecord *>(m_field80CC + 4)[textureClassIndex].firstTile +
          reinterpret_cast<TerrainTextureClassRecord *>(m_field80CC + 4)[textureClassIndex].numTiles)
   return reinterpret_cast<TerrainTextureClassRecord *>(m_field80CC + 4)[textureClassIndex].name;
 }
 return AsciiString::TheEmptyString;
}
