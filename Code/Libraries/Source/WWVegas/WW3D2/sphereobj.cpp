// cl: /DBFME_RENDEROBJ_SIZE_LOD /Ireference/shims/g7_renderobj/donor /G7 /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BFME 2 native bodies retained from the former BFME 1 donor port.
// The donor sphereobj.h supplies the AlphaVector names and quaternion member
// interpretation. Retail's assignment copies its five words, and its two
// accessors independently establish the channel offsets below. This partial
// view does not claim the remaining SphereRenderObjClass layout or donor code.
#include "quat.h"

struct AlphaVectorStruct
{
    const AlphaVectorStruct &operator=(const AlphaVectorStruct &source);
    Quaternion angle;
    float intensity;
};

const AlphaVectorStruct &AlphaVectorStruct::operator=(const AlphaVectorStruct &source)
{
    angle = source.angle;
    intensity = source.intensity;
    return *this;
}

class Vector3;
template<class T> class LERPAnimationChannelClass;
class AlphaVectorChannel;

class SphereRenderObjClass
{
public:
    const LERPAnimationChannelClass<Vector3> &Peek_Color_Channel();
    const AlphaVectorChannel &Peek_Vector_Channel();

private:
    unsigned char m_unrecoveredPrefix[0x10C];
    unsigned char m_channelsBeforeVector[0x48];
    unsigned char m_vectorChannelStart;
};

const LERPAnimationChannelClass<Vector3> &SphereRenderObjClass::Peek_Color_Channel()
{
    return *reinterpret_cast<const LERPAnimationChannelClass<Vector3> *>(m_channelsBeforeVector);
}

const AlphaVectorChannel &SphereRenderObjClass::Peek_Vector_Channel()
{
    return *reinterpret_cast<const AlphaVectorChannel *>(&m_vectorChannelStart);
}
