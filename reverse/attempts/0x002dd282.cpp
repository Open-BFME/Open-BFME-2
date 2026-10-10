// ?rva002DD282@GameState@@QAE?AVUnicodeString@@H@Z
// partial score=0.8039557307747115 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "unicode_string.h"
#include "ascii_string.h"
void *__stdcall Rva002DBC97Get(int);
class Rva000B3F84Pair {public:Rva000B3F84Pair(){} Rva000B3F84Pair *initWide(const unsigned short *);const char *m_ptr;int m_len;};
struct Rva002DBD80Val {Rva002DBD80Val(){}int m_00;Rva000B3F84Pair m_pair;};
Rva002DBD80Val Rva002DBD80Make(int,const unsigned short *);
struct AsciiStringPlusText {const AsciiString *left;Rva000B3F84Pair right;operator StringBase<unsigned short>();};
class Rva002DCCFB {public:bool rva002DCCFB(UnicodeString);};
class GameTextInterface {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual UnicodeString fetch(const char *,bool *);};
extern GameTextInterface *TheGameText;
class GameState {public:UnicodeString rva002DD282(int);};
UnicodeString GameState::rva002DD282(int mode) {
 const unsigned short *suffix=(const unsigned short *)Rva002DBC97Get(mode);
 UnicodeString formatText((const unsigned short *)L"%d");
 if(TheGameText)formatText=TheGameText->fetch("GUI:DefaultSaveFileName",0);
 for(int i=1;i<99999999;++i) {
  UnicodeString leaf;
  leaf.format(&formatText,i);
  typedef UnicodeString (AsciiStringPlusText::*WideResult)();
  WideResult materialize=reinterpret_cast<WideResult>(&AsciiStringPlusText::operator StringBase<unsigned short>);
  if(!reinterpret_cast<Rva002DCCFB *>(this)->rva002DCCFB((reinterpret_cast<AsciiStringPlusText &>(Rva002DBD80Make((int)&leaf,suffix)).*materialize)()))return leaf;
 }
 return UnicodeString((const unsigned short *)L"0");
}
