// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Target evidence: WorldBuilder identifies Init (17EF830) and ExternFunc
// (17F08B0) in W3DAptComponentColorPicker.cpp. Retail's 80-byte factory,
// ctor and two vftables establish the +8 secondary component base; Init
// uses its existing AptExternHandlerAdder at +18. The fields +60..+7C
// are independently witnessed by Init, ExternFunc and Render.
// No compatible BF1/ZH color-picker implementation was available. The
// callback binding follows the verified AptStrategicPlayerStatus idiom;
// its two-word multiple-inheritance method pointer and 16-byte binding
// are target facts established by the holder provider and retail copies.
// The scale getters retain their existing opaque integer-return ABI;
// their returned addresses and paired float fields are native evidence.
// All floor operations inline here; keep math.h's unused wrapper TU-local.
extern "C" { static float __cdecl floorf(float); }
#include "ascii_string.h"
#include <stdio.h>
#include "wwmath.h"
// Keep the same visible operation without emitting an O1 WWMath::Floor copy;
// lightenvironment.cpp owns the retail O2 body of that public member.
static inline float colorPickerFloor(float value) { return floorf(value); }
struct ColorFloatPoint {float x,y;ColorFloatPoint(float a=0,float b=0):x(a),y(b){}};
struct ColorIntPoint {int x,y; ColorIntPoint(int a,int b):x(a),y(b){} };
class Image {public:char pad[8];AsciiString filename;ColorIntPoint size;ColorFloatPoint uv;const ColorIntPoint *Get_Size() const{return &size;}const ColorFloatPoint *Get_UV() const{return &uv;}char pad1C[8];int width,height;};

class ImageCollection {public:const Image *findImageByName(const AsciiString&);};
extern ImageCollection *TheMappedImageCollection;
bool Rva004128F0GetParam(const char*,const char*,AsciiString&);
int Rva000A8F58Get();int Rva000A8F5EGet();
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);
struct FunctorBinding {
 FunctorBinding(FunctorMethod method,FunctorTarget *target):m_target(target),m_method(method){}
 FunctorTarget *m_target;unsigned m_pad;FunctorMethod m_method;
};
__forceinline FunctorBinding MakeBinding(FunctorMethod method,FunctorTarget *target){FunctorBinding b(method,target);return b;}
struct FunctorWrapperHead {void*vtable;int count;};
class Rva0057BC63FunctorHolder {public:Rva0057BC63FunctorHolder(const FunctorBinding&);FunctorWrapperHead*m_ptr;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T>class AptRef:public Rva0057BC63FunctorHolder {public:AptRef(const FunctorBinding&b):Rva0057BC63FunctorHolder(b){}~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}};
class AptExternHandler;
class AptExternHandlerAdder {public:void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>);private:void *start,*end,*limit;};
class ColorRefBase {public:virtual ~ColorRefBase();private:int refs;};
class Rva005248D0 {public:virtual ~Rva005248D0();protected:char p0C[0xC];AptExternHandlerAdder externHandlers;char rest[0x3C];};
class W3DAptComponentColorPicker:public ColorRefBase,public Rva005248D0 {
public:virtual ~W3DAptComponentColorPicker();virtual void Init(const AsciiString&,const char*);virtual void Render(int,int,int,int);void ExternFunc(int,char*,bool);
private:const Image*image;AsciiString owner;float scaleWidth,scaleHeight;unsigned color;bool sample,seek;char p76[2];int cursorX,cursorY;
};
class Display;extern Display *TheDisplay;
class W3DDisplay {public:void rva0004D6B3(Image*,float,float,float,float,int,int);};
class TextureClass {public:void Release_Ref();};
class BFME2ParticleTextureHandle {public:TextureClass *Ptr;~BFME2ParticleTextureHandle(){if(Ptr)Ptr->Release_Ref();}};
struct TextureAsset {static BFME2ParticleTextureHandle Get(const char *,int,int);};
class W3DRadarResetSurface {public:void *ptr;~W3DRadarResetSurface();};
struct CursorTextureSlot {W3DRadarResetSurface Get_Surface_Level();};
class SurfaceClass {public:struct SurfaceDescription {unsigned Format,Width,Height;};void Get_Description(SurfaceDescription &);};
class Rva001166E0 {public:void *rva001166E0(int *,int,int,int,int);};
class Member0C00739C70 {public:void clear();};
struct ColorSurfaceLock {
 W3DRadarResetSurface *surface;
 __forceinline ColorSurfaceLock(W3DRadarResetSurface &w3DRadarResetSurface,int *pitch,int left,int top,int right,int bottom,void *&pixels):surface(&w3DRadarResetSurface) {pixels=((Rva001166E0*)&w3DRadarResetSurface)->rva001166E0(pitch,left,top,right,bottom);}
 ~ColorSurfaceLock(){((Member0C00739C70*)surface)->clear();}
};
class Rva00222A8BTarget;extern Rva00222A8BTarget *TheRva00222A8BTarget;
int Rva007410ECInvoke(Rva00222A8BTarget *,void *,const char *,const char *,const unsigned &);
int Rva00525235Fire(void *,void *,const char *,const char *,int *,int *);
int Rva00740EA1DistanceSquared(const unsigned char *,const unsigned char *);
static __forceinline const char *colorName(const AsciiString &asciiString) {char *buf=*(char * const *)&asciiString;return buf?buf+8:"";}

