// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail416589..4166DB RET: displays a by-value buddy message in chat and,
// if the Messenger is closed, emits its eleven-character notification.
// ZH insertChat/WOLBuddyOverlay provides the chat and notification semantics;
// WB1336E10 is the same helper beside HandleBuddyResponses in BuddyDefs.cpp.
// Native member accesses establish the24B BuddyMessage. The already-owned
// BfmeStringRecord00415F34 copy is its ABI view (application class unreconciled).
// GameSpyColor is established at DB9198 by existing addChat; nativeDB91B8
// is its eighth colour (the ZH GSCOLOR_PLAYER_BUDDY index).
#include "ascii_string.h"
#include "unicode_string.h"
class BuddyMessage {public:unsigned timestamp;int sender;AsciiString senderNick;int recipient;AsciiString recipientNick;UnicodeString message;~BuddyMessage();};
// Composition keeps the known record copy ABI and the actual cleanup call.
struct BfmeStringRecord00415F34 {BuddyMessage message;BfmeStringRecord00415F34(const BfmeStringRecord00415F34 &);};
class GameTextInterface {public:
#define V(n) virtual void slot##n();
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)
#undef V
virtual const UnicodeString *fetchFormat(const char *,bool *exists=0);
};
extern GameTextInterface *TheGameText;
extern unsigned char g_Va00A0308C;
extern int g_Va00A03090;
void Rva004163E1Notify(AsciiString,UnicodeString);
extern int g_00DB9198;
extern int g_Va00E046B8;
void Rva00381C82AddChatText(int,const UnicodeString &,int);
// Native helper is the target-specific equivalent of ZH insertChat.
void Rva00416589(BfmeStringRecord00415F34 record)
{
 BuddyMessage &message=record.message;
 UnicodeString text;text.format(L"[%hs] %s",message.senderNick.str(),message.message.str());
 Rva00381C82AddChatText(0,text,(&g_00DB9198)[8]);
 if(!g_Va00E046B8){
  UnicodeString snippet=message.message;
  while(snippet.getLength()>11)snippet.removeLastChar();
  UnicodeString notification;
  notification.format(TheGameText->fetchFormat("Buddy:MessageNotification"),message.senderNick.str(),snippet.str());
  g_Va00A0308C=false;g_Va00A03090=0;
  Rva004163E1Notify(AsciiString::TheEmptyString,notification);
 }
}
