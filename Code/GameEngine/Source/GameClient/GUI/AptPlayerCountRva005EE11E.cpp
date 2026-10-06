// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// Target Ghidra [5EE11E,5EE250),306B; thiscall RET4.
// Native literals identify the consumed APT operation SetPlayerCount and
// PlayerIcon%d removal followed by clearing PlayerName/NumRegions/NumUnits.
// Native accesses establish level4; AsciiString8; icon collection18;
// 20B-record vector44; record word8 controls icon removal. Other fields
// and original application class identity remain unknown.
// Full providers:102B fire52519D;20B format38150;67B remove524306;
// 42B defaultresize5EE0F4;109B suffixsetter5ED516;133B release36410.
// These providers were independently verified before this recovery.
// The target retains the requested count across the APT call. It reloads
// the argument only after the icon-removal loop and reuses its stack slot
// for the growth index; explicit snapshots and guards preserve that order.
// STLport vector access is the clean source guide for the record array;
// layout and GUI semantics come from target instructions and literals.
// All calls and globals use real link providers; scoped ABI aliases below
// do not assert equivalence of original application type names.
#include "ascii_string.h"
#include "unicode_string.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void*,void*,const char*,const char*,int*);
struct Rva005EE11ERecord {UnicodeString text;unsigned word0,word1,word2,word3;};
class Rva005EE11ERecords {public:
 unsigned size()const{return finish-start;}
 Rva005EE11ERecord &operator[](unsigned i){return start[i];}
 void resize(unsigned);
private:Rva005EE11ERecord *start,*finish,*limit;
};
class Rva005EE11EIcons {public:void remove(const AsciiString&);private:void*words[3];};
class Rva005EE11EPlayerCount {public:
 void setPlayerCountRva005EE11E(int);
 void setText(int,const char*,const UnicodeString&);
private:
 unsigned word0;int level;AsciiString name;
 char pad0c[0xc];Rva005EE11EIcons icons;char pad24[0x20];
 Rva005EE11ERecords records;
};
void Rva005EE11EPlayerCount::setPlayerCountRva005EE11E(int count){
 int desired=count;
 if(desired==records.size())return;
 Rva0052519DFire(g_bfmeAptWindowManager,reinterpret_cast<void*>(level),name.str(),"SetPlayerCount",&count);
 int oldCount=records.size();
 if(desired<oldCount) {for(int i=desired;i<oldCount;++i){
  Rva005EE11ERecord &record=records[i];
  if(record.word1){
   AsciiString key;
   key.format("_level%u.%s_PlayerIcon%d",level,name.str(),i);
   icons.remove(key);
  }
 }
 desired=count;
 }
 records.resize(desired);
 if(oldCount<desired) {for(count=oldCount;count<desired;++count){
  setText(count,"PlayerName",UnicodeString::TheEmptyString);
  setText(count,"NumRegions",UnicodeString::TheEmptyString);
  setText(count,"NumUnits",UnicodeString::TheEmptyString);
 }
}
}

#pragma comment(linker, "/alternatename:?remove@Rva005EE11EIcons@@QAEXABVAsciiString@@@Z=?rva00524306@Rva00524306@@QAEXABV?$StringBase@D@@@Z")

#pragma comment(linker, "/alternatename:?setText@Rva005EE11EPlayerCount@@QAEXHPBDABVUnicodeString@@@Z=?rva005ED516@Rva005ED445@@QAEXHPBDABVUnicodeString@@@Z")

#pragma comment(linker, "/alternatename:?resize@Rva005EE11ERecords@@QAEXI@Z=?resize@Rva005EE06CVector@@QAEXI@Z")