void W3DAptComponentColorPicker::Init(const AsciiString&name,const char*params) {
 Rva004128F0GetParam(params,"_path",owner);
 AsciiString imageName;
 Rva004128F0GetParam(params,"_imageName",imageName);
 image=TheMappedImageCollection->findImageByName(imageName);
 if(!image)return;
 cursorX=image->width;cursorY=image->height;
 AsciiString callbackName(name);reinterpret_cast<StringBase<char> *>(&callbackName)->concat("Cursor");
 externHandlers.AddExternHandler(callbackName,0,MakeBinding(reinterpret_cast<FunctorMethod>(&W3DAptComponentColorPicker::ExternFunc),reinterpret_cast<FunctorTarget*>(this)));
 callbackName=name;reinterpret_cast<StringBase<char> *>(&callbackName)->concat("Color");
 externHandlers.AddExternHandler(callbackName,1,MakeBinding(reinterpret_cast<FunctorMethod>(&W3DAptComponentColorPicker::ExternFunc),reinterpret_cast<FunctorTarget*>(this)));
}
void W3DAptComponentColorPicker::ExternFunc(int slot,char*value,bool write) {
 switch(slot){
 case 0:
  if(write){float x=0,y=0;sscanf(value,"%f %f",&x,&y);const ColorFloatPoint*factor=reinterpret_cast<const ColorFloatPoint*>(Rva000A8F58Get());scaleWidth=x*factor->x;scaleHeight=y*factor->y;sample=true;}
  else {float x=scaleWidth,y=scaleHeight;const ColorFloatPoint*factor=reinterpret_cast<const ColorFloatPoint*>(Rva000A8F5EGet());_snprintf(value,255,"%f %f",x*factor->x,y*factor->y);}
  break;
 case 1:
  if(write){sscanf(value,"%u",&color);seek=true;}else _snprintf(value,255,"%u",color);
  break;
 }
}

