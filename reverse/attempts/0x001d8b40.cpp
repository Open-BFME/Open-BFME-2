// ?rva001D8B40Smooth@@YAXPBURva001D8B40ContextView@@PAEHII@Z
// partial score=0.867 date=2026-10-07
// cl: /O2 /Ob0 /MD /DNDEBUG
// Native1D8B40..1D8DCF is a complete655B cdecl leaf, followed by padding
// before the matched VP6 filter wrapper1D8DD0. BF1 has the same655B body
// only as gen_asm/d_009c5080.asm at9C8240, not a reusable C++ recovery.
// Reference ba7 table initializer9C81C0 (matched BF2 1D8AC0) independently
// supports the 256-word table at context453C..493B. The original context
// owner and enclosing allocation are unknown; this is only its read prefix.
// Native first scans unsigned pixel extrema, chooses the unsigned maximum
// of table[max] and table[255-min], then adds signed(max-min)>>5. It applies
// conditional 1:2:1 smoothing in place by rows, then by columns, with a16B
// temporary buffer. Neighbor reads outside the rectangle remain unchanged.
// Declaring locals together gives97 initial exact bytes and639B overall,
// then a register/spill gap. It is not verified. Direct reads, branch-local
// additions and table load order improve the first588B trial; alternative
// loop forms, G7, size, Og-, C mode and shared locals do not close the gap.
#include <stdlib.h>
#include <string.h>
typedef struct Rva001D8B40ContextView {
    unsigned char unknown00[0x453c];
    unsigned int weights[256];
} Rva001D8B40ContextView;
void rva001D8B40Smooth(const Rva001D8B40ContextView *context,unsigned char *buffer,int stride,unsigned int width,unsigned int height)
{
    unsigned int x,y;
    unsigned char minimum=255,maximum=0;
    unsigned char *scan=buffer;
    unsigned int high,level;
    int threshold;
    unsigned char temp[16];
    unsigned char *row;
    for (y=0;y<height;++y) {
        for (x=0;x<width;++x) {
            unsigned char pixel=*scan;
            if(pixel<minimum)minimum=pixel;
            if(pixel>maximum)maximum=pixel;
            ++scan;
        }
        scan+=stride-width;
    }
    high=context->weights[maximum];
    level=context->weights[255-minimum];
    if(level<=high)level=high;
    threshold=(int)level+((maximum-minimum)>>5);
    row=buffer;
    for (y=0;y<height;++y) {
        unsigned char *current=row;
        for (x=0;x<width;++x) {
            int diffRight=abs(current[0]-current[1]);
            int diffLeft=abs(current[0]-current[-1]);
            int sum=2*current[0];
            if(diffLeft<=threshold)sum+=current[-1]; else sum+=current[0];
            if(diffRight<=threshold)sum+=current[1]; else sum+=current[0];
            temp[x]=(unsigned char)((sum+2)>>2);
            ++current;
        }
        memcpy(row,temp,width);
        row+=stride;
    }
    for (x=0;x<width;++x) {
        unsigned char *current=buffer+x;
        unsigned char *above=current-stride;
        unsigned char *below=current+stride;
        unsigned char *destination;
        for (y=0;y<height;++y) {
            int diffBottom=abs(*current-*below);
            int diffTop=abs(*current-*above);
            int sum=2*(*current);
            if(diffTop<=threshold)sum+=*above; else sum+=*current;
            if(diffBottom<=threshold)sum+=*below; else sum+=*current;
            temp[y]=(unsigned char)((sum+2)>>2);
            above+=stride;
            current+=stride;
            below+=stride;
        }
        destination=buffer+x;
        for (y=0;y<height;++y) {
            *destination=temp[y];
            destination+=stride;
        }
    }
}
