// ?Fast_3_5_Scale@@YAXPAURva009AA260Context@@PAEPAUVP6YUVConfig@@@Z
// partial score=0.95 date=2026-10-08
// cl: /O2 /G6 /MD
// Clean-room implementation from specs/001bab40.md and specs/001babf0.md.
struct Rva009AA260Context {
    unsigned char reserved00[0x40];
    int width;
    int height;
    unsigned char reserved48[0x30];
    unsigned int reconY;
    unsigned int reconU;
    unsigned int reconV;
};
struct VP6YUVConfig {
    int yWidth, yHeight, yStride;
    int uvWidth, uvHeight, uvStride;
    unsigned char *y, *u, *v;
};
void __cdecl Rva009A9400(Rva009AA260Context *, const unsigned char *, int,
    unsigned int, unsigned int, unsigned char *, unsigned int, unsigned int, unsigned int);
void __cdecl Rva009A97B0(Rva009AA260Context *, const unsigned char *, int,
    unsigned int, unsigned int, unsigned char *, unsigned int, unsigned int, unsigned int);
void __cdecl Fast_4_5_Scale(Rva009AA260Context *p, unsigned char *frame, VP6YUVConfig *out) {
    int srcWidth = p->width;
    int srcHeight = p->height;
    int dstHeight = out->yHeight;
    int dstWidth = out->yWidth;
    Rva009A9400(p, frame + p->reconY, srcWidth + 32, srcWidth, srcHeight,
        out->y, dstWidth, dstWidth, dstHeight);
    dstHeight >>= 1; dstWidth >>= 1;
    srcHeight >>= 1; srcWidth >>= 1;
    int srcPitch = srcWidth + 16;
    Rva009A9400(p, frame + p->reconU, srcPitch, srcWidth, srcHeight,
        out->u, dstWidth, dstWidth, dstHeight);
    Rva009A9400(p, frame + p->reconV, srcPitch, srcWidth, srcHeight,
        out->v, dstWidth, dstWidth, dstHeight);
}
void __cdecl Fast_3_5_Scale(Rva009AA260Context *p, unsigned char *frame, VP6YUVConfig *out) {
    int srcWidth = p->width;
    int srcHeight = p->height;
    int dstHeight = out->yHeight;
    int dstWidth = out->yWidth;
    Rva009A97B0(p, frame + p->reconY, srcWidth + 32, srcWidth, srcHeight,
        out->y, dstWidth, dstWidth, dstHeight);
    dstHeight >>= 1; dstWidth >>= 1;
    srcHeight >>= 1; srcWidth >>= 1;
    int srcPitch = srcWidth + 16;
    Rva009A97B0(p, frame + p->reconU, srcPitch, srcWidth, srcHeight,
        out->u, dstWidth, dstWidth, dstHeight);
    Rva009A97B0(p, frame + p->reconV, srcPitch, srcWidth, srcHeight,
        out->v, dstWidth, dstWidth, dstHeight);
}
