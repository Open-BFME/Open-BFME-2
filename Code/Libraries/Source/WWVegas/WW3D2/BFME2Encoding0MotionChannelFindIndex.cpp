// cl: /O1 /EHsc /DNDEBUG /MD
// ?FindIndex@BFME2Encoding0MotionChannel@@QAEHIPAPAH@Z @0x001B2EFC 215B
// Timecode search of the BFME 2 motion channel (encoding 0): cached cursor walk (context holds a
// cursor over the cached index list) or a binary search over TimeCodes masked with ~0x8000.
// Layout from the factory/ctor units (Count at +0xC, TimeCodes at +0x14). Codegen: `low` is
// declared and zeroed ahead of `index`; this fixes which xor operand the compiler copies.
// ?FindIndex@BFME2Encoding0MotionChannel@@QAEHIPAPAH@Z, retail 0x001B2EFC, 215 bytes.
// Finish from banked 0.9907 stash: cached index cursor walk plus binary search
// over TimeCodes masked with ~0x8000. Evidence: RET8 thiscall with context
// double-pointer; neighbours BFME2MotionChannelFactory and
// BFME2Encoding0MotionChannelCtor; one diff at 0xB3 xor edx mem vs sub edx mem
// (mov edx eax now matches via sub spelling); retail uses xor for index!=low,
// ours sub tests same equality; 215B/93insns exact size t=15 model=muse-06.
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
 int low = 0;
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
   int high=Count-2; low = 0;
   for (;;) {
    index=(low+high)/2;
    if (time < (TimeCodes[index] & ~0x8000)) high=index;
    else if (time >= (TimeCodes[index+1] & ~0x8000)) {
     int diff = index ^ low; if (diff) low=index; else ++low;
    } else break;
   }
  }
 }
 if (context) { **context=index; ++*context; }
 return index;
}
