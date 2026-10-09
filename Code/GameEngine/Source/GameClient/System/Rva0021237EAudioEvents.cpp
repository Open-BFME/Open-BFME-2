// cl: /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?rva0021237E@Rva0021237E@@QAEXXZ @0x0021237E 64B
// The target walks the four-byte range at this+0x2CC, passes each word to
// TheAudio's slot 0x6C, then erases the whole range through rowed vector erase
// 0x0031BD55. TheAudio is pinned at VA 0x00DFE6E8. The neighboring 0x0021246D
// caller invokes this body at +0x48B. The handle interpretation follows the
// target call and AudioManager's established removeAudioEvent slot; the owning
// class identity remains address-derived.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva0021246DInput;

class Rva0021237E
{
	char m_pad[0x2CC];

public:
	void rva0021237E();
	void rva002123BE();
	void rva0021246D(Rva0021246DInput *input);
};

void Rva0021237E::rva0021237E()
{
	_STL::vector<void *> *eventHandles = (_STL::vector<void *> *)((char *)this + 0x2CC);
	unsigned int i;
	for (i = 0; i < (unsigned int)(eventHandles->end() - eventHandles->begin()); ++i)
	{
		_ReadWriteBarrier();
		TheAudio->removeAudioEvent((AudioHandle)(unsigned int)eventHandles->begin()[i]);
	}
	eventHandles->erase(eventHandles->begin(), eventHandles->end());
}

// Native 6123BE..61246D (175B); WB B5EDA0 confirms ordered update calls.
// +218 is a pointer-key hash table. The WindowVideoManager specialization
// is the existing byte-and-ABI twin at 427195/41E832; it does not establish
// the target map's original key/value class names. Values dispatch slot0C.
#include <hash_map>
class GameWindow;
class WindowVideo;
class WindowVideoManager { public: struct hashConstGameWindowPtr { unsigned int operator()(const GameWindow *p) const { return (unsigned int)p; } }; };
typedef _STL::hash_map<const GameWindow*,WindowVideo*,WindowVideoManager::hashConstGameWindowPtr,_STL::equal_to<const GameWindow*> > UpdateMapView;
struct UpdateSlot21123 { virtual void v00();virtual void v04();virtual void v08();virtual void v0C(); };
struct Rva00211494 { void rva00211494(); };
struct Rva002112A9 { void rva002112A9(); };
struct Rva003EEAB7 { void rva003EEAB7(); };
class LivingWorldEyeTower { friend struct Rva0021237E; void updateState(); };
struct Rva002B5073 { bool rva002B5073(int); };
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002D3627Host; extern Rva002D3627Host *g_00DFEF18; extern Rva002D3627Host *TheRva002D3627Host;
struct SingletonView21123 { char pad14[0x14];int mode; };
struct RadarWindowOverrideSource {
 virtual void v00();virtual void v04();virtual void v08();virtual void v0C();virtual void v10();virtual void v14();virtual void v18();virtual void v1C();virtual void v20();virtual void v24();virtual void v28();
 bool rva002D35E6() const;
 void rva002D4240(bool);
};
struct RGBColor;
class Mouse { public: void _bfme_setEngineVisibility(bool); void rva001EEA6D(UnicodeString,int,const RGBColor*,float); }; extern Mouse *TheMouse;
struct UpdateReceiverView21123 {
 char pad[0x218];
 UpdateMapView map218;
 char gap[(0x268-0x218)-sizeof(UpdateMapView)];
 Rva003EEAB7 *object268;
 char pad26C[0x2C0-0x26C];
 bool hidden2C0;
 char pad2C1[3];
 LivingWorldEyeTower *tower2C4;

};
void Rva0021237E::rva002123BE()
{
 UpdateReceiverView21123 *view=(UpdateReceiverView21123*)this;
 ((Rva00211494*)this)->rva00211494();
 ((Rva002112A9*)this)->rva002112A9();
 if(view->object268) view->object268->rva003EEAB7();
 if(view->tower2C4) view->tower2C4->updateState();
 for(UpdateMapView::iterator it=view->map218.begin();it!=view->map218.end();++it)
  ((UpdateSlot21123*)it->second)->v0C();
 if(!view->hidden2C0 && ((SingletonView21123*)g_00DFEF18)->mode==1 && ((RadarWindowOverrideSource*)TheRva002D3627Host)->rva002D35E6() && !((Rva002B5073*)TheLivingWorldLogic)->rva002B5073(8) && TheMouse)
  TheMouse->_bfme_setEngineVisibility(true);
 ((RadarWindowOverrideSource*)TheRva002D3627Host)->v28();
}

