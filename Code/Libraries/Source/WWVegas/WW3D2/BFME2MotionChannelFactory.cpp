// cl: /O1 /G7 /EHsc /DNDEBUG /MD
// Descriptive BFME2 channel types: original retail class names are unrecovered.
// Factory RVA 0x001A46B4 reads the eight-byte on-disk header and dispatches
// encoding 0/1/2. The trailing data member represents the payload convention
// used by W3D headers; only the fixed prefix is read here. Its twelve-byte
// local allocation reproduces the observed stack layout.
// Only Load and destruction are invoked here. UnknownSlot declarations
// preserve observed virtual positions without claiming their original APIs.
// Constructors and table identities are independently established by their
// initialization, load methods, and factory call sites; no table bytes count
// as executable progress.
void * __cdecl operator new[](unsigned int);
class ChunkLoadClass { public: unsigned long Read(void *, unsigned long); unsigned long Cur_Chunk_Length(); unsigned long Seek(unsigned long); };
class BFME2MotionChannel {
public:
    virtual bool Load(ChunkLoadClass &);
    virtual ~BFME2MotionChannel();
    virtual int UnknownSlot2();
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual void UnknownSlot6();
    BFME2MotionChannel();
    int Type, Pivot, Count, Components;
};
class BFME2StreamMotionChannel : public BFME2MotionChannel {
public:
    BFME2StreamMotionChannel();
    virtual bool Load(ChunkLoadClass &);
    virtual ~BFME2StreamMotionChannel();
    unsigned char EncodedHeader[20];
    unsigned char *Data;
};
class BFME2Encoding1MotionChannel : public BFME2StreamMotionChannel {
public:
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual void UnknownSlot6();
};
class BFME2Encoding2MotionChannel : public BFME2StreamMotionChannel {
public:
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual void UnknownSlot6();
};
class BFME2Encoding0MotionChannel : public BFME2MotionChannel {
public:
    BFME2Encoding0MotionChannel();
    virtual bool Load(ChunkLoadClass &);
    virtual ~BFME2Encoding0MotionChannel();
    unsigned short *TimeCodes;
    float *Samples;
};
struct BFME2MotionChannelHeader {
    unsigned char Version, Encoding, Components, Type;
    unsigned short Count, Pivot;
    unsigned long Data[1];
};
BFME2MotionChannel *Load_BFME2MotionChannel(ChunkLoadClass &chunk)
{
    BFME2MotionChannelHeader header;
    if (chunk.Read(&header, sizeof(header) - sizeof(header.Data)) != sizeof(header) - sizeof(header.Data)) return 0;
    if (header.Version != 0) return 0;
    BFME2MotionChannel *channel = 0;
    switch (header.Encoding) {
    case 0: channel = new BFME2Encoding0MotionChannel; break;
    case 1: channel = new BFME2Encoding1MotionChannel; break;
    case 2: channel = new BFME2Encoding2MotionChannel; break;
    }
    if (channel) {
        channel->Type = header.Type;
        channel->Pivot = header.Pivot;
        channel->Count = header.Count;
        channel->Components = header.Components;
        if (!channel->Load(chunk)) {
            ::delete channel;
            return 0;
        }
    }
    return channel;
}

bool BFME2StreamMotionChannel::Load(ChunkLoadClass &chunk)
{
    if (chunk.Read(EncodedHeader, 4) != 4) return false;
    if (chunk.Read(EncodedHeader + 4, Components * 4) != Components * 4) return false;
    unsigned long size = chunk.Cur_Chunk_Length() - 12 - Components * 4;
    Data = new unsigned char[size];
    if (chunk.Read(Data, size) != size) return false;
    return true;
}

bool BFME2Encoding0MotionChannel::Load(ChunkLoadClass &chunk)
{
    TimeCodes = new unsigned short[Count];
    Samples = new float[Components * Count];
    if (chunk.Read(TimeCodes, Count * 2) != Count * 2) return false;
    if (Count & 1) chunk.Seek(2);
    if (chunk.Read(Samples, Components * Count * 4) != Components * Count * 4) return false;
    return true;
}
