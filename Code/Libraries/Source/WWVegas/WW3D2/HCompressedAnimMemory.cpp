// cl: /DNDEBUG /EHsc
// ?rva0018FB70@HCompressedAnimClass@@UAEHXZ @0x0018FB70 166B
// Retail vtable 0x007D5D88 slot 22 offset 0x58 of ctor 0x0018F0E0.
// BFME2 VectorMotion (24B rows at +0x58) plus NodeMotion (28B rows at +0x54)
// memory sum with base 0x5C; BFME1 hcanim.cpp NodeCompressedMotionStruct
// Get_Channel_Memory_Usage pattern; rowed callees 0x0018F7B0 and 0x00195EE0
// plus virtual channel slot 6 offset 0x18; NumNodes at +0x48; callers 0.
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
    int Get_Channel_Memory_Usage();
};
struct BFME2CompressedMotionChannels {
    BFME2MotionChannel *Channels[5];
    TimeCodedBitChannelClass *Visibility;
};
class HCompressedAnimClass {
public:
    virtual int rva0018FB70();
    unsigned char Pad0[0x3C];
    int Key;
    int NumFrames;
    int NumNodes;
    int Flavor;
    float FrameRate;
    NodeCompressedMotionStruct *NodeMotion;
    BFME2CompressedMotionChannels *VectorMotion;
};
int HCompressedAnimClass::rva0018FB70()
{
    int size = 0x5C;
    if (VectorMotion != 0) {
        for (int i = 0; i < NumNodes; ++i) {
            BFME2CompressedMotionChannels &node = VectorMotion[i];
            int nodeSize = 0;
            for (int j = 0; j < 5; ++j) {
                if (node.Channels[j] != 0)
                    nodeSize += node.Channels[j]->UnknownSlot6();
            }
            if (node.Visibility != 0)
                nodeSize += node.Visibility->Get_Channel_Memory_Usage();
            size += nodeSize;
        }
    } else {
        for (int i = 0; i < NumNodes; ++i)
            size += NodeMotion[i].Get_Channel_Memory_Usage();
    }
    return size;
}
