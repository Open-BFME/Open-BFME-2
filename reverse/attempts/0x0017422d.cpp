// ?fill@Rva0017422DVector@@QAEXPAUBfmeAssignRecord32@@IABU2@@Z
// partial score=0.94 date=2026-10-05
// cl: /O1 /G7 /EHsc /MD /DNDEBUG
struct BfmeAssignRecord32 {char opaque[32];BfmeAssignRecord32(const BfmeAssignRecord32&);~BfmeAssignRecord32();};
struct Rva0017422DTag {Rva0017422DTag(){}};
BfmeAssignRecord32* rva0017398CCopy(BfmeAssignRecord32*,BfmeAssignRecord32*,BfmeAssignRecord32*,const Rva0017422DTag&);
BfmeAssignRecord32* rva00173786Backward(BfmeAssignRecord32*,BfmeAssignRecord32*,BfmeAssignRecord32*,const Rva0017422DTag&);
void rva001737A3Fill(BfmeAssignRecord32*,BfmeAssignRecord32*,const BfmeAssignRecord32&);
BfmeAssignRecord32* rva001739B2Fill(BfmeAssignRecord32*,unsigned,const BfmeAssignRecord32&);
class Rva0017422DVector {public:void fill(BfmeAssignRecord32*,unsigned,const BfmeAssignRecord32&);
private:BfmeAssignRecord32*start;BfmeAssignRecord32*finish;BfmeAssignRecord32*limit;
void overflow(BfmeAssignRecord32*,const BfmeAssignRecord32&,const Rva0017422DTag&,unsigned,bool);};
void Rva0017422DVector::fill(BfmeAssignRecord32*position,unsigned count,const BfmeAssignRecord32&value) {
 if(count!=0) {
  if(unsigned(limit-finish)>=count) {
   BfmeAssignRecord32 copy=value;
   const unsigned after=finish-position;
   BfmeAssignRecord32*oldFinish=finish;
   if(after>count) {
    rva0017398CCopy(finish-count,finish,finish,Rva0017422DTag());
    finish+=count;
    rva00173786Backward(position,oldFinish-count,oldFinish,Rva0017422DTag());
    rva001737A3Fill(position,position+count,copy);
   } else {
    rva001739B2Fill(finish,count-after,copy);
    finish+=count-after;
    rva0017398CCopy(position,oldFinish,finish,Rva0017422DTag());
    finish+=after;
    rva001737A3Fill(position,oldFinish,copy);
   }
  } else overflow(position,value,Rva0017422DTag(),count,false);
 }
}
