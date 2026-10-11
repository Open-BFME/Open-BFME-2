// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I. /Ireference/shims/bfme2_ascii
// Rva0038169D, retail 0x0038169D (494 bytes): LAN chat submission.
// Native38169D..38188B: channel and UnicodeString reference ABI; menu preferences at684; filtered whitespace and slash-command path; LAN virtual slot54 ordinary message request.
// Honest address-derived identity; no recovered retail method name claimed.
extern int g_Va00A03354;
class LANAPI;extern LANAPI *TheLAN;
#include "unicode_string.h"
extern "C" __declspec(dllimport) int __cdecl iswspace(unsigned short);
class LanguageFilter {public:void filterLine(UnicodeString&);};extern LanguageFilter*TheLanguageFilter;
class GameModePreferences {public:UnicodeString rva0044D330();};
struct ChatMenuPreferenceView {char pad[0x684];GameModePreferences preferences;};
template<int N>class ChatLANSlots:public ChatLANSlots<N-1>{public:virtual void pad(char(*)[N]);};
template<>class ChatLANSlots<1>{public:virtual void pad(char(*)[1]);};
class ChatLANCalls:public ChatLANSlots<21>{public:virtual void request(UnicodeString,int,int);};
static __forceinline bool chatEmpty(const UnicodeString&s){const char*p=*(const char*const*)&s;return !p||*(const unsigned short*)(p+4)==0;}
static __forceinline unsigned short chatFirst(const UnicodeString&s){const char*p=*(const char*const*)&s;return p?*(const unsigned short*)(p+8):0;}
bool Rva0038169D(int channel,const UnicodeString&input) {
 ChatMenuPreferenceView*menu=(ChatMenuPreferenceView*)g_Va00A03354;
 GameModePreferences*prefs=menu?&menu->preferences:0;
 if(!prefs)return false;
 UnicodeString text(input);TheLanguageFilter->filterLine(text);
 bool handled=false;
 if(!chatEmpty(text)) {
  {
  UnicodeString message;
  while(!chatEmpty(text)&&iswspace(chatFirst(text)))text=UnicodeString(text.str()+1);
  if(!chatEmpty(text)) {
   message=text;
   if(chatFirst(message)=='/') {
    UnicodeString remainder(message.str()+1),token;
    ((StringBase<unsigned short>*)&remainder)->nextToken((StringBase<unsigned short>*)&token,0);
    if(!((StringBase<unsigned short>*)&token)->compareNoCase((const unsigned short*)L"me")&&text.getLength()>=3) {
     message=prefs->rva0044D330();
     message.concat(remainder.str());
    }
   }else ((ChatLANCalls*)TheLAN)->request(message,channel==0,0);
  }
  // Retail's unwind map (FuncInfo 0x00929A88) ends with four action-less
  // states under the message scope: 6 and 8 (parent 1) each with a temporary
  // child (7, 9), code the compiler discarded but whose locals kept their EH
  // states, as in CreateAHeroSubClassParse.cpp's compiled-out blocks. Two
  // locals each reassigned from a temporary is the shape that reproduces that
  // tree (four plain locals do not); what the code did is not recoverable.
  if(0){
   UnicodeString first(text);
   first=UnicodeString(text.str()+1);
   UnicodeString second(text);
   second=UnicodeString(text.str()+1);
  }

  }
  handled=true;
 }
 return handled;
}