// Native 61246D..612653 (488B); WB B5FF00 confirms mission-start setup,
// map path formatting, replay gate, pause calls and message tag30.
// Input +18 is the map-name string; the original input class is unknown.
// Getter and flag views carry native offsets without claiming full layouts.
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct Bfme939Helper { int get()const; }; extern Bfme939Helper *g_bfme939Helper;
class RecorderClass { public:void stopRecording(); };
class Rva00210C66CmpBoolField { public: bool get() const; };
struct LANGameInfo; extern LANGameInfo *g_Rva00E02EEC;
class GameInfo { public: void setMap(AsciiString); }; extern GameInfo *TheSkirmishGameInfo;
extern void *g_00DFE758;
void InitGameLogicRandom(unsigned);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class GameMessage { public: void appendIntegerArgument(int); };
class MessageStream { public:
virtual void v00();virtual void v04();virtual void v08();virtual void v0C();virtual void v10();virtual void v14();virtual void v18();virtual void v1C();virtual void v20();virtual void v24();virtual void v28();virtual void v2C();virtual void v30();virtual void v34();virtual void v38();virtual void v3C();virtual void v40();virtual void v44();virtual GameMessage *append(int);
}; extern MessageStream *TheMessageStream;
class Rva0049CB86LeaField { public:void *get()const; };
class Rva001D96ECLeaField { public:void *get()const; };
class Rva003EFDD7LeaField { public:void *get()const; };
class Rva0053B8E5LeaField { public:void *get()const; };
struct OpaqueRefElement4;
class Rva0023DC8E {public:void rva0023DC8E(const AsciiString&);};
class Rva0023DCCE {public:void rva0023DCCE(const AsciiString&,const OpaqueRefElement4&,const OpaqueRefElement4&);};
class Rva002D3627Host; extern Rva002D3627Host *TheRva002D3627Host;
class InGameUI {public:virtual void v00();virtual void v04();virtual void v08();virtual void v0C();virtual void v10();virtual void v14();virtual void v18();virtual void v1C();virtual void v20();virtual void v24();};extern InGameUI *TheInGameUI;
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
struct LogicMissionView {char pad[0xEC];int mission;};
struct Rva0021246DInput {char pad[0x18];AsciiString name;};
void Rva0021237E::rva0021246D(Rva0021246DInput *input)
{
 if(!g_bfme939Helper->get()) ((RecorderClass*)g_bfme939Helper)->stopRecording();
 TheGameLogic->rva00376E92(false,false);
 TheMouse->_bfme_setEngineVisibility(false);
 rva0021237E();
 const char *base=input->name.str();
 AsciiString map;
 map.format("maps\\%s\\%s.map",base,base);
 ((AsciiString*)((char*)g_00DFE758+0xAC0))->format(&map);
 if(!g_Rva00E02EEC || !((Rva00210C66CmpBoolField*)TheGameLogic)->get())
  { if(TheSkirmishGameInfo) InitGameLogicRandom(timeGetTime()); else InitGameLogicRandom(0); }
 GameMessage *message=TheMessageStream->append(30);
 TheGameLogic->rva0023CD9E(true,1,false);
 TheGameLogic->rva0023CD9E(false,1,false);
 ((Rva0023DC8E*)TheGameLogic)->rva0023DC8E(*(const AsciiString*)((Rva0049CB86LeaField*)input)->get());
 ((Rva0023DCCE*)TheGameLogic)->rva0023DCCE(*(const AsciiString*)((Rva0053B8E5LeaField*)input)->get(),*(const OpaqueRefElement4*)((Rva003EFDD7LeaField*)input)->get(),*(const OpaqueRefElement4*)((Rva001D96ECLeaField*)input)->get());
 ((RadarWindowOverrideSource*)TheRva002D3627Host)->rva002D4240(true);
 TheInGameUI->v24();
 TheMouse->rva001EEA6D(UnicodeString::TheEmptyString,-1,0,1.0f);
 if(g_Rva00E02EEC && TheGameLogic->m_114==1) message->appendIntegerArgument(1);
 else if(g_Rva00E02EEC && TheGameLogic->m_114==2) message->appendIntegerArgument(5);
 else {
  if(TheSkirmishGameInfo) {TheSkirmishGameInfo->setMap(map);message->appendIntegerArgument(2);}
  else message->appendIntegerArgument(0);
  message->appendIntegerArgument(((LogicMissionView*)TheLivingWorldLogic)->mission);
  message->appendIntegerArgument(0);
 }
}
