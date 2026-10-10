// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native29BB8B..29BDBC RET8; existing C7FD410 slot55 and named caller pin
// identify InGameUI::placeBuildAvailable. ZH method2981 supplies the primary
// semantic spine; target independently adds owned placement resources588,
// collector DFEDFC, ModelConditionFlags bit108 and port/ordinary stage9C8.
class ThingTemplate {public:char p[0x118];unsigned kinds;char q[0x4d0-0x11c];float placementAngle;};
class Player {public:char p[0x280];int color,nightColor;};
class Object {public:Player*getControllingPlayer()const;char p[4];const ThingTemplate*tmpl;char q[0x74-8];unsigned id;};
class Thing {public:void setOrientation(float);};
class ModelConditionFlags;
struct Rva0028F59A {unsigned bits[19];Rva0028F59A(int,int);};
class Drawable:public Thing {public:void setIndicatorColor(int);void rva002791E7(const ModelConditionFlags&,unsigned,unsigned);char p[4];const ThingTemplate*tmpl;char q[0xb0-8];float opacity;char r[0xfc-0xb4];Object*object;};
class ThingFactory {public:void*newDrawable(void*,int,int);};extern ThingFactory*TheThingFactory;
class GlobalData {public:char p[0x134];int timeOfDay;};extern GlobalData*TheWritableGlobalData;
#define V(n) virtual void s##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
class Mouse {public:enum MouseCursor{NONE,NORMAL,ARROW,SCROLL,CROSS};V10(0) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) virtual void capture();virtual void releaseCapture();};extern Mouse*TheMouse;
class ResourceEntryCollector {public:void rva004E551E();};struct BfmeUiResourceEntryState;extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
class Rva0029B5E3 {public:void clear();void*ptr;};
class Rva0029A94F {public:void rva0029A94F();};
struct BuildIcon {Drawable*draw;float angle;};
class InGameUI {public:
 V10(0) V10(1) V10(2) V10(3) V10(4) V(50) V(51) V(52) V(53) V(54)
 virtual void placeBuildAvailable(const ThingTemplate*,Drawable*);
 V(56) V(57) virtual void setPlacementStart(const void*); V(59) V(60) V(61) V(62) V(63)
 virtual void clearPlacementPort(bool);
 V(65) V(66) V(67) V(68) V(69) V10(7) V(80) virtual void setRadiusCursorNone();
protected: void setMouseCursor(Mouse::MouseCursor);
public:
 char p[0x53c-4];const ThingTemplate*pending;unsigned sourceID;BuildIcon*icons;char q[0x554-0x548];bool port;char r[0x588-0x555];Rva0029B5E3 resources;char a[0x7fc-0x58c];int mouseMode;Mouse::MouseCursor mouseCursor;char b[0x9c8-0x804];int stage;
};
void InGameUI::placeBuildAvailable(const ThingTemplate*build,Drawable*buildDrawable)
{
 if(resources.ptr){resources.clear();((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E551E();}
 Object*source=0;if(buildDrawable)source=buildDrawable->object;
 if(build)setRadiusCursorNone();
 if(pending && build)placeBuildAvailable(0,0);
 pending=build;sourceID=0;if(source)sourceID=source->id;
 if(TheMouse){
  if(build){
   mouseMode=1;mouseCursor=Mouse::CROSS;
   TheMouse->capture();setMouseCursor(Mouse::CROSS);
   Drawable*draw=(Drawable*)TheThingFactory->newDrawable((void*)build,8,-1);
   if(source){if(TheWritableGlobalData->timeOfDay==4)draw->setIndicatorColor(source->getControllingPlayer()->nightColor);else draw->setIndicatorColor(source->getControllingPlayer()->color);}
   float angle=build->placementAngle;draw->setOrientation(angle);draw->opacity=0.45f;
   draw->rva002791E7(*(const ModelConditionFlags*)&Rva0028F59A(0,108),1,0);
   icons[0].draw=draw;icons[0].angle=angle;
   if(build->kinds&0x10000000){stage=1;if(source && (source->tmpl->kinds&0x10000000)){port=true;clearPlacementPort(false);}}else stage=2;
  }else{
   if(buildDrawable && !(buildDrawable->tmpl->kinds&0x10000000)){
    TheMouse->releaseCapture();setMouseCursor(Mouse::ARROW);setPlacementStart(0);((Rva0029A94F*)this)->rva0029A94F();clearPlacementPort(false);
   }else{
    if(mouseMode==1){mouseMode=0;mouseCursor=Mouse::ARROW;}
    TheMouse->releaseCapture();setMouseCursor(Mouse::ARROW);setPlacementStart(0);((Rva0029A94F*)this)->rva0029A94F();((ResourceEntryCollector*)&BfmeUiResourceEntryCollectorState)->rva004E551E();
   }
  }
 }
}
