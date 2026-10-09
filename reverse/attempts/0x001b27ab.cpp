// ?rva001B27AB@BFME2Encoding2MotionChannel@@QAEXPAIIIPAVQuaternion@@1@Z
// partial score=0.6932 date=2026-10-09
// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD
// ZH motchan.cpp AdaptiveDelta decompress is the semantic donor.
// BFME1 revision 874e38488; target caller ABI and factory layout supplied
// by BFME2StreamMotionChannelEvaluate.cpp. Target uses paired output frames,
// fixed 3/4 component packets and signed nibbles or biased bytes.
class ChunkLoadClass;
class Vector3 { public: float X, Y, Z; };
class Quaternion { public: float X, Y, Z, W; };
void BFME2_Nlerp(Quaternion &res, const Quaternion &p, const Quaternion &q, float alpha);
class BFME2MotionChannel {
public:
    virtual bool Load(ChunkLoadClass &);
    virtual ~BFME2MotionChannel();
    virtual int UnknownSlot2();
    virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor);
    virtual void UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor);
    virtual void UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor);
    virtual int UnknownSlot6();
    BFME2MotionChannel();
    int Type, Pivot, Count, Components;
};
class BFME2StreamMotionChannel : public BFME2MotionChannel {
public:
    unsigned char EncodedHeader[20];
    unsigned char *Data;
};
class BFME2Encoding1MotionChannel : public BFME2StreamMotionChannel {
public:
    virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor);
    virtual void UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor);
    virtual void UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor);
    void rva001B230A(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1);
    void rva001B2210(unsigned int *state, unsigned int from, unsigned int frame, float *value0, float *value1);
    void rva001B2450(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1);
};
class BFME2Encoding2MotionChannel : public BFME2StreamMotionChannel {
public:
    virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor);
    virtual void UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor);
    virtual void UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor);
    void rva001B267B(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1);
    void rva001B2599(unsigned int *state, unsigned int from, unsigned int frame, float *value0, float *value1);
    void rva001B27AB(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1);
};


extern float BFME2MotionFilterTable[256];

void BFME2Encoding1MotionChannel::rva001B230A(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1)
{
    Vector3 current;
    if (from > frame) { from = 0; current = *(Vector3 *)(EncodedHeader + 4); }
    else current = *(Vector3 *)state;
    unsigned char *packet = Data + (from >> 4) * (9 * 3);
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0) *value0 = current;
            *value1 = current;
            break;
        }
        unsigned int first = from & 15;
        from &= ~15u;
        for (int vi = 0; vi < 3; ++vi) {
            float filter = BFME2MotionFilterTable[*packet] * *(float *)EncodedHeader;
            unsigned char *data = packet + 1 + (first >> 1);
            for (unsigned int fi = first; fi < 16; ++fi) {
                if (from + fi == frame) ((float *)value0)[vi] = ((float *)&current)[vi];
                else if (from + fi == frame + 1) { ((float *)value1)[vi] = ((float *)&current)[vi]; break; }
                int advance = fi & 1;
                int factor;
                if (advance) factor = (signed char)*data;
                else factor = (signed char)(*data << 4);
                data += advance;
                factor >>= 4;
                ((float *)&current)[vi] += (float)factor * filter;
            }
            packet += 9;
        }
        from += 16;
        if (from > frame) value0 = 0;
    }
}

void BFME2Encoding1MotionChannel::rva001B2450(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1)
{
    Quaternion current;
    if (from > frame) { from = 0; current = *(Quaternion *)(EncodedHeader + 4); }
    else current = *(Quaternion *)state;
    unsigned char *packet = Data + (from >> 4) * (9 * 4);
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0) *value0 = current;
            *value1 = current;
            break;
        }
        unsigned int first = from & 15;
        from &= ~15u;
        for (int vi = 0; vi < 4; ++vi) {
            float filter = BFME2MotionFilterTable[*packet] * *(float *)EncodedHeader;
            unsigned char *data = packet + 1 + (first >> 1);
            for (unsigned int fi = first; fi < 16; ++fi) {
                if (from + fi == frame) ((float *)value0)[vi] = ((float *)&current)[vi];
                else if (from + fi == frame + 1) { ((float *)value1)[vi] = ((float *)&current)[vi]; break; }
                int advance = fi & 1;
                int factor;
                if (advance) factor = (signed char)*data;
                else factor = (signed char)(*data << 4);
                data += advance;
                factor >>= 4;
                ((float *)&current)[vi] += (float)factor * filter;
            }
            packet += 9;
        }
        from += 16;
        if (from > frame) value0 = 0;
    }
}

void BFME2Encoding2MotionChannel::rva001B267B(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1)
{
    Vector3 current;
    if (from > frame) { from = 0; current = *(Vector3 *)(EncodedHeader + 4); }
    else current = *(Vector3 *)state;
    unsigned char *packet = Data + (from >> 4) * (17 * 3);
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0) *value0 = current;
            *value1 = current;
            break;
        }
        unsigned int first = from & 15;
        from &= ~15u;
        for (int vi = 0; vi < 3; ++vi) {
            float filter = BFME2MotionFilterTable[*packet] * *(float *)EncodedHeader * (1.0 / 16.0);
            unsigned int sample_frame = from + first;
            for (unsigned int fi = first; fi < 16; ++fi, ++sample_frame) {
                if (sample_frame == frame) ((float *)value0)[vi] = ((float *)&current)[vi];
                else if (sample_frame == frame + 1) { ((float *)value1)[vi] = ((float *)&current)[vi]; break; }
                int factor = packet[fi + 1] - 128;
                ((float *)&current)[vi] += (float)factor * filter;
            }
            packet += 17;
        }
        from += 16;
        if (from > frame) value0 = 0;
    }
}

void BFME2Encoding2MotionChannel::rva001B27AB(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1)
{
    Quaternion current;
    if (from > frame) { from = 0; current = *(Quaternion *)(EncodedHeader + 4); }
    else current = *(Quaternion *)state;
    unsigned char *packet = Data + (from >> 4) * (17 * 4);
    while (from <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0) *value0 = current;
            *value1 = current;
            break;
        }
        unsigned int first = from & 15;
        from &= ~15u;
        for (int vi = 0; vi < 4; ++vi) {
            float filter = BFME2MotionFilterTable[*packet] * *(float *)EncodedHeader * (1.0 / 16.0);
            unsigned int sample_frame = from + first;
            for (unsigned int fi = first; fi < 16; ++fi, ++sample_frame) {
                if (sample_frame == frame) ((float *)value0)[vi] = ((float *)&current)[vi];
                else if (sample_frame == frame + 1) { ((float *)value1)[vi] = ((float *)&current)[vi]; break; }
                int factor = packet[fi + 1] - 128;
                ((float *)&current)[vi] += (float)factor * filter;
            }
            packet += 17;
        }
        from += 16;
        if (from > frame) value0 = 0;
    }
}
