// cl: /O1 /G7 /Oa /MD /EHsc /arch:SSE2 /D_STLP_USE_STATIC_LIB
// stlport
// WB E032F0 is the unnamed counterpart; the existing caller pin and clean
// donor establish AIStateMachine::addToGoalPath identity. Complete
// retail35385E..35389E is64B. Clean BF1 ba7ddda7e8 AIStateMachineAddToGoalPath
// and ZH AIStates.cpp provide the append-unless-final-point-equals behavior.
// Target vector3C is proved by this body and the verified xfer353667;
// equality3702 and push-back2CE7DC are existing verified providers.
// Canonical coordinates and declaration-only push-back avoid private copies.
// /Oa alone closes retail's argument push before the empty-path branch;
// there are no stores before the equality call. No new pins or aliases.
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D&); }
class AIStateMachine {public:void addToGoalPath(const Coord3D*);private:char prefix[0x3C];_STL::vector<Coord3D> goalPath;};
void AIStateMachine::addToGoalPath(const Coord3D *point)
{
 if(goalPath.size()==0)goalPath.push_back(*point);
 else {
  Coord3D *last=&goalPath[goalPath.size()-1];
  if(!(*last==*point))goalPath.push_back(*point);
 }
}
