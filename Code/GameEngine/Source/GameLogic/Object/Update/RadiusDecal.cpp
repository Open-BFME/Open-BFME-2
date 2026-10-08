// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// BFME1 RadiusDecal_update.cpp at9cbfb551 supplies opacity, visibility,
// frame and continuous rotation semantics; retail BFME2 adds the bounded
// radius/fade branch. Same owner proven by RadiusDecal::clear330DBA and
// rva330F7D receiver/callers. Native layout fields below are measured.
// The two-instruction FISTP fragment is the donor's rounded float-to-int
// machinery, proven by native731009..73100F; ordinary unsigned casts emit
// truncation/conversion helpers instead and change the rounding contract.
#include "../../../Common/GameLogicObjectLookupView.h"
extern "C" __declspec(dllimport) double __cdecl ceil(double);
float Sin(float);float normalizeAngle(float);
extern float g_00DBA500;
extern float g_bfmeSecondCF; // donor name retained for native DBA508 scalar
class GameClient { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void slot21()=0;
 virtual void slot22()=0;
 virtual void slot23()=0;
 virtual void slot24()=0;
 virtual void slot25()=0;
 virtual void slot26()=0;
 virtual void slot27()=0;
 virtual void slot28()=0;
 virtual void slot29()=0;
 virtual void slot30()=0;
 virtual unsigned getFrame()=0;
};
extern GameClient *TheGameClient;extern GameLogic *TheGameLogic;
class GlobalData { public: char pad00[0x5C];volatile bool at5C; };
extern GlobalData *TheWritableGlobalData;
class BfmeOwnVVD { public:virtual void slot0()=0;virtual void slot1()=0;virtual int slot2()=0; };
extern BfmeOwnVVD *g_bfmeSingletonVVD;
class Shadow { public:
 void setOpacity(int);void rva00330995(int);
 __forceinline void setRadius(float r) { radius58=r;radius5C=r; }
 __forceinline float getAngle() const {return angle;}
 __forceinline void setAngle(float a) {angle=a;}
 char pad00[0x20];float angle;char pad24[0x10];volatile unsigned type;
 char pad38[0x20];float radius58,radius5C;
};
struct RadiusDecalTemplateView {
 char pad00[0xC];float minOpacity,maxOpacity,throbTime;char pad18[0xC];
 float radius;volatile unsigned at28;float rotationSpeed,shrinkRate;
};
class RadiusDecal { public:
 void update();
 RadiusDecalTemplateView *data;Shadow *decal;bool empty;float previousFrame;
};
void RadiusDecal::update() {
 if(previousFrame==0.0f) previousFrame=(float)TheGameLogic->getFrame();
 if(!decal) goto update_extra;
 if(!data) goto update_extra;
 {
 unsigned frame=TheGameClient->getFrame();
 float throbTime=(float)ceil(data->throbTime*g_00DBA500);
 unsigned cycle;
 __asm fld throbTime
 __asm fistp cycle
 unsigned divisorValue=cycle;
 const unsigned minimum=1;
 const unsigned *divisor=divisorValue>1?&divisorValue:&minimum;
 unsigned phase=frame%*divisor;
 float percent=0.5f*(Sin((float)phase*6.28318548f/(float)*divisor)+1.0f);
 int opacity;
 if(TheGameLogic->getDrawIconUI()) opacity=(int)(((data->maxOpacity-data->minOpacity)*percent+data->minOpacity)*255.0f);
 else opacity=0;
 {
  bool special=decal->type==0x1000;
  unsigned value=data->at28;
  if(value>0) special=true;
  if(!special && TheWritableGlobalData->at5C && g_bfmeSingletonVVD->slot2()) opacity=0;
 }
 set_opacity:
 decal->setOpacity(opacity);
 float speed=data->rotationSpeed;
 float step=data->shrinkRate;
 float limit=2.0f*data->radius;
 if(speed>0.0f && step>0.0f && limit>0.0f) {
  float radius=decal->radius5C-step;
  if(radius<0.0f) radius+=limit;
  else if(radius>limit) radius=limit;
  decal->setRadius(radius);
  float fade=1.0f-radius/limit;
  fade*=fade;
  decal->setAngle(normalizeAngle(decal->getAngle()+fade*speed));
  opacity=(int)(fade*255.0f);
  decal->setOpacity(opacity);
  decal->rva00330995(opacity*0x10101-0x1000000);
 } else if(data->rotationSpeed!=0.0f) {
  float scale=g_bfmeSecondCF;
  scale*=0.0174532924f;
  scale*=data->rotationSpeed;
  scale*=60.0f;
  unsigned clientFrame=TheGameClient->getFrame();
  decal->angle=(float)clientFrame*scale;
 }
 }
 update_extra:
 previousFrame=(float)TheGameClient->getFrame();
}
