// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 56A83B..56A983 is the 328-byte cdecl AudioMap/Sound/Multiplier
// field parser adjacent to LargeGroupAudioSoundKeyPair::update. WB1442780
// independently shows the same keyword arrays, INI calls and record defaults.
// No original parser name or direct BFME1/ZH counterpart was found. BFME1
// cee35b7d8 LargeGroupAudioMapParseSound and AudioEventInfo's volume-multiplier
// parser are protocol/lifetime guides only; the ABI and layout below are target
// facts. The native record has two owning narrow strings, float8, pointerC and
// flag10 (stride14). Its actual dtor is rowed Rva00568C4E; append consumes the
// existing BfmeStringRecord00568CE0 vector spelling. Defaults belong in the
// constructor: this keeps the float load ahead of the string zero stores.
// This TU calls <string.h>'s imported _strcmpi; the bookkeeping owner uses
// _CRTIMP= for allocation codegen, which conflicts with that import.
// No new pin, alias, global, header or compiler override.
#include <string.h>
#include "ascii_string.h"
#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/Common/INI/FieldParse.h"
struct BfmeStringRecord00568CE0;
namespace _STL { template<class T> class allocator {}; template<class T,class A=allocator<T> > class vector {public:void push_back(const T &);}; }
class Rva00568C4E {
public:
 AsciiString map,sound;
 float multiplier;
 void *subject;
 bool flag;
 Rva00568C4E():multiplier(1.0f),subject(0),flag(false){}
 ~Rva00568C4E();
};
void Rva0056A83BParseAudioMap(INI *ini,void *,void *store,const void *)
{
 Rva00568C4E entry;
 const char *token=ini->getNextToken(ini->m_sepsColon);
 char map[]="AudioMap";
 char sound[]="Sound";
 char multiplier[]="Multiplier";
 if(_strcmpi(token,map)!=0)throw INIException(8,"Expected %s:<name> next",map);
 entry.map=ini->getNextToken(ini->m_sepsColon);
 token=ini->getNextToken(ini->m_sepsColon);
 if(_strcmpi(token,sound)!=0)throw INIException(8,"Expected %s:<name> next",sound);
 entry.sound=ini->getNextToken(ini->m_sepsColon);
 token=ini->getNextToken(ini->m_sepsColon);
 if(_strcmpi(token,multiplier)!=0)throw INIException(8,"Expected %s:<volume percent> next",multiplier);
 entry.multiplier=ini->dup_002EE10(ini->getNextToken(ini->m_sepsColon));
 ((_STL::vector<BfmeStringRecord00568CE0> *)store)->push_back(*(BfmeStringRecord00568CE0 *)&entry);
}
