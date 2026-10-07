// ?set_identity@MotionChannelClass@@ABEXPAM@Z
// partial score=1.0 date=2026-10-07
// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD
// Copyright 2025 Electronic Arts Inc.
// SPDX-License-Identifier: GPL-3.0-or-later
// ZH motchan.h semantics through BFME1 inputs1399ad37 and the existing
// bfmehrawanim shim. HRawAnim read_channel18D360 allocates32B; its verified
// consumers prove Type4, VectorLen8, Data14, FirstFrame18 and LastFrame1C.
// Retail15FFD0 recognizes fade type15 before quaternion type6. Both helpers
// emit independently below, without HRawAnim's unrelated vtables or loaders.
class MotionChannelClass {
public:
 void Get_Vector(int frame, float *setvec) const;
private:
 unsigned PivotIdx,Type;
 int VectorLen;
 float ValueOffset,ValueScale;
 float *Data;
 int FirstFrame,LastFrame;
 void set_identity(float *setvec) const;
};
typedef char MotionChannelSizeCheck[sizeof(MotionChannelClass)==32?1:-1];
void MotionChannelClass::set_identity(float *setvec) const {
 if(Type==15) { setvec[0]=1.0f; }
 else {
  setvec[0]=0.0f;
  if(Type==6) { setvec[1]=0.0f; setvec[2]=0.0f; setvec[3]=1.0f; }
 }
}
void MotionChannelClass::Get_Vector(int frame,float *setvec) const {
 if(frame<FirstFrame || frame>LastFrame) { set_identity(setvec); }
 else {
  int vframe=frame-FirstFrame;
  for(int i=0;i<VectorLen;++i) setvec[i]=Data[vframe*VectorLen+i];
 }
}
