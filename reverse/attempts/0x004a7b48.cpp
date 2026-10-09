// ?update@MissileUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9826050638015957 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include "Code/Libraries/Include/Lib/Coord3D.h"
extern "C" double __cdecl sqrt(double);
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff};
enum PathfindLayerEnum {GROUND_LAYER=0,BRIDGE_LAYER=1};
class Thing {public:virtual void anchor();void setPosition(const Coord3D*);const Coord3D *getPosition()const{return &m_position;}char pad[0x34];Coord3D m_position;};
struct MissilePoint:public Coord3D {MissilePoint(const Coord3D &p){x=p.x;y=p.y;z=p.z;}void setXY(const Coord3D&p,float height){x=p.x;y=p.y;z=height;}};
class Object:public Thing {public:int rva0028B511()const;void rva0028B4CE(PathfindLayerEnum);};
class GameLogic {public:void destroyObject(Object*);};extern GameLogic *TheGameLogic;
class TerrainLogic {public:virtual ~TerrainLogic();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual float getGroundHeight(float,float,Coord3D*)const;virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D*,bool)const;PathfindLayerEnum getHighestLayerForDestination(const Coord3D*,bool);};extern TerrainLogic *TheTerrainLogic;
class MissilePrimary {public:virtual void anchor();const void *data;Object *object;};
class MissileOther {public:virtual void anchor();};
class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};
class MissileProjectileInterface {public:virtual void slot0();virtual bool slot1();};
class MissileProjectileOther {public:virtual void slot0();};
class MissileModule:public MissilePrimary,public MissileOther,public UpdateModuleInterface {unsigned updateFields[3];};
class BezierProjectileBehavior:public MissileModule,public MissileProjectileInterface,public MissileProjectileOther {public:virtual UpdateSleepTime update();char baseTail[0x88-0x28];};
class MissileUpdate:public BezierProjectileBehavior {public:virtual UpdateSleepTime update();void rva004A7797();void rva004A78E1();void rva004A7A86(int);void rva004A7AF6();void rva004A7767();void rva004A7580();
int m_state;unsigned frame;unsigned d90,d94,d98;float remaining;Coord3D velocity;Coord3D previous;Coord3D other;unsigned c4,c8;unsigned char cc,cd,ce;
void copyPosition(const Coord3D&p){previous=p;}void state0(){}void state5(){}Object *getObject()const{return object;}
};
UpdateSleepTime MissileUpdate::update(){
 MissilePoint pos(*getObject()->getPosition());
 if(remaining>0.0f&&m_state>=2){double dx=(double)pos.x-previous.x,dy=(double)pos.y-previous.y,dz=(double)pos.z-previous.z;float distance=(float)sqrt(dz*dz+dy*dy+dx*dx);float *remainder=&remaining;*remainder-=distance;copyPosition(pos);}
 if(pos.z<0.0f){TheGameLogic->destroyObject(getObject());return UPDATE_SLEEP_FOREVER;}
 switch(m_state){case 0:state0();break;case 5:state5();break;case 1:rva004A7797();if(m_state!=2)break;case 2:rva004A78E1();break;case 3:rva004A7A86(0);break;case 4:rva004A7A86(1);break;case 6:rva004A7AF6();break;case 7:rva004A7767();break;}
 int oldLayer=getObject()->rva0028B511();PathfindLayerEnum layer=TheTerrainLogic->getHighestLayerForDestination(getObject()->getPosition(),false);getObject()->rva0028B4CE(layer);
 if(slot1()&&oldLayer!=1&&layer==1){pos.setXY(*getObject()->getPosition(),9999.0f);
 PathfindLayerEnum ground=TheTerrainLogic->getHighestLayerForDestination(&pos,false);if(ground==oldLayer){pos.z=TheTerrainLogic->getLayerHeight(pos.x,pos.y,ground,0,true)+2.0f;getObject()->Thing::setPosition(&pos);rva004A7580();return UPDATE_SLEEP_NONE;}}
 return BezierProjectileBehavior::update();
}