// ?Render@W3DAptComponentColorPicker@@UAEXHHHH@Z, retail 0x00741152..0x0074159E
// (1100 B): WB 0x017EFB40 (W3DAptComponentColorPicker.cpp lines 166..232).
// Draws the picker image, then on a sample request reads the pixel under the
// cursor (A8R8G8B8 surfaces only) and reports SetColor, and on a seek request
// scans the cursor rectangle for the pixel nearest the current colour and
// reports SetCursor. Frame homes (VC7.1 packs by liveness and reference
// weight, not declaration order): block 1's descriptor scope ends before its
// format test, the seek descriptor lives for the whole function, the nearest
// pixel is two scalars and the cursor point has its own block. WB compares
// desc.m_Format directly; the format copy-out is inferred from the frame.
void W3DAptComponentColorPicker::Render(int x,int y,int width,int height) {
 SurfaceClass::SurfaceDescription seekDesc;
 ((W3DDisplay*)TheDisplay)->rva0004D6B3(const_cast<Image*>(image),(float)x,(float)y,(float)(x+width),(float)(y+height),-1,5);
 if(sample) {
  if(!image)return;
  BFME2ParticleTextureHandle texture=TextureAsset::Get(colorName(image->filename),1,0);
  W3DRadarResetSurface surface=((CursorTextureSlot*)&texture)->Get_Surface_Level();
  unsigned format;
  {
  SurfaceClass::SurfaceDescription desc;
  ((SurfaceClass*)&surface)->Get_Description(desc);
  format=desc.Format;
  }
  if(format!=21)return;
  float rw=scaleWidth,rh=scaleHeight;
  float sx=width?((float)cursorX/(float)width)*rw:0.0f;
  float sy=height?((float)cursorY/(float)height)*rh:0.0f;
  const ColorFloatPoint *uv=image->Get_UV();
  if(!uv)return;
  const ColorIntPoint *textureSize=image->Get_Size();
  if(!textureSize)return;
  ColorFloatPoint pos(sx,sy);
  pos.x+=(float)textureSize->x*uv->x;
  pos.y+=(float)textureSize->y*uv->y;
  ColorIntPoint point((int)pos.x,(int)pos.y);
  int pitch;
  void *voidPtr;
  ColorSurfaceLock lock(surface,&pitch,point.x,point.y,point.x+1,point.y+1,voidPtr);
  if(!voidPtr)return;
  color=*(unsigned*)voidPtr;
  Rva007410ECInvoke(TheRva00222A8BTarget,(void*)14,colorName(owner),"SetColor",color);
  sample=false;
 }
 if(seek) {
  if(!image)return;
  BFME2ParticleTextureHandle texture=TextureAsset::Get(colorName(image->filename),1,0);
  W3DRadarResetSurface surface=((CursorTextureSlot*)&texture)->Get_Surface_Level();
  ((SurfaceClass*)&surface)->Get_Description(seekDesc);
  if(seekDesc.Format!=21)return;
  const ColorFloatPoint *uv=image->Get_UV();
  if(!uv)return;
  const ColorIntPoint *textureSize=image->Get_Size();
  if(!textureSize)return;
  int left=WWMath::Float_To_Long(colorPickerFloor((float)textureSize->x*uv->x+0.5f));
  int top=WWMath::Float_To_Long(colorPickerFloor((float)textureSize->y*uv->y+0.5f));
  int pitch;
  void *voidPtr;
  ColorSurfaceLock lock(surface,&pitch,left,top,left+cursorX,top+cursorY,voidPtr);
  if(!voidPtr)return;
  unsigned char *pixel=(unsigned char*)voidPtr;
  int nearestX=0,nearestY=0;
  unsigned best=0x7fffffff;
  for(int j=0;j<cursorY;++j) {
   unsigned char *rowStart=pixel;
   for(int i=0;i<cursorX;++i) {
    unsigned distance=(unsigned)Rva00740EA1DistanceSquared(pixel,(unsigned char*)&color);
    if(distance<best){best=distance;nearestX=i;nearestY=j;}
    pixel+=4;
   }
   pixel=rowStart+pitch;
  }
  ColorFloatPoint offset(0.0f,0.0f);
  if(cursorX) offset.x=((float)nearestX*(float)width)/(float)cursorX; else offset.x=0.0f;
  if(cursorY) offset.y=((float)nearestY*(float)height)/(float)cursorY; else offset.y=0.0f;
  const ColorFloatPoint *scale=(const ColorFloatPoint*)Rva000A8F5EGet();
  {
  ColorIntPoint cursor(WWMath::Float_To_Long(colorPickerFloor(offset.x*scale->x+0.5f)),WWMath::Float_To_Long(colorPickerFloor(offset.y*scale->y+0.5f)));
  Rva00525235Fire(TheRva00222A8BTarget,(void*)14,colorName(owner),"SetCursor",&cursor.x,&cursor.y);
  }
  seek=false;
 }
}
