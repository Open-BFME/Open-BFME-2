// ?rva000443BA@@YAXPBURva000443BARow@@MPAPAURva000443BALight@@@Z
// cl: /O1 /arch:SSE /G7 /MD
// Native443BA..4443E RET0 and4443E..4450E RET4; complete132/208-byte lighting family.
// BF1 donor575ba2b04 ZH W3DDisplay::setTimeOfDay provides scene/color/light semantics.
// Target independently proves four 36B row reads; selected global row stride6C at3C8/650.
// Static scene belongs to W3DDisplay; caller receiver name remains address-derived.
// Snapshot the green scale before ambient writes to preserve native alias-visible lifetime;
// red/blue retain parameter reads. No volatile/fences or synthetic caller.
// Genuine same-TU caller is required for native ECX/stack caller-cleanup helper ABI.
struct Rva000443BAVec {
 float x,y,z;
 Rva000443BAVec(float a,float b,float c) : x(a),y(b),z(c) {}
 Rva000443BAVec(const Rva000443BAVec &v):x(v.x),y(v.y),z(v.z){}
 Rva000443BAVec operator*(float s)const{return Rva000443BAVec(x*s,y*s,z*s);}
 Rva000443BAVec&operator*=(float s){x*=s;y*=s;z*=s;return *this;}
 Rva000443BAVec &operator=(const Rva000443BAVec &v) { x=v.x; y=v.y; z=v.z; return *this; }
};
struct Rva000443BALight {
 char pad[0xd4]; Rva000443BAVec ambient,diffuse,specular;
 void setAmbient(const Rva000443BAVec &v) { ambient=v; }
 void setDiffuse(const Rva000443BAVec &v) { diffuse=v; }
 void setDiffuse(float r,float g,float b){diffuse.x=r;diffuse.y=g;diffuse.z=b;}
 void setSpecular(const Rva000443BAVec &v) { specular=v; }
};
struct Rva000443BARow { float ambient[3],diffuse[3],position[3]; };
static __declspec(noinline) void rva000443BA(const Rva000443BARow *rows, float scale, Rva000443BALight **lights)
{
 for (int i=0;i<4;++i) {
  if (!lights[i]) continue;
  float green=scale;
  lights[i]->setAmbient(Rva000443BAVec(0,0,0));
  green*=rows[i].diffuse[1];
  lights[i]->setDiffuse(Rva000443BAVec(rows[i].diffuse[0]*scale,green,rows[i].diffuse[2]*scale));
  lights[i]->setSpecular(Rva000443BAVec(0,0,0));
 }
}


class GlobalData {public:char p0[0x134];int timeOfDay;char p138[0x3C8-0x138];Rva000443BARow terrain[4][3];char gap[0x650-0x3C8-4*3*sizeof(Rva000443BARow)];Rva000443BARow objects[4][3];};extern GlobalData*TheWritableGlobalData;
class RTS3DScene {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void setAmbient(const Rva000443BAVec&);char pad[0x144-4];Rva000443BAVec color;};
class W3DDisplay {public:static RTS3DScene*m_3DScene;};
class Rva0004443E {public:char p0[0x148];Rva000443BALight*lights[4];Rva000443BALight*otherLights[4];void rva0004443E(float);void rva00044688(const Rva000443BAVec*);void rva0004474C(int);void rva0004450E(int,Rva000443BAVec);void rva00044545(int,Rva000443BAVec);};
void Rva0004443E::rva0004443E(float scale){
 const Rva000443BARow*rows=&TheWritableGlobalData->terrain[TheWritableGlobalData->timeOfDay][0];
 const Rva000443BARow*objects=&TheWritableGlobalData->objects[TheWritableGlobalData->timeOfDay][0];
 if(W3DDisplay::m_3DScene){W3DDisplay::m_3DScene->setAmbient(Rva000443BAVec(rows->ambient[0]*scale,rows->ambient[1]*scale,rows->ambient[2]*scale));W3DDisplay::m_3DScene->color=Rva000443BAVec(objects->ambient[0]*scale,objects->ambient[1]*scale,objects->ambient[2]*scale);}
 rva000443BA(rows,scale,lights);rva000443BA(objects,scale,otherLights);
}

