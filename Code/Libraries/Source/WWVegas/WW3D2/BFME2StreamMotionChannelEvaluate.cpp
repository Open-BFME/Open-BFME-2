// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// Slot 3 of the two BFME 2 stream motion channel encodings, retail
// 0x001B28FA (encoding 1, table 0x007D6CD0) and 0x001B2B5F (encoding 2,
// table 0x007D6CEC), 172 bytes each and identical except for the decoder
// they call (0x001B2210 and 0x001B2599, pinned from these call sites).
// The frame splits into whole and fraction; with a cursor the channel's
// cached {frame, value0, value1} record is decoded forward from the cached
// frame and the cursor steps past it (Components * 8 + 4 bytes, the size
// slot 2 reports); without one the decoder starts from the stream header.
// The result is the linear blend of the two decoded values. Slot and
// decoder names are positional: the original API names are not recovered.
// The class layouts are the factory unit's (BFME2MotionChannelFactory.cpp).
class ChunkLoadClass;
class BFME2MotionChannel {
public:
    virtual bool Load(ChunkLoadClass &);
    virtual ~BFME2MotionChannel();
    virtual int UnknownSlot2();
    virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor);
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
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
    void rva001B2210(unsigned int *state, unsigned int from, unsigned int frame, float *value0, float *value1);
};
class BFME2Encoding2MotionChannel : public BFME2StreamMotionChannel {
public:
    virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor);
    void rva001B2599(unsigned int *state, unsigned int from, unsigned int frame, float *value0, float *value1);
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
