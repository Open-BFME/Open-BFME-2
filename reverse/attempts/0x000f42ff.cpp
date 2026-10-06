// ?RenderDynamicMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z
// partial score=0.98 date=2026-10-06
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/wwstring_teardown/zhmd /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -DBFME_VOLUMETRIC_DELETE_LAYOUT -Ireference/open-bfme-1/inputs/reference/shims/volumetricshadow -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Target candidate: W3DVolumetricShadow::RenderDynamicMeshVolume, RVA 0x000F42FF..0x000F49D0, 1745 bytes.
// Semantic donor: Open-BFME-1 d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c,
// game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderDynamicMeshVolume.cpp.
// Target identity: matched RenderVolume calls this body at RVA 0x000F4AA4.
// Reseeded Ghidra finds one contiguous range; retail branch 0x000F431C reaches
// the epilogue at 0x000F49C0 and RET12 at 0x000F49CD confirms the complete boundary.
// Target retains donor geometry +0/+0x10/+0x14, owner +0x34/+0x70/+0x80,
// 160-entry light stride and device/buffer virtual slots. Buffer limits are
// target constants 8192 vertices and 16384 indices. Target adds warning-once
// sets and cached DX8 render-state/snapshot updates; these are absent in donor.
// NOT MATCHED: /O1 /G7 /arch:SSE emits 1743 bytes. The stencil replication
// expression uses EDI directly where retail copies EDI into EDX first (+2B).
// Remaining instruction shapes agree after this shift, but all direct callee,
// DIR32, local-static, COMDAT and final link bindings still need full gates.
// Do not treat donor address suffixes or Ghidra-generated types as identity proof.
struct IDirect3DVertexBuffer8;
extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
struct IDirect3DIndexBuffer8;
extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;

#define Matrix4x4 Matrix4
#include "matrix4.h"
#include "shader.h"
#include "dx8wrapper.h"
#include <string.h>
// stlport
#include <set>
#include "ascii_string.h"
struct ShadowBuffer007BC270 {
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual int __stdcall Lock(unsigned offset,unsigned size,unsigned char** out,unsigned flags);
 virtual int __stdcall Unlock();
};
struct ShadowDevice007BC270 {
 virtual void slot000();
 virtual void slot004();
 virtual void slot008();
 virtual void slot00c();
 virtual void slot010();
 virtual void slot014();
 virtual void slot018();
 virtual void slot01c();
 virtual void slot020();
 virtual void slot024();
 virtual void slot028();
 virtual void slot02c();
 virtual void slot030();
 virtual void slot034();
 virtual void slot038();
 virtual void slot03c();
 virtual void slot040();
 virtual void slot044();
 virtual void slot048();
 virtual void slot04c();
 virtual void slot050();
 virtual void slot054();
 virtual void slot058();
 virtual void slot05c();
 virtual void slot060();
 virtual void slot064();
 virtual void slot068();
 virtual void slot06c();
 virtual void slot070();
 virtual void slot074();
 virtual void slot078();
 virtual void slot07c();
 virtual void slot080();
 virtual void slot084();
 virtual void slot088();
 virtual void slot08c();
 virtual void slot090();
 virtual void slot094();
 virtual void slot098();
 virtual void slot09c();
 virtual void slot0a0();
 virtual void slot0a4();
 virtual void slot0a8();
 virtual void slot0ac();
 virtual int __stdcall SetTransform(unsigned,const void*);
 virtual void slot0b4();
 virtual void slot0b8();
 virtual void slot0bc();
 virtual void slot0c0();
 virtual void slot0c4();
 virtual void slot0c8();
 virtual void slot0cc();
 virtual void slot0d0();
 virtual void slot0d4();
 virtual void slot0d8();
 virtual void slot0dc();
 virtual void slot0e0();
 virtual int __stdcall SetRenderState(unsigned,unsigned);
 virtual void slot0e8();
 virtual void slot0ec();
 virtual void slot0f0();
 virtual void slot0f4();
 virtual void slot0f8();
 virtual void slot0fc();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10c();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11c();
 virtual void slot120();
 virtual void slot124();
 virtual void slot128();
 virtual void slot12c();
 virtual void slot130();
 virtual void slot134();
 virtual void slot138();
 virtual void slot13c();
 virtual void slot140();
 virtual void slot144();
 virtual int __stdcall DrawIndexedPrimitive(unsigned,int,unsigned,unsigned,unsigned,unsigned);
 virtual void slot14c();
 virtual void slot150();
 virtual void slot154();
 virtual void slot158();
 virtual void slot15c();
 virtual void slot160();
 virtual void slot164();
 virtual void slot168();
 virtual void slot16c();
 virtual void slot170();
 virtual void slot174();
 virtual void slot178();
 virtual void slot17c();
 virtual void slot180();
 virtual void slot184();
 virtual void slot188();
 virtual void slot18c();
 virtual int __stdcall SetStreamSource(unsigned,ShadowBuffer007BC270*,unsigned,unsigned);
 virtual void slot194();
 virtual void slot198();
 virtual void slot19c();
 virtual int __stdcall SetIndices(ShadowBuffer007BC270*);
};


