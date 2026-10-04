// ?updateMinMax@@YAXPAMM0@Z
// partial score=1.0 date=2026-10-05
// cl: /O2 /Ob1 /GX- /GS /arch:SSE
// Clean one-function donor source: Open-BFME-1@5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/Bfme/updateMinMax.cpp, blob675764648ccff672480bb22b1cb8734cef170553.
// Native ABI and semantics are independently checked at BFME2 RVA57D0/33.
void updateMinMax(float *min, float val, float *max)
{
    if (val < *min)
    {
        *min = val;
        return;
    }
    if (val > *max)
        *max = val;
}
