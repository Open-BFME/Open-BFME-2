// cl: /O2 /G6 /Ob1 /MD /DNDEBUG
// Complete native6C2270..6C2503 RET14: Ghidra653 omits6B epilogue.
// WB709FD0 confirms fourteen groups of total/length/mode followed by
// inline/external totals and24 callstack entries; application names unknown.
// All layout offsets and flags below independently read from target bytes.
#include <string.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(strlen)
class Rva006C1F60 {public:int rva006C1F60(unsigned);};
int Rva006C4FA0(void **,unsigned);
struct Rva006C2270Slot {unsigned total,length,mode;};
struct Rva006C2270Record {
 unsigned initial;Rva006C2270Slot slots[14];
 unsigned inlineTotal,externalTotal,requestedSize,arg2,arg3,arg4,word520,word524;
 void*stack[24];
};
class GeneralAllocatorDebug {
public:void rva006C2270(Rva006C2270Record*,unsigned,unsigned,unsigned,unsigned);
private:char unknown000[0x514];unsigned flags514,flags518;const char*text51C;unsigned word520,word524;char unknown528[0x67C-0x528];unsigned mode67C;
};
static __forceinline void initSlot(Rva006C2270Slot&slot,unsigned length,const unsigned&mode){slot.length=length;slot.total=length>0?length+4:0;slot.mode=mode;}
void GeneralAllocatorDebug::rva006C2270(Rva006C2270Record*r,unsigned size,unsigned arg2,unsigned arg3,unsigned arg4)
{
 unsigned flags=flags514|flags518;
 for(unsigned i=0;i<14;++i){r->slots[i].total=0;r->slots[i].length=0;r->slots[i].mode=2;}
 r->requestedSize=size;r->initial=2;
 if(flags&2)initSlot(r->slots[1],4,mode67C);
 if(flags&4){initSlot(r->slots[2],4,mode67C);r->requestedSize=size;}
 if((flags&8)&&arg2){initSlot(r->slots[3],4,mode67C);r->arg2=arg2;}
 if(flags&16){unsigned length=arg3?(arg4?8:4):0;initSlot(r->slots[4],length,mode67C);r->arg4=arg4;r->arg3=arg3;}
 if(text51C)initSlot(r->slots[5],strlen(text51C)+1,mode67C);
 if(word520){initSlot(r->slots[6],8,mode67C);r->word520=word520;r->word524=word524;}
 if(flags&128)initSlot(r->slots[7],Rva006C4FA0(r->stack,24)*4,mode67C);
 if(flags&256)initSlot(r->slots[8],4,mode67C);
 if(flags&512)initSlot(r->slots[9],8,mode67C);
 if(flags&1024)initSlot(r->slots[10],4,mode67C);
 if(flags&2048)initSlot(r->slots[11],((Rva006C1F60*)this)->rva006C1F60(size),0);
 if(flags&4096)initSlot(r->slots[12],4,mode67C);
 if(flags&8192)initSlot(r->slots[13],4,mode67C);
 r->inlineTotal=r->initial;r->externalTotal=r->initial;
 Rva006C2270Slot*slot=r->slots;for(unsigned i=14;i--;slot++){if(slot->mode==0)r->inlineTotal+=slot->total;else r->externalTotal+=slot->total;}
}
