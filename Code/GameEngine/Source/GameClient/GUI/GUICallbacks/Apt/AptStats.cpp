// cl: /O1 /G7 /EHsc /MD /DNDEBUG /arch:SSE /Ireference/shims/bfme2_ascii
// stlport
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" unsigned char*__cdecl _mbscpy(unsigned char*,const unsigned char*);
// WB15D9470 names AptStats::ColorExtern (AptStats.cpp251). The native
// faction initializer5DD2D3 takes this callback address and the same
// six color strings; stack arguments are faction, output and bool, RET12.
// Ghidra omitted the entry: the preceding verified5B destructor ends at
//5DCFCE and this callback ends at5DD029 after its own RET12, whole91B.
// Retail calls the actual _mbscpy import thunk629176, not a guessed strcpy
// pin sharing its address. All selected literals are checked at their refs.
// Persistent's native20B table base and trailing word14 are established
// by complete retail and the verified781B Persistent constructor. The derived native ctor proves
// owner18, word1C and a12B index-vector20; individual template flags stay neutral.
class Rva005DE9E3 {public: virtual ~Rva005DE9E3(); protected: unsigned words[4];};
class GameStats {public: class Persistent:public Rva005DE9E3 {public: Persistent(int); private:int m_14;};};
class PlayerTemplate {public: unsigned char prefix[0x150]; bool flag150,flag151; unsigned char suffix[0x1dc-0x152];};
class PlayerTemplateStore {public:
 const PlayerTemplate*getNthPlayerTemplate(int)const;
 unsigned char prefix[12];PlayerTemplate*first;PlayerTemplate*finish;PlayerTemplate*limit;
};
extern PlayerTemplateStore*ThePlayerTemplateStore;
// ScienceType is the existing 49B four-byte append-provider ABI spelling.
// Native template indices do not establish science semantics or an int-template fold.
enum ScienceType { SCIENCE_STORAGE_ZERO=0 };
class AptStats : public GameStats::Persistent {
public:
 AptStats(void*host);
 virtual ~AptStats();
 virtual void*rankValues();virtual int rankPoints(int);
 void ColorExtern(int,char*,bool);
 void NextRankExtern(int,char*,bool);
 void InitializeFactionVariables();
 void*owner;
 int m_word1c;
 std::vector<ScienceType> m_factionToTemplate;
};
typedef char Persistent24[(sizeof(GameStats::Persistent)==24)?1:-1];
typedef char AptStats44[(sizeof(AptStats)==44)?1:-1];
typedef char PlayerTemplate476[(sizeof(PlayerTemplate)==476)?1:-1];
void AptStats::ColorExtern(int faction,char*out,bool lvalue) {
 if(lvalue)return;
 const char*color="0xFFFFFFFF";
 switch(faction) {
 case 0:color="0x0E75D6";break;
 case 1:color="0x12AC7F";break;
 case 2:color="0xC0B60A";break;
 case 3:color="0x646464";break;
 case 4:color="0xD00303";break;
 case 5:color="0xF5772A";break;
 }
 _mbscpy(reinterpret_cast<unsigned char*>(out),reinterpret_cast<const unsigned char*>(color));
}

// Named WB15D8A50 and complete native5DD609..5DD6B6 RET4. Native
// and WB agree on the7-column Persistent base, template selection and
// the parameterless faction initializer; WB assert62 names the index-vector.
AptStats::AptStats(void*host):GameStats::Persistent(7),owner(host),m_word1c(0)
{
 int count=ThePlayerTemplateStore->finish-ThePlayerTemplateStore->first;
 for(ScienceType index=static_cast<ScienceType>(0);index<count;index=static_cast<ScienceType>(index+1)) {
  const PlayerTemplate*pt=ThePlayerTemplateStore->getNthPlayerTemplate(index);
  if(pt->flag151 && !pt->flag150)
   m_factionToTemplate.push_back(index);
 }
 InitializeFactionVariables();
}

// WB015D9570 AptStats.cpp295 names this callback; native full68B
// [005DD029,005DD06D),RET12. Its address is taken by the faction-level
// registration at005DD2D3. Target virtual slots1/2 supply thresholds/points.
// The rank-progress dependency has independently proven entry and thiscall ABI.
class Rva00559AC1 {public:float rva00559AF9(int);};
extern "C" __declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
void AptStats::NextRankExtern(int faction,char*out,bool lvalue)
{
 if(lvalue)return;
 int points=rankPoints(faction);
 float progress=((Rva00559AC1*)rankValues())->rva00559AF9(points)*100.0f;
 sprintf(out,"%d",int(progress));
}
