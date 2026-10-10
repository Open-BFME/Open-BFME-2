// cl: /O2 /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native73E500..73E59E158B RET14; WB17E8220 QueueUndoShroudReveal.
// Correct x/y/radii/angle/mask construction from both complete bodies.
// The opaque prefix preserves the existing manager layout: sum00+38 and queue3C.
// BfmeE32 retains the established 32-byte provider spelling; fields are proven
// by target stores, and original element name and prefix field purposes remain unknown.
#include <deque>
#include <string.h>
struct BfmeE32 {int a[8];};
class ShroudManagerImpl {
 int value00;char opaque04[0x34];int value38;_STL::deque<BfmeE32> pending;
public:void QueueUndoShroudReveal(int x,int y,int *radii,float angle,unsigned mask);
};
void ShroudManagerImpl::QueueUndoShroudReveal(int x,int y,int *radii,float angle,unsigned mask) {
 if(!mask)return;
 if(radii[0]<0)return;
 mask&=0xfffff;
 BfmeE32 value;
 value.a[1]=x;value.a[2]=y;
 for(int i=0;i<3;++i)value.a[3+i]=radii[i];
 memcpy(&value.a[6],&angle,4);
 value.a[7]=mask;
 value.a[0]=value00+value38;
 pending.push_back(value);
}
