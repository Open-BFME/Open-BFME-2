// cl: /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// platformsdk
// stlport
// ?rva0021237E@Rva0021237E@@QAEXXZ @0x0021237E 64B
// The target walks the four-byte range at this+0x2CC, passes each word to
// TheAudio's slot 0x6C, then erases the whole range through rowed vector erase
// 0x0031BD55. TheAudio is pinned at VA 0x00DFE6E8. The neighboring 0x0021246D
// caller invokes this body at +0x48B. The handle interpretation follows the
// target call and AudioManager's established removeAudioEvent slot; the owning
// class identity remains address-derived.
#include <windows.h>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

#include <cstddef>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

typedef unsigned int AudioHandle;

#include "../../../Include/Common/GameAudio.h"

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
	void rva002126BB();
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
#include "../../../Include/GameClient/WindowVideoManagerClass.h"
typedef _STL::hash_map<const GameWindow*,WindowVideo*,WindowVideoManager::hashConstGameWindowPtr,_STL::equal_to<const GameWindow*> > UpdateMapView;
struct UpdateSlot21123 { virtual void v00();virtual void v04();virtual void v08();virtual void v0C(); };
struct Rva00211494 { void rva00211494(); };
struct Rva002112A9 { void rva002112A9(); };
struct Rva003EEAB7 { void rva003EEAB7(); };
class LivingWorldEyeTower { friend struct Rva0021237E; void updateState(); };
struct Rva002B5073 { bool rva002B5073(int); };
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
// LINK: rva002C004F's rowed home is Rva002BFF5A (Rva002C004FErase.cpp, 0x2C004F);
// the old Rva002D3627Host spelling named an unresolved symbol. The global keeps
// its pointer type, the call binds the rowed member through a cast.
class Rva002D3627Host;
class Rva002BFF5A { public: void rva002C004F(const char *name); }; class LivingWorld; extern LivingWorld *TheLivingWorld;
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
struct SingletonView21123 { char pad14[0x14];int mode; };
class RadarWindowOverrideSource {
public:
 virtual void v00();virtual void v04();virtual void v08();virtual void v0C();virtual void v10();virtual void v14();virtual void v18();virtual void v1C();virtual void v20();virtual void v24();virtual void v28();
 bool rva002D35E6() const;
 void rva002D4240(bool);
};
struct RGBColor;
#include "../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
struct UpdateReceiverView21123 {
 char pad[0x218];
 UpdateMapView map218;
 char gap[(0x268-0x218)-sizeof(UpdateMapView)];
 Rva003EEAB7 *object268;
 char pad26C[0x2C0-0x26C];
 bool hidden2C0;
 char pad2C1[3];
 LivingWorldEyeTower *m_eyeTower;

};
void Rva0021237E::rva002123BE()
{
 UpdateReceiverView21123 *view=(UpdateReceiverView21123*)this;
 ((Rva00211494*)this)->rva00211494();
 ((Rva002112A9*)this)->rva002112A9();
 if(view->object268) view->object268->rva003EEAB7();
 if(view->m_eyeTower) view->m_eyeTower->updateState();
 for(UpdateMapView::iterator it=view->map218.begin();it!=view->map218.end();++it)
  ((UpdateSlot21123*)it->second)->v0C();
 if(!view->hidden2C0 && ((SingletonView21123*)((Rva002D3627Host *)TheLivingWorld))->mode==1 && theRadarWindowOverrideSource->rva002D35E6() && !((Rva002B5073*)TheLivingWorldLogic)->rva002B5073(8) && TheMouse)
  TheMouse->_bfme_setEngineVisibility(true);
 theRadarWindowOverrideSource->v28();
}

