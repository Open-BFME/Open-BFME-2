// Native6F7E00..6F7FEE494B and caller6F8B70 establish thiscall RET8 with
// (AptCIH*,int); the receiver belongs to display-list registration but its
// original method name remains unproven, so the owner is address-derived.
// Checked-cast asserts prove the CIH+4C payload. Native payload+C points
// to character type; payload+1C is a signed24-bit handler field and +20 is
// count/pointer clip-action storage with12-byte entries. Root sets at8/20/28
// use unsigned16-bit capacity at+2 and pointer array+4, not element count.
// The early ReadWriteBarrier preserves retail register scheduling with no
// emitted instructions. Helpers use existing owned names and the established
// add6E9A40 pin; field names describe observed roles, not recovered symbols.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O2 /MD /EHsc
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class BfmeAptValue006DCD20{public:int isCharacterInst()const;};
class Rva006CFCD0{public:bool isSpriteInstBase()const;};
struct Record{int flags;int key;void*actions;};
struct Events{int count;Record*records;};
struct Character{int type;};
struct Payload{char pad0[12];Character*character;char pad10[12];signed int flags:24;unsigned int other:8;Events*events;};
class AptCIH{char pad[0x4C];public:Payload*payload;bool queueClipEvents(int,int,int);};
class Rva006E9A40List{public:unsigned short count,capacity;AptCIH**items;void add(AptCIH*);inline bool has(AptCIH*p)const{const int n=capacity;int i=0;if(n>0){AptCIH**item=items;do{if(*item==p)return true;++i;++item;}while(i<n);}return false;}};
class Rva006E34D0{public:char pad[8];Rva006E9A40List a;char pad10[16];Rva006E9A40List c,d;};
extern Rva006E34D0*g_bfmeAptPtrAtE176D0;
extern int g_00E17704;extern unsigned char g_00E1771C;
class Rva006F7E00{public:void rva006F7E00(AptCIH*,int);};
#define CHECK(c,s,l) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",l);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
void Rva006F7E00::rva006F7E00(AptCIH*item,int fire){
 CHECK((unsigned char)((BfmeAptValue006DCD20*)item)->isCharacterInst(),"isCharacterInst()",0xA5);
 Payload*p0=item->payload;_ReadWriteBarrier();int type=p0->character->type;
 if(type==4){if(!g_bfmeAptPtrAtE176D0->a.has(item))g_bfmeAptPtrAtE176D0->a.add(item);return;}
 if(type==5){
  CHECK(((Rva006CFCD0*)item)->isSpriteInstBase(),"isSpriteInstBase()",0x7D);
  Payload*p=item->payload;Events*ev=p->events;if(!ev)return;
  bool add=false;
  for(int i=0;i<ev->count;++i){int flags=ev->records[i].flags;if(flags&0xBFDFF){p->flags|=flags;if(ev->records[i].flags&0xBFCF8)add=true;}}
  if(add){if(!g_bfmeAptPtrAtE176D0->d.has(item))g_bfmeAptPtrAtE176D0->d.add(item);}
  if(fire){p->flags|=0x40200;item->queueClipEvents(0x200,g_00E17704,1);item->queueClipEvents(0x40000,g_00E17704,1);p->flags&=~0x40200;}
  return;
 }
 if(type==2&&g_00E1771C==1){g_bfmeAptPtrAtE176D0->c.add(item);g_bfmeAptPtrAtE176D0->d.add(item);}
}
