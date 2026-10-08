// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// StateMachine transfer: WB127D8B0 names Common/StateMachine.cpp; complete
// retail4D7744..4D795B is535B. Clean BF1 StateMachine.cpp at ba7ddda7e8
// supplies state-map/count/id checks, current-state healing, goal and flags.
// Target evidence adds light-CRC bypass, versions1..4, owner-ID lookup,
// range3 and the consumed compatibility position for versions below4.
// The return-valued Xfer chain and owner-only ID assignment are witnessed
// in retail. Existing StateMachineGoal.cpp establishes the member prefix;
// fields34/3A retain neutral names. No new pins or data owners.
// The existing ObjectID provider is void-spelled although retail returns
// XferEnum's Xfer reference; allowed_symbols --alternatenames certifies
// this exact binding at3060B2. Keep legacy callers and its single owner.
#pragma comment(linker, "/alternatename:?XferObjectID@@YAAAVXfer@@PAV1@PAW4ObjectID@@@Z=?XferObjectID@@YAXPAVXfer@@PAW4ObjectID@@@Z")
#include <cfloat>
#include <map>

// Same node comparison used by the verified StateMachineGoal home unit.
namespace _STL {
template<class T,class L,class R>
static inline bool operator!=(const _Rb_tree_iterator<T,L>& a,const _Rb_tree_iterator<T,R>& b)
{ return a._M_node != b._M_node; }
}
typedef int Int; typedef unsigned int UnsignedInt; typedef int StateID; typedef bool Bool;
#include "GameLogicObjectLookupView.h"

enum { MACHINE_DONE_STATE_ID = 999998, INVALID_STATE_ID = 999999 };
#include "../../../Libraries/Include/Lib/Coord3D.h"
class Object { public: unsigned char m_pad00[0x38]; Coord3D m_position; unsigned char m_pad44[0x74 - 0x44]; Int m_id; };
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
struct State {
  virtual void vslot00(); virtual void vslot04(); virtual void vslot08(); virtual void vslot0c();
  virtual int onEnter(); virtual void onExit(int status); virtual int update();
  virtual Bool isIdle() const; virtual Bool isAttack() const; virtual Bool isGuardIdle() const; virtual Bool isBusy() const;
  int getID() const { return m_id; } StateID m_id;
};

extern GameLogic *TheGameLogic;
class StateMachine {
public:
  void *m_currentState;
  _STL::map<StateID, State *> m_stateMap;
  Object *m_owner;
  UnsignedInt m_sleepTill;
  StateID m_defaultStateID;
  ObjectID m_goalObjectID;
  Coord3D m_goalPosition;
  float m_goalRange;
  ObjectID m_unk34ID;
  bool m_locked;
  bool m_defaultStateInited;
  bool m_extra3A;
  State *internalGetState(StateID id);
  StateID getCurrentStateID() const { return m_currentState ? ((State*)m_currentState)->getID() : INVALID_STATE_ID; }
protected:
  virtual void slot00(); virtual void slot01(); virtual void slot02();
  virtual void xfer(Xfer *xfer);
};
Xfer &XferObjectID(Xfer *xfer, ObjectID *objectID);
struct BfmeFormattedText { char *text; int tag; };
extern "C" BfmeFormattedText* __cdecl bfmeFormatText(BfmeFormattedText*, int, const char*, ...);
extern int g_guardTargetTypeThrowInfo;
__declspec(noreturn) void __stdcall _CxxThrowException(void *pExc, void *pInfo);
void StateMachine::xfer(Xfer *xfer)
{
  if (xfer->IsLightCRC()) return;
  Xfer::Version version(1,4);
  (*xfer == version) == m_sleepTill == (UnsignedInt&)m_defaultStateID;
  UnsignedInt curStateID = (UnsignedInt)getCurrentStateID(); *xfer == curStateID;
  if (version.m_minimum >= 2) { if ((StateID)curStateID == INVALID_STATE_ID) return; }
  if (xfer->IsLoading()) { m_currentState = internalGetState((StateID)curStateID); }
  Bool snapshotAllStates = false; *xfer == snapshotAllStates;
  if (snapshotAllStates) {
    Int count = 0; _STL::map<StateID, State *>::iterator i;
    for (i = m_stateMap.begin(); i != m_stateMap.end(); ++i) count++;
    Int saveCount = count; *xfer == saveCount;
    if (saveCount != count) { BfmeFormattedText error; bfmeFormatText(&error, 5, 0); _CxxThrowException(&error, &g_guardTargetTypeThrowInfo); }
    for (i = m_stateMap.begin(); i != m_stateMap.end(); i++) {
      State *state = (*i).second; UnsignedInt id = (UnsignedInt)state->getID(); *xfer == id;
      if ((StateID)id != state->getID()) { BfmeFormattedText error; bfmeFormatText(&error, 5, 0); _CxxThrowException(&error, &g_guardTargetTypeThrowInfo); }
      *xfer == (Snapshot&)*state;
    }
  } else {
    if (m_currentState == 0) {
      m_currentState = internalGetState(m_defaultStateID);
      if (m_currentState == 0) { BfmeFormattedText error; bfmeFormatText(&error, 5, 0); _CxxThrowException(&error, &g_guardTargetTypeThrowInfo); }
    }
    *xfer == (Snapshot&)*(State*)m_currentState;
  }
  XferObjectID(& (XferObjectID(xfer,&m_goalObjectID) == (Coord3DBase&)m_goalPosition),&m_unk34ID);
  if(version.m_minimum<4){Coord3D oldPosition; *xfer == (Coord3DBase&)oldPosition;}
  (*xfer == m_locked) == m_defaultStateInited; *xfer == m_extra3A;
  ObjectID tmpID = (ObjectID)0;
  if (xfer->IsLoading()) {
    XferObjectID(xfer, &tmpID);
    if (TheGameLogic) { m_owner = TheGameLogic->findObjectByID(tmpID); }
  } else {
    if(m_owner) tmpID = (ObjectID)m_owner->m_id;
    XferObjectID(xfer, &tmpID);
  }
  if (version.m_minimum >= 3) { *xfer == m_goalRange; }
}
