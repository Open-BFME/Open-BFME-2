// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native5BA02B..5BA1FD RET0 (466B); online-home vtable RVA873B70 slot6.
// Rowed dtor5B922F installs same table and closes AptOnlineHome::InitGadgets.
// WB1584B00 in AptOnlineHome.cpp corroborates the complete response loop.
// Whole BF1 9cbfb551 AptOnlineHome.cpp read: stats-only donor; it supplies
// subsystem context, not this loop. Native record ABI comes from rowed
// PeerResponse389F77/38A063 and independently matched queue38DFCA.
// Payload words remain anonymous; only native offsets and tag values asserted.
#include "ascii_string.h"
#include "unicode_string.h"
class PeerResponse {
public:
 PeerResponse(); ~PeerResponse();
 int type0; char opaque4[0x10C-4]; int word10C;
 char opaque110[0x124-0x110]; int word124,word128;
 char opaque12C[0x348-0x12C];
};
typedef char PeerResponseExtent[(sizeof(PeerResponse)==0x348)?1:-1];
class GameSpyInfoInterface;
class GameSpyPeerMessageQueueInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class NativeOnlineHomeInfoView {public:
 __forceinline int slot93(){typedef int(NativeOnlineHomeInfoView::*M)();return (this->*(*(M*)&(*(void***)this)[93]))();}
};
class NativeOnlineHomeQueueView {public:
 __forceinline bool slot9(PeerResponse &r){typedef bool(NativeOnlineHomeQueueView::*M)(PeerResponse&);return (this->*(*(M*)&(*(void***)this)[9]))(r);}
};
class GameTextInterface {public:
#define SLOT(N) virtual void slot##N();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
 virtual UnicodeString fetch(const char*,bool *exists=0);
 virtual UnicodeString fetch(const AsciiString&,bool *exists=0);
};
extern GameTextInterface *TheGameText;
class Shell {public:void rva0035BEC7();};
extern Shell *TheShell;
void rva00416C69();void rva005BDAC1();void rva005AF12F(void *);
void Rva00548C1ACleanup();void TearDownGameSpy();
void GSMessageBoxOk(UnicodeString,UnicodeString,void(*)());
class Rva005B9378 {public:void rva005B942A(int,int);};
namespace AptOnline {class OnlineHome {public:virtual void rva005BA02B();};}
void AptOnline::OnlineHome::rva005BA02B()
{
 if(TheGameSpyPeerMessageQueue){
  rva00416C69();rva005BDAC1();
  int left=reinterpret_cast<NativeOnlineHomeInfoView*>(TheGameSpyInfo)->slot93();
  bool disconnected=false;
  PeerResponse response;
  while(left-- && !disconnected && reinterpret_cast<NativeOnlineHomeQueueView*>(TheGameSpyPeerMessageQueue)->slot9(response)) {
   rva005AF12F(&response);
   switch(response.type0){
    case 21:
     reinterpret_cast<Rva005B9378*>(this)->rva005B942A(5,response.word124);
     {int value=response.word128;if(value<1)value=1;reinterpret_cast<Rva005B9378*>(this)->rva005B942A(4,value);}
     break;
    case 1:
     disconnected=true;
     {UnicodeString title,message;AsciiString key;
      key.format("GUI:GSDisconReason%d",response.word10C);
      title=TheGameText->fetch("GUI:GSErrorTitle");
      message=TheGameText->fetch(key);
      Rva00548C1ACleanup();
      GSMessageBoxOk(title,message,0);
      TheShell->rva0035BEC7();TearDownGameSpy();
     }
     break;
   }
  }
 }
}
