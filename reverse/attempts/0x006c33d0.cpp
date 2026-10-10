// ?rva006C33D0@Rva006C1F60@@QAEXHH@Z
// partial score=0.9828926905 date=2026-10-10
// cl: /O2 /MD /DNDEBUG /EHsc
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *);
int Rva00030DF0Release(Rva00030DD0Lock *);
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount();
namespace EA {namespace Allocator {class GeneralAllocator {public:unsigned rva00032A20(const void *);};}}
struct GeneralAllocatorDebugBlock;
class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator {public:void rva006C3180(GeneralAllocatorDebugBlock*);};
struct DelayedChunk {unsigned prevSize,size;DelayedChunk *prev,*next;};
struct Guard {Guard(Rva00030DD0Lock*p):lock(p){if(lock)Rva00030DD0AddRef(lock);} ~Guard(){if(lock)Rva00030DF0Release(lock);} Rva00030DD0Lock*lock;};
class Rva006C1F60 : public GeneralAllocatorDebug {
public:void rva006C33D0(int,int);
char unknown0[0x4e4];Rva00030DD0Lock*lock;char unknown4e8[0x530-0x4e8];unsigned depth;char unknown534[0x548-0x534];DelayedChunk head;unsigned count,total;
__forceinline void remove(DelayedChunk *chunk) {
 char *data=(char*)chunk+8;unsigned size=rva00032A20(data);
 chunk->prev->next=chunk->next;chunk->next->prev=chunk->prev;
 --count;total-=size;rva006C3180((GeneralAllocatorDebugBlock*)chunk);
}
};
void Rva006C1F60::rva006C33D0(int mode,int limit){
 Guard guard(lock);++depth;
 if(mode==0){while(head.next!=&head)remove(head.next);}
 else if(mode==1){while(head.next!=&head){if(count<=(unsigned)limit)break;remove(head.next);}}
 else if(mode==2){while(head.next!=&head){if(total<=(unsigned)limit)break;remove(head.next);}}
 else if(mode==3){
 unsigned now=GetTickCount()/1000;
 unsigned threshold=now+(unsigned)limit;if(threshold<now)threshold=0;
 while(head.next!=&head){DelayedChunk*chunk=head.next;char*data=(char*)chunk+8;unsigned size=rva00032A20(data);
 if((unsigned)chunk->prev<=threshold)break;
 chunk->prev->next=chunk->next;chunk->next->prev=chunk->prev;
 --count;total-=size;rva006C3180((GeneralAllocatorDebugBlock*)chunk);}
 }
 --depth;
}
