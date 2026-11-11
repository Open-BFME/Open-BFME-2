// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /MD /EHsc
// Retail 0x001EB456..0x001EB63C (486 B); thiscall RET8.
// WB 0x00AF6460 supplies the campaign-start control flow; it leaves the
// method unnamed. Native callers establish the LinearCampaign receiver.
// Retain the existing address-derived callee spelling until its name is proved.
// Native record stride 36; strings at +4/+8/+C, reference at +10, value at +14.
// The temporary reference is destroyed before the GameLogic +90 write.
// Use the matched carryover sibling's nonemitting receiver barrier to retain
// retail's mission argument/load order. The value local preserves its last use.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "unicode_string.h"
#include "GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
struct OpaqueRefElement4 { OpaqueRefCounted *p; OpaqueRefElement4 &operator=(const OpaqueRefElement4 &); };
struct CampaignTemporaryRef : OpaqueRefElement4 {
 CampaignTemporaryRef() { p=0; }
 ~CampaignTemporaryRef() { if(p) p->Release_Ref(); }
};
struct BfmeAssignRecord36 {
 AsciiString unknown00,map,name,opening;
 OpaqueRefElement4 voice;
 int field14;
 char unknown18[12];
};
class Rva001EB3A6 { public: BfmeAssignRecord36 *rva001EB3A6(int); };
AsciiString __cdecl Rva001EB2CCGetMapPath(const char *);
#include "../../../../Include/GameClient/Shell.h"
extern Shell *TheShell;
#include "../../../../Include/Common/RecorderClass.h"
#include "../../../../Include/GameNetwork/NetWrapperCommandMsg.h"
struct Bfme939Helper;
class RecorderClass; extern RecorderClass *TheRecorder;
extern GameLogic *TheGameLogic;
struct RGBColor;
#include "../../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct CampaignGlobalView { char unknown00[0xac0]; AsciiString map; };
void InitGameLogicRandom(unsigned);
#include "../../../../Include/Common/MessageStream.h"
extern MessageStream *TheMessageStream;
class Rva0023DC8E { public: void rva0023DC8E(const AsciiString &); };
class Rva0023DCCE { public: void rva0023DCCE(const AsciiString &,const OpaqueRefElement4 &,const OpaqueRefElement4 &); };
#include "../../../../Include/Common/RadarWindowOverrideSource.h"
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class InGameUI;
extern InGameUI *TheInGameUI;
class CampaignUIView {
public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();
 virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();
};
struct CampaignGameLogicView { char unknown00[0x90]; int field90; };
class Rva001EB456 {
public:
 void rva001EB456(int,int);
 char unknown00[4];
 Rva001EB3A6 *campaign;
 int difficulty,mission;
 char unknown10[0xb0];
 bool flagC0,flagC1,flagC2,flagC3;
};
void Rva001EB456::rva001EB456(int unused,int useMissionName)
{
 BfmeAssignRecord36 *record=(_ReadWriteBarrier(),campaign)->rva001EB3A6(mission);
 if(record && !flagC1) {
  if(!((NetWrapperCommandMsg *)((Bfme939Helper *)TheRecorder))->getData())
   TheRecorder->stopRecording();
  TheGameLogic->clearGameData(false,false);
  TheMouse->_bfme_setEngineVisibility(false);
  flagC0=false;flagC1=false;flagC3=false;
  ((CampaignGlobalView *)TheWritableGlobalData)->map=Rva001EB2CCGetMapPath(record->map.str());
  InitGameLogicRandom(0);
  GameMessage *message=TheMessageStream->appendMessage(30);
  message->appendIntegerArgument(0);
  message->appendIntegerArgument(difficulty);
  message->appendIntegerArgument(0);
  flagC2=false;
  TheGameLogic->rva0023CD9E(true,1,false);
  TheGameLogic->rva0023CD9E(false,1,false);
  if(useMissionName==1)
   ((Rva0023DC8E *)TheGameLogic)->rva0023DC8E(record->name);
  else
   ((Rva0023DC8E *)TheGameLogic)->rva0023DC8E(AsciiString::TheEmptyString);
  {
   CampaignTemporaryRef empty;
   ((Rva0023DCCE *)TheGameLogic)->rva0023DCCE(record->opening,empty,record->voice);
  }
  int field14=record->field14;
  ((CampaignGameLogicView *)TheGameLogic)->field90=field14;
  theRadarWindowOverrideSource->rva002D4240(true);
  ((CampaignUIView *)TheInGameUI)->v9();
  TheMouse->rva001EEA6D(UnicodeString::TheEmptyString,-1,0,1.0f);
 } else {
  TheShell->showShellMap(true,false);
  TheShell->showShell(true);
  flagC1=false;flagC0=false;
 }
}