extern ShadowBuffer007BC270* lastActiveVertexBuffer;
extern int nShadowVertsInBuf,nShadowStartBatchVertex,nShadowIndicesInBuf,nShadowStartBatchIndex;
enum { SHADOW_VERTEX_SIZE=8192, SHADOW_INDEX_SIZE=16384 };
struct W3DShadowManager { char pad[8]; int m_stencilShadowMask; int getStencilShadowMask(){return m_stencilShadowMask;} };
extern W3DShadowManager* TheW3DShadowManager;

namespace Debug_Statistics { void Record_DX8_Polys_And_Vertices(int,int,const ShaderClass&); }
class ShadowLog007BC270 {
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual ShadowLog007BC270* number(int);
 virtual ShadowLog007BC270* text(const char*);
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void end(int);
};
class ShadowDebug007BC270 { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4c();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5c();
 virtual void begin();
 virtual void slot64();
 virtual void slot68();
 virtual ShadowLog007BC270* stream(int,int,int);
};
extern ShadowDebug007BC270* debug01336E5C;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int);
class RenderObjClass { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual const char* Get_Name() const;
};
struct Geometry {
 Vector3* m_verts;
 unsigned short* m_indices;
 int m_numPolygon,m_numVertex,m_numActivePolygon,m_numActiveVertex;
 unsigned short* GetPolygonIndex(long,short*) const;
 Vector3* GetVertex(int i){return &m_verts[i];}
 int GetNumActiveVertex(){return m_numActiveVertex;}
 int GetNumActivePolygon(){return m_numActivePolygon;}
};
class W3DVolumetricShadow {
protected:
 void RenderDynamicMeshVolume(int,int,const Matrix3D*);
 char pad00[0x34]; int bitsAt0034; char pad38[0x38];
 RenderObjClass* m_robj; char pad74[0xc];
 Geometry* m_shadowVolume[1][160];
};
void W3DVolumetricShadow::RenderDynamicMeshVolume(int meshIndex,int lightIndex,const Matrix3D* meshXform)
{
 Geometry* geometry;
 int numVerts,numPolys,numIndex;
 Vector3* pvVertices;
 unsigned short* pvIndices;
 ShadowDevice007BC270* m_pDev=reinterpret_cast<ShadowDevice007BC270 *>(DX8Wrapper::_Get_D3D_Device8());
 if(!m_pDev) return;
 int playerColor=(bitsAt0034>>7)&7;
 if(playerColor) {
  unsigned mask=TheW3DShadowManager->getStencilShadowMask();
  unsigned stencil=playerColor<<4;
  DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)58,((((stencil<<8)|stencil)<<8|stencil)<<8)|mask|stencil);
  DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)57,stencil);
 }
 geometry=m_shadowVolume[lightIndex][meshIndex];
 numVerts=geometry->GetNumActiveVertex();
 numPolys=geometry->GetNumActivePolygon();
 numIndex=numPolys*3;
 if(numVerts==0 || numPolys==0) return;
 if(numVerts>SHADOW_VERTEX_SIZE) {
  static std::set<AsciiString> warned;
  if(warned.find(m_robj->Get_Name()) != warned.end()) return;
  if(_bfme_debugReportingEnabled()) {
   _bfme_debugRecordCallsite(1);
   debug01336E5C->begin();
   debug01336E5C->stream(0,0,0)->text("Shadow geometry for ")->text(m_robj->Get_Name())->text(" has too many vertices (")->number(numVerts)->text(" with a limit of ")->number(SHADOW_VERTEX_SIZE)->text("). Either reduce the geometric complexity or have engineering increase SHADOW_VERTEX_SIZE. Unless this is fixed the given object will not have a volumetric shadow. [mh]")->end(2);
  }
  warned.insert(m_robj->Get_Name());
  return;
 }
 if(numIndex>SHADOW_INDEX_SIZE) {
  static std::set<AsciiString> warned;
  if(warned.find(m_robj->Get_Name()) != warned.end()) return;
  if(_bfme_debugReportingEnabled()) {
   _bfme_debugRecordCallsite(1);
   debug01336E5C->begin();
   debug01336E5C->stream(0,0,0)->text("Shadow geometry for ")->text(m_robj->Get_Name())->text(" has too many indices (")->number(numIndex)->text(" with a limit of ")->number(SHADOW_INDEX_SIZE)->text("). Either reduce the geometric complexity or have engineering increase SHADOW_INDEX_SIZE. Unless this is fixed the given object will not have a volumetric shadow. [mh]")->end(2);
  }
  warned.insert(m_robj->Get_Name());
  return;
 }
 if(nShadowVertsInBuf>SHADOW_VERTEX_SIZE-numVerts) {
  if(((ShadowBuffer007BC270 *&)shadowVertexBufferD3D)->Lock(0,numVerts*sizeof(Vector3),(unsigned char**)&pvVertices,0x2000)!=0)return;
  nShadowVertsInBuf=0; nShadowStartBatchVertex=0;
 } else {
  if(((ShadowBuffer007BC270 *&)shadowVertexBufferD3D)->Lock(nShadowVertsInBuf*sizeof(Vector3),numVerts*sizeof(Vector3),(unsigned char**)&pvVertices,0x1000)!=0)return;
 }
 if(pvVertices) memcpy(pvVertices,geometry->GetVertex(0),numVerts*sizeof(Vector3));
 ((ShadowBuffer007BC270 *&)shadowVertexBufferD3D)->Unlock();
 if(nShadowIndicesInBuf>SHADOW_INDEX_SIZE-numIndex) {
  if(((ShadowBuffer007BC270 *&)shadowIndexBufferD3D)->Lock(0,numIndex*sizeof(short),(unsigned char**)&pvIndices,0x2000)!=0)return;
  nShadowIndicesInBuf=0; nShadowStartBatchIndex=0;
 } else {
  if(((ShadowBuffer007BC270 *&)shadowIndexBufferD3D)->Lock(nShadowIndicesInBuf*sizeof(short),numIndex*sizeof(short),(unsigned char**)&pvIndices,0x1000)!=0)return;
 }
 if(pvIndices) memcpy(pvIndices,geometry->GetPolygonIndex(0,(short*)pvIndices),numPolys*3*sizeof(short));
 ((ShadowBuffer007BC270 *&)shadowIndexBufferD3D)->Unlock();
 m_pDev->SetIndices(((ShadowBuffer007BC270 *&)shadowIndexBufferD3D));
 Matrix4 mWorld(*meshXform);
 m_pDev->SetTransform(256,&mWorld.Transpose());
 if(((ShadowBuffer007BC270 *&)shadowVertexBufferD3D)!=lastActiveVertexBuffer) {
  m_pDev->SetStreamSource(0,((ShadowBuffer007BC270 *&)shadowVertexBufferD3D),0,sizeof(Vector3));
  lastActiveVertexBuffer=((ShadowBuffer007BC270 *&)shadowVertexBufferD3D);
 }
 if(DX8Wrapper::_Is_Triangle_Draw_Enabled()) {
  Debug_Statistics::Record_DX8_Polys_And_Vertices(numPolys,numVerts,ShaderClass::_PresetOpaqueShader);
  m_pDev->DrawIndexedPrimitive(4,nShadowStartBatchVertex,0,numVerts,nShadowStartBatchIndex,numPolys);
 }
 if(playerColor) {
  DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)58,TheW3DShadowManager->getStencilShadowMask());
  DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)57,0x80808080);
 }
 nShadowVertsInBuf+=numVerts; nShadowStartBatchVertex=nShadowVertsInBuf;
 nShadowIndicesInBuf+=numIndex; nShadowStartBatchIndex=nShadowIndicesInBuf;
}
