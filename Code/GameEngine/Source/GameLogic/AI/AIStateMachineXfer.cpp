// cl: /O1 /G7 /MD /EHsc /arch:SSE2 /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /D_CRTIMP=
// stlport
// Clean BF1 AIStateMachine_xfer.cpp donor at ba7ddda7e8 supplies goal-path,
// waypoint, squad and temporary-state serialization. WB E02410 names
// AIStateMachine::DoXfer in AIStates.cpp; complete353667..35385E is503B.
// Native and verified goal setters establish vector3C/waypoint48/squad4C;
// temporary state50/end54/ObjectID58/position5C are the accessed suffix.
// Target uses canonical Coord3D, zeroed loop position, reference waypoint
// lookup through TerrainLogic slot34, Squad throw() ctor and its1C size.
// StateMachineXfer supplies the verified base at4D7744. Original field
// names58/5C remain uncertain; no new pins, aliases or data owners.
#include "ascii_string.h"
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Existing verified STLport provider owns the emitted vector members.
namespace _STL {
template<> void vector<Coord3D>::push_back(const Coord3D&);
}
#include "../../Common/GameLogicObjectLookupView.h"
class AsciiString; class UnicodeString; class PooledString; struct XferUnknown11;
class Coord3DBase; class ICoord3D; class Region3D; class IRegion3D;
class Coord2D; class ICoord2D; class Region2D; class IRegion2D;
class RealRange; class RGBColor; class RGBAColorReal; class RGBAColorInt;
class Snapshot; class Thing; class ModuleData;
#include "../../../Include/Common/BfmeXfer.h"
class Xfer::Version { public: Version(unsigned char current, unsigned char minimum) : m_current(current), m_minimum(minimum) {} unsigned char m_current; unsigned char m_minimum; };

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/GameLogic/Waypoint.h"
class Squad {public:Squad()throw();virtual ~Squad();virtual void slot01();virtual void slot02();virtual void xfer(Xfer*);private:_STL::vector<ObjectID> ids;_STL::vector<Object*> objects;};
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
#include "../../../Include/Common/StateMachineClass.h"
class AIStateMachine:public StateMachine {protected:virtual void xfer(Xfer*);public:_STL::vector<Coord3D> goalPath;const Waypoint *goalWaypoint;Squad *goalSquad;State *temporaryState;unsigned int temporaryStateFrameEnd;ObjectID objectID58;Coord3D position5C;};
void XferObjectID(Xfer*,ObjectID*);
void AIStateMachine::xfer(Xfer *xfer)
{
 Xfer::Version version(1,2);*xfer==version;
 StateMachine::xfer(xfer);
 int count=goalPath.size();*xfer==count;
 Coord3D pos={0,0,0};
 for(int i=0;i<count;++i){if(xfer->IsStoring())pos=goalPath[i];*xfer==(Coord3DBase&)pos;if(xfer->IsLoading())goalPath.push_back(pos);}
 AsciiString waypointName;if(goalWaypoint)waypointName=goalWaypoint->m_name;
 *xfer==waypointName;
 if(xfer->IsLoading()&&!waypointName.isEmpty())goalWaypoint=TheTerrainLogic->getWaypointByName(waypointName);
 bool hasSquad=goalSquad!=0;*xfer==hasSquad;
 if(xfer->IsLoading()&&hasSquad&&goalSquad==0)goalSquad=new Squad;
 if(hasSquad)*xfer==(Snapshot&)*goalSquad;
 unsigned int id=0xF423F;if(temporaryState)id=temporaryState->m_id;*xfer==id;
 if(xfer->IsLoading()&&id!=0xF423F)temporaryState=internalGetState(id);
 if(temporaryState)*xfer==(Snapshot&)*temporaryState;
 *xfer==temporaryStateFrameEnd;XferObjectID(xfer,&objectID58);
 if(version.m_minimum>=2)*xfer==(Coord3DBase&)position5C;
}
