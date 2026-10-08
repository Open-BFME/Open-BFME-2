// cl: /MD
// ??0Rva005FAB9E@@QAE@ABUPayload005FAB9E@@@Z, RVA 0x005FAB9E, 30 bytes.
// Ctor storing vtable 0x00879EC4 at +0, zeroing +4, copying 16 bytes from
// arg+0 to this+8 via 4x movsd. Sibling of 0x005FAB16 (vtable 0x879EB4).
// Evidence: caller 0x005FACA8; vtable DIR32 filled by gate.
#include "BattlePromptCallbackPayloadView.h"
struct Rva005FAB9E {
    virtual void _vf();
    int m4;
    Payload005FAB9E m8;
    Rva005FAB9E(const Payload005FAB9E &o);
};
Rva005FAB9E::Rva005FAB9E(const Payload005FAB9E &o) : m4(0), m8(o) {}
