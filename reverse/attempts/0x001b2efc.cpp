// ?FindIndex@BFME2Encoding0MotionChannel@@QAEHIPAPAH@Z
// partial score=0.981395 date=2026-09-08
// cl: /O1 /EHsc /DNDEBUG /MD
class BFME2Encoding0MotionChannel {
public:
 void *VTable;
 int Type, Pivot, Count, Components;
 unsigned short *TimeCodes;
 float *Samples;
 int FindIndex(unsigned int time, int **context);
};
int BFME2Encoding0MotionChannel::FindIndex(unsigned int time, int **context)
{
 int index;
 if (context && (unsigned int)(index = **context) < (unsigned int)Count) {
  while (index && (TimeCodes[index] & ~0x8000) > time) --index;
  while (index < Count-1 && (TimeCodes[index+1] & ~0x8000) <= time) ++index;
  **context=index; ++*context;
  return index;
 } else {
  if (time <= (TimeCodes[0] & ~0x8000)) index=0;
  else if (time >= (TimeCodes[Count-1] & ~0x8000)) index=Count-1;
  else {
   int low=0, high=Count-2;
   for (;;) {
    index=(low+high)/2;
    if (time < (TimeCodes[index] & ~0x8000)) high=index;
    else if (time >= (TimeCodes[index+1] & ~0x8000)) {
     if (index ^ low) low=index; else ++low;
    } else break;
   }
  }
 }
 if (context) { **context=index; ++*context; }
 return index;
}
