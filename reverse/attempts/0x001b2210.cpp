// ?rva001B2210@BFME2Encoding1MotionChannel@@QAEXPAIIIPAM1@Z
// partial score=0.8 date=2026-10-09
// ?rva001B2210@BFME2Encoding1MotionChannel@@QAEXPAIIIPAM1@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Oy-
// BFME2 stream motion channel encoding 1 scalar decoder (nibble adaptive delta, 9 byte packets, 16
// frames per block): continues from the cached state to frame, writing the values at frame and
// frame+1. Structure from BFME1 motchan.cpp AdaptiveDelta decompress; last value is kept as an
// address-taken dword (retail reuses the dead state argument slot for it).
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
    void rva001B2210(unsigned int *state, unsigned int from, unsigned int frame, float *value0, float *value1);
};
void BFME2Encoding1MotionChannel::rva001B2210(unsigned int *state, unsigned int from, unsigned int frame, float *value0, float *value1)
{
    unsigned int lastBits;
    if (from <= frame)
        lastBits = *state;
    else {
        from = 0;
        lastBits = *(unsigned int *)&Initial[0];
    }
    float last = *(float *)&lastBits;
    unsigned char *packet = Data + (from >> 4) * 9;
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0)
                *(unsigned int *)value0 = lastBits;
            *(unsigned int *)value1 = lastBits;
            return;
        }
        float filter = filtertable[*packet] * Scale;
        unsigned int fi = from & 0xF;
        from &= ~0xFu;
        unsigned char *p = packet + 1 + (fi >> 1);
        for (; fi < 16; ++fi) {
            unsigned int f = from + fi;
            if (f == frame)
                *value0 = last;
            else if (f == frame + 1) {
                *value1 = last;
                break;
            }
            int factor;
            if (fi & 1)
                factor = (signed char)*p >> 4;
            else
                factor = (signed char)(*p << 4) >> 4;
            p += fi & 1;
            last += (float)factor * filter;
            *(float *)&lastBits = last;
        }
        packet += 9;
        from += 16;
        if (from > frame)
            value0 = 0;
    }
}