// Native 61246D..612653 (488B); WB B5FF00 confirms mission-start setup,
// map path formatting, replay gate, pause calls and message tag30.
// Input +18 is the map-name string; the original input class is unknown.
// Getter and flag views carry native offsets without claiming full layouts.
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct Bfme939Helper { int get()const; }; class RecorderClass; extern RecorderClass *TheRecorder;
#include "../../../Include/Common/RecorderClass.h"
class Rva00210C66CmpBoolField { public: bool get() const; };
extern class GameInfo *TheGameInfo;
#include "../../../Include/GameNetwork/GameInfo.h"
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
void InitGameLogicRandom(unsigned);
#include "../../../Include/Common/MessageStream.h"
extern MessageStream *TheMessageStream;
class Rva0049CB86LeaField { public:void *get()const; };
struct RvaPair001D9F62; namespace _STL { template<class T> class allocator; template<class T, class A> class vector; }
// 0x001D96EC is rowed as AudioEventInfo::getSoundsVector.
class AudioEventInfo { public:const _STL::vector<RvaPair001D9F62, _STL::allocator<RvaPair001D9F62> > &getSoundsVector()const; };
class Rva003EFDD7LeaField { public:void *get()const; };
class Rva0053B8E5LeaField { public:void *get()const; };
struct OpaqueRefElement4;
class Rva0023DC8E {public:void rva0023DC8E(const AsciiString&);};
class Rva0023DCCE {public:void rva0023DCCE(const AsciiString&,const OpaqueRefElement4&,const OpaqueRefElement4&);};
#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
struct LogicMissionView {char pad[0xEC];int mission;};
struct Rva0021246DInput {char pad[0x18];AsciiString name;};
void Rva0021237E::rva0021246D(Rva0021246DInput *input)
{
 if(!((Bfme939Helper *)TheRecorder)->get()) TheRecorder->stopRecording();
 TheGameLogic->clearGameData(false,false);
 TheMouse->_bfme_setEngineVisibility(false);
 rva0021237E();
 const char *base=input->name.str();
 AsciiString map;
 map.format("maps\\%s\\%s.map",base,base);
 ((AsciiString*)((char*)TheWritableGlobalData+0xAC0))->format(&map);
 if(!TheGameInfo || !((Rva00210C66CmpBoolField*)TheGameLogic)->get())
  { if((*(GameInfo **)&TheSkirmishGameInfo)) InitGameLogicRandom(timeGetTime()); else InitGameLogicRandom(0); }
 GameMessage *message=TheMessageStream->appendMessage(GameMessage::MSG_NEW_GAME);
 TheGameLogic->rva0023CD9E(true,1,false);
 TheGameLogic->rva0023CD9E(false,1,false);
 ((Rva0023DC8E*)TheGameLogic)->rva0023DC8E(*(const AsciiString*)((Rva0049CB86LeaField*)input)->get());
 ((Rva0023DCCE*)TheGameLogic)->rva0023DCCE(*(const AsciiString*)((Rva0053B8E5LeaField*)input)->get(),*(const OpaqueRefElement4*)((Rva003EFDD7LeaField*)input)->get(),*(const OpaqueRefElement4*)&((AudioEventInfo*)input)->getSoundsVector());
 theRadarWindowOverrideSource->rva002D4240(true);
 TheInGameUI->reset();
 TheMouse->rva001EEA6D(UnicodeString::TheEmptyString,-1,0,1.0f);
 if(TheGameInfo && TheGameLogic->m_114==1) message->appendIntegerArgument(1);
 else if(TheGameInfo && TheGameLogic->m_114==2) message->appendIntegerArgument(5);
 else {
  if((*(GameInfo **)&TheSkirmishGameInfo)) {(*(GameInfo **)&TheSkirmishGameInfo)->setMap(map);message->appendIntegerArgument(2);}
  else message->appendIntegerArgument(0);
  message->appendIntegerArgument(((LogicMissionView*)TheLivingWorldLogic)->mission);
  message->appendIntegerArgument(0);
 }
}

// Beacon cleanup: native 6126BB..612728 (109B).
// WB B608E0/B609F0 confirms name+4, destructor flag0 and table erasure.
// CreateBeaconObject independently identifies this+218 as an int-key beacon
// map. UpdateMapView remains solely an ABI projection of the folded methods.
struct BeaconCleanupView21126 { virtual void *destroy(unsigned flags); AsciiString name; };
void Rva0021237E::rva002126BB()
{
 UpdateMapView *map=(UpdateMapView*)((char*)this+0x218);
 for(UpdateMapView::iterator it=map->begin();it!=map->end();++it) {
  BeaconCleanupView21126 *beacon=(BeaconCleanupView21126*)it->second;
  if(beacon) {
   ((Rva002BFF5A *)((Rva002D3627Host *)TheLivingWorld))->rva002C004F(beacon->name.str());
   ::operator delete(beacon->destroy(0));
  }
 }
 map->clear();
}
