// _LoopDeringBlock
// partial score=0.8670788253477589 date=2026-10-10
// cl: /O2 /DNDEBUG /MD
// Clean-Room: reverse/vp6_cleanroom/specs/001d8b40.md
// Only the approved spec, retail, and existing BFME2 repo code/history were read.
// Complete cdecl five-argument leaf, retail 1D8B40..1D8DCF, RET at 1D8DCE.
// Intended home: Code/Libraries/Source/VP6/LoopFilter.cpp; reuse its existing
// Vp6LoopFilterInstance with padA0[453C-A0] and the uint32 threshold table.
// Actual whole-home effective flags are /O2 /DNDEBUG /MD; its explicit /G6
// comment is overridden by the Code-region defaults, so do not rely on it.
// Frozen BFME2 HEAD 5bc195474a, BFME1 pointer 575ba2b04743f190f069805fbdc59936123c45da.
// Private whole-home object emits 639B with no relocations or unresolved names.
// First 97B match exactly. Native selects/spills the table value at stack+14
// before its range adjustment; this draft keeps that value in a register.
// Native's horizontal centre load then uses a separate register, while the
// draft combines it with its earlier pixel load. Pointer/threshold homes rotate.
// Three separately advancing vertical row pointers reproduce the later control
// flow more closely than the newer indexed 630B bank previously stored here.
// Twenty-one bounded local-lifetime, pointer-reuse, inline-max and centre-term
// spellings were checked, including unsigned max selection and shift/add forms.
// A reference-returning max emits 655B only through different selection and
// alignment instructions; equal extent is not verification. No tracked Code,
// header, pin, alias or gate exception was added. Revisit with a new compiler
// lifetime/aliasing explanation, rather than repeating the same expressions.
#include <stdlib.h>
#include <string.h>
struct Vp6LoopFilterInstance {
    unsigned char prefix[0x453C];
    unsigned int deringThreshold[256];
};

extern "C" void LoopDeringBlock(Vp6LoopFilterInstance *context,unsigned char *buffer,unsigned int stride,unsigned int width,unsigned int height)
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
    high=context->deringThreshold[maximum];
    level=context->deringThreshold[255-minimum];
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
