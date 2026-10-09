// cl: /O1 /G7 /MD /EHsc /arch:SSE
// BFME1 f98983a7d PlayingAudioConstructor supplies purpose and owning-event
// relationship. Native A8D5F..A8E0A171B and allocation5320F114B prove80B;
// FuncInfo D03F08 proves base10EFCD, stream0C cleanup10F149 and event1C
// cleanup519AB. Native destructorA8E0A releases file20 via AudioFileContainer
// A8A37, so folded zero constructor326BE6 alone does not establish string identity.
// Grouped float member24..2C and type qualifier are codegen views of the
// observed stores, not recovered target declarations; untouched handle08 opaque.

class Rva00051E4D
{
public:
    Rva00051E4D() : m_refCount(0) {}
    virtual ~Rva00051E4D(){}
private:
    volatile long m_refCount;
};

class BfmeStringTailRecord156 {public:~BfmeStringTailRecord156();private:void *ptr;};
class PlayingAudioUnknown0C:public BfmeStringTailRecord156 {public:PlayingAudioUnknown0C();private:int unknown4;};
class OpaqueRefCounted {public:void Release_Ref();};
struct BfmePoolHolder88 {char unknown00[0x88];OpaqueRefCounted ref;};
class BfmePoolRef10 {public:BfmePoolRef10():ptr(0){}~BfmePoolRef10(){if(ptr)ptr->ref.Release_Ref();}private:BfmePoolHolder88 *ptr;};
// Native PlayingAudio dtor releases file20 through A8A37; WorldBuilder names
// the rowed AudioFileContainer dtor there, independent of its folded zero ctor.
class AudioFileContainer {public:AudioFileContainer();~AudioFileContainer();private:void *ptr;};

struct PlayingAudioTriple {float a,b,c;PlayingAudioTriple():a(0.f),b(0.f),c(0.f){}};
struct PlayingAudio : public Rva00051E4D
{
public:
    PlayingAudio();
    virtual ~PlayingAudio();
private:
    void *m_milesHandle;
    PlayingAudioUnknown0C m_stream;
    volatile int m_type;
    volatile int m_status;
    BfmePoolRef10 m_event;
    AudioFileContainer m_file;
    PlayingAudioTriple m_triple24;
    float m_f30;
    float m_f34;
    int m_index;
    float m_f3c;
    float m_f40;
    bool m_b44;
    bool m_b45;
    bool m_b46;
    bool m_b47;
    bool m_b48;
    bool m_b49;
    bool m_b4a;
    bool m_b4b;
    bool m_b4c;
    bool m_b4d;
    bool m_b4e;
    bool m_b4f;
};

PlayingAudio::PlayingAudio() :
    Rva00051E4D(),
    m_stream(),
    m_type(5),
    m_status(1),
    m_event(),
    m_file(),
    m_triple24(),
    m_f30(0.0f),
    m_f34(1.0f),
    m_index(-1),
    m_f3c(1.0f),
    m_f40(0.0f),
    m_b44(false),
    m_b45(false),
    m_b46(false),
    m_b47(false),
    m_b48(false),
    m_b49(false),
    m_b4a(false),
    m_b4b(false),
    m_b4c(false),
    m_b4d(false),
    m_b4e(false),
    m_b4f(false)
{
}

// NativeA8E0A..A8E79 verified111B relocated from the opaque dtor owner;
// native BC5128 counted-base vtable slot0 binds Rva00051E4D deleting29B.
class AudioManager;
extern AudioManager *TheAudio;
class MilesAudioManager {public:void onPlayingAudioDeleted(PlayingAudio&);};
PlayingAudio::~PlayingAudio(){
 if(TheAudio)((MilesAudioManager*)TheAudio)->onPlayingAudioDeleted(*this);
}
