// cl: /O1 /Oy- /G7 /arch:SSE /MD /GX- /ICode/Libraries/Include/Lib
// Retail 0x000AD112..0x000AD6E8: standalone cdecl GlobalLighting v8 writer.
// The original function name and enclosing source ownership remain unknown;
// the neutral entry name records the proven boundary, not a donor method name.
// Semantic guide: GeneralsMD WorldBuilder/src/WHeightMapEdit.cpp lighting
// block in saveToFile, reviewed at BFME1 dae380faa5f6fa536eec8d6ebbe877321d4cb51d.
// Donor supplies terrain/object ambient, diffuse and position write ordering.
// Retail proves version 8, TOD +0x134, three 6x3 light arrays at +0x140,
// +0x3C8 and +0x650, 36-byte records, flag +0xD34 and final values +0x944.
// The third array, flag and final values deliberately retain neutral labels.
// Native reader 0x000ACAF7 and this writer are the only inventory users of
// three 16-byte vector slots at VA 0x00DBD788/798/7A8. The storage name below
// is descriptive; its original name and vector meaning are unproven. Retail
// data establishes each triplet as 0.5 and the fourth word as zero. The defined
// array preserves all 48 bytes without address aliases or invented field roles.
// ShaderOverbrightEnabled, TheWritableGlobalData and TheW3DShadowManager use
// existing data owners. The shadow color read is +4 as in the donor getter.
// Reusing scalar vector snapshots gives native local lifetimes and protects
// each triplet from changes made by writeReal; no aggregate copy helper emits.
#include "Coord3D.h"
class DataChunkOutput {
public:
 void openDataChunk(char *,unsigned short);
 void writeInt(int);
 void writeReal(float);
 void closeDataChunk();
};
struct LightingColor { float red,green,blue; };
struct LightingRecord { LightingColor ambient,diffuse; Coord3D lightPos; };
class GlobalData {
public:
 char prefix[0x134]; int m_timeOfDay; char pad[8];
 LightingRecord m_terrainLighting[6][3];
 LightingRecord m_terrainObjectsLighting[6][3];
 LightingRecord m_thirdLighting[6][3];
 char padTail[0x944-0x8d8]; float finalValues[3];
 char padFlag[0xd34-0x950]; unsigned char chunkFlag;
};
extern GlobalData *TheWritableGlobalData;
extern bool ShaderOverbrightEnabled;
class W3DShadowManager { public: void *vptr; int shadowColor; };
extern W3DShadowManager *TheW3DShadowManager;
struct LightingChunkVectorStorage { Coord3D components; float reserved; };
LightingChunkVectorStorage GlobalLightingChunkVectors[3] = {
 {{0.5f,0.5f,0.5f},0.0f},{{0.5f,0.5f,0.5f},0.0f},{{0.5f,0.5f,0.5f},0.0f}
};
void WriteGlobalLighting_Rva000AD112(DataChunkOutput &chunkWriter) {
 float x,y,z;
 chunkWriter.openDataChunk("GlobalLighting",8);
 chunkWriter.writeInt(TheWritableGlobalData->m_timeOfDay);
 for(int i=0;i<4;++i) {
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].ambient.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].ambient.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].ambient.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].diffuse.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].diffuse.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].diffuse.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].lightPos.x);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].lightPos.y);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][0].lightPos.z);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].ambient.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].ambient.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].ambient.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].diffuse.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].diffuse.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].diffuse.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].lightPos.x);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].lightPos.y);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][0].lightPos.z);
  for(int j=1;j<3;++j) {
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].ambient.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].ambient.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].ambient.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].diffuse.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].diffuse.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].diffuse.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].lightPos.x);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].lightPos.y);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainObjectsLighting[i+1][j].lightPos.z);
  }
  for(int j=1;j<3;++j) {
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].ambient.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].ambient.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].ambient.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].diffuse.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].diffuse.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].diffuse.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].lightPos.x);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].lightPos.y);
  chunkWriter.writeReal(TheWritableGlobalData->m_terrainLighting[i+1][j].lightPos.z);
  }
  for(int j=0;j<3;++j) {
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].ambient.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].ambient.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].ambient.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].diffuse.red);
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].diffuse.green);
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].diffuse.blue);
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].lightPos.x);
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].lightPos.y);
  chunkWriter.writeReal(TheWritableGlobalData->m_thirdLighting[i+1][j].lightPos.z);
  }
 }
 chunkWriter.writeReal(ShaderOverbrightEnabled ? 2.0f : 1.0f);
 chunkWriter.writeInt(TheWritableGlobalData->chunkFlag != 0);
 x = GlobalLightingChunkVectors[0].components.x; y = GlobalLightingChunkVectors[0].components.y; z = GlobalLightingChunkVectors[0].components.z;
 chunkWriter.writeReal(x); chunkWriter.writeReal(y); chunkWriter.writeReal(z);
 x = GlobalLightingChunkVectors[1].components.x; y = GlobalLightingChunkVectors[1].components.y; z = GlobalLightingChunkVectors[1].components.z;
 chunkWriter.writeReal(x); chunkWriter.writeReal(y); chunkWriter.writeReal(z);
 x = GlobalLightingChunkVectors[2].components.x; y = GlobalLightingChunkVectors[2].components.y; z = GlobalLightingChunkVectors[2].components.z;
 chunkWriter.writeReal(x); chunkWriter.writeReal(y); chunkWriter.writeReal(z);
 chunkWriter.writeInt(TheW3DShadowManager->shadowColor);
 chunkWriter.writeReal(TheWritableGlobalData->finalValues[0]);
 chunkWriter.writeReal(TheWritableGlobalData->finalValues[1]);
 chunkWriter.writeReal(TheWritableGlobalData->finalValues[2]);
 chunkWriter.closeDataChunk();
}
