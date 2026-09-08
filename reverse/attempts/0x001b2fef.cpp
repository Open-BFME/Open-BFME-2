// ?Evaluate@BFME2Encoding0MotionChannel@@QAEXMPAMPAPAH@Z
// partial score=0.475138 date=2026-09-08
// ?Evaluate@BFME2Encoding0MotionChannel@@QAEXMPAMPAPAH@Z
// partial score=0.475138 date=2026-09-08
// cl: /O1 /arch:SSE /EHsc /DNDEBUG /MD
class BFME2Encoding0MotionChannel {
public:
 void *VTable;
 int Type, Pivot, Count, Components;
 unsigned short *TimeCodes;
 float *Samples;
 __forceinline int FindIndex(unsigned int time, int **context)
    {    volatile unsigned int *time_ptr=&time;

    int index;
    if (context && (unsigned int)(index = **context) < (unsigned int)Count) {
        while (index && (TimeCodes[index] & ~0x8000) > *time_ptr) --index;
        while (index < Count-1 && (TimeCodes[index+1] & ~0x8000) <= time) ++index;
        **context=index; ++*context;
        return index;
        } else {
            if (*time_ptr <= (TimeCodes[0] & ~0x8000)) index=0;
            else if (time >= (TimeCodes[Count-1] & ~0x8000)) index=Count-1;
            else {
                int low=0, high=Count-2;
                for (;;) {
                    index=(low+high)/2;
                    if (*time_ptr < (TimeCodes[index] & ~0x8000)) high=index;
                    else if (time >= (TimeCodes[index+1] & ~0x8000)) {
                        if (low ^ index) low=index; else ++low;
                    } else break;
                }
            }
        }
    if (context) { **context=index; ++*context; }
        return index;
    }
 void Evaluate(float time, float *output, int **context);
};
void BFME2Encoding0MotionChannel::Evaluate(float time, float *output, int **context)
{
    int index=FindIndex((unsigned int)(int)time,context);
    if (index == Count-1 || (TimeCodes[index+1] & 0x8000)) {
        *output=Samples[index*Components];
    } else {
        float t0=(float)(TimeCodes[index] & ~0x8000);
        float t1=(float)(TimeCodes[index+1] & ~0x8000);
        float factor=(time-t0)/(t1-t0);
        float *samples=Samples+index*Components;
        *output=samples[0]+factor*(samples[Components]-samples[0]);
    }
}
