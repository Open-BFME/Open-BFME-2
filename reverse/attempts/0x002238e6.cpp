// ?rva002238E6@Rva00224CDC@@QAEXVAsciiString@@@Z
// partial score=0.9671041776044401 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"
#include "unicode_string.h"
struct Rva002226E5TextPlusString {Rva002226E5TextPlusString(){} const char*text;int length;const AsciiString*string;operator AsciiString();};
Rva002226E5TextPlusString operator+(const char*,const AsciiString&);
class Rva00056F61 {public:void*rva00056F61(const AsciiString*);char data[20];};
struct RGBColor;
class Mouse {public:void rva001EEA6D(UnicodeString,int,const RGBColor*,float);};
extern Mouse*TheMouse;
class GameText {public:
virtual void gap0();
virtual void gap1();
virtual void gap2();
virtual void gap3();
virtual void gap4();
virtual void gap5();
virtual void gap6();
virtual void gap7();
virtual void gap8();
virtual void gap9();
virtual void gap10();
virtual void gap11();
virtual void gap12();
virtual void gap13();
virtual UnicodeString fetch(const AsciiString&,bool*);
};
extern GameText*TheGameText;
class Rva00224CDC {public:void rva002238E6(AsciiString);char pad[0xc];Rva00056F61 map;};
void Rva00224CDC::rva002238E6(AsciiString name){
 Rva00056F61 *table=&map;
 void*node=table->rva00056F61(&name);
 if(node)name=*(AsciiString*)((char*)node+8);
 bool found=false;
 UnicodeString text=TheGameText->fetch("TOOLTIP:"+name,&found);
 if(found)TheMouse->rva001EEA6D(text,-1,0,1.0f);
}
