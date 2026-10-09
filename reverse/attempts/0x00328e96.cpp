// ?rva00328E96@@YAXAAVDataChunkInput@@HPAURva00328E96WaterRecord@@@Z
// partial score=0.93 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHs /ICode/Libraries/Include /D_CRTIMP= /Ireference/shims/bfme2_ascii
// Native328E96..32912D RET0 and WB BE0F10 establish this versioned water-area
// record reader. BF1 PolygonTrigger clean reader guides versioned name/layer,
// water/river and points; BF1 WaterTextureInit corroborates texture purposes.
// Target supplies all offsets and extended six-texture/color/polygon fields.
#include "ascii_string.h"
#include "Lib/Coord2D.h"
#include <stdlib.h>
class DataChunkInput {public:AsciiString readAsciiString();int readInt();unsigned char readByte();float readReal();};
struct RGBColor {float red,green,blue;void setFromInt(int);};
struct BfmeE8 {int a[2];};
class AreaPolygonBase {public:void reserve(int);};
class Rva0030B9DD {
public:Rva0030B9DD(int);
 // ?Rva0030B9DD::~Rva0030B9DD present-unmatched
 __forceinline ~Rva0030B9DD() {if(first)free(first);}
 BfmeE8 *first,*finish,*capacity;char opaque0c[0x28-12];int height;
};
struct Rva0030BA8C {void rva0030BA8C(const BfmeE8&);};
struct Rva0030B812 {void rva0030B812(Rva0030B812*);};
struct ElevatedAreaPolygon {void parse(DataChunkInput&,int);char opaque00[0x2c];};
class Rva001E35DFView {public:const Rva001E35DFView *getFinalOverride() const {if(next)return next->getFinalOverride();return this;}void *vptr;Rva001E35DFView *next;bool overrideFlag;};
class Rva00DFF488Setting : public Rva001E35DFView {public:char opaque0c[0x3c-12];AsciiString defaultTexture;float defaultHeight;};
template<class T>class OVERRIDE {public:operator const T*()const {if(!pointer)return 0;return (const T*)pointer->getFinalOverride();}const T *pointer;};
extern OVERRIDE<Rva00DFF488Setting> TheRva00DFF488Setting;
struct Rva00328E96WaterRecord {int id;AsciiString name,layer;bool river;int riverStart;AsciiString textures[6];bool colorEnabled;RGBColor color;float value3c,value40,height;ElevatedAreaPolygon polygon;bool water;};
void rva00328E96(DataChunkInput &file,int version,Rva00328E96WaterRecord *out) {
 out->name=file.readAsciiString();
 if(version>=4)out->layer=file.readAsciiString();else out->layer.clear();
 out->id=file.readInt();
 out->water=version>=2 ? file.readByte()!=0 : false;
 if(version>=3) {out->river=file.readByte()!=0;out->riverStart=file.readInt();}
 else {out->riverStart=0;out->river=false;}
 if(version>=5) {
  for(int i=0;i<6;++i)out->textures[i]=file.readAsciiString();
  out->colorEnabled=file.readByte()!=0;out->color.setFromInt(file.readInt());
  out->value3c=file.readReal();out->value40=file.readReal();out->height=file.readReal();
 } else {
  out->textures[0]=((const Rva00DFF488Setting*)TheRva00DFF488Setting)->defaultTexture;
  out->textures[1]="Noise0000.tga";out->textures[2]="TWAlphaEdge.tga";
  out->textures[3]="WaterSurfaceBubbles.tga";out->textures[4]="WaterRippleBump.tga";out->textures[5]="SkyEnv.tga";
  out->colorEnabled=false;RGBColor white={1.0f,1.0f,1.0f};out->color=white;
  out->value3c=0.06f;out->value40=0.06f;
  out->height=((const Rva00DFF488Setting*)TheRva00DFF488Setting)->defaultHeight;
 }
 if(version>=6)out->polygon.parse(file,1);
 else {
  Rva0030B9DD old(0);int points=file.readInt();((AreaPolygonBase*)&old)->reserve(points);
  while(points>0) {
   Coord2D point;point.x=(float)file.readInt();point.y=(float)file.readInt();old.height=file.readInt();
   ((Rva0030BA8C*)&old)->rva0030BA8C(*(const BfmeE8*)&point);--points;
  }
  ((Rva0030B812*)&out->polygon)->rva0030B812((Rva0030B812*)&old);
 }
}
