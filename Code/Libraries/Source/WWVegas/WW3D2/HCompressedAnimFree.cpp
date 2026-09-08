// cl: /O2 /G7 /DNDEBUG /EHsc
// Retail compressed-animation cleanup at RVA 0x0018FE30.
// The second node type has no recovered source name; the BFME2 prefix marks
// a descriptive reconstruction, not a claim about its original spelling.
void __cdecl operator delete(void *);
void __cdecl operator delete[](void *);
class TimeCodedBitChannelClass { public: ~TimeCodedBitChannelClass(); };
class BFME2MotionChannel {
public:
    virtual void UnknownSlot0();
    virtual ~BFME2MotionChannel();
};
struct NodeCompressedMotionStruct {
    unsigned char ExistingFields[28];
    ~NodeCompressedMotionStruct();
};
struct BFME2CompressedMotionChannels {
    BFME2MotionChannel *Channels[5];
    TimeCodedBitChannelClass *Visibility;
    BFME2CompressedMotionChannels();
    ~BFME2CompressedMotionChannels();
};
BFME2CompressedMotionChannels::BFME2CompressedMotionChannels() : Visibility(0)
{
    for (int i = 0; i < 5; ++i) Channels[i] = 0;
}
class HCompressedAnimClass {
    unsigned char ExistingFields[0x54];
    NodeCompressedMotionStruct *NodeMotion;
    BFME2CompressedMotionChannels *VectorMotion;
    void Free();
};
BFME2CompressedMotionChannels::~BFME2CompressedMotionChannels()
{
    if (Visibility) delete Visibility;
    for (int i = 0; i < 5; ++i) ::delete Channels[i];
}
