// cl: /O1 /G7 /MD /EHsc /arch:SSE /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Native4CC371..4CC582,529B; WB1274440 parser body proves grammar.
// Reference0bef Rva000BD640ParseSoundEventList supplies owning audio lookup
// and INIException lifecycle only. No original target parser name asserted.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *,const char *);
#include <vector>
#include "ascii_string.h"
class OpaqueRefCounted {public:void Release_Ref();};
struct OpaqueRefElement4 {OpaqueRefCounted *referent;OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);~OpaqueRefElement4(){if(referent)referent->Release_Ref();}};
template<int N>class BitFlags {public:bool setBitByName(const char *);unsigned int words[(N+31)/32];};
// Constructor4CBEB0 proves two76B subobjects at4 and50; only the named
// bit-operation prefix uses the existing folded BitFlags304 provider.
class Rva0042526Member {public:Rva0042526Member();char bytes[0x4c];};
class Rva004CBEB0 {public:Rva004CBEB0();OpaqueRefElement4 sound;Rva0042526Member required,excluded;};
typedef char ConfirmRecord156[(sizeof(Rva004CBEB0)==156)?1:-1];
// The owned STL specialization takes a156B object without observing fields.
struct BfmeStringTailRecord156 {char bytes[156];};
typedef _STL::vector<BfmeStringTailRecord156> SoundVector;
namespace _STL {template<> __declspec(noinline) void SoundVector::push_back(const BfmeStringTailRecord156 &);}
class INIException {public:INIException(int,const char *,...);INIException(const INIException &);~INIException();int code;const char *message;};
class INI {public:const char *getNextTokenOrNull(const char *);const char *getNextToken(const char *);char pad[0x420];const char *separators;};
class AudioManager {public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 virtual void v57();
 virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual void v66();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void v70();
 virtual void v71();
 virtual void v72();
 virtual void v73();
 virtual void v74();
 virtual OpaqueRefElement4 findSound(const AsciiString &);
};
extern AudioManager *TheAudio;
void Rva004CC371Parse(INI *ini,void *,void *store,const void *)
{
 char required[]="Required";
 char excluded[]="Excluded";
 char sound[]="Sound";
 Rva004CBEB0 entry;
 const char *token=ini->getNextTokenOrNull(ini->separators);
 while(token){
  if(!_strcmpi(token,required)){
   token=ini->getNextTokenOrNull(ini->separators);
   while(token && ((BitFlags<304> *)&entry.required)->setBitByName(token))token=ini->getNextTokenOrNull(ini->separators);
  }else if(!_strcmpi(token,excluded)){
   token=ini->getNextTokenOrNull(ini->separators);
   while(token && ((BitFlags<304> *)&entry.excluded)->setBitByName(token))token=ini->getNextTokenOrNull(ini->separators);
  }else if(!_strcmpi(token,sound)){
   token=ini->getNextToken(ini->separators);
   if(_strcmpi(token,"NoSound")){
    entry.sound=TheAudio->findSound(AsciiString(token));
    if(!entry.sound.referent)throw INIException(3,"Unknown sound %s",token);
    token=ini->getNextTokenOrNull(ini->separators);
   }
  }else throw INIException(5,"Expected one of %s, %s, or %s next",required,excluded,sound);
 }
 ((SoundVector *)store)->push_back(*(const BfmeStringTailRecord156 *)&entry);
}
