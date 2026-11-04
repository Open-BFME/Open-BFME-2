// ?updateScorches@BaseHeightMapRenderObjClass@@QAEXXZ
// ?updateScorches@BaseHeightMapRenderObjClass@@QAEXXZ
// ?updateScorches@BaseHeightMapRenderObjClass@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ?updateScorches@BaseHeightMapRenderObjClass@@QAEXXZ, retail 0x000678BB..
// 0x00067E8E (1491 bytes). Zero Hour's BaseHeightMapRenderObjClass::updateScorches
// (BaseHeightMap.cpp) with the BFME changes the retail body shows; the skeleton
// is the BFME 1 port (Open-BFME-1 575ba2b04 BaseHeightMapUpdateScorches.cpp:
// skipped scorches via the flag byte, border read once before the locks,
// 16-bit heights, a vertex-budget rollback). BFME 2 target evidence: the
// shade is ambient + diffuse-times-scale / 2 scaled by 2 under shader
// overbright and clamped to 1, UVs span the scorch's own quad grid in 1/3
// atlas cells, heights are ushort * 0.0390625 + 1.
// Entry stride 0x1C at +0xE0 (as addScorch), counts at +0x3790/+0x3794.
typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
// Keep the CRT's inlined floorf local; its public body is owned by the
// terrain-lightmap unit at 0x0004D649.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "wwmath.h"
struct VertexFormatXYZDUV1

{
 Real x, y, z;
 UnsignedInt diffuse;
 Real u1, v1;
 
}
;
#include "../../../Libraries/Include/Lib/RGBColor.h"
#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
extern bool ShaderOverbrightEnabled;
#include "../../../Libraries/Source/WWVegas/WW3D2/VertexBufferClass.h"
#include "../../../Libraries/Source/WWVegas/WW3D2/IndexBufferClass.h"
// The world height map view retail reads: border at +0x10, extents at +8/+0xC;
// 0x0006653B is its clamped 16-bit height lookup, 0x004ADF41 the flip-state query.
class Rva0006653B

{
 public:
 UnsignedShort rva0006653B(Int x, Int y);
 char m_pad00[8];
 Int m_xExtent;
 Int m_yExtent;
 Int m_border;
 
}
;
class Gen_0074B410

{
 public:
 bool bfmeBitA(int x, int y) const;
 
}
;
#include "../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
struct BFMEScorchEntry

{
 char m_pad00[4];
 Vector3 location;
 Real radius;
 Int scorchType;
 UnsignedByte flag;
 char m_pad19[3];
 
}
;
#define SCORCH_MARKS_IN_TEXTURE 9
#define SCORCH_PER_ROW 3
#define MAX_SCORCH_VERTEX 8194
#define MAX_SCORCH_INDEX 49164
#define BFME_MAP_XY_FACTOR 10.0f
static inline Real bfmeFloorD(Real value) 
{
 double roundedValue = floor(value);
 return (Real)roundedValue;
 
}
static inline Real bfmeCeilD(Real value) 
{
 double roundedValue = ceil(value);
 return (Real)roundedValue;
 
}
class BaseHeightMapRenderObjClass

{
 public:
 void updateScorches();
 private:
 UnsignedByte m_pad00[0xCC];
 VertexBufferClass *m_vertexScorch;
// +0xCC
 IndexBufferClass *m_indexScorch;
// +0xD0
 void *m_scorchTexture;
// +0xD4
 Int m_curNumScorchVertices;
// +0xD8
 Int m_curNumScorchIndices;
// +0xDC
 BFMEScorchEntry m_scorches[500];
// +0xE0
 Int m_numScorches;
// +0x3790
 Int m_scorchesInBuffer;
// +0x3794
 Int m_nextScorch;
// +0x3798
 UnsignedByte m_pad379C[0x37C0 - 0x379C];
 Rva0006653B *m_map;
// +0x37C0
 
}
;
void BaseHeightMapRenderObjClass::updateScorches()

