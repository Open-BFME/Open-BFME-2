// ?rva001B267B@BFME2Encoding2MotionChannel@@QAEXPAIIIPAVVector3@@1@Z
// partial score=0.75 date=2026-10-09
// ?rva001B267B@BFME2Encoding2MotionChannel@@QAEXPAIIIPAVVector3@@1@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Oy-
// BFME2 stream motion channel encoding 2 Vector3 decoder (17-byte packets: filter byte plus 16
// unsigned bytes biased by 0x80; filter = table * scale * 0.0625 through x87). Same fused
// two-output structure as the exact encoding 1 decoders (BFME2Encoding1MotionChannelDecoders.cpp);
// this body is 304B = target size with identical instruction sequence; remaining delta is register
// allocation (retail keeps block base in ECX, vi in EBX, fi/f in the dead argument slots).
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
class BFME2Encoding2MotionChannel : public BFME2StreamMotionChannel {
public:
    void rva001B267B(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1);
};
void BFME2Encoding2MotionChannel::rva001B267B(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1)
{
    Vector3 last;
    if (from <= frame)
        last = *(const Vector3 *)state;
    else {
        from = 0;
        last = *(const Vector3 *)Initial;
    }
    unsigned char *packet = Data + (from >> 4) * 51;
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0)
                *value0 = last;
            *value1 = last;
            return;
        }
        unsigned int fi0 = from & 0xF;
        from &= ~0xFu;
        for (int vi = 0; vi < 3; ++vi, packet += 17) {
            float filter = (float)(filtertable[*packet] * Scale * 0.0625);
            unsigned int f = from + fi0;
            unsigned int fi = fi0;
            for (; fi < 16; ++fi, ++f) {
                if (f == frame)
                    ((float *)value0)[vi] = ((float *)&last)[vi];
                else if (f == frame + 1) {
                    ((float *)value1)[vi] = ((float *)&last)[vi];
                    break;
                }
                int factor = (int)packet[fi + 1] - 128;
                ((float *)&last)[vi] += (float)factor * filter;
            }
        }
        from += 16;
        if (from > frame)
            value0 = 0;
    }
}
