// ?UnknownSlot3@BFME2Encoding0MotionChannel@@UAEXMPAMPAPAE@Z
// partial score=0.8 date=2026-10-09
// ?UnknownSlot3@BFME2Encoding0MotionChannel@@UAEXMPAMPAPAE@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD
// FindIndex shape: `int low = 0;` declared ahead of `index` and re-zeroed in the search arm (the same lever that closed the standalone FindIndex 0x1B2EFC); halves the differing rows. Remaining: retail copies the inlined result into EDX before the interpolation and orders low=0 before high.
// BFME1 9cbfb551fe20 motchan.cpp TimeCodedMotionChannel Get_Vector and
// Get_QuatVector supply sample selection/interpolation. BFME2 factory and
// load bodies independently prove vtable slots3..5 and timecode14/samples18.
// Target has ushort timecodes and per-call cursor instead of donor cached
// dword packets. The existing banked FindIndex helper is the same native
// search inlined by these three entries; caller-native boundaries prove it.
class Vector3 { public: float X,Y,Z; };
class Quaternion { public: float X,Y,Z,W; };
void BFME2_Nlerp(Quaternion&,const Quaternion&,const Quaternion&,float);
class ChunkLoadClass;
class BFME2MotionChannel {
public:
 virtual bool Load(ChunkLoadClass&);virtual ~BFME2MotionChannel();virtual int UnknownSlot2();
 virtual void UnknownSlot3(float,float*,unsigned char**);
 virtual void UnknownSlot4(float,Vector3*,unsigned char**);
 virtual void UnknownSlot5(float,Quaternion*,unsigned char**);virtual int UnknownSlot6();
 int Type,Pivot,Count,Components;
};
class BFME2Encoding0MotionChannel : public BFME2MotionChannel {
public:
 unsigned short *TimeCodes;float *Samples;
 // ?BFME2Encoding0MotionChannel::FindIndex present-unmatched
 __forceinline int FindIndex(unsigned,int**);
 virtual void UnknownSlot3(float,float*,unsigned char**);
 virtual void UnknownSlot4(float,Vector3*,unsigned char**);
 virtual void UnknownSlot5(float,Quaternion*,unsigned char**);
};
__forceinline int BFME2Encoding0MotionChannel::FindIndex(unsigned int time, int **context)
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

static __forceinline float lerpMotion(float a,float b,float t){return (b-a)*t+a;}
void BFME2Encoding0MotionChannel::UnknownSlot3(float frame,float *value,unsigned char **cursor)
{
 int index=FindIndex((unsigned int)frame,reinterpret_cast<int**>(cursor));
 if(index==Count-1 || (TimeCodes[index+1]&0x8000)) {
  *value=Samples[index*Components];return;
 }
 float t0=float(TimeCodes[index]&~0x8000),t1=float(TimeCodes[index+1]&~0x8000);
 float ratio=(frame-t0)/(t1-t0);
 float *samples=Samples+index*Components;
 *value=lerpMotion(samples[0],samples[Components],ratio);
}
void BFME2Encoding0MotionChannel::UnknownSlot4(float frame,Vector3 *value,unsigned char **cursor)
{
 int index=FindIndex((unsigned int)frame,reinterpret_cast<int**>(cursor));
 if(index==Count-1 || (TimeCodes[index+1]&0x8000)) {
  float *samples=Samples+index*Components;
  value->X=samples[0];value->Y=samples[1];value->Z=samples[2];return;
 }
 float t0=float(TimeCodes[index]&~0x8000),t1=float(TimeCodes[index+1]&~0x8000);
 float ratio=(frame-t0)/(t1-t0);
 float *samples=Samples+index*Components;
 value->X=lerpMotion(samples[0],samples[Components],ratio);
 value->Y=lerpMotion(samples[1],samples[Components+1],ratio);
 value->Z=lerpMotion(samples[2],samples[Components+2],ratio);
}
void BFME2Encoding0MotionChannel::UnknownSlot5(float frame,Quaternion *value,unsigned char **cursor)
{
 int index=FindIndex((unsigned int)frame,reinterpret_cast<int**>(cursor));
 if(index==Count-1 || (TimeCodes[index+1]&0x8000)) {
  float *samples=Samples+index*Components;
  value->X=samples[0];value->Y=samples[1];value->Z=samples[2];value->W=samples[3];return;
 }
 float t0=float(TimeCodes[index]&~0x8000),t1=float(TimeCodes[index+1]&~0x8000);
 float ratio=(frame-t0)/(t1-t0);
 float *samples=Samples+index*Components;
 BFME2_Nlerp(*value,*reinterpret_cast<Quaternion*>(samples),*reinterpret_cast<Quaternion*>(samples+Components),ratio);
}
