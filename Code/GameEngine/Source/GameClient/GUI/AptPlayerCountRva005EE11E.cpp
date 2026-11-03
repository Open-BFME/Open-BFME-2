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
// All calls and globals use real link providers; the icon collection and
// record vector are spelled as their providers' ledger classes (Rva00524306,
// Rva005EE06CVector), which are placeholders, not original type names.
#include "ascii_string.h"
#include "unicode_string.h"
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0052519DFire(void*,void*,const char*,const char*,int*);
struct Rva005EE11ERecord {UnicodeString text;unsigned word0,word1,word2,word3;};
class Rva005EE06CVector {public:
 unsigned size()const{return finish-start;}
 Rva005EE11ERecord &operator[](unsigned i){return start[i];}
 void resize(unsigned);
private:Rva005EE11ERecord *start,*finish,*limit;
};
class Rva00524306 {public:void rva00524306(const StringBase<char>&);private:void*words[3];};
#include "../../../Include/GameClient/RegionAwardMovieClip.h"
namespace StrategicHUD {
}

class StrategicHUD::RegionAwardMovieClip::Impl
{public:
 void SetPlayerCount(int);
 void SetPlayerString(int,const char*,const UnicodeString&);
private:
 unsigned word0;int level;AsciiString name;
 char pad0c[0xc];Rva00524306 icons;char pad24[0x20];
 Rva005EE06CVector records;
};
void StrategicHUD::RegionAwardMovieClip::Impl::SetPlayerCount(int count){
 int desired=count;
 if(desired==records.size())return;
 Rva0052519DFire(g_bfmeAptWindowManager,reinterpret_cast<void*>(level),name.str(),"SetPlayerCount",&count);
 int oldCount=records.size();
 if(desired<oldCount) {for(int i=desired;i<oldCount;++i){
  Rva005EE11ERecord &record=records[i];
  if(record.word1){
   AsciiString key;
   key.format("_level%u.%s_PlayerIcon%d",level,name.str(),i);
   icons.rva00524306(*(const StringBase<char> *)&key);
  }
 }
 desired=count;
 }
 records.resize(desired);
 if(oldCount<desired) {for(count=oldCount;count<desired;++count){
  SetPlayerString(count,"PlayerName",UnicodeString::TheEmptyString);
  SetPlayerString(count,"NumRegions",UnicodeString::TheEmptyString);
  SetPlayerString(count,"NumUnits",UnicodeString::TheEmptyString);
 }
}
}
