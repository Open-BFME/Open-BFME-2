// ?rva000B90A3@W3DScriptedModelDraw@@QAEXXZ
// partial score=0.826 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
#include <math.h>
#include "matrix3d.h"
struct B90A3Data {char pad[0x69];bool translationOnly,clientHeading;};
class Object {char pad[0x1C0];public:float orientation;};
class Drawable {char pad[0xFC];public:Object *object;const Matrix3D *getTransformMatrix()const;};
class InGameUI {public:float rva0029B3C1(const Object*)const;};
extern InGameUI *TheInGameUI;
class B90A3Render {public:
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
 virtual void Set_Transform(const Matrix3D&);
};
class B90A3Shadow {public:virtual void slot0();virtual void notify();};
class W3DScriptedModelDraw {public:
 void *vtable;B90A3Data *data;Drawable *drawable;char pad0C[0x50-0xC];B90A3Render *render;char pad54[4];B90A3Shadow *shadow;
 void rva000B710D(Matrix3D&);
 void rva000B90A3();
};
static inline void RotateZ(Matrix3D &m,float theta)
{
 float c=(float)cos((double)theta),s=(float)sin((double)theta);
 {float a=m[0][0],b=m[0][1];m[0][0]=a*c+b*s;m[0][1]=b*c-a*s;}
 {float a=m[1][0],b=m[1][1];m[1][0]=a*c+b*s;m[1][1]=b*c-a*s;}
 {float a=m[2][0],b=m[2][1];m[2][0]=a*c+b*s;m[2][1]=b*c-a*s;}
}
void W3DScriptedModelDraw::rva000B90A3()
{
 if(shadow&&render&&drawable->object){
  B90A3Data *moduleData=data;
  Matrix3D mtx(true);
  if(!moduleData->translationOnly&&!moduleData->clientHeading)
   mtx=*drawable->getTransformMatrix();
  else{
   mtx.Set_Translation(drawable->getTransformMatrix()->Get_Translation());
   if(moduleData->clientHeading){
    Object *obj=drawable->object;
    float angle=TheInGameUI?TheInGameUI->rva0029B3C1(obj):obj->orientation;
    RotateZ(mtx,angle);
   }
  }
  rva000B710D(mtx);
  render->Set_Transform(mtx);
  shadow->notify();
 }
}
