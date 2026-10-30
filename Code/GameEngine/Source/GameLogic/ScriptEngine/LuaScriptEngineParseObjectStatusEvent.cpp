// stlport
// cl: /O1 /EHsc /MD /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// ?rva002E9AA0ParseObjectStatusEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z @0x00336EB0 482B.
//
// LuaScriptEngine::ProcessObjectStatusEvent (WorldBuilder 0x00C00CD0, LuaScriptEngine.cpp 1089..1133):
// reads an object-status event element (its Name attribute and Conditions text), builds the
// required/excluded condition record and appends it unless an equal record is already listed.
// Statement shape as the twin: each parser->finish() lands in the named local `item` before its
// test, and found=false follows setKeyFromName. That gives retail's allocation: the zero constant in
// EBX up to the name.str() null test, i in ESI, the parser in EDI, `this` spilled, found later in BL.
// BF1 9cbfb551 LuaScriptEngineParseModelConditionEvent.cpp semantic source.
#include "ascii_string.h"
#include <vector>
#include <string.h>
class BfmeLexEAN
{
public:
	char *getTailEAN();
	BfmeLexEAN(char *text, char *buffer, int limit);
	~BfmeLexEAN();
	char *m_bfmePosEAN; // +0x00
	char *m_bfmeLineEAN; // +0x04
	char *m_bfmeSourceEAN; // +0x08
	int m_bfmeLineNumberEAN; // +0x0C
	int m_bfmeTagEAN; // +0x10
	char *m_bfmeBufEAN; // +0x14
	int m_bfmeLimitEAN; // +0x18
	char *m_tail; // +0x1C
	int m_bfmeDepthEAN; // +0x20
	unsigned char m_bfmeSeenEAN; // +0x24
	char m_pad25[0x3];
	int m_bfmeMarkEAN; // +0x28
	int m_bfmeStackEAN[0x61]; // +0x2C
};
class XmlNameSlotList
{
public:
	int count();
	int finish();
	const char *tagAt(int);
	const char *nameAt(int);
};
class INIException {public:char *mFailureMessage;};
struct ConditionWords {unsigned long words[4];
 ConditionWords(){memset(words,0,sizeof(words));}
 void flip(){for(unsigned i=0;i<4;++i)words[i]=~words[i];}
};
class Rva003339CE {public:void rva00334506(AsciiString);};
class BfmeObject872Header {public:char bytes[16];};
class Rva00332FC1 {public:
 Rva00332FC1(const BfmeObject872Header &,const BfmeObject872Header &);
 __declspec(nothrow) bool rva00332FE7(const Rva00332FC1 &)const;
 void *m_text;
 BfmeObject872Header m_a;
 BfmeObject872Header m_b;
};
// Both rowed predicates return equality without throwing. Keep that contract
// visible here, with their definitions supplied by the existing owner units.
__declspec(nothrow) bool Rva002634E0Equal(const void *a,const void *b);
struct EventFlagEntry {void setKeyFromName(const char *);};
struct Rva00336AECElement {unsigned char bytes[36];};
extern template void _STL::vector<Rva00336AECElement>::push_back(const Rva00336AECElement &);
class LuaScriptEngine {public:void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *);
 private:char pad[0xC8];_STL::vector<Rva00336AECElement> m_objectStatusEvents;
};
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int);
class LuaParseLog {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual LuaParseLog *write(const char *);
 virtual void v15();virtual void v16();virtual void v17();virtual void v18();
 virtual LuaParseLog *end(int);
};
class LuaParseDebug {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual void v14();virtual void v15();
 virtual void v16();virtual void v17();virtual void v18();virtual void v19();
 virtual void v20();virtual void v21();virtual void v22();virtual void v23();
 virtual void v24();virtual void v25();virtual void v26();
 virtual LuaParseLog *line(int,int,int);
};
class Debug;
extern Debug *theDebug;
void LuaScriptEngine::rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser)
{
 AsciiString name;
 for(int i=0;i<reinterpret_cast<XmlNameSlotList *>(parser)->count();++i) {
  if(strcmp(reinterpret_cast<XmlNameSlotList *>(parser)->tagAt(i),"Name")==0)
   reinterpret_cast<StringBase<char> *>(&name)->set(reinterpret_cast<XmlNameSlotList *>(parser)->nameAt(i));
 }
 int item=reinterpret_cast<XmlNameSlotList *>(parser)->finish();
 if(item!=1)return;
 bool isConditions=strcmp(parser->getTailEAN(),"Conditions")==0;
 if(!isConditions)return;
 item=reinterpret_cast<XmlNameSlotList *>(parser)->finish();
 if(item!=3)return;
 const char *text=parser->getTailEAN();
 try {
  AsciiString conditions(text);
  ConditionWords required,excluded;
  excluded.flip();
  reinterpret_cast<Rva003339CE *>(&required)->rva00334506(conditions);
  reinterpret_cast<Rva003339CE *>(&excluded)->rva00334506(conditions);
  excluded.flip();
  Rva00332FC1 record(*reinterpret_cast<BfmeObject872Header *>(&required),*reinterpret_cast<BfmeObject872Header *>(&excluded));
  reinterpret_cast<EventFlagEntry *>(&record)->setKeyFromName(name.str());
  bool found=false;

  for(Rva00336AECElement *it=m_objectStatusEvents.begin();it!=m_objectStatusEvents.end();++it) {
   if(record.rva00332FE7(*reinterpret_cast<Rva00332FC1 *>(it))) {found=true;break;}
  }
  if(!found)m_objectStatusEvents.push_back(*reinterpret_cast<Rva00336AECElement *>(&record));
  else return;
 } catch(...) {}
 if(reinterpret_cast<XmlNameSlotList *>(parser)->finish()==2)reinterpret_cast<XmlNameSlotList *>(parser)->finish();
}
