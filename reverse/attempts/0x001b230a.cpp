// ?rva001B230A@BFME2Encoding1MotionChannel@@QAEXPAIIIPAVVector3@@1@Z
// partial score=0.85 date=2026-10-09
// ?rva001B230A@BFME2Encoding1MotionChannel@@QAEXPAIIIPAVVector3@@1@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Oy-
// BFME2 stream motion channel encoding 1 (nibble adaptive delta, 9 byte packets, 16 frames per
// block) Vector3 decoder: continues from cached state/from to frame and writes the values at frame
// and frame+1. Semantics read from retail 1B230A plus BFME1 motchan.cpp AdaptiveDelta decompress
// (donor; stream layout, packet size and two-output fusion are BFME2). Layout: this+0x14 scale,
// +0x18 initial values, +0x28 data, +0xC frame count.
class ChunkLoadClass;
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
    void rva001B230A(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1);
};
void BFME2Encoding1MotionChannel::rva001B230A(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1)
{
    const Vector3 *src;
    if (from <= frame)
        src = (const Vector3 *)state;
    else {
        from = 0;
        src = (const Vector3 *)Initial;
    }
    Vector3 last = *src;
    unsigned char *packet = Data + (from >> 4) * 27;
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0)
                *value0 = last;
            *value1 = last;
            return;
        }
        unsigned int fi0 = from & 0xF;
        from &= ~0xFu;
        for (int vi = 0; vi < 3; ++vi) {
            float filter = filtertable[*packet] * Scale;
            unsigned char *p = packet + 1 + (fi0 >> 1);
            for (unsigned int fi = fi0; fi < 16; ++fi) {
                unsigned int f = from + fi;
                if (f == frame)
                    ((float *)value0)[vi] = ((float *)&last)[vi];
                else if (f == frame + 1) {
                    ((float *)value1)[vi] = ((float *)&last)[vi];
                    break;
                }
                int factor;
                if (fi & 1)
                    factor = (signed char)*p >> 4;
                else
                    factor = (signed char)(*p << 4) >> 4;
                p += fi & 1;
                ((float *)&last)[vi] += (float)factor * filter;
            }
            packet += 9;
        }
        from += 16;
        if (from > frame)
            value0 = 0;
    }
}
