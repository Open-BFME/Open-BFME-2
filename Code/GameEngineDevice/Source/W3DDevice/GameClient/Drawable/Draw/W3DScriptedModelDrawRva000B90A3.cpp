// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
#include <math.h>
#include "matrix3d.h"
// ?rva000B90A3@W3DScriptedModelDraw@@QAEXXZ @0x000B90A3 559B: copy the drawable
// transform to the render object (translation only, or translation plus client
// heading via the real WWMath Matrix3D::Rotate_Z(theta) with cosf/sinf, otherwise
// the full matrix), run the rowed 0x000B710D adjuster, then notify the shadow.
// The branch is the natural "special case first" form: with the heading/translation-only
// arm first and the full-copy arm as the else, cl lays the arms out as retail does
// (the inverted !a && !b test with the copy first left the arms swapped).
struct B90A3Data {char pad[0x69];bool translationOnly,clientHeading;};
class Object {char pad[0x1C0];public:float orientation;};
#include "../../../../../../GameEngine/Include/GameClient/Drawable.h"
#include "../../../../../../GameEngine/Include/GameClient/InGameUI.h"
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
void W3DScriptedModelDraw::rva000B90A3()
{
 if(shadow&&render&&drawable->m_object){
  B90A3Data *moduleData=data;
  Matrix3D mtx(true);
  if (moduleData->translationOnly||moduleData->clientHeading) {
   mtx.Set_Translation(drawable->getTransformMatrix()->Get_Translation());
   if(moduleData->clientHeading){
    Object *obj=drawable->m_object;
    float angle=TheInGameUI?TheInGameUI->rva0029B3C1(obj):obj->orientation;
    mtx.Rotate_Z(angle);
   }
  } else mtx=*drawable->getTransformMatrix();
  rva000B710D(mtx);
  render->Set_Transform(mtx);
  shadow->notify();
 }
}
