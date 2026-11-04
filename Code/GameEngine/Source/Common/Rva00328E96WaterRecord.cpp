// ?rva00328E96@@YAXAAVDataChunkInput@@HPAURva00328E96WaterRecord@@@Z @ 0x00328E96 (663B)
// Versioned water-area record reader: version 4+ name/layer, version 2+ water
// flag, version 3+ river/start, version 5+ six textures plus colour and the
// three real fields, version 6+ polygon parse; older versions fall back to the
// WaterTransparency defaults. The dead AsciiString in the version<6 else branch
// is the gen_eh_if0 closure that restores the action-less EH states. Ported from
// the W7-S1 t1search exact scratch source; no pins added.
// cl: /O1 /G7 /arch:SSE /MD /EHs /ICode/Libraries/Include /D_CRTIMP= /Ireference/shims/bfme2_ascii
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// Native328E96..32912D RET0 and WB BE0F10 establish this versioned water-area
// record reader. BF1 PolygonTrigger clean reader guides versioned name/layer,
// water/river and points; BF1 WaterTextureInit corroborates texture purposes.
// Target supplies all offsets and extended six-texture/color/polygon fields.
#include "ascii_string.h"
#include "Lib/Coord2D.h"
#include "Lib/RGBColor.h"
namespace _STL { void free(void*); }
#include "../../Include/Common/DataChunk.h"
struct BfmeE8 
{
 int a[2];
 
}
;
class AreaPolygonBase 
{
 public:void reserve(int);
 
}
;
class Rva0030B9DD 
{
 public:Rva0030B9DD(int);
// ?Rva0030B9DD::~Rva0030B9DD present-unmatched
 ~Rva0030B9DD() 
 {
  if(first)_STL::free(first);
 }
 BfmeE8 *first,*finish,*capacity;
 char opaque0c[0x28-12];
 int height;
 
}
;
struct Rva0030BA8C 
{
 void rva0030BA8C(const BfmeE8&);
 
}
;
struct Rva0030B812 
{
 void rva0030B812(Rva0030B812*);
 
}
;
struct ElevatedAreaPolygon 
{
 void parse(DataChunkInput&,int);
 char opaque00[0x2c];
 
}
;
#include "../../Include/GameClient/Water.h"
template<class T>class OVERRIDE 
{
 public: __declspec(dllimport) __forceinline operator const T*()const 
 {
  if(!pointer)return 0;
  return (const T*)pointer->getFinalOverride();
  
 }
 const T *pointer;
 
}
;
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
struct Rva00328E96WaterRecord 
{
 int id;
 AsciiString name,layer;
 bool river;
 int riverStart;
 AsciiString textures[6];
 bool colorEnabled;
 RGBColor color;
 float value3c,value40,height;
 ElevatedAreaPolygon polygon;
 bool water;
 
}
;
void rva00328E96(DataChunkInput &file,int version,Rva00328E96WaterRecord *out) 
{
 out->name=file.readAsciiString();
 if(version>=4)out->layer=file.readAsciiString();
 else ((StringBase<char>*)&out->layer)->clear();
 out->id=file.readInt();
 if(version>=2)out->water=file.readByte()!=0;
 else out->water=false;
 if(version>=3) 
 {
  out->river=file.readByte()!=0;
  out->riverStart=file.readInt();
  
 }
 else 
 {
  out->riverStart=0;
  out->river=false;
  
 }
 if(version>=5) 
 {
  for(int i=0;i<6;++i)out->textures[i]=file.readAsciiString();
  out->colorEnabled=file.readByte()!=0;
  out->color.setFromInt(file.readInt());
  out->value3c=file.readReal();
  out->value40=file.readReal();
  out->height=file.readReal();
  
 }
 else 
 {
  out->textures[0]=((const WaterTransparencySetting*)TheWaterTransparency)->m_standingWaterTexture;
  out->textures[1]="Noise0000.tga";
  out->textures[2]="TWAlphaEdge.tga";
  out->textures[3]="WaterSurfaceBubbles.tga";
  out->textures[4]="WaterRippleBump.tga";
  out->textures[5]="SkyEnv.tga";
  out->colorEnabled=false;
  RGBColor white=
  {
   1.0f,1.0f,1.0f
  }
  ;
  out->color=white;
  _ReadWriteBarrier();
  static const float defaultRippleScale=0.06f;
  out->value3c=*(const volatile float*)&defaultRippleScale;
  out->value40=*(const volatile float*)&defaultRippleScale;
  out->height=((const WaterTransparencySetting*)TheWaterTransparency)->m_riverTransparencyMultiplier;
  
 }
 if(version>=6)out->polygon.parse(file,1);
 else 
 {
  Rva0030B9DD old(0);
  int points=file.readInt();
  ((AreaPolygonBase*)&old)->reserve(points);
  while(points>0) 
  {
   Coord2D point;
   point.x=(float)file.readInt();
   point.y=(float)file.readInt();
   old.height=file.readInt();
   ((Rva0030BA8C*)&old)->rva0030BA8C(*(const BfmeE8*)&point);
   --points;
   
  }
 if (0) { AsciiString t1_dead; }
  ((Rva0030B812*)&out->polygon)->rva0030B812((Rva0030B812*)&old);
  
 }
 
}
