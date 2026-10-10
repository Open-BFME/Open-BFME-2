// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2renderobj /DNDEBUG /DBFME_SNAPSHOT_NAME_SLOT /D_OPERATOR_NEW_DEFINED_ /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/shims/moduledata/Common
// stlport
// Native6C9CF..6CE57 complete1160B constructor. Snapshot slot2 at BC5D98
// returns the BaseHeightMapRenderObjClass name; primary tableBC5DB0 and
// RenderObj constructor13BF00 establish owner and bases C4/C8.
// Reference ZH BaseHeightMap.cpp ctor (BF1 donor575ba2b04) establishes terrain
// initialization purpose and buffer roles. Target offsets, additional buffers,
// allocation sizes, texture names, two height bytes and configuration fields
// come from native. Unidentified buffer types retain callee-derived names.
// Integer override fields18/1C are copied as words; no original option names
// are asserted. The float-zero local and store fence preserve native x87/SSE
// scheduling; no data, headers or compiler machinery changed.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
namespace _STL {template<>_Bvector_base<allocator<bool> >::_Bvector_base(const allocator<bool>&) throw();}
#include "rendobj.h"
#include "Snapshot.h"
class DX8_CleanupHook {public:DX8_CleanupHook(){}virtual void ReleaseResources()=0;virtual void ReAcquireResources()=0;};
class TScorch:public Snapshot {public:TScorch();virtual~TScorch(){}virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);unsigned char data[24];};
class TerrainRef {public:TerrainRef():data(0){}~TerrainRef();void *data;};
#include "ascii_string.h"
class W3DTreeBuffer {public:W3DTreeBuffer();char data[285800];};
class Rva000E9C1D {public:Rva000E9C1D();char data[332416];};
class W3DPropBuffer {public:W3DPropBuffer();char data[194344];};
class W3DBibBuffer {public:W3DBibBuffer();char data[68048];};
class W3DBridgeBuffer {public:W3DBridgeBuffer();char data[55224];};
class Rva000E5A47 {public:Rva000E5A47();char data[36];};
class W3DWaypointBuffer {public:W3DWaypointBuffer();char data[12];};
class Rva000E0AE2 {public:Rva000E0AE2();char data[620];};
class W3DRoadBuffer {public:W3DRoadBuffer();char data[80];};
class Rva000D3A17 {public:Rva000D3A17();char data[272];};
class W3DShroud {public:W3DShroud();char data[88];};
class Rva00074136 {public:Rva00074136();char data[80];};
class GlobalData;extern GlobalData*TheWritableGlobalData;
struct TerrainGlobalView {char data[0xC6A];bool useTaint;};
class Rva001E35DFView {public:const Rva001E35DFView*getFinalOverride()const{if(next)return next->getFinalOverride();return this;}void*unknown00;Rva001E35DFView*next;bool isOverride;};
class Rva00DFF488Setting:public Rva001E35DFView {public:char unknown0C[12];int field18,field1C;};
template<class T>class OVERRIDE {public:operator const T*()const{if(!pointer)return 0;return(const T*)pointer->getFinalOverride();}const T*operator->()const{if(!pointer)return 0;return(const T*)pointer->getFinalOverride();}const T*pointer;};
extern OVERRIDE<Rva00DFF488Setting>TheRva00DFF488Setting;
class BaseHeightMapRenderObjClass;extern BaseHeightMapRenderObjClass*TheTerrainRenderObject;extern DX8_CleanupHook*TerrainCleanupHook;
double Rva006C5BE0(double,int);
class BaseHeightMapRenderObjClass:public RenderObjClass,public DX8_CleanupHook,public Snapshot {public:
BaseHeightMapRenderObjClass();virtual~BaseHeightMapRenderObjClass();
virtual void ReleaseResources();virtual void ReAcquireResources();
virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
int x;
int y;
TerrainRef vertexScorch;
void* indexScorch;
void* scorchTexture;
TScorch scorches[500];
int count;
int cached;
int unk3798;
float slope;
float slope2;
int f37a4;
int f37a8;
int f37ac;
char pad37B0[16];
void* map;
bool useDepthFade;
bool updating;
char pad37C6[2];
float depthX;
float depthY;
float depthZ;
bool disableTextures;
char pad37D5[3];
float minHeight;
float maxHeight;
bool showImpassable;
char pad37E1[3];
int config18;
int config1C;
std::vector<bool> flags1;
std::vector<bool> flags2;
unsigned shader;
int f3818;
TerrainRef f381c;
TerrainRef f3820;
AsciiString f3824;
TerrainRef f3828;
TerrainRef f382c;
AsciiString f3830;
char pad3834[4];
TerrainRef f3838;
TerrainRef f383c;
AsciiString f3840;
TerrainRef f3844;
TerrainRef f3848;
AsciiString f384c;
W3DTreeBuffer* buffer0;
Rva000E9C1D* buffer1;
W3DPropBuffer* buffer2;
W3DBibBuffer* buffer3;
Rva000E5A47* buffer5;
W3DWaypointBuffer* buffer6;
Rva000E0AE2* buffer7;
W3DRoadBuffer* buffer8;
W3DBridgeBuffer* buffer4;
Rva000D3A17* buffer9;
W3DShroud* buffer10;
Rva00074136* buffer11;
bool initialized;
};
BaseHeightMapRenderObjClass::BaseHeightMapRenderObjClass():shader(0x10441B)
{
 disableTextures=false;showImpassable=false;updating=false;
 double h=Rva006C5BE0(256.0,2);float zero=0;h-=1.0;minHeight=zero;maxHeight=h*0.0390625;_ReadWriteBarrier();
 f3818=0;map=0;depthX=0;depthY=0;depthZ=0;useDepthFade=false;TheTerrainRenderObject=this;
buffer0=0;
buffer0=new W3DTreeBuffer;
buffer1=0;
buffer1=new Rva000E9C1D;
buffer2=0;
buffer2=new W3DPropBuffer;
buffer3=0;
buffer3=new W3DBibBuffer;
slope=89.9f;slope2=70.0f;
buffer4=0;
buffer4=new W3DBridgeBuffer;
buffer5=0;buffer5=new Rva000E5A47;
buffer6=new W3DWaypointBuffer;
buffer7=new Rva000E0AE2;
buffer8=0;
buffer8=new W3DRoadBuffer;
buffer9=0;
buffer9=new Rva000D3A17;
x=0;y=0;count=0;cached=0;unk3798=0;f37a4=0;f37a8=0;f37ac=0;
buffer10=new W3DShroud;
if(((const TerrainGlobalView*)TheWritableGlobalData)->useTaint)buffer11=new Rva00074136;else buffer11=0;
TerrainCleanupHook=this;
f3824.set("TSCloudMed.tga");f3830.set("TSNoiseUrb.tga");f3840.set("TSTaintMed.tga");f384c.set("TSElvenMed.tga");
config1C=TheRva00DFF488Setting->field1C;config18=TheRva00DFF488Setting->field18;
initialized=true;
}
