// ?findMyMangledPort@NAT@@QAEXXZ
// partial score=0.8913006102115306 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// BFME1 NAT.cpp9cbfb551 sendMangledSourcePort is semantic reference;
// BFME2 native5A8405/327 replaces cached-port reuse with UDP slot creation.
#include <string.h>
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
struct hostent { char *name; char **aliases; short addrtype,length; char **addr_list; };
extern "C" __declspec(dllimport) hostent *__stdcall gethostbyname(const char *);
class FirewallHelperClass { public: static void getManglerName(int,char *); };
struct Rva00A063B0Obj;
extern Rva00A063B0Obj *g_a063b0;
extern unsigned long g_00DD35BC;
struct Rva005A684FWord { unsigned int m_00; unsigned short m_04; };
class Rva005A684F { public: __declspec(noinline) unsigned int get(unsigned int) const; char pad[0x90C]; Rva005A684FWord *slots[8]; };
class Rva005A6A83 { public: void rva005A6A83(); };
struct UDPBindValues { unsigned long address; unsigned short port; };
struct NATSlotView { char pad[0x40]; unsigned int flags40; };
class NAT {
public:
 void findMyMangledPort();
 void rva005A6C90(int);
 void rva005A7974(unsigned short,void *);
 bool SetUDPSocketForSlot(unsigned int,unsigned short,int *);
 char pad0[8]; NATSlotView **slots; char padC[8]; int localIndex,targetIndex;
 char pad1C[0x90C-0x1C]; Rva005A684FWord *sockets[8];
 char pad92C[0x938-0x92C]; unsigned long retryTime,retries;
 unsigned short previousPort; char pad942[2]; unsigned long manglerAddress;
};
unsigned int Rva005A684F::get(unsigned int index) const {
 return slots[index] ? slots[index]->m_04 : 0;
}
void NAT::findMyMangledPort() {
 unsigned int sourcePort=((const Rva005A684F *)this)->get(localIndex);
 NATSlotView *localSlot=slots[localIndex];
 unsigned int flags=localSlot->flags40;
 NATSlotView *targetSlot=slots[targetIndex];
 if (!targetSlot || !localSlot) { rva005A6C90(5); return; }
 rva005A6C90(2);
 if (sockets[targetIndex]->m_00 == sockets[localIndex]->m_00) {
  for (;;) {
   UDPBindValues values;
   values.address=0; values.port=0;
   if (SetUDPSocketForSlot(sourcePort,(unsigned short)targetIndex,(int *)&values)) break;
   ++sourcePort;
  }
  rva005A7974((unsigned short)sourcePort,targetSlot);
  return;
 }
 if (flags && !(flags&1)) {
  char name[256];
  FirewallHelperClass::getManglerName(1,name);
  hostent *host=gethostbyname(name);
  if (!host) { rva005A7974((unsigned short)sourcePort,targetSlot); return; }
  memcpy(&manglerAddress,host->addr_list[0],4);
  manglerAddress=htonl(manglerAddress);
  retryTime=timeGetTime()+g_00DD35BC;
  retries=0;
  if(g_a063b0) ((Rva005A6A83 *)this)->rva005A6A83();
 } else {
  for (;;) {
   UDPBindValues values;
   values.address=0; values.port=0;
   if (SetUDPSocketForSlot(sourcePort,(unsigned short)targetIndex,(int *)&values)) break;
   ++sourcePort;
  }
  rva005A7974((unsigned short)sourcePort,targetSlot);
  previousPort=(unsigned short)sourcePort;
 }
}