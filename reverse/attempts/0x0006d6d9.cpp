// ?initHeightData@BaseHeightMapRenderObjClass@@QAEHHHPAVWorldHeightMap@@PAX@Z
// partial score=0.8688652430169018 date=2026-10-09
// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG /MD /EHsc
// stlport
#include "ascii_string.h"
#include <set>
class WorldHeightMap {
public:
 virtual void Delete_This();
 int refs,xExtent,yExtent,border;
 char pad14[0x24-0x14]; unsigned short *data;
};
class GlobalData {public: char pad[0xd4];float partitionCellSize;};
extern GlobalData *TheWritableGlobalData;
class W3DShroud {public:void init(WorldHeightMap*,float,float);};
class W3DTaint {public:void init(WorldHeightMap*,float,float);};
class W3DRoadBuffer {public:void setMap(WorldHeightMap*);};
class BoundedShortGrid {public:short rva00062A58(int,int);};
struct Region2D {struct Point {float x,y;}lo,hi;};
class TreeBoundsView {public:char pad[0x1948];Region2D bounds;};
class TextureBaseClass {public:void Release_Ref();};
class TextureClass:public TextureBaseClass {};
template<class T>class RefCountPtr {
public:T*Referent;
 const RefCountPtr&operator=(const RefCountPtr&);
};
class BFME2ParticleTextureHandle {
public:TextureClass*Ptr;
 ~BFME2ParticleTextureHandle(){if(Ptr)Ptr->Release_Ref();}
};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct BFMEDX8DeviceLock {
 BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();}
 ~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();}
};
struct Rva001408C0Target;
struct AssetList00208F90 {
 std::set<Rva001408C0Target*> m_prototypes;
 unsigned int m_treeLayoutPad;bool m_changed;
 AssetList00208F90&operator<<(const AsciiString&);
};
class Rva0006C995 {public:Rva0006C995*rva0006C995(Rva001408C0Target*);};
void bfmeMergeReceiverKeys(int);
class Rva00067878 {public:void rva0006B3F3();};
class Rva000686F2 {public:void rva000686F2();};
class VertexMaterialClass {public:enum PresetType{PRELIT_DIFFUSE};static VertexMaterialClass*Get_Preset(PresetType);};
extern unsigned int detailOpaqueShader;
class BaseHeightMapRenderObjClass {
public:
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
 int initHeightData(int,int,WorldHeightMap*,void*);
private:
 char pad04[0xd8-4];int vertices,indices;
 char padE0[0x3794-0xe0];int scorches;
 char pad3798[0x37c0-0x3798];WorldHeightMap*map;
 char pad37C4[0x37d4-0x37c4];bool needFullUpdate;
 float minHeight,maxHeight;
 char pad37E0[0x3814-0x37e0];unsigned int shader;
 VertexMaterialClass*material;
 RefCountPtr<TextureClass> stageTwo;
 AsciiString stageTwoName,stageTwoDefault;
 RefCountPtr<TextureClass> stageThree;
 AsciiString macroName,macroDefault;
 bool flag;char pad3835[3];
 RefCountPtr<TextureClass> layer3;
 AsciiString layer3Name,layer3Default;
 RefCountPtr<TextureClass> layer4;
 AsciiString layer4Name,layer4Default;
 char pad3850[4];TreeBoundsView*treeBuffer;
 char pad3858[0x386c-0x3858];W3DRoadBuffer*roadBuffer;
 char pad3870[8];W3DShroud*shroud;W3DTaint*taint;
 bool terrainFlag;
};
static __forceinline void setMapRef(WorldHeightMap*&dest,WorldHeightMap*src) {
 if(src)++src->refs;
 WorldHeightMap*old=dest;
 if(old && --old->refs==0)old->Delete_This();
 dest=src;
}
int BaseHeightMapRenderObjClass::initHeightData(int x,int y,WorldHeightMap*pMap,void*lights)
{
 setMapRef(map,pMap);
 terrainFlag=false;
 if(shroud)shroud->init(pMap,TheWritableGlobalData->partitionCellSize,TheWritableGlobalData->partitionCellSize);
 if(taint)taint->init(map,TheWritableGlobalData->partitionCellSize,TheWritableGlobalData->partitionCellSize);
 roadBuffer->setMap(map);
 unsigned short*data=0;
 if(pMap)data=pMap->data;
 if(treeBuffer){
  Region2D bounds;
  int border=pMap->border,xExtent=pMap->xExtent,yExtent=pMap->yExtent;
  bounds.lo.x=0;bounds.lo.y=0;
  bounds.hi.x=(xExtent-2*border)*10.0f;
  bounds.hi.y=(yExtent-2*border)*10.0f;
  treeBuffer->bounds=bounds;
 }
 if(pMap){
  int mapDY=pMap->yExtent;
  int maxHt=0;int minHt=65535;
  for(int j=0;j<mapDY;++j)for(int i=0;i<pMap->xExtent;++i){
   unsigned short cur=((BoundedShortGrid*)pMap)->rva00062A58(i,j);
   if(cur<minHt)minHt=cur;
   if(maxHt<cur)maxHt=cur;
  }
  minHeight=minHt*0.0390625f;maxHeight=maxHt*0.0390625f;
 }
 Set_Force_Visible(true);needFullUpdate=true;
 scorches=0;vertices=0;indices=0;
 if(data && (!stageTwo.Referent || !stageThree.Referent || !layer3.Referent || !layer4.Referent)){
  freeMapResources();setMapRef(map,pMap);
  if(((StringBase<char>*)&macroName)->isEmpty())macroName=macroDefault;
  if(((StringBase<char>*)&stageTwoName)->isEmpty())stageTwoName=stageTwoDefault;
  if(((StringBase<char>*)&layer3Name)->isEmpty())layer3Name=layer3Default;
  if(((StringBase<char>*)&layer4Name)->isEmpty())layer4Name=layer4Default;
  AssetList00208F90 assets;assets.m_treeLayoutPad=0;assets.m_changed=true;
  assets<<macroName<<stageTwoName<<layer3Name<<layer4Name;
  ((Rva0006C995*)&assets)->rva0006C995((Rva001408C0Target*)"exscorch01.tga");
  bfmeMergeReceiverKeys((int)&assets);
  stageTwo=*(RefCountPtr<TextureClass>*)&BFME2LoadParticleTexture(stageTwoName.str(),0,0);
  stageThree=*(RefCountPtr<TextureClass>*)&BFME2LoadParticleTexture(macroName.str(),0,0);
  {
   BFMEDX8DeviceLock lock;
   layer3=*(RefCountPtr<TextureClass>*)&BFME2LoadParticleTexture(layer3Name.str(),0,0);
   layer4=*(RefCountPtr<TextureClass>*)&BFME2LoadParticleTexture(layer4Name.str(),0,0);
   ((Rva00067878*)this)->rva0006B3F3();
   ((Rva000686F2*)this)->rva000686F2();
   material=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
   shader=detailOpaqueShader;
  }
 }
 return 0;
}
