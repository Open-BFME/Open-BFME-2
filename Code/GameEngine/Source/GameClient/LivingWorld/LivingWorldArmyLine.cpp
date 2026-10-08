// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /EHsc /ICode/Libraries/Include/Lib
// WB14342C0 names LivingWorldArmyLine::allocatePoints and its source file.
// Native5390AE..539141 is147B RET4; count0/points4 and three-float
// stride12 are target facts. Minimum2 and z/y/x zeroing preserve native.
// The original point typedef is unknown. This address-derived point uses
// the canonical Coord3D layout, with a real empty default constructor whose
// full3 bytes fold with the already verified coordinate ctor47A6A9.
// Its observed out-of-line array callback requires noinline. No new pins,
// private canonical-class copy or generated alias are introduced.
#include <stdlib.h>
extern void *__cdecl operator new[](size_t);
#include "Coord3D.h"
struct Rva005390AEPoint : Coord3D {
 __declspec(noinline) Rva005390AEPoint();
};
class LivingWorldArmyLine {
public:
 void allocatePoints(unsigned count);
 void rva00539141();
 unsigned m_count;
 Rva005390AEPoint *m_points;
};
void LivingWorldArmyLine::allocatePoints(unsigned count) {
 free(m_points);
 m_count=count;
 if(m_count<2)m_count=2;
 m_points=new Rva005390AEPoint[m_count];
 for(unsigned i=0;i<m_count;++i) {
  m_points[i].z=0.0f;
  m_points[i].y=0.0f;
  m_points[i].x=0.0f;
 }
}
Rva005390AEPoint::Rva005390AEPoint() {}

// WB1434440 preserves this and calls the named allocator with manager+F8.
// Native539141..539152 RET0 establishes the member wrapper; its name is unknown.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
struct Rva00539141ManagerView { char pad[0xF8]; unsigned pointCount; };
void LivingWorldArmyLine::rva00539141() {
 allocatePoints(reinterpret_cast<Rva00539141ManagerView *>(TheLivingWorldManager)->pointCount);
}
