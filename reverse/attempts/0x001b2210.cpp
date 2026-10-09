// ?rva001B2210@BFME2Encoding1MotionChannel@@QAEXPAIIIPAM1@Z
// partial score=0.9 date=2026-10-09
// ?rva001B2210@BFME2Encoding1MotionChannel@@QAEXPAIIIPAM1@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Oy-
// Scalar encoding 1 decoder. `volatile unsigned fi` reproduces the retail memory-resident loop
// counter (46 differing rows instead of 91); retail uses INC where volatile emits ADD, and fi is
// not really volatile there, so the true lever (what keeps fi and f in the dead argument slots)
// is still unknown. See the exact Vector3/quaternion twins for the rest of the structure.
class ChunkLoadClass;
struct Slot1 { float v; };
class Vector3 { public: float X, Y, Z; };
class BFME2MotionChannel {
public:
    virtual bool Load(ChunkLoadClass &);
    virtual ~BFME2MotionChannel();
    virtual int UnknownSlot2();
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual int UnknownSlot6();
    int Type, Pivot, Count, Components;
};
extern float filtertable[256];
class BFME2StreamMotionChannel : public BFME2MotionChannel {
public:
    float Scale;
    float Initial[3];
    unsigned int pad24;
    unsigned char *Data;
};
class BFME2Encoding1MotionChannel : public BFME2StreamMotionChannel {
public:
    void rva001B2210(unsigned int *state, unsigned int from, unsigned int frame, float *value0, float *value1);
};
void BFME2Encoding1MotionChannel::rva001B2210(unsigned int *state, unsigned int from, unsigned int frame, float *value0, float *value1)
{
    Slot1 last;
    if (from > frame) {
        from = 0;
        last = *(const Slot1 *)Initial;
    } else
        last = *(const Slot1 *)state;
    unsigned char *packet = Data + (from >> 4) * 9;
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0)
                *(Slot1 *)value0 = last;
            *(Slot1 *)value1 = last;
            return;
        }
        float filter = filtertable[*packet] * Scale;
        volatile unsigned int fi = from & 0xF;
        from &= ~0xFu;
        unsigned char *p = packet + 1 + ((from & 0xF) >> 1);
        for (; fi < 16; ++fi) {
            unsigned int f = from + fi;
            if (f == frame)
                *value0 = last.v;
            else if (f == frame + 1) {
                *value1 = last.v;
                break;
            }
            int bit = fi & 1;
            int factor = bit ? (signed char)*p >> 4 : (signed char)(*p << 4) >> 4;
            p += bit;
            last.v += (float)factor * filter;
        }
        packet += 9;
        from += 16;
        if (from > frame)
            value0 = 0;
    }
}
