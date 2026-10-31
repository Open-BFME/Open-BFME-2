// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// Native4D9B6..4DB33 RET0; BF1 f989 W3DRadar::reconstructViewBox
// supplies four-corner projection and deltas. Target uses float radar points.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "W3DDevice/Common/W3DRadar.h"

struct BfmeRadarWorldPoint:Coord3D{BfmeRadarWorldPoint();~BfmeRadarWorldPoint();};
struct BfmeRadarMapPoint:Coord2D{BfmeRadarMapPoint();~BfmeRadarMapPoint();};
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
void W3DRadar::reconstructViewBox(){
BfmeRadarWorldPoint world[4];BfmeRadarMapPoint radar[4];int i;
((W3DRadarTacticalView*)TheTacticalView)->getScreenCornerWorldPointsAtZ(&world[0],&world[1],&world[2],&world[3],m_terrainAverageZ);
for(i=0;i<4;++i){radar[i].x=world[i].x/(m_mapExtent.width()/128);radar[i].y=world[i].y/(m_mapExtent.height()/128);
if(i==0){m_viewBox[i].x=0;m_viewBox[i].y=0;}else{m_viewBox[i].x=radar[i].x-radar[i-1].x;m_viewBox[i].y=radar[i].y-radar[i-1].y;}}
m_viewAngle=((W3DRadarTacticalView*)TheTacticalView)->getAngle();Coord3D pos;((W3DRadarTacticalView*)TheTacticalView)->getPosition(&pos);m_viewZoom=((W3DRadarTacticalView*)TheTacticalView)->getZoom();m_reconstructViewBox=false;
}
