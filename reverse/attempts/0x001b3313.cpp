// ?Evaluate_Quaternion@BFME2Encoding0MotionChannel@@QAEXMPAMPAPAH@Z
// partial score=0.4375 date=2026-09-08
// ?Evaluate_Quaternion@BFME2Encoding0MotionChannel@@QAEXMPAMPAPAH@Z
// Compiler probe: selective volatile stack-time reads force addressability;
// original source volatility is unproven. This bank is not executable progress.
// cl: /O1 /arch:SSE /EHsc /DNDEBUG /MD
class Quaternion { public: float X, Y, Z, W; };
void BFME2_Nlerp(Quaternion &res,const Quaternion &p,const Quaternion &q,float alpha);
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
 void Evaluate_Quaternion(float time, float *output, int **context);
};
void BFME2Encoding0MotionChannel::Evaluate_Quaternion(float time, float *output, int **context)
{
    int index=FindIndex((unsigned int)(int)time,context);
    Quaternion *result=reinterpret_cast<Quaternion *>(output);
    if (index == Count-1 || (TimeCodes[index+1] & 0x8000)) {
        Quaternion *frame=reinterpret_cast<Quaternion *>(Samples+index*Components);
        result->X=frame->X; result->Y=frame->Y; result->Z=frame->Z; result->W=frame->W;
    } else {
        float t0=(float)(TimeCodes[index] & ~0x8000);
        float t1=(float)(TimeCodes[index+1] & ~0x8000);
        float factor=(time-t0)/(t1-t0);
        float *frame1=Samples+index*Components;
        float *frame2=frame1+Components;
        BFME2_Nlerp(*result,*reinterpret_cast<Quaternion *>(frame1),*reinterpret_cast<Quaternion *>(frame2),factor);
    }
}
