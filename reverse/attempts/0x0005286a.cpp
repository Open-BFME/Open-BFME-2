// ?rva0005286A@MilesAudioManager@@QAE?AVBfmePoolRef10@@PAVAudioEventRTS@@H@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
struct BfmeAudioEventPrefix136;
class OpaqueRefCounted { public: void Release_Ref(); };
struct BfmePoolHolder88;
class GameMessageList;
class GameMessage { public: void friend_setList(GameMessageList *); };
class AudioEventRTS {
public:
 void setPlayingHandle(int handle) { reinterpret_cast<GameMessage *>(this)->friend_setList(reinterpret_cast<GameMessageList *>(handle)); }
 void rva002D9ADC();
 void generatePlayInfo();
};
class Rva005813E { public: Rva005813E(const BfmeAudioEventPrefix136 &); private: char opaque[0x90]; };
class BfmePoolRef10 {
public:
 BfmePoolRef10(BfmePoolHolder88 *);
 BfmePoolRef10(const BfmePoolRef10 &);
 ~BfmePoolRef10() { if (ptr) reinterpret_cast<OpaqueRefCounted *>((char *)ptr+0x88)->Release_Ref(); }
 AudioEventRTS *operator->() const { return ptr; }
private: AudioEventRTS *ptr;
};
class MilesAudioManager {
public:
 BfmePoolRef10 rva0005286A(AudioEventRTS *,int);
 unsigned allocateNewHandle() { return nextHandle++; }
private: char unknown[0xd0]; unsigned nextHandle;
};
BfmePoolRef10 MilesAudioManager::rva0005286A(AudioEventRTS *event,int keepHandle) {
 BfmePoolRef10 audioEvent(reinterpret_cast<BfmePoolHolder88 *>(new Rva005813E(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(event))));
 if(!keepHandle) audioEvent->setPlayingHandle(allocateNewHandle());
 audioEvent->rva002D9ADC();
 audioEvent->generatePlayInfo();
 return audioEvent;
}
