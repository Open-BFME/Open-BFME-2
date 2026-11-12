// cl: /ICode/Libraries/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Oi /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// Native 0x005A92DE..0x005A943C (350B, RET4), the priority AIEnemyManager::update
// stores per enemy (rowed caller 0x005A9824, sibling file AIEnemyManager.cpp). The WorldBuilder
// call graph supplies an AIEnemyManager priority-distance lead, not a proved original
// name, so the neutral owner class stays. Target byte facts: owner pointer at +0,
// player record lookup 0x002A8AB1 on the converged-neighbour global TheSkirmishAIManager, base
// center 0x004EBF4B, home point 0x00506CF5 for a non-record enemy.
//
// Retail's Coord3D is the non-POD class (Lib/Coord3DCtorView.h, included first: it
// takes Coord3D.h's guard). The by-value saved position is an expression
// temporary built by the member-wise copy constructor and both return temporaries
// stay live across the call; arguments are spelled (saved, other) so the frame
// homes come out in retail's order.
#include "Lib/Coord3DCtorView.h"
class Rva005A9562 { public: float rva005A92DE(void *); private: void *m_ptr; };
#include "wwmath.h"
struct Rva002A8AB1Record;
#include "../../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
#include "../../../../../Include/Common/Rva004EBF4B.h"
Coord3D __cdecl Rva00506CF5(void *, Coord3D *);

static __forceinline float positionDistance(Coord3D saved, const Coord3D &pos)
{
 float x = pos.x - saved.x, y = pos.y - saved.y, z = pos.z - saved.z;
 return WWMath::Sqrt(z * z + y * y + x * x);
}
float Rva005A9562::rva005A92DE(void *other)
{
 Rva004EBF4B *mine = (Rva004EBF4B *)TheSkirmishAIManager->rva002A8AB1(m_ptr);
 Rva004EBF4B *enemy = (Rva004EBF4B *)TheSkirmishAIManager->rva002A8AB1(other);
 if(enemy) {
  return positionDistance(Coord3D(mine->rva004EBF4B()), enemy->rva004EBF4B());
 }
 {
  Coord3D position = Rva00506CF5(other, 0);
  if(!(position == Coord3D(0, 0, 0))) {
   return positionDistance(Coord3D(position), mine->rva004EBF4B());
  }
 }
 return 0;
}
