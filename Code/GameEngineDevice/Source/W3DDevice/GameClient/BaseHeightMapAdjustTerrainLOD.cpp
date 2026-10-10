// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Target 0x0006669F..0x00066808, RET 4 (361 bytes). Zero Hour's
// BaseHeightMapRenderObjClass::adjustTerrainLOD (BaseHeightMap.cpp) in its
// BFME2 form: the LOD steps clamp to 1..7, automatic (8) becomes 7, and only
// the shaded HeightMap object is ever created (LOD 5 detaches the terrain);
// the flat variant and staticLightingChanged are gone. Evidence: the render
// object fields m_map at +0x37C0 (draw size at +0x120E8/+0x120EC), the scene
// at +0x78 (slots 3/15/2/14 are Remove_Render_Object/Unregister/
// Add_Render_Object/Register), the shroud at +0x3878 (reset 0x000731AE), the
// road buffer at +0x386C (loadRoads 0x000DD71C), the 0x393C-byte object built
// by 0x000E3BFE, and the tactical view angle nudge through view slots
// 0x100/0xFC. The singleton read at VA 0x00DEBC5C is the existing
// g_bfmeTaintModeView owner (W3DTaint.cpp names it by observed use only).

typedef int Int;

class RenderObjClass;

class SceneClass
{
public:
	virtual void s00(); virtual void s01(); virtual void Add_Render_Object(RenderObjClass *obj);
	virtual void Remove_Render_Object(RenderObjClass *obj);
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual void Register(RenderObjClass *obj, int for_what);
	virtual void Unregister(RenderObjClass *obj, int for_what);
};

class View
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void setAngle(float angle);
	virtual float getAngle();
};
extern View *TheTacticalView;

class GlobalData
{
public:
	char m_pad00[0x50];
	Int m_terrainLOD;
};
extern GlobalData *TheWritableGlobalData;

class W3DRoadBuffer { public: void loadRoads(); };
class Rva000731AE { public: void rva000731AE(); };

class Rva000E3BFE
{
public:
	Rva000E3BFE(bool);
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void s126();
	virtual void s127();
	virtual void s128();
	virtual void s129();
	virtual void s130();
	virtual void initHeightData(Int x, Int y, void *map, void *stripped);
	char m_pad04[0x386C - 4];
	W3DRoadBuffer *m_roadBuffer;	// +0x386C
	char m_pad3870[0x393C - 0x3870];
};

class BfmeTaintModeView;
extern BfmeTaintModeView *g_bfmeTaintModeView;
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class RenderObjClass
{
public:
	virtual void Notify_Added(SceneClass *scene);
};

struct WorldHeightMapView
{
	char m_pad00[0x120E8];
	Int m_drawWidth;	// +0x120E8
	Int m_drawHeight;	// +0x120EC
};

class BaseHeightMapRenderObjClass : public RenderObjClass
{
public:
	virtual void adjustTerrainLOD(Int adj);

private:
	char m_pad04[0x78 - 4];
	SceneClass *m_scene;	// +0x78
	char m_pad7C[0x37C0 - 0x7C];
	WorldHeightMapView *m_map;	// +0x37C0
	char m_pad37C4[0x3878 - 0x37C4];
	Rva000731AE *m_shroud;	// +0x3878
};

void BaseHeightMapRenderObjClass::adjustTerrainLOD(Int adj)
{
	if (adj > 0 && TheWritableGlobalData->m_terrainLOD < 7)
		TheWritableGlobalData->m_terrainLOD = TheWritableGlobalData->m_terrainLOD + 1;
	if (adj < 0 && TheWritableGlobalData->m_terrainLOD > 1)
		TheWritableGlobalData->m_terrainLOD = TheWritableGlobalData->m_terrainLOD - 1;

	if (TheWritableGlobalData->m_terrainLOD == 8)
		TheWritableGlobalData->m_terrainLOD = 7;

	if (m_map == 0)
		return;
	if (m_shroud)
		m_shroud->rva000731AE();

	Rva000E3BFE *newROBJ = (Rva000E3BFE *)g_bfmeTaintModeView;
	if (newROBJ == 0)
		newROBJ = new Rva000E3BFE(false);
	if (TheWritableGlobalData->m_terrainLOD == 5)
		newROBJ = 0;

	SceneClass *scene = m_scene;
	if (scene) {
		scene->Remove_Render_Object(this);
		scene->Unregister(this, 0);
		if (newROBJ) {
			scene->Add_Render_Object((RenderObjClass *)newROBJ);
			scene->Register((RenderObjClass *)newROBJ, 0);
		}
	}

	if (newROBJ) {
		newROBJ->initHeightData(m_map->m_drawWidth, m_map->m_drawHeight, m_map, 0);
		TheTerrainRenderObject = (BaseHeightMapRenderObjClass *)newROBJ;
		newROBJ->m_roadBuffer->loadRoads();
	}
	if (TheTacticalView) {
		TheTacticalView->setAngle(TheTacticalView->getAngle() + 1.0f);
		TheTacticalView->setAngle(TheTacticalView->getAngle() - 1.0f);
	}
}
