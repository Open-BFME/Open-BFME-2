// cl: /DNDEBUG /EHsc
// Retail compressed-animation cleanup at RVA 0x0018FE30.
// The second node type has no recovered source name; the BFME2 prefix marks
// a descriptive reconstruction, not a claim about its original spelling.
void __cdecl operator delete(void *);
void __cdecl operator delete[](void *);
class TimeCodedBitChannelClass { public: ~TimeCodedBitChannelClass(); int Get_Channel_Memory_Usage(); };
class BFME2MotionChannel {
public:
    virtual void UnknownSlot0();
    virtual ~BFME2MotionChannel();
    virtual void UnknownSlot2();
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual int UnknownSlot6();
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
    int Get_Channel_Memory_Usage();
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
void HCompressedAnimClass::Free()
{
    delete[] NodeMotion;
    NodeMotion = 0;
    delete[] VectorMotion;
    VectorMotion = 0;
}
// ?Get_Channel_Memory_Usage@BFME2CompressedMotionChannels@@QAEHXZ @0x0018F8C0 60B
// Retail single VectorMotion node (24B: 5 channels + visibility at +0x14) memory sum.
// Evidence: BFME1 hcanim.cpp NodeCompressedMotionStruct::Get_Channel_Memory_Usage pattern;
// rowed TimeCodedBitChannel 0x00195EE0 callee; virtual channel slot 6 offset 0x18;
// stride 24 proven by Free array delete and ctor/dtor rows; callers 0; BFME2 prefix descriptive.
int BFME2CompressedMotionChannels::Get_Channel_Memory_Usage()
{
    int size = 0;
    for (int i = 0; i < 5; ++i) {
        if (Channels[i])
            size += Channels[i]->UnknownSlot6();
    }
    if (Visibility)
        size += Visibility->Get_Channel_Memory_Usage();
    return size;
}
typedef char FirstNodeStrideIs28[(sizeof(NodeCompressedMotionStruct) == 28) ? 1 : -1];
typedef char SecondNodeStrideIs24[(sizeof(BFME2CompressedMotionChannels) == 24) ? 1 : -1];
