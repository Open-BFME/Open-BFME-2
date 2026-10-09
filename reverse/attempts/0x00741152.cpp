// ?Render@W3DAptComponentColorPicker@@UAEXHHHH@Z
// partial score=0.9665714285714286 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
extern "C" __declspec(dllimport) double __cdecl floor(double);
struct ColorIntPoint {int x,y; ColorIntPoint(int a,int b):x(a),y(b){} };
struct ColorFloatPoint {float x,y;};
class Image {public:char pad[8];AsciiString filename;ColorIntPoint size;ColorFloatPoint uv;const ColorIntPoint *Get_Size() const{return &size;}const ColorFloatPoint *Get_UV() const{return &uv;}};
class Display;extern Display *TheDisplay;
class W3DDisplay {public:void rva0004D6B3(Image*,float,float,float,float,int,int);};
class TextureClass {public:void Release_Ref();};
class BFME2ParticleTextureHandle {public:TextureClass *Ptr;~BFME2ParticleTextureHandle(){if(Ptr)Ptr->Release_Ref();}};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *,int,int);
class W3DRadarResetSurface {public:void *ptr;~W3DRadarResetSurface();};
struct CursorTextureSlot {W3DRadarResetSurface Get_Surface_Level();};
class SurfaceClass {public:struct SurfaceDescription {unsigned Format,Width,Height;};void Get_Description(SurfaceDescription &);};
class Rva001166E0 {public:void *rva001166E0(int *,int,int,int,int);};
class Member0C00739C70 {public:void clear();};
struct ColorSurfaceLock {
 W3DRadarResetSurface *surface;
 __forceinline ColorSurfaceLock(W3DRadarResetSurface &s,int *pitch,int x0,int y0,int x1,int y1,void *&pixels):surface(&s) {pixels=((Rva001166E0*)&s)->rva001166E0(pitch,x0,y0,x1,y1);}
 ~ColorSurfaceLock(){((Member0C00739C70*)surface)->clear();}
};
class Rva00222A8BTarget;extern Rva00222A8BTarget *TheRva00222A8BTarget;
int Rva007410ECInvoke(Rva00222A8BTarget *,void *,const char *,const char *,const unsigned &);
int Rva00525235Fire(void *,void *,const char *,const char *,int *,int *);
int Rva00740EA1DistanceSquared(const unsigned char *,const unsigned char *);
int Rva000A8F5EGet();
static __forceinline const char *colorName(const AsciiString &s) {char *p=*(char * const *)&s;return p?p+8:"";}
static __forceinline int colorRound(float f) {int i;__asm {
 fld f
 fistp i
 }return i;}
class W3DAptComponentColorPicker {public:virtual void p0();virtual void p1();virtual void Render(int,int,int,int);char p[0x5C];Image *image;AsciiString owner;float scaleWidth,scaleHeight;unsigned color;bool sample,seek;char p76[2];int cursorX,cursorY;};
void W3DAptComponentColorPicker::Render(int x,int y,int width,int height) {
 ((W3DDisplay*)TheDisplay)->rva0004D6B3(image,(float)x,(float)y,(float)(x+width),(float)(y+height),-1,5);
 if(sample) {
  if(!image)return;
  BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(colorName(image->filename),1,0);
  W3DRadarResetSurface surface=((CursorTextureSlot*)&texture)->Get_Surface_Level();
  SurfaceClass::SurfaceDescription desc;
  ((SurfaceClass*)&surface)->Get_Description(desc);
  if(desc.Format!=21)return;
  float rw=scaleWidth,rh=scaleHeight;
  float sx=width?((float)cursorX/(float)width)*rw:0.0f;
  float sy=height?((float)cursorY/(float)height)*rh:0.0f;
  const ColorFloatPoint *uv=image->Get_UV();
  if(!uv)return;
  const ColorIntPoint *size=image->Get_Size();
  if(!size)return;
  float fx=(float)size->x*uv->x+sx; float fy=(float)size->y*uv->y+sy; ColorIntPoint point((int)fx,(int)fy);
  int pitch;
  void *pixels;
  ColorSurfaceLock lock(surface,&pitch,point.x,point.y,point.x+1,point.y+1,pixels);
  if(!pixels)return;
  color=*(unsigned*)pixels;
  Rva007410ECInvoke(TheRva00222A8BTarget,(void*)14,colorName(owner),"SetColor",color);
  sample=false;
 }
 if(seek) {
  if(!image)return;
  BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(colorName(image->filename),1,0);
  W3DRadarResetSurface surface=((CursorTextureSlot*)&texture)->Get_Surface_Level();
  SurfaceClass::SurfaceDescription desc;
  ((SurfaceClass*)&surface)->Get_Description(desc);
  if(desc.Format!=21)return;
  const ColorFloatPoint *uv=image->Get_UV();
  if(!uv)return;
  const ColorIntPoint *size=image->Get_Size();
  if(!size)return;
  int left=colorRound((float)floor((float)size->x*uv->x+0.5f));
  int top=colorRound((float)floor((float)size->y*uv->y+0.5f));
  int pitch;
  void *pixels;
  ColorSurfaceLock lock(surface,&pitch,left,top,left+cursorX,top+cursorY,pixels);
  if(!pixels)return;
  int bestX=0,bestY=0;unsigned best=0x7fffffff;
  unsigned char *pixel=(unsigned char*)pixels;
  for(int j=0;j<cursorY;++j) {
   unsigned char *rowStart=pixel;
   for(int i=0;i<cursorX;++i) {
    unsigned distance=(unsigned)Rva00740EA1DistanceSquared(pixel,(unsigned char*)&color);
    if(distance<best){best=distance;bestX=i;bestY=j;}
    pixel+=4;
   }
   pixel=rowStart+pitch;
  }
  float ox=cursorX?((float)bestX*(float)width)/(float)cursorX:0.0f;
  float oy=cursorY?((float)bestY*(float)height)/(float)cursorY:0.0f;
  const ColorFloatPoint *screenScale=(const ColorFloatPoint*)Rva000A8F5EGet();
  ColorIntPoint cursor(colorRound((float)floor(ox*screenScale->x+0.5f)),colorRound((float)floor(oy*screenScale->y+0.5f)));
  Rva00525235Fire(TheRva00222A8BTarget,(void*)14,colorName(owner),"SetCursor",&cursor.x,&cursor.y);
  seek=false;
 }
}
