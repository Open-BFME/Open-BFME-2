// cl: /O1 /arch:SSE /G7 /MD /EHsc
// W3DShadowMapManager::RenderBorder, native7BBA2..7BDAD RET0 (523B).
// WB7F6070 names RenderBorder in W3DShadowMapManager.cpp:789 and supplies
// the four viewport strips, six44B vertices, shader pass loop and final restore.
// Native fixes shader+20, dynamic wrapper24B, write lock12B and slots8/C/14/18.
#include <string.h>
struct ShadowBorderVertex {
 float x,y,z,nx,ny,nz;unsigned diffuse;float u,v,u2,v2;
 void Set(float a,float b,float c) {x=a;y=b;z=c;}
};
class DynamicVBAccessClass {
public:
 DynamicVBAccessClass(unsigned,unsigned,unsigned short,unsigned);
 ~DynamicVBAccessClass();
 char data[24];
 class WriteLock {
 public:
  WriteLock(DynamicVBAccessClass*);
  ~WriteLock();
  void *owner;ShadowBorderVertex *vertices;unsigned guard;
 };
};
struct _D3DVIEWPORT8 {unsigned X,Y,Width,Height;float MinZ,MaxZ;};
class DX8Wrapper {
public:
 static void Set_Vertex_Buffer(const DynamicVBAccessClass&);
 static void Set_Viewport(const _D3DVIEWPORT8*);
 static void bfmeRva00120650(unsigned,unsigned);
};
class WW3D {public:static void Get_Render_Target_Resolution(int&,int&,int&,bool&);};
class ShadowBorderShader {
public:
 virtual void slot0();virtual void slot1();
 virtual bool Begin(int*,unsigned short);
 virtual void BeginPass(int);
 virtual void slot4();virtual void EndPass();virtual void End();
};
class W3DShadowMapManager {
public:void RenderBorder();
private:char prefix[0x20];ShadowBorderShader *shader;
};
void W3DShadowMapManager::RenderBorder() {
 if(!shader)return;
 DynamicVBAccessClass access(2,5,6,0);
 {
  DynamicVBAccessClass::WriteLock lock(&access);
  ShadowBorderVertex *vertices=lock.vertices;
  memset(vertices,0,6*sizeof(ShadowBorderVertex));
  vertices[0].x=1.0f;vertices[0].y=1.0f;vertices[0].z=0.0f;
  vertices[1].x=1.0f;vertices[1].y=-1.0f;vertices[1].z=0.0f;
  vertices[2].x=-1.0f;vertices[2].y=1.0f;vertices[2].z=0.0f;
  vertices[3].x=1.0f;vertices[3].y=-1.0f;vertices[3].z=0.0f;
  vertices[4].x=-1.0f;vertices[4].y=1.0f;vertices[4].z=0.0f;
  vertices[5].x=-1.0f;vertices[5].y=-1.0f;vertices[5].z=0.0f;
 }
 DX8Wrapper::Set_Vertex_Buffer(access);
 int width,height,bits;bool windowed;
 WW3D::Get_Render_Target_Resolution(width,height,bits,windowed);
 for(int side=0;side<4;++side) {
  _D3DVIEWPORT8 viewport;
  viewport.X=0;viewport.Y=0;viewport.Width=width;viewport.Height=height;
  viewport.MinZ=0.0f;viewport.MaxZ=1.0f;
  if(side==0) viewport.Height=1;
  else if(side==1) {viewport.Y=height-1;viewport.Height=1;}
  else if(side==2) viewport.Width=1;
  else if(side==3) {viewport.X=width-1;viewport.Width=1;}
  DX8Wrapper::Set_Viewport(&viewport);
  int passes;
  if(shader->Begin(&passes,65535)) {
   for(int pass=0;pass<passes;++pass) {
    shader->BeginPass(pass);
    DX8Wrapper::bfmeRva00120650(0,2);
    shader->EndPass();
   }
   shader->End();
  }
 }
 _D3DVIEWPORT8 viewport;
 viewport.X=0;viewport.Y=0;viewport.Width=width;viewport.Height=height;
 viewport.MinZ=0.0f;viewport.MaxZ=1.0f;
 DX8Wrapper::Set_Viewport(&viewport);
}
