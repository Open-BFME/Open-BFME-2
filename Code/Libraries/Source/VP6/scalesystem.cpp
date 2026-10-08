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
    unsigned char pad48[0x30];
    int reconY,reconU,reconV;
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
