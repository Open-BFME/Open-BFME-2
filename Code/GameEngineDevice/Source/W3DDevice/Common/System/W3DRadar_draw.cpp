// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
//
// ?draw@W3DRadar@@QAEXHHHHH@Z, retail 0x0005053e, 1314 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native [0x0005053E,0x00050A60),1314B, RET20. BFME1 W3DRadar::draw
// at f98983a7d3bb405f1a4ba94bb6a2a168062a819d and GeneralsMD W3DRadar.cpp
// guide the aspect bars, overlay refresh, texture layers and view-box order.
// Target evidence supplies alpha argument5, clipping and dirty-overlay checks,
// exact fields14/18/1434..1498/14D4..14DF, and view slots64/73. Existing Radar
// ctor/dtor at2D87B9/2D7CED prove Snapshot + twelve-byte SubsystemInterface.
// Its existing BFME2 subsystem header is used unchanged.
// Direct callee interfaces are target facts, not inferred from byte matching:
// 50125..5053E RET12 receives list/texture-slot/colour under Radar ECX;
// 4E5A2..4E704 RET20 walks64 events of stride50 at+2C and projects pings;
// 4DBD5..4DDBF RET20 projects the four view corners and forwards to2D55D2.
// The last two take the same origin/dimensions/unused-colour stack arguments.
// Reconstruction banks preserve their implementations and remaining codegen
// blockers; their direct in-image pins add no recovered callee bytes.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "W3DDevice/Common/W3DRadar.h"

// BFME's offset of the local player, reached through the real ThePlayerList.
class W3DRadarPlayerListView
{
public:
	Player *bfme_local_player() { return m_local; }
	char m_pad00[0x10];
	Player *m_local; // +0x10
};
// BFME's Display slots, reached through the real TheDisplay.
class W3DRadarDisplayView{public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void setClip(void*);
virtual void slot43();
virtual void resetClip(void*);
};
class W3DDisplay{public:void rva0004D664(float,float,float,float,float,int);void rva0004D6B3(Image*,float,float,float,float,int,int);};
class Rva0004263F{public:void rva0004263F(float,float,float,float,int);};
// BFME's View slots, reached through the real TheTacticalView.
class W3DRadarTacticalView{public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void getScreenCornerWorldPointsAtZ(Coord3D*,Coord3D*,Coord3D*,Coord3D*,float);
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual float getAngle();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void getPosition(Coord3D*);
virtual void slot71();
virtual void slot72();
virtual float getZoom();
};
class BeaconClientFrame
{
public:
#define SLOT(N) virtual void slot##N();
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6)
    SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12)
    SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18)
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
#undef SLOT
    virtual unsigned getFrame();
};

class GameClient;
extern GameClient *TheGameClient;
int Rva0004D76EBlend(int,int);
void W3DRadar::draw(int pixelX,int pixelY,int width,int height,int color){
Player*player=((W3DRadarPlayerListView *)ThePlayerList)->m_local;
if(!player->hasRadar()&&!*(bool*)((char*)TheRadar+0x11))return;
if(m_clip)((W3DRadarDisplayView *)TheDisplay)->setClip(m_clipRect);
ICoord2D ul,lr;findDrawPositions(pixelX,pixelY,width,height,&ul,&lr);
int scaledWidth=lr.x-ul.x,scaledHeight=lr.y-ul.y;
if(!m_useAltTerrainTexture&&!m_scrollShroudLoaded){int fillColor=Rva0004D76EBlend(0xff000000,color);int lineColor=Rva0004D76EBlend(0xff323232,color);
if(m_mapExtent.width()/width>=m_mapExtent.height()/height){
((Rva0004263F*)TheDisplay)->rva0004263F(pixelX,pixelY,width,ul.y-pixelY-1,fillColor);
((Rva0004263F*)TheDisplay)->rva0004263F(pixelX,lr.y+1,width,pixelY+height-lr.y-1,fillColor);
((W3DDisplay*)TheDisplay)->rva0004D664(pixelX,ul.y,pixelX+width,ul.y,1,lineColor);
((W3DDisplay*)TheDisplay)->rva0004D664(pixelX,lr.y+1,pixelX+width,lr.y+1,1,lineColor);
}else{
((Rva0004263F*)TheDisplay)->rva0004263F(pixelX,pixelY,ul.x-pixelX-1,height,fillColor);
((Rva0004263F*)TheDisplay)->rva0004263F(lr.x+1,pixelY,width-(lr.x-pixelX)-1,height,fillColor);
((W3DDisplay*)TheDisplay)->rva0004D664(ul.x,pixelY,ul.x,pixelY+height,1,lineColor);
((W3DDisplay*)TheDisplay)->rva0004D664(lr.x+1,pixelY,lr.x+1,pixelY+height,1,lineColor);
}}
((W3DDisplay*)TheDisplay)->rva0004D6B3(m_terrainImage,ul.x,ul.y,lr.x,lr.y,color,2);
if(m_dirty||reinterpret_cast<BeaconClientFrame *>(TheGameClient)->getFrame()%6==0){
m_overlayTexture.Get_Surface_Level().clear(false);
rva00050125(m_objectList,&m_overlayTexture,color);rva00050125(m_localObjectList,&m_overlayTexture,color);
}
((W3DDisplay*)TheDisplay)->rva0004D6B3(m_fogImage,ul.x,ul.y,lr.x,lr.y,color,2);
((W3DDisplay*)TheDisplay)->rva0004D6B3(m_overlayImage,ul.x,ul.y,lr.x,lr.y,color,2);
((W3DDisplay*)TheDisplay)->rva0004D6B3(m_shroudImage,pixelX,pixelY,pixelX+width,pixelY+height,color,2);
drawEvents(ul.x,ul.y,scaledWidth,scaledHeight,color);
rva0004F515(ul.x,ul.y,scaledWidth,scaledHeight);
if(((W3DRadarTacticalView*)TheTacticalView)->getZoom()!=m_viewZoom)m_reconstructViewBox=true;
if(((W3DRadarTacticalView*)TheTacticalView)->getAngle()!=m_viewAngle)m_reconstructViewBox=true;
if(m_reconstructViewBox==true)reconstructViewBox();
drawViewBox(ul.x,ul.y,scaledWidth,scaledHeight,color);
if(m_clip)((W3DRadarDisplayView *)TheDisplay)->resetClip(0);
m_dirty=false;
}