{
 if (m_scorchesInBuffer > 1) 
 {
  return;
  
 }
 if (m_numScorches == 0) 
 {
  return;
  
 }
 if (!m_indexScorch || !m_vertexScorch) 
 {
  return;
  
 }
 m_scorchesInBuffer = 0;
 m_curNumScorchVertices = 0;
 m_curNumScorchIndices = 0;
 Real shadeR, shadeG, shadeB;
 shadeR = TheWritableGlobalData->field0944[0] * TheWritableGlobalData->m_terrainDiffuse[0].red;
 shadeG = TheWritableGlobalData->field0944[1] * TheWritableGlobalData->m_terrainDiffuse[0].green;
 shadeB = TheWritableGlobalData->field0944[2] * TheWritableGlobalData->m_terrainDiffuse[0].blue;
 shadeR = shadeR * 0.5f + TheWritableGlobalData->m_terrainAmbient[0].red;
 shadeG = shadeG * 0.5f + TheWritableGlobalData->m_terrainAmbient[0].green;
 shadeB = shadeB * 0.5f + TheWritableGlobalData->m_terrainAmbient[0].blue;
 Real scale = 1.0f;
 if (ShaderOverbrightEnabled) scale = 2.0f;
 shadeR = scale * shadeR;
 if (shadeR > 1.0f) shadeR = 1.0f;
 shadeG = scale * shadeG;
 if (shadeG > 1.0f) shadeG = 1.0f;
 shadeB = scale * shadeB;
 if (shadeB > 1.0f) shadeB = 1.0f;
 shadeR *= 255.0f;
 shadeG *= 255.0f;
 shadeB *= 255.0f;
 Int diffuse = (Int)shadeR;
 diffuse |= 0xffffff00;
 diffuse <<= 8;
 diffuse |= (Int)shadeG;
 diffuse <<= 8;
 diffuse |= (Int)shadeB;
 Int borderSize = m_map->m_border;
 IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexScorch, 0);
 UnsignedShort *indexCursor = lockIdxBuffer.Get_Index_Array();
 VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexScorch, 0);
 VertexFormatXYZDUV1 *vertexCursor = (VertexFormatXYZDUV1 *)lockVtxBuffer.Get_Vertex_Array();
 Int scorchIndex;
 for (scorchIndex = m_numScorches - 1; scorchIndex >= 0; scorchIndex--) 
 {
  UnsignedByte flag = m_scorches[scorchIndex].flag;
  if (flag) 
  {
   continue;
   
  }
  m_scorchesInBuffer++;
  Int type = m_scorches[scorchIndex].scorchType;
  if (type < 0 || type >= SCORCH_MARKS_IN_TEXTURE) 
  {
   type = 0;
   
  }
  Real uOffset = (type % SCORCH_PER_ROW) * (1.0f / (SCORCH_PER_ROW));
  Real vOffset = (type / SCORCH_PER_ROW) * (1.0f / (SCORCH_PER_ROW));
  Real radius = m_scorches[scorchIndex].radius;
  Vector3 scorchPosition = m_scorches[scorchIndex].location;
  Int minX = WWMath::Float_To_Long(bfmeFloorD((scorchPosition.X - radius) * (1.0f / BFME_MAP_XY_FACTOR)));
  minX--;
  Int minY = WWMath::Float_To_Long(bfmeFloorD((scorchPosition.Y - radius) * (1.0f / BFME_MAP_XY_FACTOR)));
  minY--;
  if (minX < -borderSize) minX = -borderSize;
  if (minY < -borderSize) minY = -borderSize;
  Int maxX = WWMath::Float_To_Long(bfmeCeilD((scorchPosition.X + radius) * (1.0f / BFME_MAP_XY_FACTOR)));
  maxX++;
  Int maxY = WWMath::Float_To_Long(bfmeCeilD((scorchPosition.Y + radius) * (1.0f / BFME_MAP_XY_FACTOR)));
  maxY++;
  if (maxX > m_map->m_xExtent - borderSize) { Int extent = m_map->m_xExtent; maxX = extent - borderSize; }
  if (maxY > m_map->m_yExtent - borderSize) { Int extent = m_map->m_yExtent; maxY = extent - borderSize; }
  Int firstScorchVertex = m_curNumScorchVertices;
  Real width = (1 ? (maxX - minX - 1) * BFME_MAP_XY_FACTOR : (maxX - minX - 1) * BFME_MAP_XY_FACTOR);
  Real height = (maxY - minY - 1) * BFME_MAP_XY_FACTOR;
  Real worldLeft = minX * BFME_MAP_XY_FACTOR;
  Real worldTop = minY * BFME_MAP_XY_FACTOR;
  Int verticesPerRow = maxX - minX;
  Int columnIndex, j;
  for (j = minY; j < maxY; j++) 
  {
   Real Y = j * BFME_MAP_XY_FACTOR;
   for (columnIndex = minX; columnIndex < maxX; columnIndex++) 
   {
    if (m_curNumScorchVertices >= MAX_SCORCH_VERTEX) 
    {
     m_curNumScorchVertices = firstScorchVertex;
     return;
     
    }
    Real X = columnIndex * BFME_MAP_XY_FACTOR;
    vertexCursor->diffuse = diffuse;
    vertexCursor->u1 = (X - worldLeft) / width * (1.0f / (SCORCH_PER_ROW)) + uOffset;
    vertexCursor->v1 = (Y - worldTop) / height * (1.0f / (SCORCH_PER_ROW)) + vOffset;
    vertexCursor->x = X;
    vertexCursor->y = Y;
    vertexCursor->z = m_map->rva0006653B(columnIndex + borderSize, j + borderSize) * 0.0390625f + 1.0f;
    vertexCursor++;
    m_curNumScorchVertices++;
    
   }
   
  }
  for (j = 0; j < maxY - minY - 1; j++) 
  {
   Int mapRow = j + minY + borderSize;
   for (columnIndex = 0; columnIndex < maxX - minX - 1; columnIndex++) 
   {
    if (m_curNumScorchIndices + 6 > MAX_SCORCH_INDEX) return;
    Int mapColumn = columnIndex + minX + borderSize;
    Bool flipForBlend = reinterpret_cast<const Gen_0074B410 *>(m_map)->bfmeBitA(mapColumn, mapRow);
    if (flipForBlend) 
    {
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + 1;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + verticesPerRow;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + 1;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + 1 + verticesPerRow;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + verticesPerRow;
     
    }
    else 
    {
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + 1 + verticesPerRow;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + verticesPerRow;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + 1;
     *indexCursor++ = firstScorchVertex + j * verticesPerRow + columnIndex + 1 + verticesPerRow;
     
    }
    m_curNumScorchIndices += 6;
    
   }
   
  }
  
 }
 
}
