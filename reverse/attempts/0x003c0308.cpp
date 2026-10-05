// ?Rva003C0308Do@@YGXHH_NHABVAsciiString@@H@Z
// partial score=0.97 date=2026-10-05
// ?Rva003C0308Do@@YGXHH_NHABVAsciiString@@H@Z
// partial score=0.97 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc /O1 /G7
// ?Rva003C0308Do@@YGXHH_NHABVAsciiString@@H@Z @0x003C0308 285B via audio-event stack recreate with TheAudio Weapon PlayerList ScriptEngine callers
//
// SEAT-7 PASS (2026-10-05): two levers moved this from nd=224/first=+0x17/275B
// to nd=148/first=+0x0C/281B, and both are load-bearing:
//  (1) `volatile bool noActive` for the v8c third argument.  Without volatile
//      MSVC folds the test into the call sequence and loads TheAudio's vtable
//      into EAX, so the bool must also live in AL and the call becomes
//      [eax+0x8c].  Retail loads the vtable into EDX and materialises the bool
//      with `sete dl`, so the two must be separate values; volatile is what
//      forces a stack round-trip that keeps them apart.
//  (2) The pointer must be read from TheAudio afresh for EACH virtual call.
//      Hoisting it into a named `AudioManager *audio` lets the compiler keep
//      one vtable in a register and reuses it, which drops 281B->271B and
//      moves the first diff back to +0x10.  Retail reloads 0xDFE6E8 before the
//      v12c and again before playBfme, so only the v8c call uses the local.
// Measured, no effect: volatile on the audio pointer alone (nd=244), dropping
// volatile from the bool (nd=224), an explicit inner scope for the event
// object and a flat no-scope form (nd=155 each), inline Release_Ref vs the
// named rc local (identical), and the ternary form of the p4 sentinel clamp
// (exact 285B but nd=238, so the size match is coincidental, not progress).
// Remaining: retail emits `mov byte ptr [ebp-4], bl` before the event dtor
// call at +0x118 and this build omits it, so the tail is 4 bytes short; the
// remaining body also still needs the EDX vtable for the FIRST call.
// ?Rva003C0308Do@@YGXHH_NHABVAsciiString@@H@Z present-unmatched
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

class Weapon
{
public:
    void setLeechRangeActive(bool v);
};

class Rva0033F15DDwordSlot
{
public:
    void set(int v);
};

class BfmeStringTailRecord144
{
public:
    virtual ~BfmeStringTailRecord144();
};

class AudioManager
{
public:
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03(); virtual void d04();
    virtual void d05(); virtual void d06(); virtual void d07(); virtual void d08(); virtual void d09();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void playBfme(BfmeAudioEventPrefix136 *e);
    virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void v8c(int a, int b, bool c);
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40();
    virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45();
    virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50();
    virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60();
    virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65();
    virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70();
    virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74();
    virtual void v12c(const OpaqueRefElement4 *a, int b);
};
extern AudioManager *TheAudio;

struct PlayerMid
{
    char m_pad[0x54];
    int m_val;
};
class PlayerList
{
public:
    char m_pad[0x10];
    PlayerMid *m_mid;
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
    AsciiString rva00205CE7(AsciiString a);
};
extern ScriptEngine *g_Va009FE16C;

void __stdcall Rva003C0308Do(int p1, int p2, bool p3, int p4, const AsciiString &p5, int p6)
{
    AudioManager *audio = TheAudio;
    volatile bool noActive = (*(unsigned char *)&p2 == 0);
    audio->v8c(0, p6, noActive);
    int esi = p4;
    if (esi < 1) {
        if (esi != -12345)
            esi = 1;
    }
    TheAudio->v12c((const OpaqueRefElement4 *)&p2, p1);
    {
        BfmeAudioEventPrefix136 tmp(*(const OpaqueRefElement4 *)&p2, 0);
        ((Weapon *)&tmp)->setLeechRangeActive(p3);
        ((Rva0033F15DDwordSlot *)&tmp)->set(ThePlayerList->m_mid->m_val);
        tmp.m_int78 = p6;
        tmp.m_int7C = esi;
        if (!((const StringBase<char> &)p5).isEmpty()) {
            tmp.m_string84.set(g_Va009FE16C->rva00205CE7(p5));
        }
        TheAudio->playBfme(&tmp);
    }
    OpaqueRefCounted *rc = *(OpaqueRefCounted **)&p2;
    if (rc != 0)
        rc->Release_Ref();
}
