// ?rva0007054F@RTS3DScene@@UAEXAAVRenderInfoClass@@@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
// Source guide: pinned BFME1 f98983a7d GeneralsMD W3DScene.cpp Customized_Render.
// Target facts: whole7054F..70841 RET4, scene vslot5C calls this from71E40,
// UpdateList74/head78 and RenderListEC/headF0; BFME2 pass3..7 branches read
// render-object slots1C0/1C8/1D0 and global shader override. No ZH layout
// is asserted as a target fact. Iterator Current_Object wrapper retains the
// donor null-adjustment shape; common mode7/mode0 call must follow both guards.
// Render helper6FB59 is separately bounded2550B, four stack arguments; original
// helper name remains unknown and its fourth argument is unused in retail.
class Vector3{public:float X,Y,Z;Vector3(){}Vector3(const Vector3&v):X(v.X),Y(v.Y),Z(v.Z){}Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return *this;}};
class RenderObjClass;
class RenderInfoClass{public:RenderObjClass*camera;char gap4[4];Vector3 FogColor;char gap14[0x14];void*light_environment;};
class RefCountClass{public:virtual ~RefCountClass();int refs;};class MultiListObjectClass{public:struct MultiListNodeClass*node;};
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
virtual void slot018();
virtual void slot019();
virtual void slot020();
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
virtual void slot065();
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
virtual void Set_User_Data(void*,bool);
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
virtual void slot115();
virtual int OnlyEmissive()const;
};
struct DrawableInfo{unsigned shroudStatusObjectID;void*drawable;unsigned gap8;unsigned flags;};
struct MultiListNodeClass{MultiListNodeClass*prev,*next,*nextList;MultiListObjectClass*object;void*list;};
class GenericMultiListClass{public:virtual ~GenericMultiListClass();MultiListNodeClass Head;};
class RefRenderObjListIterator{public:RefRenderObjListIterator(GenericMultiListClass*l):List(l),CurNode(l->Head.next){}bool Is_Done()const{return CurNode==&List->Head;}void Next(){CurNode=CurNode->next;}MultiListObjectClass*Current_Object()const{return CurNode->object;}RenderObjClass*Peek_Obj()const{return (RenderObjClass*)Current_Object();}GenericMultiListClass*List;MultiListNodeClass*CurNode;};
class PlayerList;extern PlayerList*ThePlayerList;struct ScenePlayerView{char gap[0x54];int index;};struct ScenePlayerListView{char gap[0x10];ScenePlayerView*local;};
class TerrainLogic;extern TerrainLogic*TheTerrainLogic;struct SceneTerrainView{char gap[0x1914];bool preview;};
class GlobalData;extern GlobalData*TheWritableGlobalData;struct SceneGlobalView{char gap[0xd34];bool modeD34;char gapD35[15];bool skipTerrain;};
class DX8Wrapper{public:static bool FogEnable;};extern bool bfmeCameraProjectionOverride,bfmeOnlyEmissiveDraws;// Neutral modeling name for the unowned bool at native DE1EB8; original identity unknown.
extern bool SceneModeOverride;
class WW3D{static bool IsCurrentlyRenderingShadowMap;public:static bool Is_Rendering_Shadow_Map(){return IsCurrentlyRenderingShadowMap;}};
extern int Rva00309E4BGet();struct SceneWaterView{char gap[0x20];bool active;};
class W3DShadowManager;extern W3DShadowManager*TheW3DShadowManager;
class ParticleSystemManager;extern ParticleSystemManager*TheParticleSystemManager;
struct SceneShadowView{bool update;};class SceneParticlesView{public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();virtual void v17();virtual void v18();};
class RTS3DScene{public:
virtual void slot000();
virtual void slot001();
virtual void slot002();
virtual void slot003();
virtual void slot004();
virtual void slot005();
virtual void slot006();
virtual void slot007();
virtual void slot008();
virtual void slot009();
virtual void slot010();
virtual void slot011();
virtual void slot012();
virtual void slot013();
virtual void slot014();
virtual void slot015();
virtual void slot016();
virtual void slot017();
virtual void slot018();
virtual void slot019();
virtual void slot020();
virtual void slot021();
virtual void slot022();
virtual void rva0007054F(RenderInfoClass&);
virtual void slot024();
virtual void slot025();
virtual void slot026();
virtual void Visibility_Check(RenderObjClass*);
void rva0006FB59(RenderInfoClass&,RenderObjClass*,int,bool);char gap4[0x14];int polygonMode;char gap1C[4];Vector3 FogColor;char gap2C[0x48];GenericMultiListClass UpdateList;char gap8C[0x60];GenericMultiListClass RenderList;char gap104[0x28];bool drawTerrainOnly;char gap12D[0x7EC-0x12D];int customPassMode;int translucentCount;char gap7F4[4];int occludedCount;};
void RTS3DScene::rva0007054F(RenderInfoClass&rinfo)
{
 RenderObjClass*terrainObject=0,*robj;
 translucentCount=0;occludedCount=0;
 int localPlayerIndex=ThePlayerList?((ScenePlayerListView*)ThePlayerList)->local->index:0;
 if(DX8Wrapper::FogEnable)rinfo.FogColor=FogColor;
 if(customPassMode==0)Visibility_Check(rinfo.camera);
 int preview=0;if(TheTerrainLogic)preview=((SceneTerrainView*)TheTerrainLogic)->preview;
 if(customPassMode==0){
  RefRenderObjListIterator it(&UpdateList);
  for(;!it.Is_Done();it.Next()){
   robj=it.Peek_Obj();if(robj->Class_ID()==4){terrainObject=robj;if(preview)continue;}
   if(!bfmeCameraProjectionOverride&&!WW3D::Is_Rendering_Shadow_Map())it.Peek_Obj()->On_Frame_Update();
  }
  if(terrainObject&&!((SceneGlobalView*)TheWritableGlobalData)->skipTerrain&&!preview){
   rinfo.light_environment=0;rinfo.camera->Set_User_Data(this,false);
   if(customPassMode==3||customPassMode==4){if(terrainObject->TerrainMode()||((SceneWaterView*)Rva00309E4BGet())->active)terrainObject->Render(rinfo);}
   else if(customPassMode!=5&&customPassMode!=7&&customPassMode!=6)terrainObject->Render(rinfo);
  }
 }
 if(drawTerrainOnly||customPassMode==4)return;
 RefRenderObjListIterator it(&RenderList);
 while(!it.Is_Done()){
  robj=it.Peek_Obj();it.Next();
  if(robj->Class_ID()==4)continue;
  if(!robj->Is_Really_Visible())continue;
  if(customPassMode==3||customPassMode==5||customPassMode==6){
   if(((SceneGlobalView*)TheWritableGlobalData)->modeD34){
    bool infantry=robj->Is_Infantry()!=0;if(customPassMode==6&&!infantry)continue;if(customPassMode==5&&infantry)continue;
    rva0006FB59(rinfo,robj,localPlayerIndex,false);
   }else if(robj->TerrainMode()){
    bfmeOnlyEmissiveDraws=robj->OnlyEmissive()!=0;rva0006FB59(rinfo,robj,localPlayerIndex,false);bfmeOnlyEmissiveDraws=false;
   }
   continue;
  }
  if(customPassMode==7){
   bool infantry=robj->Is_Infantry()!=0;if(SceneModeOverride)infantry=true;if(!infantry)continue;
  }else if(customPassMode==0){
   DrawableInfo*info=(DrawableInfo*)robj->Get_User_Data();if(info&&info->drawable&&(info->flags&0x1e))continue;
  }else{robj->Render(rinfo);continue;}
  rva0006FB59(rinfo,robj,localPlayerIndex,false);
 }
 if(TheW3DShadowManager){if(!terrainObject)return;if(!bfmeCameraProjectionOverride&&polygonMode==0&&customPassMode==0)((SceneShadowView*)TheW3DShadowManager)->update=true;}
 if(terrainObject&&TheParticleSystemManager&&polygonMode==0&&customPassMode==0)((SceneParticlesView*)TheParticleSystemManager)->v18();
}
