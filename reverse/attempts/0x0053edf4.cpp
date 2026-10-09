// ?rva0053EDF4@Rva0053ED1A@@QAE?AUICoord2D@@XZ
// partial score=0.85 date=2026-10-10
// cl: /O1 /Op /MD /EHsc /arch:SSE /ICode/Libraries/Include
#include "Lib/Coord3D.h"
struct ICoord2D{int x,y;};
class Drawable {public:const Coord3D* getPosition() const;};
class GeometryInfo {public:float getMaxHeightAbovePosition() const;};
class Object {public:Drawable* getDrawable() const;bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool) const;};
enum ObjectID { INVALID_ID=0 };class GameLogic{public:Object* findObjectByID(ObjectID);};extern GameLogic* TheGameLogic;
class View {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
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
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual int worldToScreenTriReturn(const Coord3D*,ICoord2D*);
};extern View* TheTacticalView;
struct Rva0053EDF4Object {char p0[4];char* info;char p8[0x30];Coord3D position;char p44[0x64];GeometryInfo geometry;};
class Rva0053ED1A {public:ICoord2D rva0053EDF4();char pad[0x48];int id;};
ICoord2D Rva0053ED1A::rva0053EDF4()
{
 Object* obj=TheGameLogic->findObjectByID((ObjectID)id);ICoord2D screen;
 if(obj && !(reinterpret_cast<Rva0053EDF4Object*>(obj)->info[0x109]&0x40))
 {
  Drawable* draw=obj->getDrawable();
  const Coord3D* position;
  if(draw) position=draw->getPosition();else position=&reinterpret_cast<Rva0053EDF4Object*>(obj)->position;
  Coord3D world=*position;
  Coord3D contact={0,0,0};
  if(obj->getWorldspaceBestContactPoint(&contact,&contact,"Menu",0,0,false))
  {
    contact.x-=reinterpret_cast<Rva0053EDF4Object*>(obj)->position.x;
    contact.y-=reinterpret_cast<Rva0053EDF4Object*>(obj)->position.y;
    contact.z-=reinterpret_cast<Rva0053EDF4Object*>(obj)->position.z;
    world.x+=contact.x;world.y+=contact.y;world.z+=contact.z;
  }
  else world.z+=reinterpret_cast<Rva0053EDF4Object*>(obj)->geometry.getMaxHeightAbovePosition()*0.5f;
  if(TheTacticalView->worldToScreenTriReturn(&world,&screen)==0)return screen;
 }
 screen.x=screen.y=-999;return screen;
}
