// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// stlport
//
// ?rva0059DF60@Rva0059E242@@UAEXXZ @0x0059DF60 (155B): play the stored 3D audio
// event: when the event source (+0x14) carries a sound at +0x10, build the audio
// event at the stored position (+0x18/+0x1C/+0x20), attach the sequence handle
// when +0x38 is set, post it through TheAudio, then run 0x005391A9.
// The equal-arm receiver on the event argument keeps cl from sharing the
// &source->m_10 address with the earlier null test (retail tests [eax+0x10]
// directly and adds 0x10 only for the push); W7-S2 r4 receiver-chain generator.
#include "Common/BfmeAudioEventPrefix136.h"

struct Rva0059DF60EventSource { char pad[0x10]; OpaqueRefElement4 m_10,m_14; };
struct Rva0059DF60Sequence { char pad[0x13c]; int m_13c; };
struct Rva0059DF60Owner { char pad[0x1c]; Rva0059DF60Sequence *m_1c; };
#include "../../Include/Common/Rva005391A9.h"
class Rva0059DF60AudioView {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
};
class AudioManager;
extern AudioManager *TheAudio;

class Rva0059E242 {
public:
    virtual ~Rva0059E242();
    virtual void rva0059DF60(); virtual void rva0059DFFB();
private:
    char m_pad04[0x10];
    Rva0059DF60EventSource *m_14;
    float m_18, m_1c, m_20;
    char m_pad24[0x14];
    Rva0059DF60Owner *m_38;
};

// Target: slot 1 of vtable 0x00C70F88; boundary 155B at 0x0059DF60.
void Rva0059E242::rva0059DF60()
{
    if (m_14->m_10.referent != 0) {
        BfmeEventPositionView position;
        position.x = m_18;
        position.y = m_1c;
        position.z = m_20;
        BfmeAudioEventPrefix136 event((m_14 ? m_14 : m_14)->m_10, position, 1);
        if (m_38 != 0)
            event.m_int70 = m_38->m_1c->m_13c;
        reinterpret_cast<Rva0059DF60AudioView *>(TheAudio)->addAudioEvent(&event);
    }
    ((Rva005391A9 *)this)->rva005391A9();
}
