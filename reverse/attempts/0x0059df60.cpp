// ?rva0059DF60@Rva0059E242@@UAEXXZ
// partial score=0.9 date=2026-10-07
// cl: /O2 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
#include "Common/BfmeAudioEventPrefix136.h"

struct Rva0059DF60EventSource { char pad[0x10]; OpaqueRefElement4 m_10; };
struct Rva0059DF60Sequence { char pad[0x13c]; int m_13c; };
struct Rva0059DF60Owner { char pad[0x1c]; Rva0059DF60Sequence *m_1c; };
class Rva005391A9 { public: void rva005391A9(); };
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
    virtual void rva0059DF60();
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
        BfmeEventPositionView position(0.0f, 0.0f, 0.0f);
        position.x = m_18;
        position.y = m_1c;
        position.z = m_20;
        BfmeAudioEventPrefix136 event(m_14->m_10, position, 1);
        if (m_38 != 0)
            event.m_int70 = m_38->m_1c->m_13c;
        reinterpret_cast<Rva0059DF60AudioView *>(TheAudio)->addAudioEvent(&event);
    }
    ((Rva005391A9 *)this)->rva005391A9();
}
