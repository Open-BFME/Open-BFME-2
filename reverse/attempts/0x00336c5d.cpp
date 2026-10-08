// ?rva002E9680ParseModelConditionEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// partial score=0.9966386555 date=2026-10-08
// stlport
// cl: /O1 /EHsc /MD /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// BF1 9cbfb551 LuaScriptEngineParseModelConditionEvent.cpp semantic source.
#include "ascii_string.h"
#include <vector>
#include <string.h>
class BfmeLexEAN {public: char *getTailEAN();};
class XmlNameSlotList {public:int count();int finish();const char *tagAt(int);const char *nameAt(int);};
class INIException {public:char *mFailureMessage;};
struct ConditionWords {unsigned long words[19];
 ConditionWords(){memset(words,0,sizeof(words));}
 void flip(){for(unsigned i=0;i<19;++i)words[i]=~words[i];}
};
class Rva000B664E {public:void rva0033394D(AsciiString);};
class WeaponTemplateSetHead {public:char bytes[76];};
class Rva00332F5B {public:
 Rva00332F5B(const WeaponTemplateSetHead &,const WeaponTemplateSetHead &);
 int rva00332F81(const Rva00332F5B &)const;
 unsigned char bytes[156];
};
struct EventFlagEntry {void setKeyFromName(const char *);};
struct Rva00336AB2Element {unsigned char bytes[156];};
extern template void _STL::vector<Rva00336AB2Element>::push_back(const Rva00336AB2Element &);
class LuaScriptEngine {public:void rva002E9680ParseModelConditionEvent(BfmeLexEAN *);
 private:char pad[0xBC];_STL::vector<Rva00336AB2Element> m_modelConditionEvents;
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
void LuaScriptEngine::rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser)
{
 AsciiString name;
 for(int i=0;i<reinterpret_cast<XmlNameSlotList *>(parser)->count();++i) {
  if(strcmp(reinterpret_cast<XmlNameSlotList *>(parser)->tagAt(i),"Name")==0)
   reinterpret_cast<StringBase<char> *>(&name)->set(reinterpret_cast<XmlNameSlotList *>(parser)->nameAt(i));
 }
 if(reinterpret_cast<XmlNameSlotList *>(parser)->finish()!=1)return;
 bool isConditions=strcmp(parser->getTailEAN(),"Conditions")==0;
 if(!isConditions)return;
 if(reinterpret_cast<XmlNameSlotList *>(parser)->finish()!=3)return;
 const char *text=parser->getTailEAN();
 try {
  AsciiString conditions(text);
  ConditionWords required,excluded;
  excluded.flip();
  reinterpret_cast<Rva000B664E *>(&required)->rva0033394D(conditions);
  reinterpret_cast<Rva000B664E *>(&excluded)->rva0033394D(conditions);
  excluded.flip();
  bool found=false;
  Rva00332F5B record(*reinterpret_cast<WeaponTemplateSetHead *>(&required),*reinterpret_cast<WeaponTemplateSetHead *>(&excluded));
  reinterpret_cast<EventFlagEntry *>(&record)->setKeyFromName(name.str());

  for(Rva00336AB2Element *it=m_modelConditionEvents.begin();it!=m_modelConditionEvents.end();++it) {
   if((record.rva00332F81(*reinterpret_cast<Rva00332F5B *>(it)) & 0xff)!=0) {found=true;break;}
  }
  if(!found)m_modelConditionEvents.push_back(*reinterpret_cast<Rva00336AB2Element *>(&record));
  else return;
 } catch(INIException &e) {
  if(_bfme_debugReportingEnabled()) {
   _bfme_debugRecordCallsite(1);
   reinterpret_cast<LuaParseDebug *>(theDebug)->v24();
   LuaParseLog *log=reinterpret_cast<LuaParseDebug *>(theDebug)->line(0,0,0)->write("Error during parsing XML data: "); const char *message=e.mFailureMessage; log->write(message)->end(2);
  }
 } catch(...) {}
 if(reinterpret_cast<XmlNameSlotList *>(parser)->finish()==2)reinterpret_cast<XmlNameSlotList *>(parser)->finish();
}
