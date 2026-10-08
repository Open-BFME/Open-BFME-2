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
class Xfer {
public: class Version; Xfer(); virtual ~Xfer(); void Version1();
  virtual bool IsLoading() const; virtual bool IsStoring() const; virtual bool IsCRC() const; virtual bool IsLightCRC() const;
  virtual void v5() = 0; virtual void v6() = 0; virtual void v7() = 0;
  virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
  virtual Xfer &XferRawBytes(void *data, unsigned int size);
  virtual Xfer &operator==(bool &value); virtual Xfer &operator==(char &value);
  virtual Xfer &operator==(unsigned char &value); virtual Xfer &operator==(short &value);
  virtual Xfer &operator==(unsigned short &value); virtual Xfer &operator==(int &value);
  virtual Xfer &operator==(unsigned int &value); virtual Xfer &operator==(__int64 &value);
  virtual Xfer &operator==(float &value); virtual Xfer &operator==(AsciiString &value);
  virtual Xfer &operator==(UnicodeString &value); virtual Xfer &operator==(PooledString &value);
  virtual Xfer &operator==(Coord3DBase &value); virtual Xfer &operator==(ICoord3D &value);
  virtual Xfer &operator==(Region3D &value); virtual Xfer &operator==(IRegion3D &value);
  virtual Xfer &operator==(Coord2D &value); virtual Xfer &operator==(ICoord2D &value);
  virtual Xfer &operator==(Region2D &value); virtual Xfer &operator==(IRegion2D &value);
  virtual Xfer &operator==(RealRange &value); virtual Xfer &operator==(RGBColor &value);
  virtual Xfer &operator==(RGBAColorReal &value); virtual Xfer &operator==(RGBAColorInt &value);
  virtual Xfer &operator==(Snapshot &value); virtual Xfer &operator==(XferUnknown11 &value) = 0;
  virtual Xfer &operator==(Version &value);
  virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected: virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};
class Xfer::Version { public: Version(unsigned char current, unsigned char minimum) : m_current(current), m_minimum(minimum) {} unsigned char m_current; unsigned char m_minimum; };

struct State {virtual ~State();unsigned int id;};
class Waypoint {public:char unknown00[8];AsciiString name;};
class Squad {public:Squad()throw();virtual ~Squad();virtual void slot01();virtual void slot02();virtual void xfer(Xfer*);private:_STL::vector<ObjectID> ids;_STL::vector<Object*> objects;};
class TerrainLogic {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
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
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual Waypoint *getWaypointByName(const AsciiString&);
};
extern TerrainLogic *TheTerrainLogic;
class StateMachine {public:virtual ~StateMachine();virtual void slot01();virtual void slot02();protected:virtual void xfer(Xfer*);char beforeGoalPath[0x38];public:State *internalGetState(int);};
class AIStateMachine:public StateMachine {protected:virtual void xfer(Xfer*);public:_STL::vector<Coord3D> goalPath;const Waypoint *goalWaypoint;Squad *goalSquad;State *temporaryState;unsigned int temporaryStateFrameEnd;ObjectID objectID58;Coord3D position5C;};
void XferObjectID(Xfer*,ObjectID*);
void AIStateMachine::xfer(Xfer *xfer)
{
 Xfer::Version version(1,2);*xfer==version;
 StateMachine::xfer(xfer);
 int count=goalPath.size();*xfer==count;
 Coord3D pos={0,0,0};
 for(int i=0;i<count;++i){if(xfer->IsStoring())pos=goalPath[i];*xfer==(Coord3DBase&)pos;if(xfer->IsLoading())goalPath.push_back(pos);}
 AsciiString waypointName;if(goalWaypoint)waypointName=goalWaypoint->name;
 *xfer==waypointName;
 if(xfer->IsLoading()&&!waypointName.isEmpty())goalWaypoint=TheTerrainLogic->getWaypointByName(waypointName);
 bool hasSquad=goalSquad!=0;*xfer==hasSquad;
 if(xfer->IsLoading()&&hasSquad&&goalSquad==0)goalSquad=new Squad;
 if(hasSquad)*xfer==(Snapshot&)*goalSquad;
 unsigned int id=0xF423F;if(temporaryState)id=temporaryState->id;*xfer==id;
 if(xfer->IsLoading()&&id!=0xF423F)temporaryState=internalGetState(id);
 if(temporaryState)*xfer==(Snapshot&)*temporaryState;
 *xfer==temporaryStateFrameEnd;XferObjectID(xfer,&objectID58);
 if(version.m_minimum>=2)*xfer==(Coord3DBase&)position5C;
}
