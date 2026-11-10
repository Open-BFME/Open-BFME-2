// cl: /DBFME_WWSTRING_NATIVE_COPY_ASSIGN /DBFME_WWSTRING_NATIVE_COPY_CTOR /DBFME_WWSTRING_NATIVE_LENGTH /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmestages /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Retained BFME 2 native bodies from the former BFME 1 donor port.
// The six accessors independently establish the offsets annotated below.
// Names and intervening member interpretations come from pinned BFME 1's
// ringobj.h; this partial view does not recover the remaining class or tables.
#include "../WWMath/Vector3Data.h"
#include "../../../../../reference/shims/wwmath/Vector2.h"
#include "prim_anim.h"

// These two existing template bodies remain instantiated from the donor
// header, rather than retaining unrelated prototype and loader code to emit them.
template const PrimitiveAnimationChannelClass<float>::KeyClass &
PrimitiveAnimationChannelClass<float>::Get_Key(int) const;
template PrimitiveAnimationChannelClass<Vector3>::KeyClass::KeyClass();

class RingRenderObjClass
{
public:
    unsigned int Get_Flags();
    const Vector2 &Get_Inner_Extent() const;
    virtual const char *Get_Name() const;
    const LERPAnimationChannelClass<float> &Peek_Alpha_Channel();
    const LERPAnimationChannelClass<Vector2> &Peek_Inner_Scale_Channel();
    const LERPAnimationChannelClass<Vector2> &Peek_Outer_Scale_Channel();

private:
    unsigned char m_unrecoveredPrefix[0x14C - 4];
    unsigned char AlphaChannel[0x18];       // native +0x14C
    unsigned char InnerScaleChannel[0x18];  // native +0x164
    unsigned char OuterScaleChannel[0x18];  // native +0x17C
    char Name[32];                         // native +0x194
    Vector3 ObjSpaceCenter;
    Vector3 ObjSpaceExtent;
    Vector2 InnerExtent;                   // native +0x1CC
    Vector2 OuterExtent;
    int TextureTileCount;
    Vector3 Color;
    float Alpha;
    Vector2 InnerScale;
    Vector2 OuterScale;
    unsigned int Flags;                    // native +0x200
};

unsigned int RingRenderObjClass::Get_Flags() { return Flags; }
const Vector2 &RingRenderObjClass::Get_Inner_Extent() const { return InnerExtent; }
const char *RingRenderObjClass::Get_Name() const { return Name; }
const LERPAnimationChannelClass<float> &RingRenderObjClass::Peek_Alpha_Channel()
{
    return *reinterpret_cast<const LERPAnimationChannelClass<float> *>(AlphaChannel);
}
const LERPAnimationChannelClass<Vector2> &RingRenderObjClass::Peek_Inner_Scale_Channel()
{
    return *reinterpret_cast<const LERPAnimationChannelClass<Vector2> *>(InnerScaleChannel);
}
const LERPAnimationChannelClass<Vector2> &RingRenderObjClass::Peek_Outer_Scale_Channel()
{
    return *reinterpret_cast<const LERPAnimationChannelClass<Vector2> *>(OuterScaleChannel);
}
