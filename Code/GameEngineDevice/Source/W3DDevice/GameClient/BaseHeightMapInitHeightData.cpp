// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// BaseHeightMapRenderObjClass::initHeightData, retail 0x0006D6D9..0x0006DB1C (1091 B, RET 0x10).
// Identity: WorldBuilder debug body (wb_show 0x6D6D9 --gd) has the ZH BaseHeightMap.cpp
// initHeightData spine with BFME2 taint/four texture layers/asset preload/DX lock; callees rowed.
// Codegen keys: REF_PTR_SET macro form fixes the map-store timing; a visible inline getHeight body
// (not inlined at /O1, so a COMDAT for 0x62A58) makes DX re-read and DY in edi; inline extent and
// border getters stop the 2*border CSE; AssetList inline ctor and separate << statements fix the
// asset block; the texture layers assign through a forced-inline TexSlot operator= so the slot
// address is formed before the loaded handle is pushed. Shader global 0xDB4140 is an extern.
#include "ascii_string.h"
#include <set>
class WorldHeightMap {
public:
 virtual void Delete_This();
 void Add_Ref() { refs++; }
 void Release_Ref() { refs--; if (refs == 0) Delete_This(); }
 // Keep prefix accessors inline without competing canonical getter copies.
 __declspec(dllimport) __forceinline int getXExtent(void) {return xExtent;}
 __declspec(dllimport) __forceinline int getYExtent(void) {return yExtent;}
 int getBorderSize(void) {return border;}
 int refs,xExtent,yExtent,border;
 char pad14[0x24-0x14]; unsigned short *data;
};
#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
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
class BaseHeightMapRenderObjClass;
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
class BoundedShortGrid {public:
 short load(int a,int b){int idx=m_stride*b+a;if(idx<0)return 0;if(idx>=m_capacity)return 0;if(m_data)return m_data[idx];return 0;}
 unsigned char m_unknown00[0x08];int m_stride;unsigned char m_unknown0C[0x20-0x0C];int m_capacity;short *m_data;};
