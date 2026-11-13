// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Native 540DCA..540E82184B and WB A9D800 establish the frame-channel wrapper.
// The24-byte frame has mode0, a12-byte coordinate at4 and scalar channels10/14.
// Constructing the result evaluates mode, scalar14, scalar10 and coordinates
// in native order. The existing providers retain their established ABI views;
// source frame and helper names are unknown. No reference donor was available.
struct Rva00540E9DSrc { int a,b,c; };
#include "../../../Include/Common/Rva00540D94.h"
class CameraAnimationFrameData {
public:
    float doInterpolate(float,float *,int,float *,int,float *,int,float *,int);
    int mode;
};
class Rva005C71ADView {
public:
    void *rva005C71AD(void *,float,void *,void *,void *,void *,void *,void *,void *,void *);
    int mode;
};
Rva00540D94 Rva00540DCAGet(float fraction,Rva00540D94 *prevFrame,int prevFrameNum,Rva00540D94 *startFrame,int startFrameNum,Rva00540D94 *endFrame,int endFrameNum,Rva00540D94 *nextFrame,int nextFrameNum)
{
    Rva00540E9DSrc position;
    return Rva00540D94(
        *(Rva00540E9DSrc *)((Rva005C71ADView *)startFrame)->rva005C71AD(&position,fraction,&prevFrame->position,(void *)prevFrameNum,&startFrame->position,(void *)startFrameNum,&endFrame->position,(void *)endFrameNum,&nextFrame->position,(void *)nextFrameNum),
        ((CameraAnimationFrameData *)startFrame)->doInterpolate(fraction,&prevFrame->scalar10,prevFrameNum,&startFrame->scalar10,startFrameNum,&endFrame->scalar10,endFrameNum,&nextFrame->scalar10,nextFrameNum),
        ((CameraAnimationFrameData *)startFrame)->doInterpolate(fraction,&prevFrame->scalar14,prevFrameNum,&startFrame->scalar14,startFrameNum,&endFrame->scalar14,endFrameNum,&nextFrame->scalar14,nextFrameNum),
        startFrame->mode);
}

