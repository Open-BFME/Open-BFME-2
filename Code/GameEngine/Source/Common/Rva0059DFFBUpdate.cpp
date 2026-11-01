// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// stlport
//
// ?rva0059DFFB@Rva0059E242@@UAEXXZ @0x0059DFFB (148B): the sibling of 0x0059DF60
// that plays the second stored sound (source +0x14, sound at +0x14) and returns
// without the trailing call. Same equal-arm receiver on the event argument, plus
// one on the sequence pointer so cl reuses ESI for m_38->m_1c (W7-S2 r4).
#include "Common/BfmeAudioEventPrefix136.h"

struct Rva0059DF60EventSource { char pad[0x10]; OpaqueRefElement4 m_10,m_14; };
struct Rva0059DF60Sequence { char pad[0x13c]; int m_13c; };
struct Rva0059DF60Owner { char pad[0x1c]; Rva0059DF60Sequence *m_1c; };
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
void Rva0059E242::rva0059DFFB()
{
    if (m_14->m_14.referent != 0) {
        BfmeEventPositionView position;
        position.x = m_18;
        position.y = m_1c;
        position.z = m_20;
        BfmeAudioEventPrefix136 event((m_14 ? m_14 : m_14)->m_14, position, 1);
        if (m_38 != 0)
            event.m_int70 = (m_38->m_1c ? m_38->m_1c : m_38->m_1c)->m_13c;
        reinterpret_cast<Rva0059DF60AudioView *>(TheAudio)->addAudioEvent(&event);
    }

}
