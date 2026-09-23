// ??0AdaptiveDeltaMotionChannelClass@@QAE@XZ
// partial score=0.8496240602 date=2026-09-23
// cl: /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "wwmath.h"
static float filtertable[256] = { 0.00000001f, 0.0000001f, 0.000001f, 0.00001f, 0.0001f, 0.001f, 0.01f, 0.1f, 1.0f, 10.0f, 100.0f, 1000.0f, 10000.0f, 100000.0f, 1000000.0f, 10000000.0f };
static bool table_valid = false;
class AdaptiveDeltaMotionChannelClass {
public:
    AdaptiveDeltaMotionChannelClass();
private:
    unsigned long PivotIdx;
    unsigned long Type;
    int VectorLen;
    unsigned long NumFrames;
    unsigned long DataByteCount;
    float Scale;
    unsigned long *Data;
};
AdaptiveDeltaMotionChannelClass::AdaptiveDeltaMotionChannelClass()
    : PivotIdx(0), Type(0), VectorLen(0), NumFrames(0), DataByteCount(0), Scale(0.0f), Data(0)
{
    if (false == table_valid) {
        float ratio = 0.0f;
        float *entry = filtertable + 16;
        do {
            *entry = 1.0f - WWMath::Sin(DEG_TO_RADF(0.375f * ratio));
            ratio += 1.0f;
            ++entry;
        } while (entry < filtertable + 256);
        table_valid = true;
    }
}
