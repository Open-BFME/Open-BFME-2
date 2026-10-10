// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Oy-
// BFME 2 stream motion channel encoding 1: nibble adaptive-delta decoders, called from the
// slot 3/4/5 evaluators (BFME2StreamMotionChannelEvaluate.cpp). The decoder continues from a
// cached state (first value record, frame) to `frame` and writes the values at `frame` and
// `frame + 1`; blocks are 16 frames, each component packet is a filter byte plus 16 signed
// nibbles (9 bytes). Structure is BFME 1 motchan.cpp AdaptiveDeltaMotionChannelClass::decompress
// (donor, 9cbfb551) fused for two outputs; packet size, component count and layout are read
// from retail 0x001B230A. Layout: Data at +0x28, scale at +0x14, initial values at +0x18,
// frame count at +0xC.
// Codegen: `bit` kept as an int and used for both the select and the pointer step; the vi
// loop advances packet in its increment expression.
class ChunkLoadClass;
class Vector3 { public: float X, Y, Z; };
class Quaternion { public: float X, Y, Z, W; };
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
// Native stream decoders230A/2450 use the separate table at VA DB6C28.
// Legacy AdaptiveDelta decompression18F910 uses DB67D8, whose constructor
// initializes that table. Both image tables have the same16 power-of-ten seeds,
// but they are distinct storage instances; one external global conflates them.
// This descriptive namespace records the stream table's identity and scope;
// its original spelling and initializer owner remain unknown.
// The decode filter table is the data-ledger global ?filtertable@@3PAMA (0x009B6C28,
// BFME2EncodingFilterTableInit.cpp).
extern float filtertable[];
class BFME2StreamMotionChannel : public BFME2MotionChannel {
public:
    float Scale;
    float Initial[4];
    unsigned char *Data;
};
class BFME2Encoding1MotionChannel : public BFME2StreamMotionChannel {
public:
    void rva001B230A(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1);
    void rva001B2450(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1);
};
void BFME2Encoding1MotionChannel::rva001B230A(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1)
{
    Vector3 last;
    if (from > frame) {
        from = 0;
        last = *(const Vector3 *)Initial;
    } else
        last = *(const Vector3 *)state;
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
        for (int vi = 0; vi < 3; ++vi, packet += 9) {
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
                int bit = fi & 1;
                int factor = bit ? (signed char)*p >> 4 : (signed char)(*p << 4) >> 4;
                p += bit;
                ((float *)&last)[vi] += (float)factor * filter;
            }
        }
        from += 16;
        if (from > frame)
            value0 = 0;
    }
}

void BFME2Encoding1MotionChannel::rva001B2450(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1)
{
    Quaternion last;
    if (from > frame) {
        from = 0;
        last = *(const Quaternion *)Initial;
    } else
        last = *(const Quaternion *)state;
    unsigned char *packet = Data + (from >> 4) * 36;
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0)
                *value0 = last;
            *value1 = last;
            return;
        }
        unsigned int fi0 = from & 0xF;
        from &= ~0xFu;
        for (int vi = 0; vi < 4; ++vi, packet += 9) {
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
                int bit = fi & 1;
                int factor = bit ? (signed char)*p >> 4 : (signed char)(*p << 4) >> 4;
                p += bit;
                ((float *)&last)[vi] += (float)factor * filter;
            }
        }
        from += 16;
        if (from > frame)
            value0 = 0;
    }
}
