// ?Rva0040A46FFind@@YAPAPAVCreateAHeroData@@PAPAV1@0VAsciiString@@@Z
// partial score=0.9191437142 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
#include "ascii_string.h"
class CreateAHeroData;
class Rva0040A424 {
 void *text;
public: bool rva0040A424(CreateAHeroData*);
 __forceinline bool operator()(CreateAHeroData*p){return rva0040A424(p);}
};
CreateAHeroData** Rva0040A46FFind(CreateAHeroData** first,CreateAHeroData** last,AsciiString pred) {
 int trip=(last-first)>>2;
 for(;trip>0;--trip) {
  if(reinterpret_cast<Rva0040A424*>(&pred)->rva0040A424(*first))return first;
  ++first;
  if(reinterpret_cast<Rva0040A424*>(&pred)->rva0040A424(*first))return first;
  ++first;
  if(reinterpret_cast<Rva0040A424*>(&pred)->rva0040A424(*first))return first;
  ++first;
  if(reinterpret_cast<Rva0040A424*>(&pred)->rva0040A424(*first))return first;
  ++first;
 }
 switch(last-first) {
 case 3: if(reinterpret_cast<Rva0040A424*>(&pred)->rva0040A424(*first))return first; ++first;
 case 2: if(reinterpret_cast<Rva0040A424*>(&pred)->rva0040A424(*first))return first; ++first;
 case 1: if(reinterpret_cast<Rva0040A424*>(&pred)->rva0040A424(*first))return first;
 default: return last;
 }
}