#include "../../../../Libraries/Include/Lib/Region2D.h"
// Suppress this TU's non-retail copy of ??0?$set@PAURva001408C0Target@@U?$less@PAURva001408C0Target@@@_STL@@V?$allocator@PAURva001:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> set<Rva001408C0Target *,less<Rva001408C0Target *>,allocator<Rva001408C0Target *> >::set(); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_Rb_tree(const less<Rva001408C0Target *> &, const allocator<Rva001408C0Target *> &); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *, allocator<Rva001408C0Target *> >::_Rb_tree_base(const allocator<Rva001408C0Target *> &); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_erase(_Rb_tree_node<Rva001408C0Target *> *); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *, size_t) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEPAU?$_Rb_tre:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@U12@V?$alloc:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t); }
class TreeBoundsView {public:char pad[0x1948];Region2D bounds;};
class TextureBaseClass
{
public:
	void Release_Ref();
};
class TextureClass:public TextureBaseClass {};
template<class T>class RefCountPtr {
public:T*Referent;
 const RefCountPtr&operator=(const RefCountPtr&);
};
class BFME2ParticleTextureHandle {
public:TextureClass*Ptr;
 ~BFME2ParticleTextureHandle(){if(Ptr)Ptr->Release_Ref();}
};
#include "../../../Include/W3DDevice/GameClient/TextureAsset.h"
template<class T>class TexSlot:public RefCountPtr<T>{public:
 __forceinline TexSlot&operator=(const BFME2ParticleTextureHandle&h){RefCountPtr<T>::operator=(*(const RefCountPtr<T>*)&h);return *this;}};
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
#include "../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"
struct Rva001408C0Target;
struct AssetList00208F90
{
public:
	AssetList00208F90 &operator=(const AssetList00208F90 &other)
	{
		m_prototypes = other.m_prototypes;
		m_treeLayoutPad = other.m_treeLayoutPad;
		m_changed = other.m_changed;
		return *this;
	}
	// ??6AssetList00208F90@@QAEAAU0@ABVAsciiString@@@Z
	AssetList00208F90 &operator <<(const AsciiString &name);
	AssetList00208F90() : m_treeLayoutPad(0), m_changed(true) {}
	_STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > m_prototypes; // +0x00
	unsigned int m_treeLayoutPad; // +0x0C
	bool m_changed; // +0x10
	char m_pad11[0x3];
};
class Rva0006C995
{
public:
	Rva0006C995 *rva0006C995(Rva001408C0Target *p);
private:
	_STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > m_set; // +0x00
	char m_pad0C[0x4];
	unsigned char m_flag; // +0x10
	char m_pad11[0x3];
};
void bfmeMergeReceiverKeys(int);
class BfmeDynamicNativeVB;
class DX8IndexBufferClass;
class Rva000686F2
{
public:
	void rva000686F2();
	char m_pad00[0x37A4];
private:
	BfmeDynamicNativeVB *m_vb; // +0x37A4
	DX8IndexBufferClass *m_ib; // +0x37A8
	int m_37ac; // +0x37AC
	int m_37b0; // +0x37B0
	int m_37b4; // +0x37B4
	unsigned int m_37b8; // +0x37B8
	unsigned int m_37bc; // +0x37BC
};
#include "../../../../Libraries/Source/WWVegas/WW3D2/VertexMaterialClass.h"
// HeightMap.cpp's detail-blend shader (one ShaderBits dword).
class DX8Wrapper;
#include "../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"
extern ShaderClass detailOpaqueShader;
class BaseHeightMapRenderObjClass {
public:
 void rva0006B3F3();	// 0x0006B3F3 (BaseHeightMapScorchResources.cpp)
 virtual void gap000();
 virtual void gap001();
 virtual void gap002();
 virtual void gap003();
 virtual void gap004();
 virtual void gap005();
 virtual void gap006();
 virtual void gap007();
 virtual void gap008();
 virtual void gap009();
 virtual void gap010();
 virtual void gap011();
 virtual void gap012();
 virtual void gap013();
 virtual void gap014();
 virtual void gap015();
 virtual void gap016();
 virtual void gap017();
 virtual void gap018();
 virtual void gap019();
 virtual void gap020();
 virtual void gap021();
 virtual void gap022();
 virtual void gap023();
 virtual void gap024();
 virtual void gap025();
 virtual void gap026();
 virtual void gap027();
 virtual void gap028();
 virtual void gap029();
 virtual void gap030();
 virtual void gap031();
 virtual void gap032();
 virtual void gap033();
 virtual void gap034();
 virtual void gap035();
 virtual void gap036();
 virtual void gap037();
 virtual void gap038();
 virtual void gap039();
 virtual void gap040();
 virtual void gap041();
 virtual void gap042();
 virtual void gap043();
 virtual void gap044();
 virtual void gap045();
 virtual void gap046();
 virtual void gap047();
 virtual void gap048();
 virtual void gap049();
 virtual void gap050();
 virtual void gap051();
 virtual void gap052();
 virtual void gap053();
 virtual void gap054();
 virtual void gap055();
 virtual void gap056();
 virtual void gap057();
 virtual void gap058();
 virtual void gap059();
 virtual void gap060();
 virtual void gap061();
 virtual void gap062();
 virtual void gap063();
 virtual void gap064();
 virtual void gap065();
 virtual void gap066();
 virtual void gap067();
 virtual void gap068();
 virtual void gap069();
 virtual void gap070();
 virtual void gap071();
 virtual void gap072();
 virtual void gap073();
 virtual void gap074();
 virtual void gap075();
 virtual void gap076();
 virtual void gap077();
 virtual void gap078();
 virtual void gap079();
 virtual void gap080();
 virtual void gap081();
 virtual void gap082();
 virtual void gap083();
 virtual void gap084();
 virtual void gap085();
 virtual void gap086();
 virtual void gap087();
 virtual void gap088();
 virtual void gap089();
 virtual void gap090();
 virtual void gap091();
 virtual void gap092();
 virtual void gap093();
 virtual void gap094();
 virtual void gap095();
 virtual void gap096();
 virtual void gap097();
 virtual void gap098();
 virtual void gap099();
 virtual void gap100();
 virtual void gap101();
 virtual void gap102();
 virtual void gap103();
 virtual void gap104();
 virtual void Set_Force_Visible(bool);
 virtual void gap106();
 virtual void gap107();
 virtual void gap108();
 virtual void gap109();
 virtual void gap110();
 virtual void gap111();
 virtual void gap112();
 virtual void gap113();
 virtual void gap114();
 virtual void gap115();
 virtual void gap116();
 virtual void gap117();
 virtual void gap118();
 virtual void gap119();
 virtual void gap120();
 virtual void gap121();
 virtual void gap122();
 virtual void gap123();
 virtual void gap124();
 virtual void gap125();
 virtual void gap126();
 virtual void gap127();
 virtual void gap128();
 virtual void gap129();
 virtual void gap130();
 virtual void gap131();
 virtual void gap132();
 virtual void freeMapResources();
 virtual int initHeightData(int,int,WorldHeightMap*,void*);
private:
 char pad04[0xd8-4];int vertices,indices;
 char padE0[0x3794-0xe0];int scorches;
 char pad3798[0x37c0-0x3798];WorldHeightMap*map;
 char pad37C4[0x37d4-0x37c4];bool needFullUpdate;
 float minHeight,maxHeight;
 char pad37E0[0x3814-0x37e0];unsigned int shader;
 VertexMaterialClass*material;
 TexSlot<TextureClass> stageTwo;
 AsciiString stageTwoName,stageTwoDefault;
 TexSlot<TextureClass> stageThree;
 AsciiString macroName,macroDefault;
 bool flag;char pad3835[3];
 TexSlot<TextureClass> layer3;
 AsciiString layer3Name,layer3Default;
 TexSlot<TextureClass> layer4;
 AsciiString layer4Name,layer4Default;
 char pad3850[4];TreeBoundsView*treeBuffer;
 char pad3858[0x386c-0x3858];W3DRoadBuffer*roadBuffer;
 char pad3870[8];W3DShroud*shroud;W3DTaint*taint;
 bool terrainFlag;
};
#define REF_PTR_SET(dst,src) { if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }
int BaseHeightMapRenderObjClass::initHeightData(int x,int y,WorldHeightMap*pMap,void*lights)
{
 REF_PTR_SET(map,pMap);
 terrainFlag=false;
 if(shroud)shroud->init(map,TheWritableGlobalData->m_partitionCellSize,TheWritableGlobalData->m_partitionCellSize);
 if(taint)taint->init(map,TheWritableGlobalData->m_partitionCellSize,TheWritableGlobalData->m_partitionCellSize);
 roadBuffer->setMap(map);
 unsigned short*data=0;
 if(pMap)data=pMap->data;
 if(treeBuffer){
  Region2D bounds;
  bounds.lo.x=0;bounds.lo.y=0;
  bounds.hi.x=(pMap->getXExtent()-2*pMap->getBorderSize())*10.0f;
  bounds.hi.y=(pMap->getYExtent()-2*pMap->getBorderSize())*10.0f;
  treeBuffer->bounds=bounds;
 }
 if(pMap){
  int mapDX=pMap->getXExtent();
  int mapDY=pMap->getYExtent();
  int i,j,minHt,maxHt;
  minHt=65535;
  maxHt=0;
  for(j=0;j<mapDY;j++){
   for(i=0;i<mapDX;i++){
    unsigned short cur=((BoundedShortGrid*)pMap)->load(i,j);
    if(cur<minHt)minHt=cur;
    if(maxHt<cur)maxHt=cur;
   }
  }
  minHeight=minHt*0.0390625f;maxHeight=maxHt*0.0390625f;
 }
 Set_Force_Visible(true);
 needFullUpdate=true;
 scorches=0;vertices=0;indices=0;
 if(data && (!stageTwo.Referent || !stageThree.Referent || !layer3.Referent || !layer4.Referent)){
  freeMapResources();
  REF_PTR_SET(map,pMap);
  if(((StringBase<char>*)&macroName)->isEmpty())macroName=macroDefault;
  if(((StringBase<char>*)&stageTwoName)->isEmpty())stageTwoName=stageTwoDefault;
  if(((StringBase<char>*)&layer3Name)->isEmpty())layer3Name=layer3Default;
  if(((StringBase<char>*)&layer4Name)->isEmpty())layer4Name=layer4Default;
  AssetList00208F90 assets;
  assets<<macroName;
  assets<<stageTwoName;
  assets<<layer3Name;
  assets<<layer4Name;
  ((Rva0006C995*)&assets)->rva0006C995((Rva001408C0Target*)"exscorch01.tga");
  bfmeMergeReceiverKeys((int)&assets);
  stageTwo=TextureAsset::Get(stageTwoName.str(),0,0);
  stageThree=TextureAsset::Get(macroName.str(),0,0);
  {
   BFMEDX8DeviceLock lock;
   layer3=TextureAsset::Get(layer3Name.str(),0,0);
   layer4=TextureAsset::Get(layer4Name.str(),0,0);
   rva0006B3F3();
   ((Rva000686F2*)this)->rva000686F2();
   material=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
   shader=detailOpaqueShader.ShaderBits;
  }
 }
 return 0;
}
