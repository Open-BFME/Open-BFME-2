// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
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
#include "ascii_string.h"
extern "C" __declspec(dllimport) int __cdecl sscanf(const char*,const char*,...);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char*,unsigned int,const char*,...);
class Image {public:char p24[0x24];int width,height;};
class ImageCollection {public:const Image *findImageByName(const AsciiString&);};
extern ImageCollection *TheImageCollection;
bool Rva004128F0GetParam(const char*,const char*,AsciiString&);
int Rva000A8F58Get();int Rva000A8F5EGet();
struct ColorFloatPoint {float x,y;};
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
void W3DAptComponentColorPicker::Init(const AsciiString&name,const char*params) {
 Rva004128F0GetParam(params,"_path",owner);
 AsciiString imageName;
 Rva004128F0GetParam(params,"_imageName",imageName);
 image=TheImageCollection->findImageByName(imageName);
 if(!image)return;
 cursorX=image->width;cursorY=image->height;
 AsciiString callbackName(name);callbackName.concat("Cursor");
 externHandlers.AddExternHandler(callbackName,0,MakeBinding(reinterpret_cast<FunctorMethod>(&W3DAptComponentColorPicker::ExternFunc),reinterpret_cast<FunctorTarget*>(this)));
 callbackName=name;callbackName.concat("Color");
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