void Rva0004443E::rva0004450E(int i,Rva000443BAVec color){Rva000443BALight*light=lights[i];if(light)light->setDiffuse(color);}
void Rva0004443E::rva00044545(int i,Rva000443BAVec color){Rva000443BALight*light=otherLights[i];if(light)light->setDiffuse(color);}

struct Rva0004457CMatrix {float m[3][4];__forceinline void set(const Rva000443BAVec&x,const Rva000443BAVec&y,const Rva000443BAVec&z,const Rva000443BAVec&t){m[0][0]=x.x;m[0][1]=y.x;m[0][2]=z.x;m[0][3]=t.x;m[1][0]=x.y;m[1][1]=y.y;m[1][2]=z.y;m[1][3]=t.y;m[2][0]=x.z;m[2][1]=y.z;m[2][2]=z.z;m[2][3]=t.z;}};
class Rva0004457CTransform {public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();

virtual void setTransform(const Rva0004457CMatrix&);};
static __declspec(noinline) void rva0004457C(const Rva000443BARow*rows,const Rva000443BAVec*direction,Rva000443BALight**lights){
 for(int i=0;i<4;++i){if(!lights[i])continue;
 lights[i]->setAmbient(Rva000443BAVec(0,0,0));
 lights[i]->setDiffuse(Rva000443BAVec(rows[i].diffuse[0],rows[i].diffuse[1],rows[i].diffuse[2]));
 lights[i]->setSpecular(Rva000443BAVec(0,0,0));
 Rva0004457CMatrix matrix;
 if(direction)matrix.set(Rva000443BAVec(1,0,0),Rva000443BAVec(0,1,0),*direction,Rva000443BAVec(0,0,0));else matrix.set(Rva000443BAVec(1,0,0),Rva000443BAVec(0,1,0),Rva000443BAVec(rows[i].position[0],rows[i].position[1],rows[i].position[2]),Rva000443BAVec(0,0,0));
 reinterpret_cast<Rva0004457CTransform*>(lights[i])->setTransform(matrix);
 }
}
class BaseHeightMapRenderObjClass {public:void rva0006846A(int);};extern BaseHeightMapRenderObjClass*TheTerrainRenderObject;
class View {public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();

virtual void forceRedraw();};extern View*TheTacticalView;
int bfmeRva0011F600();
void Rva0004443E::rva00044688(const Rva000443BAVec*direction){
 const Rva000443BARow*rows=&TheWritableGlobalData->terrain[1][0];
 const Rva000443BARow*objects=&TheWritableGlobalData->objects[1][0];
 if(W3DDisplay::m_3DScene){W3DDisplay::m_3DScene->setAmbient(Rva000443BAVec(rows->ambient[0],rows->ambient[1],rows->ambient[2]));W3DDisplay::m_3DScene->color=Rva000443BAVec(objects->ambient[0],objects->ambient[1],objects->ambient[2]);}
 rva0004457C(rows,direction,lights);rva0004457C(objects,direction,otherLights);
 if(TheTerrainRenderObject){TheTerrainRenderObject->rva0006846A(1);if(static_cast<unsigned char>(bfmeRva0011F600()))TheTacticalView->forceRedraw();}
}
void Rva0004443E::rva0004474C(int tod){
 const Rva000443BARow*rows=&TheWritableGlobalData->terrain[tod][0];
 const Rva000443BARow*objects=&TheWritableGlobalData->objects[tod][0];
 if(W3DDisplay::m_3DScene){W3DDisplay::m_3DScene->setAmbient(Rva000443BAVec(rows->ambient[0],rows->ambient[1],rows->ambient[2]));W3DDisplay::m_3DScene->color=Rva000443BAVec(objects->ambient[0],objects->ambient[1],objects->ambient[2]);}
 rva0004457C(rows,0,lights);rva0004457C(objects,0,otherLights);
 if(TheTerrainRenderObject){TheTerrainRenderObject->rva0006846A(tod);if(static_cast<unsigned char>(bfmeRva0011F600()))TheTacticalView->forceRedraw();}
}
