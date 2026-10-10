// ?iniParsePredefinedEvaEvent@Eva@@SAXPAVINI@@@Z
// partial score=0.851851851851852 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/iniexception
#include "Common/INIException.h"
class AsciiString;
template<class T> class StringBase {friend class AsciiString;private:StringBase(const T*);void releaseBuffer();char *data;};
class AsciiString {public:AsciiString(const char*t){((StringBase<char>*)this)->StringBase<char>::StringBase(t);}~AsciiString(){((StringBase<char>*)this)->releaseBuffer();}const char*str()const{return data?data+8:"";}char*data;};
class Rva00056F61 {public:void*rva00056F61(const AsciiString*);char bytes[20];};
class Rva001DE727 {public:Rva001DE727&operator=(const Rva001DE727&);char bytes[48];};
class INI {public:const char*getNextToken(const char*);char pad[8];int loadType;};
class Eva {public:static void iniParsePredefinedEvaEvent(INI*);void rva001DCFC9(INI*,void*);char pad[0x1c];Rva001DE727 *infos,*infosFinish,*infosStorage;Rva001DE727 *originalInfos,*originalFinish,*originalStorage;char pad34[20];Rva00056F61 predefined;};
extern Eva *TheEva;
void Eva::iniParsePredefinedEvaEvent(INI*ini)
{
 AsciiString name(ini->getNextToken(0));
 Rva00056F61 *table=&TheEva->predefined;
 void*node=table->rva00056F61(&name);
 if(!node)throw INIException(3,"'%s' is not a predefined Eva event name",name.str());
 int id=*(int*)((char*)node+8);
 if(id<0||id>=22)throw INIException(3,"'%s' is not a predefined Eva event name",name.str());
 Rva001DE727 *base;
 if(ini->loadType==2){
  if(id==0)throw INIException(3,"You cannot redefine the default Eva event in a map.ini");
  base=TheEva->infos;
 }else base=TheEva->originalInfos;
 Rva001DE727 *record=&base[id];
 if(id!=0)*record=TheEva->originalInfos[0];
 TheEva->rva001DCFC9(ini,record);
}
