// cl: /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
** BFME1 hcanim.cpp getters adapted to the two BFME2 channel layouts.
*/
// The ctor at 18F0E0 installs vtable BD5D88: visibility is slot 11;
// any-motion is slot 14; X/Y/Z/rotation/visibility presence are slots 15-19.
// Target accesses establish NodeMotion+54 (28-byte rows) and VectorMotion+58
// (24-byte rows). The second row's original source type name is unknown.
// This local view declares only the virtual methods emitted here.
class TimeCodedBitChannelClass
{
public:
    int Get_Bit(int frame);
};
struct NodeMotionStructView
{
    int Flavor;
    void *Channels[5];
    TimeCodedBitChannelClass *Visibility;
};
struct VectorMotionStructView
{
    void *Channels[5];
    TimeCodedBitChannelClass *Visibility;
};
class HCompressedAnimClass
{
public:
    virtual bool Is_Node_Motion_Present(int pivot);
    virtual bool Get_Visibility(int pivot, float frame);
    virtual bool Has_X_Translation(int pivot);
    virtual bool Has_Y_Translation(int pivot);
    virtual bool Has_Z_Translation(int pivot);
    virtual bool Has_Rotation(int pivot);
    virtual bool Has_Visibility(int pivot);
    unsigned char prefix[0x50];
    NodeMotionStructView *NodeMotion;
    VectorMotionStructView *VectorMotion;
};
bool HCompressedAnimClass::Get_Visibility(int pivot, float frame)
{
    if (VectorMotion != 0) {
        if (VectorMotion[pivot].Visibility != 0) {
            return VectorMotion[pivot].Visibility->Get_Bit((int)frame) == 1;
        }
        return true;
    }
    if (NodeMotion[pivot].Visibility != 0) {
        return NodeMotion[pivot].Visibility->Get_Bit((int)frame) == 1;
    }
    return true;
}

bool HCompressedAnimClass::Has_X_Translation(int pivot)
{
    if (VectorMotion != 0) return VectorMotion[pivot].Channels[0] != 0;
    return NodeMotion[pivot].Channels[0] != 0;
}
bool HCompressedAnimClass::Has_Y_Translation(int pivot)
{
    if (VectorMotion != 0) return VectorMotion[pivot].Channels[1] != 0;
    return NodeMotion[pivot].Channels[1] != 0;
}
bool HCompressedAnimClass::Has_Z_Translation(int pivot)
{
    if (VectorMotion != 0) return VectorMotion[pivot].Channels[2] != 0;
    return NodeMotion[pivot].Channels[2] != 0;
}
bool HCompressedAnimClass::Has_Rotation(int pivot)
{
    if (VectorMotion != 0) return VectorMotion[pivot].Channels[3] != 0;
    return NodeMotion[pivot].Channels[3] != 0;
}
bool HCompressedAnimClass::Has_Visibility(int pivot)
{
    if (VectorMotion != 0) return VectorMotion[pivot].Visibility != 0;
    return NodeMotion[pivot].Visibility != 0;
}

typedef char NodeStrideIs28[(sizeof(NodeMotionStructView) == 28) ? 1 : -1];
typedef char VectorStrideIs24[(sizeof(VectorMotionStructView) == 24) ? 1 : -1];

bool HCompressedAnimClass::Is_Node_Motion_Present(int pivot)
{
    if (VectorMotion != 0) {
        for (int i = 0; i < 5; ++i) if (VectorMotion[pivot].Channels[i] != 0) return true;
        if (VectorMotion[pivot].Visibility != 0) return true;
    } else {
        if (NodeMotion[pivot].Channels[0] != 0) return true;
        if (NodeMotion[pivot].Channels[1] != 0) return true;
        if (NodeMotion[pivot].Channels[2] != 0) return true;
        if (NodeMotion[pivot].Channels[3] != 0) return true;
        if (NodeMotion[pivot].Visibility != 0) return true;
    }
    return false;
}
