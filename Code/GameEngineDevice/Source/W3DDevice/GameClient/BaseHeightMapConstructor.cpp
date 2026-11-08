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
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
// The texture handles' unwind funclets (0x0075E810, 0x0075E855, ...) jump to
// the rowed release-if-non-null destructor 0x0017098D (RefCountPtr<TextureClass>'s, rowed in
// streakRender.cpp; about 50 holder destructors fold there); the other four strings at
// 0x3820/0x382C/0x383C/0x3848 are released through AsciiString's 0x0048BA39.
class TextureBaseClass {public:void Release_Ref();};
class TextureClass:public TextureBaseClass {};
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
class Rva00DFF488Setting:public Rva001E35DFView {public:char unknown0C[12];float m_transparentWaterDepth,m_minWaterOpacity;};
template<class T>class OVERRIDE {public:__forceinline operator const T*()const{if(!pointer)return 0;return(const T*)pointer->getFinalOverride();}__forceinline const T*operator->()const{if(!pointer)return 0;return(const T*)pointer->getFinalOverride();}const T*pointer;};
class WaterTransparencySetting;
extern OVERRIDE<WaterTransparencySetting>TheWaterTransparency;
class BaseHeightMapRenderObjClass;extern BaseHeightMapRenderObjClass*TheTerrainRenderObject;class DX8Wrapper {public:static void SetCleanupHook(DX8_CleanupHook*h){m_pCleanupHook=h;}protected:static DX8_CleanupHook*m_pCleanupHook;};
double Rva006C5BE0(double,int);
BaseHeightMapRenderObjClass::BaseHeightMapRenderObjClass():field3814(0x10441B)
{
 m_disableTextures=false;m_showImpassableAreas=false;m_updating=false;
 double h=Rva006C5BE0(256.0,2);float zero=0;h-=1.0;m_minHeight=zero;m_maxHeight=h*0.0390625;_ReadWriteBarrier();
 field3818=0;m_map=0;field37C8=0;field37CC=0;field37D0=0;m_useDepthFade=false;TheTerrainRenderObject=this;
m_treeBuffer=0;
m_treeBuffer=new W3DTreeBuffer;
m_shrubBuffer=0;
m_shrubBuffer=new W3DShrubBuffer;
m_propBuffer=0;
m_propBuffer=new W3DPropBuffer;
m_bibBuffer=0;
m_bibBuffer=new W3DBibBuffer;
m_curImpassableSlope=89.9f;field37A0=70.0f;
m_bridgeBuffer=0;
m_bridgeBuffer=new W3DBridgeBuffer;
field3860=0;field3860=new Rva000E59D3;
m_waypointBuffer=new W3DWaypointBuffer;
field3868=new Rva000E0AE2;
m_roadBuffer=0;
m_roadBuffer=new W3DRoadBuffer;
field3874=0;
field3874=new Rva000D3A17;
m_vertexScorch=0;m_indexScorch=0;m_numScorches=0;m_scorchesInBuffer=0;field3798=0;field37A4=0;field37A8=0;field37AC=0;
m_shroud=new W3DShroud;
if(((const TerrainGlobalView*)TheWritableGlobalData)->useTaint)field387C=new W3DTaint;else field387C=0;
DX8Wrapper::SetCleanupHook(this);
field3824.set("TSCloudMed.tga");field3830.set("TSNoiseUrb.tga");field3840.set("TSTaintMed.tga");field384C.set("TSElvenMed.tga");
const OVERRIDE<Rva00DFF488Setting>&settings=(const OVERRIDE<Rva00DFF488Setting>&)TheWaterTransparency;
field37E8=settings->m_minWaterOpacity;field37E4=settings->m_transparentWaterDepth;
field3880=true;
}
