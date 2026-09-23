// ?Resize@?$VectorClass@VTCBClass@TCBSpline3DClass@@@@UAE_NHPBVTCBClass@TCBSpline3DClass@@@Z
// partial score=0.3436123348 date=2026-09-23
// Isolated target-specific TCB vector trial: the retail vector constructor
// iterator proves a user-written default constructor despite BFME1's TCBClass
// being implicit. Scratch-only.
// cl: /O1 /arch:SSE2 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
#include "vector.h"

class TCBSpline3DClass
{
public:
    class TCBClass
    {
    public:
        TCBClass();
        bool operator==(const TCBClass &other) const
        {
            return Tension == other.Tension && Continuity == other.Continuity && Bias == other.Bias;
        }
        bool operator!=(const TCBClass &other) const { return !(*this == other); }
        float Tension;
        float Continuity;
        float Bias;
    };
};

TCBSpline3DClass::TCBClass::TCBClass()
{
}

template class VectorClass<TCBSpline3DClass::TCBClass>;
