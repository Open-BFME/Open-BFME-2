// _AnyRatioFrameScale
// partial score=0.88 date=2026-10-08
// cl: /MD
// Clean-room wrappers from reviewed specs001bab40/001babf0 and retail only.
// Native 161B cdecl owners pass nine slots to the existing fixed-ratio
// providers at 1B9E40/1BA1F0. The offset views below are limited to the
// target-proven postprocessor fields and nine-dword YUV output record.
struct Rva009AA260Context;
void __cdecl Rva009A9400(Rva009AA260Context *,const unsigned char *,int,unsigned,unsigned,unsigned char *,unsigned,unsigned,unsigned);
void __cdecl Rva009A97B0(Rva009AA260Context *,const unsigned char *,int,unsigned,unsigned,unsigned char *,unsigned,unsigned,unsigned);
struct VP6ScalePostProcessor {
    unsigned char pad00[0x40];
    int width,height;
    unsigned char pad48[0x10];
    int hScale,hRatio,vScale,vRatio;
    unsigned char pad68[8];
    int expandedWidth,expandedHeight;
    int reconY,reconU,reconV;
    unsigned char pad84[0x30];
    unsigned border;
};
struct VP6ScaleYUVConfig {
    int yWidth,yHeight,yStride,uvWidth,uvHeight,uvStride;
    unsigned char *y,*u,*v;
};

extern "C" void Fast_4_5_Scale(VP6ScalePostProcessor *post,unsigned char *frame,VP6ScaleYUVConfig *config)
{
    int width=post->width;
    int height=post->height;
    int destWidth=config->yWidth;
    int destHeight=config->yHeight;
    Rva009A9400((Rva009AA260Context *)post,frame+post->reconY,width+32,width,height,config->y,destWidth,destWidth,destHeight);
    width>>=1;
    height>>=1;
    destWidth>>=1;
    destHeight>>=1;
    int sourcePitch=width+16;
    Rva009A9400((Rva009AA260Context *)post,frame+post->reconU,sourcePitch,width,height,config->u,destWidth,destWidth,destHeight);
    Rva009A9400((Rva009AA260Context *)post,frame+post->reconV,sourcePitch,width,height,config->v,destWidth,destWidth,destHeight);
}

extern "C" void Fast_3_5_Scale(VP6ScalePostProcessor *post,unsigned char *frame,VP6ScaleYUVConfig *config)
{
    int width=post->width;
    int height=post->height;
    int destWidth=config->yWidth;
    int destHeight=config->yHeight;
    Rva009A97B0((Rva009AA260Context *)post,frame+post->reconY,width+32,width,height,config->y,destWidth,destWidth,destHeight);
    width>>=1;
    height>>=1;
    destWidth>>=1;
    destHeight>>=1;
    int sourcePitch=width+16;
    Rva009A97B0((Rva009AA260Context *)post,frame+post->reconU,sourcePitch,width,height,config->u,destWidth,destWidth,destHeight);
    Rva009A97B0((Rva009AA260Context *)post,frame+post->reconV,sourcePitch,width,height,config->v,destWidth,destWidth,destHeight);
}

// Clean-room spec001baf30 and native606B: postprocessor ratio and padding
// fields are target facts. Reuse the genuine existing generic scaler.
int __cdecl Rva009AA260Scale(Rva009AA260Context *,const unsigned char *,int,unsigned,unsigned,unsigned char *,unsigned,unsigned,unsigned);
extern "C" void *__cdecl memset(void *,int,unsigned);
#pragma intrinsic(memset)
extern "C" int AnyRatioFrameScale(VP6ScalePostProcessor *post,unsigned char *frame,VP6ScaleYUVConfig *config,int yOffset,int uvOffset)
{
    int destWidth=post->expandedWidth;
    int hRatio=post->hRatio;
    int hScale=post->hScale;
    int sourceWidth=(unsigned)(destWidth*hRatio+hScale-1)/(unsigned)hScale;
    int destHeight=post->expandedHeight;
    int vScale=post->vScale;
    int sourceHeight=(unsigned)(destHeight*post->vRatio+vScale-1)/(unsigned)vScale;
    int paddedWidth;
    if(hRatio==3) paddedWidth=((sourceWidth+2)/3)*3*hScale/3;
    else paddedWidth=((sourceWidth+7)/8)*8*hScale/hRatio;
    int paddedHeight;
    if(post->vRatio==3) paddedHeight=((sourceHeight+2)/3)*3*vScale/3;
    else paddedHeight=((sourceHeight+7)/8)*8*vScale/post->vRatio;
    int result=Rva009AA260Scale((Rva009AA260Context *)post,frame+post->reconY,post->width+2*post->border,sourceWidth,sourceHeight,config->y+yOffset,config->yStride,destWidth,destHeight);
    for(int y=0;y<paddedHeight;++y)
        memset(config->y+y*config->yStride+destWidth+yOffset,0,paddedWidth-destWidth);
    for(y=destHeight;y<paddedHeight;++y)
        memset(config->y+y*config->yStride+yOffset,0,paddedWidth);
    if(!result) return 0;
    sourceWidth=(sourceWidth+1)>>1;
    sourceHeight=(sourceHeight+1)>>1;
    destWidth=(destWidth+1)>>1;
    destHeight=(destHeight+1)>>1;
    Rva009AA260Scale((Rva009AA260Context *)post,frame+post->reconU,((unsigned)post->width>>1)+post->border,sourceWidth,sourceHeight,config->u+uvOffset,config->uvStride,destWidth,destHeight);
    Rva009AA260Scale((Rva009AA260Context *)post,frame+post->reconV,((unsigned)post->width>>1)+post->border,sourceWidth,sourceHeight,config->v+uvOffset,config->uvStride,destWidth,destHeight);
    return result;
}
