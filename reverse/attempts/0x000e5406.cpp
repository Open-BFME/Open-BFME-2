// ?rva006F83F0@Gen_uw_000e5033@@QAEHPAXH00@Z
// partial score=0.980303 date=2026-10-10
// cl: /O1 /arch:SSE /G7 /Oy- /MD /DNDEBUG /EHs-c- /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// Bank-only declaration snapshot of the actual canonical floor contract.
// Apply the recorded header proposal and reconcile all real owners before landing.
#pragma once
// Shared 0xA0 target floor element: layout validated by the complete
// 275-byte constructor, 104-byte destructor and independent EH checks.
// Original class identity remains represented by its existing neutral name.
#include "../../Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DFloorElementTypes.h"
class Gen_uw_000e5033 {
public:
    Gen_uw_000e5033();
    ~Gen_uw_000e5033();
    bool load();
    int rva006F83F0(void *a,int b,void *c,void *p);
    int rva006F8700(void *a,int b,void *c,void *p);
    friend class W3DFloorBuffer;
private:
    FloorSphere m_sphere00;
    float m_sphere10[4];
    FloorTextureRef m_texture20;
    FloorTextureRef m_texture24;
    void *m_render28;
    void *m_drawable2c;
    struct Position { float x,y,z; Position() : x(0),y(0),z(0) {} } m_position30;
    int m_3c,m_40,m_44,m_48,m_id4c;
    FloorMatrix m_matrix50;
    bool m_active80,m_flag81,m_flag82;
    float m_opacity84,m_speed88;
    AsciiString m_name8c,m_name90;
    int m_94,m_state98;
    bool m_flag9c,m_flag9d;
};
typedef char FloorElementExtentShared[(sizeof(Gen_uw_000e5033)==0xa0)?1:-1];

#include "../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/matrix3d.h"
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
class GlobalData; extern GlobalData *TheWritableGlobalData;
struct BfmeLighting36;
struct FloorGlobalLightAccess { char pad[0x134];int time;char gap[8];BfmeLighting36 *unused; };
class Rva000E4BD5Lighting { public: unsigned int doLighting(const BfmeLighting36*,const Coord3D*,unsigned int,float,unsigned int); };
class Drawable { public: float rva00272C9E(int); };
class VertexMaterialClass { public: void Get_Emissive(Vector3*) const; };
class MeshMatDescClass { public: Vector2 *Get_UV_Array_By_Index(int,bool); unsigned int *Get_Color_Array(int,bool); };
struct FloorVertexBufferAccess { char pad[12];Vector3 *vertices; };
struct FloorGeometryAccess { char pad[0x28];int count;char gap[4];FloorVertexBufferAccess *vertices;char tail[0x60];MeshMatDescClass *materials; __forceinline int vertexCount() const {return count;} __forceinline Vector3 *vertexArray() {return vertices->vertices;} __forceinline Vector2 *uvArray(int i) {return materials->Get_UV_Array_By_Index(i,false);} __forceinline unsigned int *colorArray(int i) {return materials->Get_Color_Array(i,false);} };
struct FloorMaterialInfoAccess { virtual void destroy();int refs;int unused;VertexMaterialClass **materials;char gap[8];int count; };
struct FloorMeshAccess { virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();virtual void slot16();virtual void slot17();virtual void slot18();virtual void slot19();virtual void slot20();virtual void slot21();virtual void slot22();virtual void slot23();virtual void slot24();virtual void slot25();virtual void slot26();virtual void slot27();virtual void slot28();virtual void slot29();virtual void slot30();virtual void slot31();virtual void slot32();virtual void slot33();virtual void slot34();virtual void slot35();virtual void slot36();virtual void slot37();virtual void slot38();virtual void slot39();virtual void slot40();virtual void slot41();virtual void slot42();virtual void slot43();virtual void slot44();virtual void slot45();virtual void slot46();virtual void slot47();virtual void slot48();virtual void slot49();virtual void slot50();virtual void slot51();virtual void slot52();virtual void slot53();virtual void slot54();virtual void slot55();virtual void slot56();virtual void slot57();virtual void slot58();virtual void slot59();virtual void slot60();virtual void slot61();virtual void slot62();virtual void slot63();virtual void slot64();virtual void slot65();virtual void slot66();virtual void slot67();virtual void slot68();virtual void slot69();virtual void slot70();virtual void slot71();virtual void slot72();virtual void slot73();virtual void slot74();virtual void slot75();virtual void slot76();virtual void slot77();virtual void slot78();virtual void slot79();virtual void slot80();virtual void slot81();virtual void slot82();virtual void slot83();virtual void slot84(); virtual FloorMaterialInfoAccess *materials();char pad[0xC0];FloorGeometryAccess *geometry; __forceinline FloorGeometryAccess *model() {return geometry;} };
struct FloorVertex { float x,y,z,nx,ny,nz;unsigned int color;float u,v; };
int Gen_uw_000e5033::rva006F8700(void *a,int b,void *c,void *p) { if(!p)return 0; return rva006F83F0(a,b,c,p); }
int Gen_uw_000e5033::rva006F83F0(void *a,int b,void *c,void *p) {
 FloorMeshAccess *mesh=(FloorMeshAccess*)p;
 if(!mesh)return 0;
 float opacity;
 if(m_drawable2c && ((Drawable*)m_drawable2c)->rva00272C9E(0)!=1.0f) opacity=((Drawable*)m_drawable2c)->rva00272C9E(0);
 else opacity=m_opacity84;
 opacity=opacity<0.0f?0.0f:(opacity>1.0f?1.0f:opacity);
 unsigned int alpha=(unsigned int)(opacity*255.0);
 const BfmeLighting36 *lights=(const BfmeLighting36*)((char*)TheWritableGlobalData+0x140+((FloorGlobalLightAccess*)TheWritableGlobalData)->time*0x6C);
 int count=mesh->geometry->vertexCount();Vector3 *vertices=mesh->geometry->vertexArray();
 if(b+count+2>=15000)return 0;
 Vector3 emissive;emissive.Set(0,0,0);
 FloorMaterialInfoAccess *info=mesh->materials();
 if(info) { VertexMaterialClass *material=info->count>0?info->materials[0]:0;if(material)material->Get_Emissive(&emissive);if(--info->refs==0)info->destroy(); }
 Vector2 *uv=mesh->geometry->uvArray(0);
 FloorVertex *destination=(FloorVertex*)a+b;
 FloorGeometryAccess *model=mesh->geometry; unsigned int *colors=model->colorArray(0);
 const Matrix3D &matrix=*(const Matrix3D*)c;
 for(int i=0;i<count;++i) {
  destination->u=uv[i].X;destination->v=uv[i].Y;
  Vector3 position;const Vector3 &sourceVertex=vertices[i];Matrix3D::Transform_Vector(matrix,sourceVertex,&position);
  position=*(const Vector3*)&m_position30+position;
  destination->x=position.X;destination->y=position.Y;destination->z=position.Z;
  unsigned int color=colors?colors[i]:0xFFFFFFFF;
  destination->color=((Rva000E4BD5Lighting*)this)->doLighting(lights,(const Coord3D*)&emissive,color,1.0f,alpha);
  destination->nx=0;destination->ny=0;destination->nz=1;
  ++destination;
 }
 return count;
}
