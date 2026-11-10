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
#include "BfmeAptValue006DCD20.h"
#include "Rva006CFCD0.h"
struct Record{int flags;int key;void*actions;};
struct Events{int count;Record*records;};
struct Character{int type;};
struct Payload{char pad0[12];Character*character;char pad10[12];signed int flags:24;unsigned int other:8;Events*events;};
#include "AptCIHClass.h"
class Rva006E9A40List{public:unsigned short count,capacity;AptCIH**items;void add(AptCIH*);inline bool has(AptCIH*p)const{const int n=capacity;int i=0;if(n>0){AptCIH**item=items;do{if(*item==p)return true;++i;++item;}while(i<n);}return false;}};
// The canonical pool splits these eight-byte sets into their scalar fields.
// Its constructor proves set storage at +8, +0x20 and +0x28; retain the
// existing list API through typed views of those same members.
#include "Rva006E34D0.h"
extern Rva006E34D0*g_bfmeAptPtrAtE176D0;
// Apt's clip-event channel id, retail VA 0x00E17704 (RVA 0x00A17704): the rowed
// 0x006F7E00 body loads it twice as queueClipEvents' channel argument (retail
// 0x006F7F70 `mov 0xe17704,%edx` and 0x006F7F85 `mov 0xe17704,%eax`). RVA
// 0x00A17704 is past .data's raw end (0x009DE008) but inside .data's virtual
// size, so retail's image holds zero, which is what the definition carries.
// Five Apt units read it with this same `extern int` spelling; the natural home
// (Apt.cpp, owner of the neighbouring g_00E1771C) is claimed by another seat,
// and this is the sole reader otherwise ready to link, so the definition lives
// here.
extern int g_00E17704;  // defined in Rva0070F680.cpp
extern unsigned char g_00E1771C;
class Rva006F7E00{public:void rva006F7E00(AptCIH*,int);};
#define CHECK(c,s,l) if(!(c)){g_bfmeAptAssertAtE17734(s,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",l);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
void Rva006F7E00::rva006F7E00(AptCIH*item,int fire){
 CHECK((unsigned char)((BfmeAptValue006DCD20*)item)->isCharacterInst(),"isCharacterInst()",0xA5);
 Payload*p0=(Payload*)item->field4C;_ReadWriteBarrier();int type=p0->character->type;
 if(type==4){if(!((Rva006E9A40List*)&g_bfmeAptPtrAtE176D0->m_field08)->has(item))((Rva006E9A40List*)&g_bfmeAptPtrAtE176D0->m_field08)->add(item);return;}
 if(type==5){
  CHECK(((Rva006CFCD0*)item)->isSpriteInstBase(),"isSpriteInstBase()",0x7D);
  Payload*p=(Payload*)item->field4C;Events*ev=p->events;if(!ev)return;
  bool add=false;
  for(int i=0;i<ev->count;++i){int flags=ev->records[i].flags;if(flags&0xBFDFF){p->flags|=flags;if(ev->records[i].flags&0xBFCF8)add=true;}}
  if(add){if(!((Rva006E9A40List*)&g_bfmeAptPtrAtE176D0->m_field28)->has(item))((Rva006E9A40List*)&g_bfmeAptPtrAtE176D0->m_field28)->add(item);}
  if(fire){p->flags|=0x40200;item->queueClipEvents(0x200,g_00E17704,1);item->queueClipEvents(0x40000,g_00E17704,1);p->flags&=~0x40200;}
  return;
 }
 if(type==2&&g_00E1771C==1){((Rva006E9A40List*)&g_bfmeAptPtrAtE176D0->m_field20)->add(item);((Rva006E9A40List*)&g_bfmeAptPtrAtE176D0->m_field28)->add(item);}
}
