extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/Libraries/Include/Lib
// stlport
#include <vector>
#include "Coord3D.h"
class Object;
// Complete native [281A76,281AB7) allocates a 40-byte group.
// Callers establish active00 and selected18 byte flags plus a pointer vector1C.
// The field subobject describes the observed initialization footprint; its
// source composition is inferred. One compiler-only barrier retains the
// native order before the empty-vector constructor and emits no instruction.
struct Rva00281A76Fields {bool active00;float radius04,centerX08,centerY0C,centerZ10;
 __forceinline Rva00281A76Fields(){radius04=0.0f;active00=false;centerX08=0.0f;centerY0C=0.0f;centerZ10=0.0f;_ReadWriteBarrier();}
};
class Rva00281A76 {public:Rva00281A76(float);Rva00281A76Fields fields;float padding14;bool selected18;_STL::vector<Object*>objects1C;};
Rva00281A76::Rva00281A76(float padding):padding14(padding),selected18(false),objects1C(){}
