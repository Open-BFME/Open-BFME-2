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

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
namespace _STL {template<>_Bvector_base<allocator<bool> >::_Bvector_base(const allocator<bool>&) throw();}
#define BFME_RO_DTOR_DECL_ONLY
#include "rendobj.h"
#include "Snapshot.h"
class DX8_CleanupHook {public:DX8_CleanupHook(){}virtual void ReleaseResources()=0;virtual void ReAcquireResources()=0;};
class TScorch:public Snapshot {public:TScorch();virtual~TScorch(){}virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);unsigned char data[24];};
// The texture handles' unwind funclets (0x0075E810, 0x0075E855, ...) jump to
// the rowed release-if-non-null destructor 0x0017098D, which the destructor
// unit Rva0006D0D7Dtor.cpp emits as RefTex's; the other four strings at
// 0x3820/0x382C/0x383C/0x3848 are released through AsciiString's 0x0048BA39.
class RefTex {public:RefTex():data(0){}~RefTex();void *data;};
#include "ascii_string.h"
// Suppress this TU's non-retail copy of ??1?$_Bvector_base@V?$allocator@_N@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Bvector_base<allocator<bool> >::~_Bvector_base(); }
namespace _STL { template <> vector<bool, allocator<bool> >::~vector(); }
class W3DTreeBuffer {public:W3DTreeBuffer();char data[285800];};
class W3DShrubBuffer {public:W3DShrubBuffer();char data[332416];};
struct Coord3D;
class GeometryInfo;
class AsciiString;
#include "../../../Include/W3DDevice/GameClient/W3DPropBufferClass.h"
enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};
class Vector3;
class BaseHeightMapRenderObjClass;
class W3DBibBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void addBibDrawable(Vector3 corners[4], DrawableID id, bool highlight);
	void removeHighlighting();
	void clearAllBibs();
	void removeBib(ObjectID id);
	void removeBibDrawable(DrawableID id);
	void addBib(Vector3 corners[4], ObjectID id, bool highlight);
protected:
	void freeBibBuffers();
	void allocateBibBuffers();
public:
	W3DBibBuffer();
	~W3DBibBuffer();
	char data[68048]; // +0x00
};
class W3DBridgeBuffer {public:W3DBridgeBuffer();char data[55224];};
class Rva000E59D3 {public:Rva000E59D3();char data[36];};
class W3DWaypointBuffer
{
public:
	W3DWaypointBuffer();
	~W3DWaypointBuffer();
	char data[12]; // +0x00
};
class Rva000E0AE2
{
public:
	Rva000E0AE2();
	~Rva000E0AE2();
	char data[620]; // +0x00
};
class WorldHeightMap;
class W3DRoadBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void loadRoads();
protected:
	void freeRoadBuffers();
	void allocateRoadBuffers();
public:
	W3DRoadBuffer();
	~W3DRoadBuffer();
	void clearAllRoads();
	void setMap(WorldHeightMap*);
	char data[80]; // +0x00
};
class Rva000D3A17
{
public:
	Rva000D3A17();
	~Rva000D3A17();
	void rva000D3A17();
	char data[272]; // +0x00
};
#include "../../../Include/W3DDevice/GameClient/W3DShroudClass.h"
class W3DTaint
{
public:
	bool ReAcquireResources();
	~W3DTaint();
	W3DTaint();
	void init(WorldHeightMap*,float,float);
	char data[80]; // +0x00
};
class GlobalData;extern GlobalData*TheWritableGlobalData;
struct TerrainGlobalView {char data[0xC6A];bool useTaint;};
class Rva001E35DFView {public:const Rva001E35DFView*getFinalOverride()const{if(next)return next->getFinalOverride();return this;}void*unknown00;Rva001E35DFView*next;bool isOverride;};
class Rva00DFF488Setting:public Rva001E35DFView {public:char unknown0C[12];int m_transparentWaterDepth,m_minWaterOpacity;};
template<class T>class OVERRIDE {public:__forceinline operator const T*()const{if(!pointer)return 0;return(const T*)pointer->getFinalOverride();}__forceinline const T*operator->()const{if(!pointer)return 0;return(const T*)pointer->getFinalOverride();}const T*pointer;};
class WaterTransparencySetting;
extern OVERRIDE<WaterTransparencySetting>TheWaterTransparency;
class BaseHeightMapRenderObjClass;extern BaseHeightMapRenderObjClass*TheTerrainRenderObject;class DX8Wrapper {public:static void SetCleanupHook(DX8_CleanupHook*h){m_pCleanupHook=h;}protected:static DX8_CleanupHook*m_pCleanupHook;};
double Rva006C5BE0(double,int);
class BaseHeightMapRenderObjClass:public RenderObjClass,public DX8_CleanupHook,public Snapshot {public:
BaseHeightMapRenderObjClass();virtual~BaseHeightMapRenderObjClass();
virtual void ReleaseResources();virtual void ReAcquireResources();
virtual void loadPostProcess() = 0;virtual const char*GetSnapshotName()const = 0;virtual void xfer(Xfer*) = 0;
int x;
int y;
RefTex vertexScorch;
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
RefTex f381c;
AsciiString f3820;
AsciiString f3824;
RefTex f3828;
AsciiString f382c;
AsciiString f3830;
char pad3834[4];
RefTex f3838;
AsciiString f383c;
AsciiString f3840;
RefTex f3844;
AsciiString f3848;
AsciiString f384c;
W3DTreeBuffer* buffer0;
W3DShrubBuffer* buffer1;
W3DPropBuffer* buffer2;
W3DBibBuffer* buffer3;
Rva000E59D3* buffer5;
W3DWaypointBuffer* buffer6;
Rva000E0AE2* buffer7;
W3DRoadBuffer* buffer8;
W3DBridgeBuffer* buffer4;
Rva000D3A17* buffer9;
W3DShroud* buffer10;
W3DTaint* buffer11;
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
buffer1=new W3DShrubBuffer;
buffer2=0;
buffer2=new W3DPropBuffer;
buffer3=0;
buffer3=new W3DBibBuffer;
slope=89.9f;slope2=70.0f;
buffer4=0;
buffer4=new W3DBridgeBuffer;
buffer5=0;buffer5=new Rva000E59D3;
buffer6=new W3DWaypointBuffer;
buffer7=new Rva000E0AE2;
buffer8=0;
buffer8=new W3DRoadBuffer;
buffer9=0;
buffer9=new Rva000D3A17;
x=0;y=0;count=0;cached=0;unk3798=0;f37a4=0;f37a8=0;f37ac=0;
buffer10=new W3DShroud;
if(((const TerrainGlobalView*)TheWritableGlobalData)->useTaint)buffer11=new W3DTaint;else buffer11=0;
DX8Wrapper::SetCleanupHook(this);
f3824.set("TSCloudMed.tga");f3830.set("TSNoiseUrb.tga");f3840.set("TSTaintMed.tga");f384c.set("TSElvenMed.tga");
const OVERRIDE<Rva00DFF488Setting>&settings=(const OVERRIDE<Rva00DFF488Setting>&)TheWaterTransparency;
config1C=settings->m_minWaterOpacity;config18=settings->m_transparentWaterDepth;
initialized=true;
}
