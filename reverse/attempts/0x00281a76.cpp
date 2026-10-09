// ??0Rva00281A76@@QAE@M@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/Libraries/Include/Lib
// stlport
#include <vector>
#include "Coord3D.h"
class Object;
class Rva00281A76 {
public:
 Rva00281A76(float);
 bool active00;
 float radius04;
 float centerX08, centerY0C, centerZ10;
 float padding14;
 bool selected18;
 _STL::vector<Object*> objects1C;
};
Rva00281A76::Rva00281A76(float padding)
 :active00(false),radius04(0.0f),centerX08(0.0f),centerY0C(0.0f),centerZ10(0.0f),padding14(padding),selected18(false),objects1C()
{}
