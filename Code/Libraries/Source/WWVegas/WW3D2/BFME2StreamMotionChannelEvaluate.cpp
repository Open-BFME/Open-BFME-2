// cl: /DNDEBUG /MD
//
// Slots 3, 4 and 5 of the two BFME 2 stream motion channel encodings: slot
// 3 at 0x001B28FA (encoding 1, table 0x007D6CD0) and 0x001B2B5F (encoding
// 2, table 0x007D6CEC), 172 bytes each; slot 4 at 0x001B29A6 and
// 0x001B2C0B, 280 bytes each; slot 5 at 0x001B2ABE and 0x001B2D23, 161
// bytes each. The twins are identical except for the decoder they call
// (scalar 0x001B2210/0x001B2599, vector 0x001B230A/0x001B267B, quaternion
// 0x001B2450/0x001B27AB, pinned from these call sites).
// The frame splits into whole and fraction; with a cursor the channel's
// cached {frame, value0, value1} record is decoded forward from the cached
// frame and the cursor steps past it (Components * 8 + 4 bytes, the size
// slot 2 reports); without one the decoder starts from the stream header.
// Slot 3 blends the two decoded floats linearly, slot 4 two Vector3s per
// component; slot 5 decodes two
// quaternions and blends them through BFME2_Nlerp (0x00717550). Slot and
// decoder names are positional: the original API names are not recovered.
// The class layouts are the factory unit's (BFME2MotionChannelFactory.cpp).
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

struct BFME2StreamCache
{
    unsigned int Frame;
    float Value0;
    float Value1;
};

static inline float Bfme_Lerp(float a, float b, float t)
{
    return (b - a) * t + a;
}

void BFME2Encoding1MotionChannel::UnknownSlot3(float frame, float *value, unsigned char **cursor)
{
    int whole = (int)frame;
    frame -= (float)whole;
    if (cursor) {
        BFME2StreamCache *cache = (BFME2StreamCache *)*cursor;
        float *value0 = &cache->Value0;
        float *value1 = value0 + 1;
        rva001B2210((unsigned int *)value0, cache->Frame, whole, value0, value1);
        cache->Frame = whole;
        *value = Bfme_Lerp(*value0, *value1, frame);
        *cursor += Components * 8 + 4;
    } else {
        float value0, value1;
        rva001B2210((unsigned int *)(EncodedHeader + 4), 0, whole, &value0, &value1);
        *value = Bfme_Lerp(value0, value1, frame);
    }
}

void BFME2Encoding2MotionChannel::UnknownSlot3(float frame, float *value, unsigned char **cursor)
{
    int whole = (int)frame;
    frame -= (float)whole;
    if (cursor) {
        BFME2StreamCache *cache = (BFME2StreamCache *)*cursor;
        float *value0 = &cache->Value0;
        float *value1 = value0 + 1;
        rva001B2599((unsigned int *)value0, cache->Frame, whole, value0, value1);
        cache->Frame = whole;
        *value = Bfme_Lerp(*value0, *value1, frame);
        *cursor += Components * 8 + 4;
    } else {
        float value0, value1;
        rva001B2599((unsigned int *)(EncodedHeader + 4), 0, whole, &value0, &value1);
        *value = Bfme_Lerp(value0, value1, frame);
    }
}

void BFME2Encoding1MotionChannel::UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor)
{
    int whole = (int)frame;
    frame -= (float)whole;
    if (cursor) {
        unsigned int *cache = (unsigned int *)*cursor;
        Quaternion *value0 = (Quaternion *)(cache + 1);
        rva001B2450((unsigned int *)value0, cache[0], whole, value0, value0 + 1);
        cache[0] = whole;
        BFME2_Nlerp(*value, value0[0], value0[1], frame);
        *cursor += Components * 8 + 4;
    } else {
        Quaternion value0, value1;
        rva001B2450((unsigned int *)(EncodedHeader + 4), 0, whole, &value0, &value1);
        BFME2_Nlerp(*value, value0, value1, frame);
    }
}

void BFME2Encoding2MotionChannel::UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor)
{
    int whole = (int)frame;
    frame -= (float)whole;
    if (cursor) {
        unsigned int *cache = (unsigned int *)*cursor;
        Quaternion *value0 = (Quaternion *)(cache + 1);
        rva001B27AB((unsigned int *)value0, cache[0], whole, value0, value0 + 1);
        cache[0] = whole;
        BFME2_Nlerp(*value, value0[0], value0[1], frame);
        *cursor += Components * 8 + 4;
    } else {
        Quaternion value0, value1;
        rva001B27AB((unsigned int *)(EncodedHeader + 4), 0, whole, &value0, &value1);
        BFME2_Nlerp(*value, value0, value1, frame);
    }
}

void BFME2Encoding1MotionChannel::UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor)
{
    int whole = (int)frame;
    frame -= (float)whole;
    if (cursor) {
        unsigned int *cache = (unsigned int *)*cursor;
        Vector3 *value0 = (Vector3 *)(cache + 1);
        Vector3 *value1 = value0 + 1;
        rva001B230A((unsigned int *)value0, cache[0], whole, value0, value1);
        cache[0] = whole;
        value->X = Bfme_Lerp(value0->X, value1->X, frame);
        value->Y = Bfme_Lerp(value0->Y, value1->Y, frame);
        value->Z = Bfme_Lerp(value0->Z, value1->Z, frame);
        *cursor += Components * 8 + 4;
    } else {
        Vector3 value0, value1;
        rva001B230A((unsigned int *)(EncodedHeader + 4), 0, whole, &value0, &value1);
        value->X = Bfme_Lerp(value0.X, value1.X, frame);
        value->Y = Bfme_Lerp(value0.Y, value1.Y, frame);
        value->Z = Bfme_Lerp(value0.Z, value1.Z, frame);
    }
}

void BFME2Encoding2MotionChannel::UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor)
{
    int whole = (int)frame;
    frame -= (float)whole;
    if (cursor) {
        unsigned int *cache = (unsigned int *)*cursor;
        Vector3 *value0 = (Vector3 *)(cache + 1);
        Vector3 *value1 = value0 + 1;
        rva001B267B((unsigned int *)value0, cache[0], whole, value0, value1);
        cache[0] = whole;
        value->X = Bfme_Lerp(value0->X, value1->X, frame);
        value->Y = Bfme_Lerp(value0->Y, value1->Y, frame);
        value->Z = Bfme_Lerp(value0->Z, value1->Z, frame);
        *cursor += Components * 8 + 4;
    } else {
        Vector3 value0, value1;
        rva001B267B((unsigned int *)(EncodedHeader + 4), 0, whole, &value0, &value1);
        value->X = Bfme_Lerp(value0.X, value1.X, frame);
        value->Y = Bfme_Lerp(value0.Y, value1.Y, frame);
        value->Z = Bfme_Lerp(value0.Z, value1.Z, frame);
    }
}
