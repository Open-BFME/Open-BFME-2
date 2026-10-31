// ?update@MissileUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.980602 date=2026-10-13
// ?update@MissileUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9826050638015957 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /I. /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <math.h>
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff};
enum PathfindLayerEnum {GROUND_LAYER=0,BRIDGE_LAYER=1};
#include "../../../Common/Thing/thing.h"
struct MissilePoint:public Coord3D {MissilePoint(const Coord3D &p){x=p.x;y=p.y;z=p.z;}void setXY(const Coord3D&p,float height){x=p.x;y=p.y;z=height;}};
#include "../../../Common/GameLogicObjectLookupView.h"
enum ObjectStatusTypes { OBJECT_STATUS_NONE=0 };
class Object : public Thing
{
public:
	unsigned char m_pad60[0x74 - 0x60];
	ObjectID m_id; // +0x74
	void setStatus(ObjectStatusTypes, bool);
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum);
};
extern GameLogic *TheGameLogic;
class TerrainLogic {public:virtual ~TerrainLogic();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual float getGroundHeight(float,float,Coord3D*)const;virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D*,bool)const;PathfindLayerEnum getHighestLayerForDestination(const Coord3D*,bool);};extern TerrainLogic *TheTerrainLogic;
class ModuleData;
class MissileUpdateModuleData;
class Xfer;
struct Rva0045B936Arg;
class Rva002CBA7C;
class Matrix3D;
enum NameKeyType
{
	NK_UNKNOWN = 0
};
class Rva004A76DEBase0 { public: virtual ~Rva004A76DEBase0(); virtual NameKeyType getModuleNameKey() const; protected: virtual void xfer(Xfer *xfer); public: const ModuleData *m_moduleData; Object *m_object; };

class Rva004A76DEBase1 { public: virtual ~Rva004A76DEBase1(); };

class Rva004A76DEBase2 { public: virtual UpdateSleepTime update() = 0; virtual ~Rva004A76DEBase2(); unsigned char m_pad[12]; };

class Rva004A76DEBase3 {
public:
 virtual void projectileLaunchAtObjectOrPosition(Object *, const Coord3D *, Object *, int, int, const Rva0045B936Arg *, Rva002CBA7C *, const Matrix3D *) = 0;
 virtual unsigned char rva004A768A() const = 0;
 virtual int getLauncherID() const = 0;
 virtual bool rva0045CD6E(Object *) = 0;
 virtual bool rva0045BF06(Object *) = 0;
 virtual void rva0045B4E2(int) = 0;
};

class Rva004A76DEBase4 {
public:
 virtual void rva0045B4C0(Object *, int, int) = 0;
 virtual bool rva0045BF06(Object *) = 0;
 virtual bool rva0047A699_2() = 0; virtual bool rva0047A699_3() = 0;
 virtual bool rva0047A699_4() = 0; virtual bool rva0047A699_5() = 0;
};

class BezierProjectileBehavior : public Rva004A76DEBase0, public Rva004A76DEBase1, public Rva004A76DEBase2, public Rva004A76DEBase3, public Rva004A76DEBase4
{
public:
	BezierProjectileBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~BezierProjectileBehavior();
	virtual UpdateSleepTime update();
 virtual void projectileLaunchAtObjectOrPosition(Object *, const Coord3D *, Object *, int, int, const Rva0045B936Arg *, Rva002CBA7C *, const Matrix3D *);
 virtual bool rva0045CD6E(Object *);
 virtual void rva0045B4C0(Object *, int, int);
	virtual void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
	void rva0045C026();

protected:
	virtual void xfer(Xfer *xfer);

protected:
	unsigned char m_pad28[0x40 - 0x28]; // +0x28..+0x3F
	int m_40; // +0x40 (rva004A7767 destroys the object when it is nonzero)
	unsigned char m_pad44[0x88 - 0x44]; // +0x44..+0x87
};

class MissileUpdate : public BezierProjectileBehavior
{
public:
	MissileUpdate(Thing *thing, const ModuleData *moduleData);
	virtual UpdateSleepTime update();
	void copyPosition(const Coord3D &p) { m_prevPos = p; }
	void state0() {}
	void state5() {}
	Object *getObject() const { return m_object; }
 virtual void projectileLaunchAtObjectOrPosition(Object *, const Coord3D *, Object *, int, int, const Rva0045B936Arg *, Rva002CBA7C *, const Matrix3D *);
 virtual unsigned char rva004A768A() const;
 virtual int getLauncherID() const;
 virtual bool rva0045CD6E(Object *);
 virtual bool rva0045BF06(Object *);
 virtual void rva0045B4E2(int);
 virtual bool rva0047A699_2(); virtual bool rva0047A699_3();
 virtual bool rva0047A699_4(); virtual bool rva0047A699_5();
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual ~MissileUpdate();
	virtual void xfer(Xfer *xfer);
public:
	virtual void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
	void Rva004A7512Clear();
	void Rva004A7530Set(int val);
	void Rva004A75A3Init();
	void rva004A7580();
	void rva004A7AF6();
	void rva004A7A86(int);
	void rva004A7767();
	void rva004A7797();
	void rva004A78E1();

private:
	const MissileUpdateModuleData *getMissileUpdateModuleData() const
	{
		return (const MissileUpdateModuleData *)m_moduleData;
	}


	int m_state; // +0x88
	unsigned int m_frame; // +0x8C (TheGameLogic frame)
	ObjectID m_90; // +0x90 (launcher)
	ObjectID m_94; // +0x94 (victim)
	unsigned int m_98; // +0x98
	float remaining; // +0x9C (module data +0xCC)
	Coord3D m_velA; // +0xA0
	Coord3D m_prevPos; // +0xAC (the object's position at +0x38)
	Coord3D m_velB; // +0xB8
	unsigned int m_C4; // +0xC4
	int m_C8; // +0xC8
	bool m_CC; // +0xCC
	bool m_CD; // +0xCD
	bool m_CE; // +0xCE
};

UpdateSleepTime MissileUpdate::update(){
 MissilePoint pos(*getObject()->getPosition());
 if(remaining>0.0f&&m_state>=2){double dx=(double)pos.x-m_prevPos.x,dy=(double)pos.y-m_prevPos.y,dz=(double)pos.z-m_prevPos.z;double sum=dz*dz+dy*dy+dx*dx;
  double root=sqrt(sum);
  float distance=(float)root;
  remaining-=distance;
  copyPosition(pos);}
 if(pos.z<0.0f){TheGameLogic->destroyObject(getObject());return UPDATE_SLEEP_FOREVER;}
 switch(m_state){case 0:state0();break;case 5:state5();break;case 1:rva004A7797();if(m_state!=2)break;case 2:rva004A78E1();break;case 3:rva004A7A86(0);break;case 4:rva004A7A86(1);break;case 6:rva004A7AF6();break;case 7:rva004A7767();break;}
 int oldLayer=getObject()->rva0028B511();PathfindLayerEnum layer=TheTerrainLogic->getHighestLayerForDestination(getObject()->getPosition(),false);getObject()->setLayer(layer);
 if(rva004A768A()&&oldLayer!=1&&layer==1){pos.setXY(*getObject()->getPosition(),9999.0f);
 PathfindLayerEnum ground=TheTerrainLogic->getHighestLayerForDestination(&pos,false);if(ground==oldLayer){pos.z=TheTerrainLogic->getLayerHeight(pos.x,pos.y,ground,0,true)+2.0f;getObject()->Thing::setPosition(&pos);rva004A7580();return UPDATE_SLEEP_NONE;}}
 return BezierProjectileBehavior::update();
}
