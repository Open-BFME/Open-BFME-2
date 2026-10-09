// cl: /O1 /G7 /EHsc /MD /DNDEBUG /arch:SSE /Ireference/shims/bfme2_ascii
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
class AptStats {
public:
 virtual ~AptStats();
 virtual void*rankValues();virtual int rankPoints(int);
 void ColorExtern(int,char*,bool);
 void NextRankExtern(int,char*,bool);
 char beforeOwner[0x14];void*owner;
};
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
