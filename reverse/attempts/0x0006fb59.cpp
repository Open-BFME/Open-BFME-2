// ?rva0006FB59@RTS3DScene@@QAEXAAVRenderInfoClass@@PAVRenderObjClass@@H_N@Z
// partial score=0.8359247699 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
// ZH W3DScene.cpp renderOneObject supplies the semantic skeleton; native
// 6FB59..7054F determines BF2 additions and layout. Fourth stack arg unused.
class Vector3 {public:float X,Y,Z;Vector3(){}Vector3(float x,float y,float z):X(x),Y(y),Z(z){}__forceinline Vector3(const Vector3&v):X(v.X),Y(v.Y),Z(v.Z){}Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return *this;}void Set(float x,float y,float z){X=x;Y=y;Z=z;}static void Add(const Vector3&a,const Vector3&b,Vector3*c){c->X=a.X+b.X;c->Y=a.Y+b.Y;c->Z=a.Z+b.Z;}void Scale(const Vector3&v){X*=v.X;Y*=v.Y;Z*=v.Z;}};
class SphereClass{public:SphereClass(){}__forceinline SphereClass(const SphereClass&s):Center(s.Center),Radius(s.Radius){}Vector3 Center;float Radius;};
class Matrix3D{public:float m[12];};
class LightClass;
class LightEnvironmentClass{public:LightEnvironmentClass();~LightEnvironmentClass();void Add_Light(const LightClass&);void Pre_Render_Update(const Matrix3D&);char prefix[0x164];Vector3 OutputAmbient;char tail[0x228-0x170];};
class BfmeVecHF{public:float x,y,z;};class Gen_0094AC70{public:void bfmeSetPair(const BfmeVecHF*,const BfmeVecHF*);};
class MaterialPassClass;
namespace FXShader{class RenderingMethod;}
template<class T>class RefCountPtr{public:RefCountPtr();RefCountPtr(const RefCountPtr&);~RefCountPtr();T*p;};
class RenderInfoClass{public:void Push_Material_Pass(MaterialPassClass*);void Pop_Material_Pass();enum RINFO_OVERRIDE_FLAGS{ONLY_ADDITIONAL=4};void Push_Override_Flags(RINFO_OVERRIDE_FLAGS);void Pop_Override_Flags();void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod>);void Pop_Rendering_Method();class RenderObjClass*camera;char g04[4];Vector3 fog;char g14[0x10];float materialPassEmissiveOverride;LightEnvironmentClass*light_environment;};
class RefCountClass{public:virtual ~RefCountClass();int refs;};
class MultiListObjectClass{public:struct MultiListNodeClass*node;};
class RenderObjClass:public RefCountClass,public MultiListObjectClass{public:
virtual void slot001();
virtual void slot002();
virtual int Class_ID()const;
virtual void slot004();
virtual void slot005();
virtual void slot006();
virtual void slot007();
virtual void slot008();
virtual void slot009();
virtual void slot010();
virtual void slot011();
virtual void Render(RenderInfoClass&);
virtual void On_Frame_Update();
virtual void slot014();
virtual void slot015();
virtual void slot016();
virtual void slot017();
virtual void*Peek_Scene()const;
virtual void slot019();
virtual void Update_Cached_Bounding_Volumes()const;
virtual void slot021();
virtual void slot022();
virtual void slot023();
virtual void slot024();
virtual void slot025();
virtual void slot026();
virtual void slot027();
virtual void slot028();
virtual void slot029();
virtual void slot030();
virtual void slot031();
virtual void slot032();
virtual void slot033();
virtual void slot034();
virtual void slot035();
virtual void slot036();
virtual void slot037();
virtual void slot038();
virtual void slot039();
virtual void slot040();
virtual void slot041();
virtual void slot042();
virtual void slot043();
virtual void slot044();
virtual void slot045();
virtual void slot046();
virtual void slot047();
virtual void slot048();
virtual void slot049();
virtual void slot050();
virtual void slot051();
virtual void slot052();
virtual void slot053();
virtual void slot054();
virtual void slot055();
virtual void slot056();
virtual void slot057();
virtual void slot058();
virtual void slot059();
virtual void slot060();
virtual void slot061();
virtual void slot062();
virtual void slot063();
virtual void slot064();
virtual const SphereClass&Get_Bounding_Sphere()const;
virtual void slot066();
virtual void slot067();
virtual void slot068();
virtual void slot069();
virtual void slot070();
virtual void slot071();
virtual void slot072();
virtual void slot073();
virtual void slot074();
virtual void slot075();
virtual void slot076();
virtual void slot077();
virtual void slot078();
virtual void slot079();
virtual void slot080();
virtual void slot081();
virtual void slot082();
virtual void slot083();
virtual void slot084();
virtual void slot085();
virtual void slot086();
virtual void*Get_User_Data()const;
virtual void slot088();
virtual void slot089();
virtual void slot090();
virtual void slot091();
virtual void slot092();
virtual void slot093();
virtual void slot094();
virtual void slot095();
virtual int Is_Really_Visible()const;
virtual void slot097();
virtual void slot098();
virtual void slot099();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual void slot111();
virtual int Is_Infantry()const;
virtual void slot113();
virtual int TerrainMode()const;
Vector3 Get_Position()const;char g0c[0xc];Matrix3D transform;};
class LightClass:public RenderObjClass{public:char gap48[0xc4-0x48];int type;char gapc8[0x18];Vector3 diffuse;char gapec[0x144-0xec];bool enabled;void Get_Diffuse(Vector3*)const;void Set_Diffuse(const Vector3&v){diffuse=v;}};
struct MultiListNodeClass{MultiListNodeClass*prev,*next,*nextList;MultiListObjectClass*object;void*list;};
struct GenericMultiListClass{virtual ~GenericMultiListClass();MultiListNodeClass head;};
class RefRenderObjListIterator{public:RefRenderObjListIterator(GenericMultiListClass*l):list(l),cur(l->head.next){}bool Is_Done()const{return cur==&list->head;}void Next(){cur=cur->next;}RenderObjClass*Peek_Obj()const{return static_cast<RenderObjClass*>(cur->object);}GenericMultiListClass*list;MultiListNodeClass*cur;};
bool Spheres_Intersect(const SphereClass&,const SphereClass&);
enum CellShroudStatus{CELL_INVALID};class Object{public:CellShroudStatus getShroudStatusForPlayer(int)const;char gap[0x438];unsigned char status;};
class GameLogic{public:Object*findObjectByID(int);char gap[0x40];unsigned frame;};extern GameLogic*TheGameLogic;
class Rva00270260{public:bool rva00270260();};struct Rva0027070CData{float X,Y,Z;};class Rva0027070C{public:Rva0027070CData*rva0027070C();};class BfmeThingDDA{public:int bfmeGoDDA();};class BfmeThingDDB{public:int bfmeGoDDB();};
class Drawable{public:char gap[0x9c];Vector3 color;char gapA8[0xe4-0xa8];bool renderFlag;char gapE5[11];int renderMode;char gapF4[8];Object*object;char gap100[0x38];unsigned shroudClearFrame;char gap13C[0x28];int stealth;char gap168[0x358-0x168];float opacity;};
struct DrawableInfo{unsigned shroudStatusObjectID;Drawable*drawable;};
class SceneRenderGlobalView{public:char gap944[0x944];Vector3 lightAdjust;char gap950[0xbe8-0x950];unsigned char fogScaleDenominator,fogScaleNumerator;};class GlobalData;extern GlobalData*TheWritableGlobalData;
class Rva0027DA6A{public:bool rva0027DA6A(const Vector3&,Vector3*);};class SceneLightManagerView{public:char gap[0x1914];bool terrainPreview;};class TerrainLogic;extern TerrainLogic*TheTerrainLogic;
class DX8Wrapper{public:static bool FogEnable;};extern bool ShaderAlphaReferenceOverride;extern unsigned char ShaderAlphaReference;extern int g_Va00DBA4E4,g_Va00DB5FA0;
class W3DShroud{public:RefCountPtr<FXShader::RenderingMethod>rva0006F1FE();};class BaseHeightMapRenderObjClass;extern BaseHeightMapRenderObjClass*TheTerrainRenderObject;struct RenderTerrainView{char gap[0x3878];W3DShroud*shroud;};
class RTS3DScene{public:virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual const Vector3&Get_Ambient_Light()const;
 void rva0006FB59(RenderInfoClass&,RenderObjClass*,int,bool);
 char gap04[0x88];GenericMultiListClass LightList;char gapA4[0x70];GenericMultiListClass dynamicLights;char gap12C[4];LightClass*globalLight[4];char gap140[4];Vector3 infantryAmbient;LightClass*infantryLight[4];int numGlobalLights;LightEnvironmentClass fixedLightEnv,foggedLightEnv,infantryLightEnv;char gap7DC[4];MaterialPassClass*shroudPass,*heatVisionPass,*heatVisionOnlyPass;int customPassMode;
};
void RTS3DScene::rva0006FB59(RenderInfoClass&rinfo,RenderObjClass*robj,int localPlayerIndex,bool unused)
{
 Drawable*draw=0;DrawableInfo*drawInfo=0;Object*obj=0;int ss=0;bool drawableHidden=false;bool doExtraMaterialPop=false,doExtraFlagsPop=false;LightClass**sceneLights=globalLight;
 LightEnvironmentClass lightEnv;
 int needsUpdate=0;
 SphereClass sph=robj->Get_Bounding_Sphere();
 drawInfo=(DrawableInfo*)robj->Get_User_Data();
 if(drawInfo){draw=drawInfo->drawable;if(!draw)ss=3;}
 SceneRenderGlobalView*config=(SceneRenderGlobalView*)TheWritableGlobalData;
 float fogScale=(float)config->fogScaleNumerator/(float)config->fogScaleDenominator;
 if(DX8Wrapper::FogEnable)rinfo.fog=*(Vector3*)((char*)this+0x20);
 Vector3 ambient=Get_Ambient_Light();
 Vector3 lightMap;bool haveLightMap=false;
 if(TheTerrainLogic){Vector3 position=robj->Get_Position();Vector3 localLightMap;if(((Rva0027DA6A*)TheTerrainLogic)->rva0027DA6A(position,&localLightMap)){Vector3::Add(ambient,localLightMap,&ambient);lightMap=localLightMap;haveLightMap=true;}}
 if(draw&&(drawableHidden=((Rva00270260*)draw)->rva00270260())!=true){
  obj=draw->object;
  if(obj){ss=obj->getShroudStatusForPlayer(localPlayerIndex);if(ss==1)draw->shroudClearFrame=TheGameLogic->frame;
   else if(ss>=3&&draw->shroudClearFrame!=0){unsigned limit=2*g_Va00DBA4E4;if(obj->status&1)limit+=3*g_Va00DBA4E4;if(TheGameLogic->frame<limit+draw->shroudClearFrame)ss=2;}
   if(!robj->Peek_Scene())return;
  }else{ss=1;if(drawInfo->shroudStatusObjectID){Object*shroud=TheGameLogic->findObjectByID(drawInfo->shroudStatusObjectID);if(shroud&&shroud->getShroudStatusForPlayer(localPlayerIndex)>=3)ss=4;}}
  if(robj->Is_Infantry()){ambient=infantryAmbient;if(haveLightMap)Vector3::Add(ambient,lightMap,&ambient);sceneLights=infantryLight;}
  ((Gen_0094AC70*)&lightEnv)->bfmeSetPair((BfmeVecHF*)&sph.Center,(BfmeVecHF*)&ambient);
  Vector3*damage=(Vector3*)&draw->color;
  Vector3*filter=(Vector3*)((Rva0027070C*)draw)->rva0027070C();
  Vector3*tint=(Vector3*)((BfmeThingDDA*)draw)->bfmeGoDDA();
  Vector3*selection=(Vector3*)((BfmeThingDDB*)draw)->bfmeGoDDB();
  if(tint||selection||damage||filter||g_Va00DB5FA0<2){
   Vector3 sumTint(0,0,0),temp,restore;
   if(tint)Vector3::Add(sumTint,*tint,&sumTint);
   if(selection)Vector3::Add(sumTint,*selection,&sumTint);
   if(damage)Vector3::Add(sumTint,*damage,&sumTint);
   Vector3&multiplier=lightMap;multiplier.Set(1,1,1);if(filter)multiplier.Set(1-filter->X,1-filter->Y,1-filter->Z);
   if(g_Va00DB5FA0<2)multiplier.Scale(((SceneRenderGlobalView*)TheWritableGlobalData)->lightAdjust);
   for(int i=0;i<numGlobalLights;++i){sceneLights[i]->Get_Diffuse(&temp);restore=temp;Vector3::Add(temp,sumTint,&temp);temp.Scale(multiplier);sceneLights[i]->Set_Diffuse(temp);lightEnv.Add_Light(*sceneLights[i]);sceneLights[i]->Set_Diffuse(restore);}
   temp=lightEnv.OutputAmbient;Vector3::Add(sumTint,temp,&temp);temp.Scale(multiplier);lightEnv.OutputAmbient=temp;needsUpdate=true;
  }else for(int i=0;i<numGlobalLights;++i)lightEnv.Add_Light(*sceneLights[i]);
  if(draw->opacity!=0){rinfo.materialPassEmissiveOverride=draw->opacity+0.0f;if(draw->stealth==3){rinfo.Push_Override_Flags(RenderInfoClass::ONLY_ADDITIONAL);rinfo.Push_Material_Pass(heatVisionOnlyPass);doExtraFlagsPop=true;}else rinfo.Push_Material_Pass(heatVisionPass);doExtraMaterialPop=true;}
 }else{
  if(drawableHidden)return;
  if(ss==3){rinfo.light_environment=&foggedLightEnv;if(DX8Wrapper::FogEnable){Vector3 v=*(Vector3*)((char*)this+0x20);v.X*=fogScale;v.Y*=fogScale;v.Z*=fogScale;rinfo.fog=v;}robj->Render(rinfo);rinfo.light_environment=0;return;}
  if(robj->Is_Infantry()){ambient=infantryAmbient;if(haveLightMap)Vector3::Add(ambient,lightMap,&ambient);sceneLights=infantryLight;}
  ((Gen_0094AC70*)&lightEnv)->bfmeSetPair((BfmeVecHF*)&sph.Center,(BfmeVecHF*)&ambient);
  if(g_Va00DB5FA0<2){Vector3 scale=((SceneRenderGlobalView*)TheWritableGlobalData)->lightAdjust;for(int i=0;i<numGlobalLights;++i){Vector3 temp;sceneLights[i]->Get_Diffuse(&temp);Vector3 scaled=temp;scaled.Scale(scale);sceneLights[i]->Set_Diffuse(scaled);lightEnv.Add_Light(*sceneLights[i]);sceneLights[i]->Set_Diffuse(temp);}}
  else for(int i=0;i<numGlobalLights;++i)lightEnv.Add_Light(*sceneLights[i]);
 }
 if(!drawableHidden){
  RefRenderObjListIterator it2(&LightList);for(;!it2.Is_Done();it2.Next()){LightClass*light=(LightClass*)it2.Peek_Obj();SphereClass ls=light->Get_Bounding_Sphere();bool cull=light->type==0&&!Spheres_Intersect(sph,ls);if(!cull){lightEnv.Add_Light(*light);needsUpdate=true;}}
  RefRenderObjListIterator dyn(&dynamicLights);for(;!dyn.Is_Done();dyn.Next()){LightClass*light=(LightClass*)dyn.Peek_Obj();if(!light->enabled)continue;SphereClass ls=light->Get_Bounding_Sphere();if(light->type==0&&!Spheres_Intersect(sph,ls))continue;lightEnv.Add_Light(*(LightClass*)dyn.Peek_Obj());needsUpdate=true;}
  if(!needsUpdate&&!haveLightMap)rinfo.light_environment=robj->Is_Infantry()?&infantryLightEnv:&fixedLightEnv;
  else{rinfo.camera->Update_Cached_Bounding_Volumes();lightEnv.Pre_Render_Update(rinfo.camera->transform);rinfo.light_environment=&lightEnv;}
  if(draw&&draw->renderFlag){ShaderAlphaReferenceOverride=true;ShaderAlphaReference=(unsigned char)draw->renderMode;}else{ShaderAlphaReferenceOverride=false;ShaderAlphaReference=0x60;}
  if(drawInfo&&customPassMode==0&&ss>1){if(ss==2){rinfo.Push_Material_Pass(shroudPass);if(TheTerrainRenderObject&&((RenderTerrainView*)TheTerrainRenderObject)->shroud)rinfo.Push_Rendering_Method(((RenderTerrainView*)TheTerrainRenderObject)->shroud->rva0006F1FE());robj->Render(rinfo);if(TheTerrainRenderObject&&((RenderTerrainView*)TheTerrainRenderObject)->shroud)rinfo.Pop_Rendering_Method();rinfo.Pop_Material_Pass();}}
  else robj->Render(rinfo);
 }
 rinfo.light_environment=0;if(doExtraMaterialPop)rinfo.Pop_Material_Pass();if(doExtraFlagsPop)rinfo.Pop_Override_Flags();
}
